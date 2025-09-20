// Copyright (c) 2014-2019 The Dash Core developers
// Copyright (c) 2020-2023 The Raptoreum developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_GOVERNANCE_GOVERNANCE_CLASSES_H
#define BITCOIN_GOVERNANCE_GOVERNANCE_CLASSES_H

#include <governance/governance.h>
#include <primitives/transaction.h>
#include <script/standard.h>
#include <sync.h>
#include <util.h>

#include <univalue.h>

class CGovernanceObject;
class CGovernanceTriggerManager;
class CSuperblock;
class CSuperblockManager;
class CGovernancePayment;

// DECLARE GLOBAL VARIABLES FOR GOVERNANCE CLASSES
extern CGovernanceTriggerManager triggerman;

typedef std::shared_ptr<CSuperblock> CSuperblock_sptr;

// SPLIT UP STRING BY DELIMITER
// http://www.boost.org/doc/libs/1_58_0/doc/libs/boost_algorithm/string/split_idp202406848.html
std::vector<std::string> SplitBy(const std::string& strCommand, const std::string& strDelimit);

CAmount ParsePaymentAmount(const std::string& strAmount);

/**
*   Trigger Manager
*
*   - Track governance objects which are triggers
*   - After triggers are activated and executed, they can be removed
*/

class CGovernanceTriggerManager {
    friend class CSuperblockManager;
    friend class CGovernanceManager;

private:
    typedef std::map<uint256, CSuperblock_sptr> trigger_m_t;
    typedef trigger_m_t::iterator trigger_m_it;
    typedef trigger_m_t::const_iterator trigger_m_cit;

    trigger_m_t mapTrigger;

    std::vector<CSuperblock_sptr> GetActiveTriggers();

    bool AddNewTrigger(uint256 nHash);

    void CleanAndRemove();

public:
    CGovernanceTriggerManager() : mapTrigger() {}

    void Clear() {
        LOCK(governance.cs);
        mapTrigger.clear();
    }
};

/**
*   Superblock Manager
*
*   Class for querying superblock information
*/

class CSuperblockManager {
private:
    static bool GetBestSuperblock(CSuperblock_sptr& pSuperblockRet, int nBlockHeight);

public:
    static bool IsSuperblockTriggered(int nBlockHeight);

    static bool GetSuperblockPayments(int nBlockHeight, std::vector<CTxOut>& voutSuperblockRet);

    static bool IsValid(const CTransaction& txNew, int nBlockHeight, CAmount blockReward);

    static void ExecuteBestSuperblock(int nBlockHeight);
};

/**
*   Governance Object Payment
*
*/

class CGovernancePayment {
private:
    bool fValid;

public:
    CScript script;
    CAmount nAmount;

    CGovernancePayment() :
            fValid(false),
            script(),
            nAmount(0) {}

    CGovernancePayment(CTxDestination dest, CAmount nAmountIn) :
            fValid(false),
            script(),
            nAmount(0) {
        try {
            CTxDestination address = dest;
            script = GetScriptForDestination(address);
            nAmount = nAmountIn;
            fValid = true;
        } catch (std::exception& e) {
            LogPrintf("CGovernancePayment Payment not valid: %s\n", e.what());
        } catch (...) {
            LogPrintf("CGovernancePayment Payment not valid: unknown error\n");
        }
    }

    bool IsValid() {
        return fValid;
    }
};

/**
*   Governance Object
*
*/

class CGovernanceObject {
public:
    static const int MAX_TIME_FUTURE_DEVIATION = 60 * 60;
    static const int RELIABLE_PROPAGATION_TIME = 60;

    int GetObjectType() {
        // TODO - compile error
        //        return nObjectType;
        return 0;
    }

    uint256 GetHash() const {
        // TODO - compile error
        //        return GetHash();
        return uint256();
    }

    int64_t GetCreationTime() {
        // TODO - compile error
        //        return nTime;
        return 0;
    }

    int64_t GetDeletionTime() {
        // TODO - compile error
        //        return nDeletionTime;
        return 0;
    }

    bool IsSetCachedFunding() {
        // TODO - compile error
        //        return fCachedFunding;
        return false;
    }

    bool IsSetCachedValid() {
        // TODO - compile error
        //        return fCachedValid;
        return false;
    }

    bool IsSetCachedDelete() {
        // TODO - compile error
        //        return fCachedDelete;
        return false;
    }

    bool IsSetCachedEndorsed() {
        // TODO - compile error
        //        return fCachedEndorsed;
        return false;
    }

    void SetExpired() {
        // TODO - compile error
        //        nDeletionTime = GetAdjustedTime();
    }

    bool IsExpired() {
        // TODO - compile error
        //        return (GetAdjustedTime() > nDeletionTime);
        return false;
    }

    CAmount GetAbsoluteYesCount(int nSignal) {
        // TODO - compile error
        //        return mapCurrentMNVotes[CMasternodeVote(nSignal, vote_signal_vals[nSignal].name)].GetYes();
        return 0;
    }

    bool GetCachedFunding() {
        // TODO - compile error
        //        return fCachedFunding;
        return false;
    }

    bool GetCachedValid() {
        // TODO - compile error
        //        return fCachedValid;
        return false;
    }

    bool GetCachedDelete() {
        // TODO - compile error
        //        return fCachedDelete;
        return false;
    }

    bool GetCachedEndorsed() {
        // TODO - compile error
        //        return fCachedEndorsed;
        return false;
    }

    void UpdateSentinelVariables() {
        // TODO - compile error
        //        if (nObjectType == GOVERNANCE_OBJECT_TRIGGER) {
        //            if (nDeletionTime == 0) {
        //                fCachedFunding = false;
        //            } else {
        //                fCachedFunding = true;
        //            }
        //        } else {
        //            fCachedFunding = false;
        //        }
    }

    CGovernanceObject() {}

    CGovernanceObject(const uint256& nHash, const CGovernanceObject& other) {
        // TODO - compile error
        //        *this = other;
        //        this->nHash = nHash;
    }

    // TODO - compile error
    //    CGovernanceObjectVote GetCurrentVote(int nSignal) {
    //        return mapCurrentMNVotes[CMasternodeVote(nSignal, vote_signal_vals[nSignal].name)];
    //    }

    std::string GetDataAsHexString() {
        // TODO - compile error
        //        return strData;
        return "";
    }

    std::string GetDataAsPlainString() {
        // TODO - compile error
        //        return strData;
        return "";
    }

    void PrepareDeletion(int64_t nDeletionTime_) {
        // TODO - compile error
        //        fCachedDelete = true;
        //        if (nDeletionTime == 0) {
        //            nDeletionTime = nDeletionTime_;
        //        } else {
        //            nDeletionTime = std::min(nDeletionTime, nDeletionTime_);
        //        }
    }

    // TODO - compile error
    //    UniValue GetJSONObject() {
    //        UniValue obj(UniValue::VOBJ);
    //        obj.push_back(Pair("DataHex", GetDataAsHexString()));
    //        obj.push_back(Pair("DataString", GetDataAsPlainString()));
    //        obj.push_back(Pair("Hash", GetHash().ToString()));
    //        obj.push_back(Pair("CollateralHash", GetCollateralHash().ToString()));
    //        obj.push_back(Pair("ObjectType", (int) nObjectType));
    //        obj.push_back(Pair("CreationTime", (int64_t) nTime));
    //        obj.push_back(Pair("AbsoluteYesCount", (int64_t) GetAbsoluteYesCount(VOTE_SIGNAL_FUNDING)));
    //        obj.push_back(Pair("YesCount", (int64_t) GetYesCount(VOTE_SIGNAL_FUNDING)));
    //        obj.push_back(Pair("NoCount", (int64_t) GetNoCount(VOTE_SIGNAL_FUNDING)));
    //        obj.push_back(Pair("AbstainCount", (int64_t) GetAbstainCount(VOTE_SIGNAL_FUNDING)));
    //        return obj;
    //    }

    UniValue GetJSONObject() {
        UniValue obj(UniValue::VOBJ);
        obj.push_back(Pair("DataHex", GetDataAsHexString()));
        obj.push_back(Pair("DataString", GetDataAsPlainString()));
        obj.push_back(Pair("Hash", GetHash().ToString()));
        obj.push_back(Pair("CollateralHash", GetHash().ToString()));
        obj.push_back(Pair("ObjectType", (int) GetObjectType()));
        obj.push_back(Pair("CreationTime", (int64_t) GetCreationTime()));
        obj.push_back(Pair("AbsoluteYesCount", (int64_t) GetAbsoluteYesCount(VOTE_SIGNAL_FUNDING)));
        obj.push_back(Pair("YesCount", (int64_t) GetAbsoluteYesCount(VOTE_SIGNAL_FUNDING)));
        obj.push_back(Pair("NoCount", (int64_t) 0));
        obj.push_back(Pair("AbstainCount", (int64_t) 0));
        return obj;
    }
};

/**
*   Superblock
*
*   Object for governance object trigger
*/

class CSuperblock {
private:
    uint256 nGovObjHash;

    int nBlockHeight;

    int nStatus;

    std::vector<CGovernancePayment> vecPayments;

public:
    CSuperblock();

    CSuperblock(uint256& nHash);

    static bool IsValidBlockHeight(int nBlockHeight);

    static void GetNearestSuperblocksHeights(int nBlockHeight, int& nLastSuperblockRet, int& nNextSuperblockRet);

    CAmount GetPaymentsLimit(int nBlockHeight);

    void ParsePaymentSchedule(const std::string& strPaymentAddresses, const std::string& strPaymentAmounts);

    bool GetPayment(int nPaymentIndex, CGovernancePayment& paymentRet);

    CAmount GetPaymentsTotalAmount();

    bool IsValid(const CTransaction& txNew, int nBlockHeight, CAmount blockReward);

    bool IsExpired() const;

    CGovernanceObject* GetGovernanceObject();

    int CountPayments() {
        return (int) vecPayments.size();
    }

    bool IsValidBlockHeight(int nBlockHeight) {
        return IsValidBlockHeight(nBlockHeight);
    }

    int GetBlockHeight() {
        return nBlockHeight;
    }

    int GetStatus() {
        return nStatus;
    }

    void SetStatus(int nStatusIn) {
        nStatus = nStatusIn;
    }

    void SetExecuted() {
        nStatus = SEEN_OBJECT_EXECUTED;
    }
};

#endif // BITCOIN_GOVERNANCE_GOVERNANCE_CLASSES_H