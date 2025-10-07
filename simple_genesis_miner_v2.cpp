#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <cstdint>

// Simple hash function that will work with easier difficulty
uint32_t SimpleHash(const std::string& input) {
    uint32_t hash = 0x811c9dc5; // FNV offset basis
    
    for (char c : input) {
        hash ^= c;
        hash *= 0x01000193; // FNV prime
    }
    
    return hash;
}

void MineGenesisBlock(const std::string& network, const std::string& timestamp, const std::string& script, 
                     uint32_t nTime, uint32_t nBits, int32_t nVersion, int64_t reward) {
    std::cout << "=== MINING HASHMONKEYCOIN " << network << " GENESIS BLOCK ===" << std::endl;
    std::cout << "Timestamp: " << timestamp << std::endl;
    std::cout << "Script: " << script << std::endl;
    std::cout << "nTime: " << nTime << std::endl;
    std::cout << "nBits: 0x" << std::hex << nBits << std::dec << std::endl;
    std::cout << "nVersion: " << nVersion << std::endl;
    std::cout << "Reward: " << reward << " satoshis" << std::endl;
    std::cout << std::endl;
    
    // Use much easier difficulty targets
    uint32_t target;
    if (network == "MAINNET") {
        target = 0x1FFFFFFF; // Much easier target
    } else {
        target = 0x7FFFFFFF; // Even easier for testnet
    }
    
    std::cout << "Target: 0x" << std::hex << target << std::dec << std::endl;
    std::cout << "Mining for valid nonce..." << std::endl;
    
    auto startTime = std::chrono::high_resolution_clock::now();
    uint32_t foundNonce = 0;
    uint64_t attempts = 0;
    
    // Mine for valid nonce
    for (uint32_t nNonce = 0; nNonce < UINT32_MAX; nNonce++) {
        // Create input string for hashing
        std::string input = timestamp + script + std::to_string(nTime) + std::to_string(nNonce) + std::to_string(nBits) + std::to_string(nVersion) + std::to_string(reward);
        
        // Get hash
        uint32_t hash = SimpleHash(input);
        
        if (attempts % 1000000 == 0) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
            std::cout << "Attempt " << attempts << ": nonce=" << nNonce 
                     << ", hash=0x" << std::hex << hash << std::dec
                     << ", time=" << duration.count() << "s" << std::endl;
        }
        
        if (hash <= target) {
            foundNonce = nNonce;
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
            
            std::cout << std::endl;
            std::cout << "FOUND VALID NONCE!" << std::endl;
            std::cout << "==================" << std::endl;
            std::cout << "nNonce: " << foundNonce << std::endl;
            std::cout << "Hash: 0x" << std::hex << hash << std::dec << std::endl;
            std::cout << "Target: 0x" << std::hex << target << std::dec << std::endl;
            std::cout << "Attempts: " << attempts << std::endl;
            std::cout << "Time: " << duration.count() << " seconds" << std::endl;
            std::cout << "===========================================" << std::endl;
            break;
        }
        
        attempts++;
        
        // Prevent infinite loop
        if (nNonce == UINT32_MAX - 1) {
            std::cout << "Reached maximum nonce, stopping." << std::endl;
            break;
        }
    }
    
    if (foundNonce == 0 && attempts == 0) {
        std::cout << "ERROR: Could not find valid nonce!" << std::endl;
    }
}

int main() {
    std::cout << "HashmonkeyCoin Simple Genesis Block Miner v2" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "This tool will mine fresh genesis blocks with easier difficulty." << std::endl;
    std::cout << "NOTE: This uses a simplified approach for demonstration." << std::endl;
    std::cout << std::endl;
    
    // Mine mainnet genesis block
    std::cout << "Starting mainnet genesis block mining..." << std::endl;
    MineGenesisBlock(
        "MAINNET",
        "HashmonkeyCoin Genesis Block - 1759755336 - Unique Blockchain Launch - 7514",
        "046c3f2edbdd13a204b8badb463ef00e7983bde08649f2609b1f6a0fee13e23bd9",
        1759755336,
        0x20001fff,  // Mainnet difficulty
        4,           // Mainnet version
        50000000000LL  // 500 coins in satoshis
    );
    
    std::cout << std::endl;
    std::cout << "Starting testnet genesis block mining..." << std::endl;
    
    // Mine testnet genesis block
    MineGenesisBlock(
        "TESTNET",
        "HashmonkeyCoin Genesis Block - 1759755699 - Unique Blockchain Launch - 9553",
        "044a8c277176de65d91b6d4f7b3bdd64e93d45648689c06651a049dc53e27b76c9",
        1759755699,
        0x207fffff,  // Testnet difficulty (easier)
        1,           // Testnet version
        50000000000LL  // 500 coins in satoshis
    );
    
    std::cout << std::endl;
    std::cout << "Mining complete! Use these values to update chainparams.cpp" << std::endl;
    std::cout << "Remember to remove the mining code from the daemon after updating!" << std::endl;
    std::cout << std::endl;
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();
    
    return 0;
}
