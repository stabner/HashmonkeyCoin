#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>

// Simple hash function for demonstration (in real implementation, use SHA256)
uint32_t simple_hash(const std::string& input) {
    uint32_t hash = 0;
    for (char c : input) {
        hash = hash * 31 + c;
    }
    return hash;
}

// Convert to hex string
std::string to_hex(uint32_t value) {
    std::stringstream ss;
    ss << "0x" << std::hex << std::uppercase << value;
    return ss.str();
}

int main() {
    // Current timestamp (will be updated)
    uint32_t nTime = 1759752916; // Current Unix timestamp
    
    // Target difficulty (0x20001fff)
    uint32_t nBits = 0x20001fff;
    
    // Genesis reward
    uint64_t genesisReward = 5000 * 100000000; // 5000 coins in satoshis
    
    // Version
    int32_t nVersion = 4;
    
    std::cout << "HashmonkeyCoin Genesis Block Generator" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Timestamp: " << nTime << std::endl;
    std::cout << "Bits: " << to_hex(nBits) << std::endl;
    std::cout << "Version: " << nVersion << std::endl;
    std::cout << "Reward: " << genesisReward << " satoshis" << std::endl;
    std::cout << std::endl;
    
    // Try different nonces to find a valid hash
    for (uint32_t nNonce = 0; nNonce < 1000000; ++nNonce) {
        // Create a simple hash from the parameters
        std::string input = std::to_string(nTime) + std::to_string(nNonce) + std::to_string(nBits) + std::to_string(nVersion);
        uint32_t hash = simple_hash(input);
        
        // Check if hash meets difficulty (simplified check)
        if (hash < (nBits & 0x00ffffff)) {
            std::cout << "Found valid nonce: " << nNonce << std::endl;
            std::cout << "Hash: " << to_hex(hash) << std::endl;
            std::cout << std::endl;
            std::cout << "Genesis block parameters:" << std::endl;
            std::cout << "nTime: " << nTime << std::endl;
            std::cout << "nNonce: " << nNonce << std::endl;
            std::cout << "nBits: " << to_hex(nBits) << std::endl;
            std::cout << "nVersion: " << nVersion << std::endl;
            std::cout << "genesisReward: " << genesisReward << std::endl;
            break;
        }
    }
    
    return 0;
}
