#include <iostream>
#include <string>
#include <cstdint>

// Simple genesis block generator for HashmonkeyCoin
// This will help us get the correct hash and merkle root

int main() {
    std::cout << "=== HashmonkeyCoin Genesis Block Generator ===" << std::endl;
    std::cout << "This tool will help generate the correct genesis block values." << std::endl;
    std::cout << std::endl;
    
    // Genesis block parameters
    uint32_t genesisTime = 1755295200;  // August 16, 2025
    uint32_t genesisBits = 0x20001fff;
    uint32_t genesisVersion = 4;
    uint32_t genesisNonce = 1130;  // Current nonce from chainparams.cpp
    
    std::cout << "Genesis Block Parameters:" << std::endl;
    std::cout << "  Timestamp: " << genesisTime << " (August 16, 2025)" << std::endl;
    std::cout << "  Bits: 0x" << std::hex << genesisBits << std::endl;
    std::cout << "  Version: " << std::dec << genesisVersion << std::endl;
    std::cout << "  Nonce: " << genesisNonce << std::endl;
    std::cout << "  Reward: 500 HMNY" << std::endl;
    std::cout << std::endl;
    
    std::cout << "To get the correct genesis block values:" << std::endl;
    std::cout << "1. Build the HashmonkeyCoin project" << std::endl;
    std::cout << "2. Run: ./src/hashmonkeycoind --print-genesis-block" << std::endl;
    std::cout << "3. Or run the daemon once and check the debug log" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Expected output format:" << std::endl;
    std::cout << "Genesis Block Hash: 0x..." << std::endl;
    std::cout << "Genesis Merkle Root: 0x..." << std::endl;
    std::cout << std::endl;
    
    std::cout << "Then update chainparams.cpp with:" << std::endl;
    std::cout << "assert(consensus.hashGenesisBlock == uint256S(\"0x...\"));" << std::endl;
    std::cout << "assert(genesis.hashMerkleRoot == uint256S(\"0x...\"));" << std::endl;
    std::cout << std::endl;
    
    return 0;
}
