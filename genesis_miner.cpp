/*
 * HashmonkeyCoin Genesis Block Miner
 * ==================================
 * 
 * This tool mines genesis blocks for HashmonkeyCoin (Raptoreum fork) using the real GhostRider PoW algorithm.
 * 
 * BUILD INSTRUCTIONS:
 * ==================
 * 
 * 1. Build the main Raptoreum project first:
 *    ./autogen.sh
 *    ./configure
 *    make
 * 
 * 2. Then compile this miner:
 *    g++ -std=c++17 -I. -I./src genesis_miner.cpp -o genesis_miner
 * 
 * 3. Run the miner:
 *    ./genesis_miner
 * 
 * The miner will output the exact values needed for chainparams.cpp:
 * - hashGenesisBlock (for consensus.hashGenesisBlock)
 * - hashMerkleRoot (for genesis.hashMerkleRoot) 
 * - nNonce (for CreateGenesisBlock call)
 * 
 * Note: This uses the REAL GhostRider hashing algorithm, so mining may take
 * several hours depending on your hardware and the difficulty targets.
 */

#include <iostream>
#include <chrono>
#include <iomanip>
#include "src/chainparams.h"
#include "src/consensus/merkle.h"
#include "src/primitives/block.h"
#include "src/pow.h"
#include "src/uint256.h"
#include "src/arith_uint256.h"
#include "src/util/system.h"
#include "src/script/script.h"
#include "src/util/strencodings.h"

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "    HashmonkeyCoin Genesis Block Miner" << std::endl;
    std::cout << "    Real GhostRider PoW Algorithm" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << std::endl;

    // Mainnet parameters
    const char* mainnet_pszTimestamp = "HashmonkeyCoin Genesis: HashmonkeyCoin Launch 4 October 2025 - mainnet";
    const CScript mainnet_genesisOutputScript = CScript() << ParseHex(
        "040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9"
    ) << OP_CHECKSIG;
    
    CAmount genesisReward = 500 * COIN;
    uint32_t mainnet_nTime = 1759743064;
    uint32_t mainnet_nBits = 0x20001fff;
    int32_t mainnet_nVersion = 4;

    // Testnet parameters
    const char* testnet_pszTimestamp = "HashmonkeyCoin Genesis: HashmonkeyCoin Launch 4 October 2025 - testnet";
    const CScript testnet_genesisOutputScript = CScript() << ParseHex(
        "040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9"
    ) << OP_CHECKSIG;
    
    uint32_t testnet_nTime = 1759706139;
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
            std::cout << std::endl;
            std::cout << "COPY THESE VALUES TO chainparams.cpp:" << std::endl;
            std::cout << "consensus.hashGenesisBlock = uint256S(\"0x" << genesis.GetHash().ToString() << "\");" << std::endl;
            std::cout << "genesis.hashMerkleRoot = uint256S(\"0x" << genesis.hashMerkleRoot.ToString() << "\");" << std::endl;
            std::cout << "nNonce: " << mainnet_nNonce << std::endl;
            std::cout << std::endl;
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
            std::cout << std::endl;
            std::cout << "COPY THESE VALUES TO chainparams.cpp:" << std::endl;
            std::cout << "consensus.hashGenesisBlock = uint256S(\"0x" << genesis.GetHash().ToString() << "\");" << std::endl;
            std::cout << "genesis.hashMerkleRoot = uint256S(\"0x" << genesis.hashMerkleRoot.ToString() << "\");" << std::endl;
            std::cout << "nNonce: " << testnet_nNonce << std::endl;
            std::cout << std::endl;
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