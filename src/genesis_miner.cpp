#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <sstream>

// Include the necessary headers from the HashmonkeyCoin source
#include "arith_uint256.h"
#include "uint256.h"
#include "chainparams.h"
#include "primitives/block.h"
#include "script/script.h"
#include "util/strencodings.h"
#include "consensus/consensus.h"

int main() {
    std::cout << "HashmonkeyCoin Genesis Block Miner (Proper)" << std::endl;
    std::cout << "===========================================" << std::endl;
    
    // Genesis block parameters
    const char *pszTimestamp = "HashmonkeyCoin Genesis Block - October 2025";
    const CScript genesisOutputScript = CScript() << ParseHex(
            "040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9")
                                                  << OP_CHECKSIG;
    
    uint32_t nTime = 1759752916;
    uint32_t nBits = 0x20001fff;
    uint32_t nVersion = 4;
    CAmount genesisReward = 500 * COIN;
    
    std::cout << "Timestamp: " << pszTimestamp << std::endl;
    std::cout << "nTime: " << nTime << std::endl;
    std::cout << "nBits: 0x" << std::hex << nBits << std::dec << std::endl;
    std::cout << "nVersion: " << nVersion << std::endl;
    std::cout << "Genesis Reward: " << genesisReward / COIN << " coins" << std::endl;
    std::cout << std::endl;
    
    // Create the genesis block
    CBlock genesis = CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, 0, nBits, nVersion, genesisReward);
    
    std::cout << "Initial Genesis Block:" << std::endl;
    std::cout << "  Block Hash: " << genesis.GetHash().ToString() << std::endl;
    std::cout << "  Merkle Root: " << genesis.hashMerkleRoot.ToString() << std::endl;
    std::cout << "  POW Hash: " << genesis.GetPOWHash().ToString() << std::endl;
    std::cout << "  nNonce: " << genesis.nNonce << std::endl;
    std::cout << std::endl;
    
    // Set up the target
    arith_uint256 bnTarget;
    bnTarget.SetCompact(genesis.nBits);
    std::cout << "Target: " << bnTarget.ToString() << std::endl;
    std::cout << std::endl;
    
    // Mine for the correct nonce using the same logic as VerifyGenesisPOW
    std::cout << "Mining for valid nonce using Raptoreum hashing..." << std::endl;
    uint32_t nonce = 0;
    uint64_t attempts = 0;
    
    do {
        genesis.nNonce = nonce;
        uint256 powHash = genesis.GetPOWHash();
        arith_uint256 powHashArith = UintToArith256(powHash);
        
        if (attempts % 100000 == 0) {
            std::cout << "Attempt " << attempts << ": nonce=" << nonce 
                      << ", powHash=" << powHash.ToString() << std::endl;
        }
        
        if (powHashArith <= bnTarget) {
            std::cout << std::endl;
            std::cout << "FOUND VALID NONCE!" << std::endl;
            std::cout << "==================" << std::endl;
            std::cout << "nNonce: " << nonce << std::endl;
            std::cout << "Block Hash: " << genesis.GetHash().ToString() << std::endl;
            std::cout << "Merkle Root: " << genesis.hashMerkleRoot.ToString() << std::endl;
            std::cout << "POW Hash: " << powHash.ToString() << std::endl;
            std::cout << "Attempts: " << attempts << std::endl;
            std::cout << std::endl;
            
            // Output the exact values for chainparams.cpp
            std::cout << "For chainparams.cpp:" << std::endl;
            std::cout << "genesis = CreateGenesisBlock(pszTimestamp, genesisOutputScript, " 
                      << nTime << ", " << nonce << ", 0x" << std::hex << nBits << std::dec 
                      << ", " << nVersion << ", " << genesisReward << " * COIN);" << std::endl;
            std::cout << "assert(consensus.hashGenesisBlock == uint256S(\"" 
                      << genesis.GetHash().ToString() << "\"));" << std::endl;
            std::cout << "assert(genesis.hashMerkleRoot == uint256S(\"" 
                      << genesis.hashMerkleRoot.ToString() << "\"));" << std::endl;
            
            return 0;
        }
        
        nonce++;
        attempts++;
        
        // Prevent infinite loop
        if (nonce == 0) {
            std::cout << "Wrapped around to nonce 0, stopping." << std::endl;
            break;
        }
        
    } while (true);
    
    std::cout << "Could not find valid nonce!" << std::endl;
    return 1;
}