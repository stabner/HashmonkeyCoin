/*
 * HashmonkeyCoin Genesis Block Miner - PROPER VERSION
 * ===================================================
 * 
 * This tool mines genesis blocks for HashmonkeyCoin using the REAL GhostRider PoW algorithm.
 * It must be built with the full Raptoreum codebase in WSL.
 * 
 * How to build in WSL:
 * 1. Build the main project first: make
 * 2. Then build this miner: g++ -std=c++17 -I. genesis_miner_proper.cpp -o genesis_miner_proper
 * 
 * How to run:
 * ./genesis_miner_proper
 */

#include <iostream>
#include <chrono>
#include <iomanip>
#include "chainparams.h"
#include "consensus/merkle.h"
#include "primitives/block.h"
#include "pow.h"
#include "uint256.h"
#include "arith_uint256.h"
#include "util/system.h"
#include "script/script.h"
#include "util/strencodings.h"

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "    HashmonkeyCoin Genesis Block Miner" << std::endl;
    std::cout << "    REAL GhostRider PoW Algorithm" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << std::endl;

    // Mainnet parameters - using the same values as in chainparams.cpp
    const char* mainnet_pszTimestamp = "HashmonkeyCoin launch — October 2025";
    const CScript mainnet_genesisOutputScript = CScript() << ParseHex(
        "04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f"
    ) << OP_CHECKSIG;
    
    CAmount genesisReward = 500 * COIN;
    uint32_t mainnet_nTime = 1759755336;
    uint32_t mainnet_nBits = 0x20001fff;
    int32_t mainnet_nVersion = 4;

    // Testnet parameters
    const char* testnet_pszTimestamp = "HashmonkeyCoin testnet launch — October 2025";
    const CScript testnet_genesisOutputScript = CScript() << ParseHex(
        "044a8c277176de65d91b6d4f7b3bdd64e93d45648689c06651a049dc53e27b76c9"
    ) << OP_CHECKSIG;
    
    uint32_t testnet_nTime = 1759755699;
    uint32_t testnet_nBits = 0x207fffff;
    int32_t testnet_nVersion = 1;

    // ========================================
    // MINE MAINNET GENESIS BLOCK
    // ========================================
    std::cout << "=== MINING HASHMONKEYCOIN MAINNET GENESIS BLOCK ===" << std::endl;
    std::cout << "Timestamp: " << mainnet_pszTimestamp << std::endl;
    std::cout << "nTime: " << mainnet_nTime << std::endl;
    std::cout << "nBits: 0x" << std::hex << mainnet_nBits << std::dec << std::endl;
    std::cout << "nVersion: " << mainnet_nVersion << std::endl;
    std::cout << "Reward: " << genesisReward << " satoshis" << std::endl;
    std::cout << std::endl;

    // Set the target
    arith_uint256 mainnet_bnTarget;
    mainnet_bnTarget.SetCompact(mainnet_nBits);
    std::cout << "Target: " << mainnet_bnTarget.GetHex() << std::endl;
    std::cout << "Mining for valid nonce..." << std::endl;
    std::cout << std::endl;

    auto mainnet_start_time = std::chrono::high_resolution_clock::now();
    uint32_t mainnet_nNonce = 0;
    uint64_t mainnet_attempts = 0;

    while (true) {
        CBlock genesis = CreateGenesisBlock(mainnet_pszTimestamp, mainnet_genesisOutputScript, 
                                          mainnet_nTime, mainnet_nNonce, mainnet_nBits, 
                                          mainnet_nVersion, genesisReward);
        uint256 powHash = genesis.GetPOWHash();
        
        if (UintToArith256(powHash) <= mainnet_bnTarget) {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - mainnet_start_time).count();
            
            std::cout << "✅ FOUND VALID MAINNET GENESIS BLOCK!" << std::endl;
            std::cout << "=====================================" << std::endl;
            std::cout << "Nonce: " << mainnet_nNonce << std::endl;
            std::cout << "Block Hash: " << genesis.GetHash().ToString() << std::endl;
            std::cout << "Merkle Root: " << genesis.hashMerkleRoot.ToString() << std::endl;
            std::cout << "POW Hash: " << powHash.ToString() << std::endl;
            std::cout << "Attempts: " << mainnet_attempts << std::endl;
            std::cout << "Time: " << duration << "s" << std::endl;
            std::cout << "=====================================" << std::endl;
            break;
        }

        if (mainnet_nNonce % 1000000 == 0) {
            auto current_time = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current_time - mainnet_start_time).count();
            std::cout << "Attempt " << mainnet_attempts << " | Nonce: " << mainnet_nNonce 
                      << " | Hash: " << powHash.ToString() 
                      << " | Elapsed: " << elapsed << "s" << std::endl;
        }

        mainnet_nNonce++;
        mainnet_attempts++;
    }

    std::cout << std::endl;

    // ========================================
    // MINE TESTNET GENESIS BLOCK
    // ========================================
    std::cout << "=== MINING HASHMONKEYCOIN TESTNET GENESIS BLOCK ===" << std::endl;
    std::cout << "Timestamp: " << testnet_pszTimestamp << std::endl;
    std::cout << "nTime: " << testnet_nTime << std::endl;
    std::cout << "nBits: 0x" << std::hex << testnet_nBits << std::dec << std::endl;
    std::cout << "nVersion: " << testnet_nVersion << std::endl;
    std::cout << "Reward: " << genesisReward << " satoshis" << std::endl;
    std::cout << std::endl;

    // Set the target
    arith_uint256 testnet_bnTarget;
    testnet_bnTarget.SetCompact(testnet_nBits);
    std::cout << "Target: " << testnet_bnTarget.GetHex() << std::endl;
    std::cout << "Mining for valid nonce..." << std::endl;
    std::cout << std::endl;

    auto testnet_start_time = std::chrono::high_resolution_clock::now();
    uint32_t testnet_nNonce = 0;
    uint64_t testnet_attempts = 0;

    while (true) {
        CBlock genesis = CreateGenesisBlock(testnet_pszTimestamp, testnet_genesisOutputScript, 
                                          testnet_nTime, testnet_nNonce, testnet_nBits, 
                                          testnet_nVersion, genesisReward);
        uint256 powHash = genesis.GetPOWHash();
        
        if (UintToArith256(powHash) <= testnet_bnTarget) {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - testnet_start_time).count();
            
            std::cout << "✅ FOUND VALID TESTNET GENESIS BLOCK!" << std::endl;
            std::cout << "======================================" << std::endl;
            std::cout << "Nonce: " << testnet_nNonce << std::endl;
            std::cout << "Block Hash: " << genesis.GetHash().ToString() << std::endl;
            std::cout << "Merkle Root: " << genesis.hashMerkleRoot.ToString() << std::endl;
            std::cout << "POW Hash: " << powHash.ToString() << std::endl;
            std::cout << "Attempts: " << testnet_attempts << std::endl;
            std::cout << "Time: " << duration << "s" << std::endl;
            std::cout << "======================================" << std::endl;
            break;
        }

        if (testnet_nNonce % 100000 == 0) {
            auto current_time = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current_time - testnet_start_time).count();
            std::cout << "Attempt " << testnet_attempts << " | Nonce: " << testnet_nNonce 
                      << " | Hash: " << powHash.ToString() 
                      << " | Elapsed: " << elapsed << "s" << std::endl;
        }

        testnet_nNonce++;
        testnet_attempts++;
    }

    std::cout << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "    MINING COMPLETE!" << std::endl;
    std::cout << "    Copy the values above to chainparams.cpp" << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
