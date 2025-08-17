#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <sstream>

// Simple SHA256 implementation for genesis block mining
#include <openssl/sha.h>

// Genesis block parameters
const uint32_t GENESIS_TIME = 1755295200; // August 16, 2025
const uint32_t GENESIS_BITS = 0x20001fff;
const uint32_t GENESIS_VERSION = 4;
const uint64_t GENESIS_REWARD = 50000000000; // 500 HMNY in satoshis

// Genesis message
const char* GENESIS_MESSAGE = "The Times 16/Aug/2025 HashmonkeyCoin - The Future of Decentralized Finance";

// Genesis output script (simplified)
const std::string GENESIS_OUTPUT_SCRIPT = "41040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b179c45070ac7b03a9ac";

// Simple block header structure
struct BlockHeader {
    uint32_t version;
    uint256 prevBlock;
    uint256 merkleRoot;
    uint32_t timestamp;
    uint32_t bits;
    uint32_t nonce;
};

// Simple uint256 structure
struct uint256 {
    uint8_t data[32];
    
    uint256() {
        memset(data, 0, 32);
    }
    
    std::string ToString() const {
        std::stringstream ss;
        ss << "0x";
        for (int i = 31; i >= 0; i--) {
            ss << std::hex << std::setfill('0') << std::setw(2) << (int)data[i];
        }
        return ss.str();
    }
};

// Double SHA256 function
std::string DoubleSHA256(const std::string& input) {
    unsigned char hash1[SHA256_DIGEST_LENGTH];
    unsigned char hash2[SHA256_DIGEST_LENGTH];
    
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    SHA256_Final(hash1, &sha256);
    
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, hash1, SHA256_DIGEST_LENGTH);
    SHA256_Final(hash2, &sha256);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setfill('0') << std::setw(2) << (int)hash2[i];
    }
    return ss.str();
}

// Calculate target from bits
uint256 CalculateTarget(uint32_t bits) {
    uint256 target;
    uint32_t exponent = bits >> 24;
    uint32_t mantissa = bits & 0x007fffff;
    
    if (exponent <= 3) {
        mantissa >>= (8 * (3 - exponent));
    } else {
        mantissa <<= (8 * (exponent - 3));
    }
    
    // Set the target (simplified)
    memset(target.data, 0, 32);
    target.data[31] = mantissa & 0xff;
    target.data[30] = (mantissa >> 8) & 0xff;
    target.data[29] = (mantissa >> 16) & 0xff;
    
    return target;
}

// Check if hash meets target
bool HashMeetsTarget(const std::string& hash, const uint256& target) {
    // Simple comparison (in real implementation, this would be more complex)
    for (int i = 31; i >= 0; i--) {
        uint8_t hash_byte = std::stoi(hash.substr(i*2, 2), nullptr, 16);
        if (hash_byte < target.data[i]) return true;
        if (hash_byte > target.data[i]) return false;
    }
    return true;
}

int main() {
    std::cout << "=== HashmonkeyCoin Genesis Block Miner ===" << std::endl;
    std::cout << "Timestamp: " << GENESIS_TIME << " (August 16, 2025)" << std::endl;
    std::cout << "Bits: 0x" << std::hex << GENESIS_BITS << std::endl;
    std::cout << "Reward: 500 HMNY" << std::endl;
    std::cout << "Message: " << GENESIS_MESSAGE << std::endl;
    std::cout << std::endl;
    
    // Calculate target
    uint256 target = CalculateTarget(GENESIS_BITS);
    std::cout << "Target: " << target.ToString() << std::endl;
    std::cout << std::endl;
    
    // Create genesis transaction (simplified)
    std::string genesisTx = "0100000001000000000000000000000000000000000000000000000000000000000000000000ffffffff";
    genesisTx += "4d04ffff001d0104455468652054696d65732031362f4175672f3230323520486173686d6f6e6b6579436f696e202d2054686520467574757265206f6620446563656e7472616c697a65642046696e616e636500000000";
    genesisTx += "01";
    genesisTx += "00ca9a3b00000000"; // 500 HMNY in little-endian
    genesisTx += "23";
    genesisTx += GENESIS_OUTPUT_SCRIPT;
    genesisTx += "00000000";
    
    // Calculate merkle root
    std::string merkleRoot = DoubleSHA256(genesisTx);
    std::cout << "Genesis Transaction: " << genesisTx << std::endl;
    std::cout << "Merkle Root: " << merkleRoot << std::endl;
    std::cout << std::endl;
    
    // Mine the genesis block
    std::cout << "Mining genesis block..." << std::endl;
    
    uint32_t nonce = 0;
    std::string blockHash;
    
    while (nonce < UINT32_MAX) {
        // Create block header
        std::string header;
        header += "04000000"; // version (little-endian)
        header += "0000000000000000000000000000000000000000000000000000000000000000"; // prev block
        header += merkleRoot; // merkle root
        header += std::to_string(GENESIS_TIME); // timestamp (little-endian)
        header += std::to_string(GENESIS_BITS); // bits (little-endian)
        header += std::to_string(nonce); // nonce (little-endian)
        
        // Calculate block hash
        blockHash = DoubleSHA256(header);
        
        // Check if hash meets target
        if (HashMeetsTarget(blockHash, target)) {
            std::cout << "Genesis block found!" << std::endl;
            std::cout << "Nonce: " << nonce << std::endl;
            std::cout << "Block Hash: " << blockHash << std::endl;
            std::cout << "Merkle Root: " << merkleRoot << std::endl;
            break;
        }
        
        nonce++;
        if (nonce % 1000000 == 0) {
            std::cout << "Tried nonce: " << nonce << std::endl;
        }
    }
    
    if (nonce >= UINT32_MAX) {
        std::cout << "Failed to find valid genesis block!" << std::endl;
        return 1;
    }
    
    std::cout << std::endl;
    std::cout << "=== Genesis Block Values for chainparams.cpp ===" << std::endl;
    std::cout << "// Replace the TODO comments with:" << std::endl;
    std::cout << "assert(consensus.hashGenesisBlock == uint256S(\"" << blockHash << "\"));" << std::endl;
    std::cout << "assert(genesis.hashMerkleRoot == uint256S(\"" << merkleRoot << "\"));" << std::endl;
    std::cout << "// And update the nonce in CreateGenesisBlock call:" << std::endl;
    std::cout << "genesis = CreateGenesisBlock(" << GENESIS_TIME << ", " << nonce << ", 0x" << std::hex << GENESIS_BITS << ", " << GENESIS_VERSION << ", 500 * COIN);" << std::endl;
    
    return 0;
}
