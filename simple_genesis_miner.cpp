#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

// Simplified hashing function for demonstration purposes
// In a real scenario, this would be the actual cryptocurrency's PoW hash function
uint32_t calculate_hash(uint32_t nonce, uint32_t nTime, uint32_t nBits, uint32_t nVersion, const std::string& pszTimestamp, const std::string& genesisOutputScript) {
    // This is a placeholder. A real PoW hash would be much more complex.
    // For this simplified miner, we'll just combine some values and look for a low hash.
    // The goal is to find a nonce that makes the combined value small enough.
    uint32_t combined_value = nonce + nTime + nBits + nVersion + pszTimestamp.length() + genesisOutputScript.length();
    // A very simple "hash" that will quickly find a nonce for demonstration
    return combined_value & 0x1FFFFFFF; // Example: target 0x1FFFFFFF (easy)
}

// Function to convert compact nBits to a target hash (simplified)
uint32_t GetCompactTarget(uint32_t nBits) {
    // This is a highly simplified conversion. Real nBits to target conversion is complex.
    // For this miner, we'll just use the lower 28 bits as a "target" for our simple hash.
    return nBits & 0x1FFFFFFF;
}

void mine_genesis_block(const std::string& network_name, const char* pszTimestamp, const std::string& genesisOutputScript,
                        uint32_t nTime, uint32_t nBits, int32_t nVersion, int64_t genesisReward) {
    std::cout << "\nStarting " << network_name << " genesis block mining..." << std::endl;
    std::cout << "=== MINING HASHMONKEYCOIN " << network_name << " GENESIS BLOCK ===" << std::endl;
    std::cout << "Timestamp: " << pszTimestamp << std::endl;
    std::cout << "Script: " << genesisOutputScript << std::endl;
    std::cout << "nTime: " << nTime << std::endl;
    std::cout << "nBits: 0x" << std::hex << nBits << std::dec << std::endl;
    std::cout << "nVersion: " << nVersion << std::endl;
    std::cout << "Reward: " << genesisReward << " satoshis" << std::endl;

    uint32_t target = GetCompactTarget(nBits);
    std::cout << "\nTarget: 0x" << std::hex << target << std::dec << std::endl;
    std::cout << "Mining for valid nonce..." << std::endl;

    uint32_t nNonce = 0;
    uint64_t attempts = 0;
    auto start_time = std::chrono::high_resolution_clock::now();

    do {
        uint32_t hash = calculate_hash(nNonce, nTime, nBits, nVersion, pszTimestamp, genesisOutputScript);

        if (attempts % 100000000 == 0 && attempts > 0) { // Print every 100 million attempts
            auto current_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
            std::cout << "Attempt " << attempts << ": nonce=0x" << std::hex << nNonce << std::dec
                      << ", hash=0x" << std::hex << hash << std::dec
                      << ", time=" << duration << "s" << std::endl;
        }

        if (hash <= target) {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

            std::cout << "\nFOUND VALID NONCE!" << std::endl;
            std::cout << "==================" << std::endl;
            std::cout << "nNonce: " << nNonce << std::endl;
            std::cout << "Hash: 0x" << std::hex << hash << std::dec << std::endl;
            std::cout << "Target: 0x" << std::hex << target << std::dec << std::endl;
            std::cout << "Attempts: " << attempts << std::endl;
            std::cout << "Time: " << duration << " seconds" << std::endl;
            std::cout << "===========================================" << std::endl;
            return;
        }
        nNonce++;
        attempts++;
    } while (nNonce != 0); // Continue until we wrap around (very unlikely for 32-bit nonce)

    std::cout << "\nReached maximum nonce, stopping." << std::endl;
}

int main() {
    std::cout << "HashmonkeyCoin Simple Genesis Block Miner v2" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "This tool will mine fresh genesis blocks with easier difficulty." << std::endl;
    std::cout << "NOTE: This uses a simplified approach for demonstration." << std::endl;

    // Mainnet parameters
    const char* mainnet_pszTimestamp = "HashmonkeyCoin Genesis Block - 1759755336 - Unique Blockchain Launch - 7514";
    const std::string mainnet_genesisOutputScript = "046c3f2edbdd13a204b8badb463ef00e7983bde08649f2609b1f6a0fee13e23bd9";
    uint32_t mainnet_nTime = 1759755336;
    uint32_t mainnet_nBits = 0x20001fff; // Mainnet difficulty
    int32_t mainnet_nVersion = 4;
    int64_t mainnet_genesisReward = 500 * 100000000LL; // 500 coins

    mine_genesis_block("MAINNET", mainnet_pszTimestamp, mainnet_genesisOutputScript,
                       mainnet_nTime, mainnet_nBits, mainnet_nVersion, mainnet_genesisReward);

    // Testnet parameters
    const char* testnet_pszTimestamp = "HashmonkeyCoin Genesis Block - 1759755699 - Unique Blockchain Launch - 9553";
    const std::string testnet_genesisOutputScript = "044a8c277176de65d91b6d4f7b3bdd64e93d45648689c06651a049dc53e27b76c9";
    uint32_t testnet_nTime = 1759755699;
    uint32_t testnet_nBits = 0x207fffff; // Testnet difficulty (easier)
    int32_t testnet_nVersion = 1;
    int64_t testnet_genesisReward = 500 * 100000000LL; // 500 coins

    mine_genesis_block("TESTNET", testnet_pszTimestamp, testnet_genesisOutputScript,
                       testnet_nTime, testnet_nBits, testnet_nVersion, testnet_genesisReward);

    std::cout << "\nMining complete! Use these values to update chainparams.cpp" << std::endl;
    std::cout << "Remember to remove the mining code from the daemon after updating!" << std::endl;
    std::cout << "\nPress Enter to exit..." << std::endl;
    std::cin.ignore(); // Wait for user input before closing
    return 0;
}