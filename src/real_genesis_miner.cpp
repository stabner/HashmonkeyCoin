#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

// Include the necessary Raptoreum headers
#include "chainparams.h"
#include "primitives/block.h"
#include "consensus/merkle.h"
#include "uint256.h"
#include "arith_uint256.h"
#include "script/script.h"
#include "util/strencodings.h"

// Forward declarations to avoid including everything
extern "C" {
    // We need to define these to avoid linking issues
    void InitLogging() {}
    void ShutdownLogging() {}
}

int main() {
    std::cout << "HashmonkeyCoin Real Genesis Block Miner" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "This tool will mine genesis blocks using the real Raptoreum hashing algorithm." << std::endl;

    // Mainnet parameters - using the same values as in chainparams.cpp
    const char* pszTimestamp = "HashmonkeyCoin Genesis Block - 1759755336 - Unique Blockchain Launch - 7514";
    const CScript genesisOutputScript = CScript() << ParseHex(
        "046c3f2edbdd13a204b8badb463ef00e7983bde08649f2609b1f6a0fee13e23bd9"
    ) << OP_CHECKSIG;

    CAmount genesisReward = 500 * COIN;
    uint32_t nTime = 1759755336;
    uint32_t nBits = 0x20001fff;
    int32_t nVersion = 4;

    std::cout << "\n=== MINING MAINNET GENESIS BLOCK ===" << std::endl;
    std::cout << "Timestamp: " << pszTimestamp << std::endl;
    std::cout << "nTime: " << nTime << std::endl;
    std::cout << "nBits: 0x" << std::hex << nBits << std::dec << std::endl;
    std::cout << "nVersion: " << nVersion << std::endl;
    std::cout << "Reward: " << genesisReward << " satoshis" << std::endl;

    // Set the target
    arith_uint256 bnTarget;
    bnTarget.SetCompact(nBits);
    std::cout << "Target: " << bnTarget.GetHex() << std::endl;

    std::cout << "\nMining for valid nonce..." << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();

    // Mine for a valid nonce
    for (uint32_t nNonce = 0; nNonce < UINT32_MAX; nNonce++) {
        CBlock genesis = CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
        uint256 powHash = genesis.GetPOWHash();

        if (nNonce % 1000000 == 0 && nNonce > 0) {
            auto current_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
            std::cout << "Attempt " << nNonce << ": nonce=" << nNonce 
                      << ", powHash=" << powHash.ToString() 
                      << ", time=" << duration << "s" << std::endl;
        }

        if (UintToArith256(powHash) <= bnTarget) {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

            std::cout << "\n✅ FOUND VALID MAINNET GENESIS BLOCK!" << std::endl;
            std::cout << "=====================================" << std::endl;
            std::cout << "Nonce: " << nNonce << std::endl;
            std::cout << "Block Hash: " << genesis.GetHash().ToString() << std::endl;
            std::cout << "Merkle Root: " << genesis.hashMerkleRoot.ToString() << std::endl;
            std::cout << "POW Hash: " << powHash.ToString() << std::endl;
            std::cout << "Time: " << duration << " seconds" << std::endl;
            std::cout << "=====================================" << std::endl;
            break;
        }
    }

    // Now mine testnet
    std::cout << "\n=== MINING TESTNET GENESIS BLOCK ===" << std::endl;
    
    const char* testnet_pszTimestamp = "HashmonkeyCoin Genesis Block - 1759755699 - Unique Blockchain Launch - 9553";
    const CScript testnet_genesisOutputScript = CScript() << ParseHex(
        "044a8c277176de65d91b6d4f7b3bdd64e93d45648689c06651a049dc53e27b76c9"
    ) << OP_CHECKSIG;

    uint32_t testnet_nTime = 1759755699;
    uint32_t testnet_nBits = 0x207fffff;
    int32_t testnet_nVersion = 1;

    std::cout << "Timestamp: " << testnet_pszTimestamp << std::endl;
    std::cout << "nTime: " << testnet_nTime << std::endl;
    std::cout << "nBits: 0x" << std::hex << testnet_nBits << std::dec << std::endl;
    std::cout << "nVersion: " << testnet_nVersion << std::endl;

    arith_uint256 testnet_bnTarget;
    testnet_bnTarget.SetCompact(testnet_nBits);
    std::cout << "Target: " << testnet_bnTarget.GetHex() << std::endl;

    std::cout << "\nMining for valid testnet nonce..." << std::endl;
    start_time = std::chrono::high_resolution_clock::now();

    for (uint32_t nNonce = 0; nNonce < UINT32_MAX; nNonce++) {
        CBlock genesis = CreateGenesisBlock(testnet_pszTimestamp, testnet_genesisOutputScript, testnet_nTime, nNonce, testnet_nBits, testnet_nVersion, genesisReward);
        uint256 powHash = genesis.GetPOWHash();

        if (nNonce % 100000 == 0 && nNonce > 0) {
            auto current_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
            std::cout << "Attempt " << nNonce << ": nonce=" << nNonce 
                      << ", powHash=" << powHash.ToString() 
                      << ", time=" << duration << "s" << std::endl;
        }

        if (UintToArith256(powHash) <= testnet_bnTarget) {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

            std::cout << "\n✅ FOUND VALID TESTNET GENESIS BLOCK!" << std::endl;
            std::cout << "======================================" << std::endl;
            std::cout << "Nonce: " << nNonce << std::endl;
            std::cout << "Block Hash: " << genesis.GetHash().ToString() << std::endl;
            std::cout << "Merkle Root: " << genesis.hashMerkleRoot.ToString() << std::endl;
            std::cout << "POW Hash: " << powHash.ToString() << std::endl;
            std::cout << "Time: " << duration << " seconds" << std::endl;
            std::cout << "======================================" << std::endl;
            break;
        }
    }

    std::cout << "\nMining complete! Use these values to update chainparams.cpp" << std::endl;
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.ignore();
    return 0;
}
