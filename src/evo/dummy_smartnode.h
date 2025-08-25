// Copyright (c) 2024 The HashmonkeyCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_EVO_DUMMY_SMARTNODE_H
#define BITCOIN_EVO_DUMMY_SMARTNODE_H

#include <evo/deterministicmns.h>
#include <key.h>
#include <bls/bls.h>

class CDummySmartnodeManager {
public:
    // Create a dummy smartnode with 0 collateral and 0 rewards
    static CDeterministicMNCPtr CreateDummySmartnode();
    
    // Check if a smartnode is the dummy smartnode
    static bool IsDummySmartnode(const CDeterministicMNCPtr& dmn);
    
    // Get the dummy smartnode's ProTxHash (constant across all instances)
    static uint256 GetDummyProTxHash();
    
    // Get the dummy smartnode's internal ID
    static uint64_t GetDummyInternalId();

private:
    // Generate a deterministic dummy public key
    static CBLSPublicKey GetDummyBLSPublicKey();
    
    // Generate a deterministic dummy owner key
    static CKeyID GetDummyOwnerKey();
    
    // Generate a deterministic dummy voting key
    static CKeyID GetDummyVotingKey();
    
    // Generate a deterministic dummy service address
    static CService GetDummyService();
    
    // Generate a deterministic dummy payout script
    static CScript GetDummyPayoutScript();
};

#endif // BITCOIN_EVO_DUMMY_SMARTNODE_H
