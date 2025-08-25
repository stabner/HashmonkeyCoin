// Copyright (c) 2024 The HashmonkeyCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <evo/dummy_smartnode.h>
#include <crypto/sha256.h>
#include <util/strencodings.h>
#include <chainparams.h>

// Dummy smartnode constants - these are deterministic and constant across all instances
static const uint64_t DUMMY_INTERNAL_ID = 0xDEADBEEF;
static const std::string DUMMY_SEED = "HashmonkeyCoinDummySmartnode2024";

CDeterministicMNCPtr CDummySmartnodeManager::CreateDummySmartnode() {
    // Create a new deterministic smartnode with our dummy internal ID
    auto dmn = std::make_shared<CDeterministicMN>(GetDummyInternalId());
    
    // Set the ProTxHash to our deterministic dummy hash
    dmn->proTxHash = GetDummyProTxHash();
    
    // Set collateral outpoint to a dummy value (no real collateral)
    dmn->collateralOutpoint = COutPoint(uint256(), 0);
    
    // Set operator reward to 0 (no rewards)
    dmn->nOperatorReward = 0;
    
    // Create the smartnode state
    auto state = std::make_shared<CDeterministicMNState>();
    
    // Set registration height to 0 (registered from genesis)
    state->nRegisteredHeight = 0;
    state->nLastPaidHeight = 0;
    state->nPoSePenalty = 0;
    state->nPoSeRevivedHeight = -1;
    state->nRevocationReason = CProUpRevTx::REASON_NOT_SPECIFIED;
    
    // Set collateral amount to 0 (no collateral required)
    state->nCollateralAmount = 0;
    
    // Set dummy keys and addresses
    state->keyIDOwner = GetDummyOwnerKey();
    state->pubKeyOperator.Set(GetDummyBLSPublicKey());
    state->keyIDVoting = GetDummyVotingKey();
    state->addr = GetDummyService();
    state->scriptPayout = GetDummyPayoutScript();
    state->scriptOperatorPayout = CScript(); // Empty script for operator payout
    
    // Set confirmed hash to a dummy value
    state->confirmedHash = uint256();
    state->confirmedHashWithProRegTxHash = uint256();
    
    // Assign the state to the smartnode
    dmn->pdmnState = state;
    
    return dmn;
}

bool CDummySmartnodeManager::IsDummySmartnode(const CDeterministicMNCPtr& dmn) {
    if (!dmn) return false;
    return dmn->proTxHash == GetDummyProTxHash();
}

uint256 CDummySmartnodeManager::GetDummyProTxHash() {
    // Generate a deterministic hash from our seed
    CSHA256 hasher;
    hasher.Write((const unsigned char*)DUMMY_SEED.c_str(), DUMMY_SEED.length());
    uint256 hash;
    hasher.Finalize(hash.begin());
    return hash;
}

uint64_t CDummySmartnodeManager::GetDummyInternalId() {
    return DUMMY_INTERNAL_ID;
}

CBLSPublicKey CDummySmartnodeManager::GetDummyBLSPublicKey() {
    // Generate a deterministic BLS public key from our seed
    CSHA256 hasher;
    hasher.Write((const unsigned char*)DUMMY_SEED.c_str(), DUMMY_SEED.length());
    hasher.Write((const unsigned char*)"BLS", 3);
    uint256 hash;
    hasher.Finalize(hash.begin());
    
    // Create a BLS public key from the hash
    CBLSPublicKey pubKey;
    pubKey.SetByteVector(std::vector<unsigned char>(hash.begin(), hash.end()));
    return pubKey;
}

CKeyID CDummySmartnodeManager::GetDummyOwnerKey() {
    // Generate a deterministic owner key from our seed
    CSHA256 hasher;
    hasher.Write((const unsigned char*)DUMMY_SEED.c_str(), DUMMY_SEED.length());
    hasher.Write((const unsigned char*)"OWNER", 6);
    uint256 hash;
    hasher.Finalize(hash.begin());
    
    // Convert uint256 to uint160 for CKeyID
    uint160 key160;
    memcpy(key160.begin(), hash.begin(), 20);
    return CKeyID(key160);
}

CKeyID CDummySmartnodeManager::GetDummyVotingKey() {
    // Generate a deterministic voting key from our seed
    CSHA256 hasher;
    hasher.Write((const unsigned char*)DUMMY_SEED.c_str(), DUMMY_SEED.length());
    hasher.Write((const unsigned char*)"VOTING", 7);
    uint256 hash;
    hasher.Finalize(hash.begin());
    
    // Convert uint256 to uint160 for CKeyID
    uint160 key160;
    memcpy(key160.begin(), hash.begin(), 20);
    return CKeyID(key160);
}

CService CDummySmartnodeManager::GetDummyService() {
    // Generate a deterministic service address from our seed
    CSHA256 hasher;
    hasher.Write((const unsigned char*)DUMMY_SEED.c_str(), DUMMY_SEED.length());
    hasher.Write((const unsigned char*)"SERVICE", 7);
    uint256 hash;
    hasher.Finalize(hash.begin());
    
    // Use the first 4 bytes for IP and last 2 bytes for port
    uint32_t ip = hash.GetUint64(0) & 0xFFFFFFFF;
    uint16_t port = (hash.GetUint64(1) >> 32) & 0xFFFF;
    
    // Ensure port is in valid range (1024-65535)
    port = 1024 + (port % (65535 - 1024));
    
    // Create CNetAddr from IP and then CService
    CNetAddr netAddr(ip);
    return CService(netAddr, port);
}

CScript CDummySmartnodeManager::GetDummyPayoutScript() {
    // Generate a deterministic payout script from our seed
    CSHA256 hasher;
    hasher.Write((const unsigned char*)DUMMY_SEED.c_str(), DUMMY_SEED.length());
    hasher.Write((const unsigned char*)"PAYOUT", 7);
    uint256 hash;
    hasher.Finalize(hash.begin());
    
    // Convert uint256 to uint160 for CKeyID
    uint160 key160;
    memcpy(key160.begin(), hash.begin(), 20);
    CKeyID keyID(key160);
    return GetScriptForDestination(keyID);
}
