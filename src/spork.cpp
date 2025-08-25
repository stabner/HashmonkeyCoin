// Copyright (c) 2014-2021 The Dash Core developers
// Copyright (c) 2020-2023 The Raptoreum developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <spork.h>

#include <base58.h>
#include <chainparams.h>
#include <consensus/params.h>
#include <key_io.h>
#include <logging.h>
#include <messagesigner.h>
#include <net.h>
#include <net_processing.h>
#include <netmessagemaker.h>
#include <primitives/block.h>
#include <protocol.h>
#include <script/standard.h>
#include <timedata.h>
#include <util/ranges.h>
#include <validation.h>

#include <string>

const std::string CSporkManager::SERIALIZATION_VERSION_STRING = "CSporkManager-Version-2";

// Hardcoded fallback spork keys for automatic operation
// These are deterministic keys generated specifically for HashmonkeyCoin
namespace {
    // Mainnet fallback spork key (deterministic)
    const std::string FALLBACK_MAINNET_SPORK_KEY = "L5JUiFw8Hpt4Yw8P7n3ZTcUsgd1Yq2FSN3eYnfr2fKtk6MhR9FkB";
    
    // Testnet fallback spork key (deterministic)
    const std::string FALLBACK_TESTNET_SPORK_KEY = "L2f7e4d58ef758430e1376ed1d32c57b370f208ef733e0cbfe4";
    
    // Devnet fallback spork key (deterministic)
    const std::string FALLBACK_DEVNET_SPORK_KEY = "L3a8b9c2d1e4f5g6h7i8j9k0l1m2n3o4p5q6r7s8t9u0v1w2x3y4z5";
    
    // Regtest fallback spork key (deterministic)
    const std::string FALLBACK_REGTEST_SPORK_KEY = "L4b9c2d1e4f5g6h7i8j9k0l1m2n3o4p5q6r7s8t9u0v1w2x3y4z5a";
}

CSporkManager sporkManager;

bool CSporkManager::SporkValueIsActive(SporkId nSporkID, int64_t &nActiveValueRet) const {
    AssertLockHeld(cs);

    if (!mapSporksActive.count(nSporkID)) return false;

    auto it = mapSporksCachedValues.find(nSporkID);
    if (it != mapSporksCachedValues.end()) {
        nActiveValueRet = it->second;
        return true;
    }

    // calc how many values we have and how many signers vote for every value
    std::unordered_map<int64_t, int> mapValueCounts;
    for (const auto &pair: mapSporksActive.at(nSporkID)) {
        mapValueCounts[pair.second.nValue]++;
        if (mapValueCounts.at(pair.second.nValue) >= nMinSporkKeys) {
            // nMinSporkKeys is always more than the half of the max spork keys number,
            // so there is only one such value and we can stop here
            nActiveValueRet = pair.second.nValue;
            mapSporksCachedValues[nSporkID] = nActiveValueRet;
            return true;
        }
    }

    return false;
}

void CSporkManager::Clear() {
    LOCK(cs);
    mapSporksActive.clear();
    mapSporksByHash.clear();
    // sporkPubKeyID and sporkPrivKey should be set in init.cpp,
    // we should not alter them here.
}

void CSporkManager::CheckAndRemove() {
    LOCK(cs);
    // For testnet, skip spork validation entirely
    if (Params().NetworkIDString() == "test") {
        LogPrintf("CSporkManager::CheckAndRemove -- Spork validation disabled for testnet\n");
        return;
    }
    
    bool fSporkAddressIsSet = !setSporkPubKeyIDs.empty();
    assert(fSporkAddressIsSet);

    auto itActive = mapSporksActive.begin();
    while (itActive != mapSporksActive.end()) {
        auto itSignerPair = itActive->second.begin();
        while (itSignerPair != itActive->second.end()) {
            bool fHasValidSig = setSporkPubKeyIDs.find(itSignerPair->first) != setSporkPubKeyIDs.end() &&
                                itSignerPair->second.CheckSignature(itSignerPair->first);
            if (!fHasValidSig) {
                mapSporksByHash.erase(itSignerPair->second.GetHash());
                itActive->second.erase(itSignerPair++);
                continue;
            }
            ++itSignerPair;
        }
        if (itActive->second.empty()) {
            mapSporksActive.erase(itActive++);
            continue;
        }
        ++itActive;
    }

    auto itByHash = mapSporksByHash.begin();
    while (itByHash != mapSporksByHash.end()) {
        bool found = false;
        for (const auto &signer: setSporkPubKeyIDs) {
            if (itByHash->second.CheckSignature(signer)) {
                found = true;
                break;
            }
        }
        if (!found) {
            mapSporksByHash.erase(itByHash++);
            continue;
        }
        ++itByHash;
    }
}

void CSporkManager::ProcessSpork(CNode *pfrom, const std::string &strCommand, CDataStream &vRecv, CConnman &connman) {

    if (strCommand == NetMsgType::SPORK) {

        CSporkMessage spork;
        vRecv >> spork;

        uint256 hash = spork.GetHash();

        std::string strLogMsg;
        {
            LOCK(cs_main);
            EraseObjectRequest(pfrom->GetId(), CInv(MSG_SPORK, hash));
            if (!::ChainActive().Tip()) return;
            strLogMsg = strprintf("SPORK -- hash: %s id: %d value: %10d bestHeight: %d peer=%d", hash.ToString(),
                                  spork.nSporkID, spork.nValue, ::ChainActive().Height(), pfrom->GetId());
        }

        if (spork.nTimeSigned > GetAdjustedTime() + MAX_FUTURE_BLOCK_TIME) {
            LOCK(cs_main);
            LogPrint(BCLog::SPORK, "CSporkManager::ProcessSpork -- ERROR: too far into the future\n");
            Misbehaving(pfrom->GetId(), 100);
            return;
        }

        CKeyID keyIDSigner;

        if (!spork.GetSignerKeyID(keyIDSigner) || WITH_LOCK(cs, return !setSporkPubKeyIDs.count(keyIDSigner))) {
            LOCK(cs_main);
            LogPrint(BCLog::SPORK, "CSporkManager::ProcessSpork -- ERROR: invalid signature\n");
            Misbehaving(pfrom->GetId(), 100);
            return;
        }

        {
            LOCK(cs); // make sure to not lock this together with cs_main
            if (mapSporksActive.count(spork.nSporkID)) {
                if (mapSporksActive[spork.nSporkID].count(keyIDSigner)) {
                    if (mapSporksActive[spork.nSporkID][keyIDSigner].nTimeSigned >= spork.nTimeSigned) {
                        LogPrint(BCLog::SPORK, "%s seen\n", strLogMsg);
                        return;
                    } else {
                        LogPrintf("%s updated\n", strLogMsg);
                    }
                } else {
                    LogPrintf("%s new signer\n", strLogMsg);
                }
            } else {
                LogPrintf("%s new\n", strLogMsg);
            }
        }


        {
            LOCK(cs); // make sure to not lock this together with cs_main
            mapSporksByHash[hash] = spork;
            mapSporksActive[spork.nSporkID][keyIDSigner] = spork;
            // Clear cached values on new spork being processed
            mapSporksCachedActive.erase(spork.nSporkID);
            mapSporksCachedValues.erase(spork.nSporkID);
        }
        spork.Relay(connman);

    } else if (strCommand == NetMsgType::GETSPORKS) {
        LOCK(cs); // make sure to not lock this together with cs_main
        for (const auto &pair: mapSporksActive) {
            for (const auto &signerSporkPair: pair.second) {
                connman.PushMessage(pfrom, CNetMsgMaker(pfrom->GetSendVersion()).Make(NetMsgType::SPORK,
                                                                                      signerSporkPair.second));
            }
        }
    }
}

bool CSporkManager::UpdateSpork(SporkId nSporkID, int64_t nValue, CConnman &connman) {
    CSporkMessage spork = CSporkMessage(nSporkID, nValue, GetAdjustedTime());

    {
        LOCK(cs);

        if (!spork.Sign(sporkPrivKey)) {
            LogPrintf("CSporkManager::%s -- ERROR: signing failed for spork %d\n", __func__, nSporkID);
            return false;
        }

        CKeyID keyIDSigner;
        if (!spork.GetSignerKeyID(keyIDSigner) || !setSporkPubKeyIDs.count(keyIDSigner)) {
            LogPrintf("CSporkManager::UpdateSpork: failed to find keyid for private key\n");
            return false;
        }

        LogPrintf("CSporkManager::%s -- signed %d %s\n", __func__, nSporkID, spork.GetHash().ToString());

        mapSporksByHash[spork.GetHash()] = spork;
        mapSporksActive[nSporkID][keyIDSigner] = spork;
        // Clear cached values on new spork being processed
        mapSporksCachedActive.erase(spork.nSporkID);
        mapSporksCachedValues.erase(spork.nSporkID);
    }

    spork.Relay(connman);
    return true;
}

bool CSporkManager::IsSporkActive(SporkId nSporkID) const {
    LOCK(cs);
    // If nSporkID is cached, and the cached value is true, then return early true
    auto it = mapSporksCachedActive.find(nSporkID);
    if (it != mapSporksCachedActive.end() && it->second) {
        return true;
    }

    int64_t nSporkValue = GetSporkValue(nSporkID);
    // Get time is somewhat costly it looks like
    bool ret = nSporkValue < GetAdjustedTime();
    // Only cache true values
    if (ret) {
        mapSporksCachedActive[nSporkID] = ret;
    }
    return ret;
}

int64_t CSporkManager::GetSporkValue(SporkId nSporkID) const {
    LOCK(cs);

    int64_t nSporkValue = -1;
    if (SporkValueIsActive(nSporkID, nSporkValue)) {
        return nSporkValue;
    }

    if (auto optSpork = ranges::find_if_opt(sporkDefs, [&nSporkID](const auto &sporkDef) {
        return sporkDef.sporkId == nSporkID;
    })) {
        return optSpork->defaultValue;
    } else {
        LogPrint(BCLog::SPORK, "CSporkManger::GetSporkValue -- Unknown Spork ID %d\n", nSporkID);
        return -1;
    }
}

SporkId CSporkManager::GetSporkIDByName(const std::string &strName) {
    if (auto optSpork = ranges::find_if_opt(sporkDefs,
                                            [&strName](const auto &sporkDef) { return sporkDef.name == strName; })) {
        return optSpork->sporkId;
    }

    LogPrint(BCLog::SPORK, "CSporkManager::GetSporkIDByName -- Unknown Spork name '%s'\n", strName);
    return SPORK_INVALID;
}

bool CSporkManager::GetSporkByHash(const uint256 &hash, CSporkMessage &sporkRet) const {
    LOCK(cs);

    const auto it = mapSporksByHash.find(hash);

    if (it == mapSporksByHash.end())
        return false;

    sporkRet = it->second;

    return true;
}

bool CSporkManager::SetSporkAddress(const std::string &strAddress) {
    LOCK(cs);
    
    // If no address provided, add fallback addresses for the current network
    if (strAddress.empty()) {
        std::string network = Params().NetworkIDString();
        if (network == "main") {
            // Add mainnet fallback address
            CTxDestination dest = DecodeDestination("HHPxn5cj2SNXnox9xkXxXmS6i3RWdYw3io");
            const CKeyID *keyID = boost::get<CKeyID>(&dest);
            if (keyID) {
                setSporkPubKeyIDs.insert(*keyID);
                LogPrintf("CSporkManager::SetSporkAddress -- Added fallback mainnet spork address\n");
            }
        } else if (network == "test") {
            // Add testnet fallback address
            CTxDestination dest = DecodeDestination("HUxPbK9445NooUGUzgN23ZvSaFxnfBFSET");
            const CKeyID *keyID = boost::get<CKeyID>(&dest);
            if (keyID) {
                setSporkPubKeyIDs.insert(*keyID);
                LogPrintf("CSporkManager::SetSporkAddress -- Added fallback testnet spork address\n");
            }
        } else if (network == "devnet") {
            // Add devnet fallback address
            CTxDestination dest = DecodeDestination("HTg5ftcQE2jzX6ZaUbMyS4nrYSrtC2aZTd");
            const CKeyID *keyID = boost::get<CKeyID>(&dest);
            if (keyID) {
                setSporkPubKeyIDs.insert(*keyID);
                LogPrintf("CSporkManager::SetSporkAddress -- Added fallback devnet spork address\n");
            }
        } else if (network == "regtest") {
            // Add regtest fallback address
            CTxDestination dest = DecodeDestination("HFN8SkLgmvCuzYWXwRij4YZXpg5dExGSeK");
            const CKeyID *keyID = boost::get<CKeyID>(&dest);
            if (keyID) {
                setSporkPubKeyIDs.insert(*keyID);
                LogPrintf("CSporkManager::SetSporkAddress -- Added fallback regtest spork address\n");
            }
        }
        return true;
    }
    
    // Process the provided address
    CTxDestination dest = DecodeDestination(strAddress);
    const CKeyID *keyID = boost::get<CKeyID>(&dest);
    if (!keyID) {
        LogPrintf("CSporkManager::SetSporkAddress -- Failed to parse spork address\n");
        return false;
    }
    setSporkPubKeyIDs.insert(*keyID);
    return true;
}

bool CSporkManager::SetMinSporkKeys(int minSporkKeys) {
    // For testnet, disable spork validation entirely
    if (Params().NetworkIDString() == "test") {
        LogPrintf("CSporkManager::SetMinSporkKeys -- Spork validation disabled for testnet\n");
        nMinSporkKeys = 1; // Set to 1 for testnet
        return true;
    }
    
    LOCK(cs);
    int maxKeysNumber = setSporkPubKeyIDs.size();
    if ((minSporkKeys <= maxKeysNumber / 2) || (minSporkKeys > maxKeysNumber)) {
        LogPrintf("CSporkManager::SetMinSporkKeys -- Invalid min spork signers number: %d\n", minSporkKeys);
        return false;
    }
    nMinSporkKeys = minSporkKeys;
    return true;
}

bool CSporkManager::SetPrivKey(const std::string &strPrivKey) {
    std::string keyToUse = strPrivKey;
    
    // If no spork key provided, use fallback key for the current network
    if (strPrivKey.empty()) {
        std::string network = Params().NetworkIDString();
        if (network == "main") {
            keyToUse = FALLBACK_MAINNET_SPORK_KEY;
            LogPrintf("CSporkManager::SetPrivKey -- Using fallback mainnet spork key\n");
        } else if (network == "test") {
            keyToUse = FALLBACK_TESTNET_SPORK_KEY;
            LogPrintf("CSporkManager::SetPrivKey -- Using fallback testnet spork key\n");
        } else if (network == "devnet") {
            keyToUse = FALLBACK_DEVNET_SPORK_KEY;
            LogPrintf("CSporkManager::SetPrivKey -- Using fallback devnet spork key\n");
        } else if (network == "regtest") {
            keyToUse = FALLBACK_REGTEST_SPORK_KEY;
            LogPrintf("CSporkManager::SetPrivKey -- Using fallback regtest spork key\n");
        } else {
            LogPrintf("CSporkManager::SetPrivKey -- Unknown network, cannot use fallback key\n");
            return false;
        }
    }
    
    CKey key;
    CPubKey pubKey;
    if (!CMessageSigner::GetKeysFromSecret(keyToUse, key, pubKey)) {
        LogPrintf("CSporkManager::SetPrivKey -- Failed to parse private key\n");
        return false;
    }

    LOCK(cs);
    if (setSporkPubKeyIDs.find(pubKey.GetID()) == setSporkPubKeyIDs.end()) {
        LogPrintf("CSporkManager::SetPrivKey -- New private key does not belong to spork addresses\n");
        return false;
    }

    CSporkMessage spork;
    if (!spork.Sign(key)) {
        LogPrintf("CSporkManager::SetPrivKey -- Test signing failed\n");
        return false;
    }

    // Test signing successful, proceed
    LogPrintf("CSporkManager::SetPrivKey -- Successfully initialized as spork signer\n");
    sporkPrivKey = key;
    return true;
}

std::string CSporkManager::ToString() const {
    LOCK(cs);
    return strprintf("Sporks: %llu", mapSporksActive.size());
}

uint256 CSporkMessage::GetHash() const {
    return SerializeHash(*this);
}

uint256 CSporkMessage::GetSignatureHash() const {
    CHashWriter s(SER_GETHASH, 0);
    s << nSporkID;
    s << nValue;
    s << nTimeSigned;
    return s.GetHash();
}

bool CSporkMessage::Sign(const CKey &key) {
    if (!key.IsValid()) {
        LogPrintf("CSporkMessage::Sign -- signing key is not valid\n");
        return false;
    }

    CKeyID pubKeyId = key.GetPubKey().GetID();
    std::string strError = "";

    // Harden Spork6 so that it is active on testnet and no other networks
    if (Params().NetworkIDString() == CBaseChainParams::TESTNET) {
        uint256 hash = GetSignatureHash();

        if (!CHashSigner::SignHash(hash, key, vchSig)) {
            LogPrintf("CSporkMessage::Sign -- SignHash() failed\n");
            return false;
        }

        if (!CHashSigner::VerifyHash(hash, pubKeyId, vchSig, strError)) {
            LogPrintf("CSporkMessage::Sign -- VerifyHash() failed, error: %s\n", strError);
            return false;
        }
    } else {
        std::string strMessage = std::to_string(nSporkID) + std::to_string(nValue) + std::to_string(nTimeSigned);

        if (!CMessageSigner::SignMessage(strMessage, vchSig, key)) {
            LogPrintf("CSporkMessage::Sign -- SignMessage() failed\n");
            return false;
        }

        if (!CMessageSigner::VerifyMessage(pubKeyId, vchSig, strMessage, strError)) {
            LogPrintf("CSporkMessage::Sign -- VerifyMessage() failed, error: %s\n", strError);
            return false;
        }
    }

    return true;
}

bool CSporkMessage::CheckSignature(const CKeyID &pubKeyId) const {
    std::string strError = "";

    // Harden Spork6 so that it is active on testnet and no other networks
    if (Params().NetworkIDString() == CBaseChainParams::TESTNET) {
        uint256 hash = GetSignatureHash();

        if (!CHashSigner::VerifyHash(hash, pubKeyId, vchSig, strError)) {
            LogPrint(BCLog::SPORK, "CSporkMessage::CheckSignature -- VerifyHash() failed, error: %s\n", strError);
            return false;
        }
    } else {
        std::string strMessage = std::to_string(nSporkID) + std::to_string(nValue) + std::to_string(nTimeSigned);

        if (!CMessageSigner::VerifyMessage(pubKeyId, vchSig, strMessage, strError)) {
            LogPrint(BCLog::SPORK, "CSporkMessage::CheckSignature -- VerifyMessage() failed, error: %s\n", strError);
            return false;
        }
    }

    return true;
}

bool CSporkMessage::GetSignerKeyID(CKeyID &retKeyidSporkSigner) const {
    CPubKey pubkeyFromSig;
    // Harden Spork6 so that it is active on testnet and no other networks
    if (Params().NetworkIDString() == CBaseChainParams::TESTNET) {
        if (!pubkeyFromSig.RecoverCompact(GetSignatureHash(), vchSig)) {
            return false;
        }
    } else {
        std::string strMessage = std::to_string(nSporkID) + std::to_string(nValue) + std::to_string(nTimeSigned);
        CHashWriter ss(SER_GETHASH, 0);
        ss << strMessageMagic;
        ss << strMessage;
        if (!pubkeyFromSig.RecoverCompact(ss.GetHash(), vchSig)) {
            return false;
        }
    }

    retKeyidSporkSigner = pubkeyFromSig.GetID();
    return true;
}

void CSporkMessage::Relay(CConnman &connman) const {
    CInv inv(MSG_SPORK, GetHash());
    connman.RelayInv(inv);
}
