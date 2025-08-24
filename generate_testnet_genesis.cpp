#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <ctime>

std::string sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string double_sha256(const std::string& input) {
    std::string first_hash = sha256(input);
    return sha256(first_hash);
}

int main() {
    // Generate unique testnet genesis block
    time_t now = time(NULL);
    std::string testnet_genesis = "HashmonkeyCoin Testnet Genesis Block - " + std::to_string(now);
    
    std::cout << "=== HashmonkeyCoin Testnet Genesis Block Generator ===" << std::endl;
    std::cout << "Timestamp: " << now << std::endl;
    std::cout << "Genesis text: " << testnet_genesis << std::endl;
    std::cout << std::endl;
    
    // Generate single SHA256
    std::string single_hash = sha256(testnet_genesis);
    std::cout << "Single SHA256: " << single_hash << std::endl;
    
    // Generate double SHA256 (like Bitcoin)
    std::string double_hash = double_sha256(testnet_genesis);
    std::cout << "Double SHA256: " << double_hash << std::endl;
    
    // Generate Merkle root (simplified - using the same text)
    std::string merkle_root = sha256("HashmonkeyCoin Testnet Merkle Root - " + std::to_string(now));
    std::cout << "Merkle Root: " << merkle_root << std::endl;
    
    std::cout << std::endl;
    std::cout << "=== For chainparams.cpp ===" << std::endl;
    std::cout << "// Testnet Genesis Block Hash" << std::endl;
    std::cout << "assert(consensus.hashGenesisBlock == uint256S(\"" << double_hash << "\"));" << std::endl;
    std::cout << std::endl;
    std::cout << "// Testnet Merkle Root" << std::endl;
    std::cout << "assert(genesis.hashMerkleRoot == uint256S(\"" << merkle_root << "\"));" << std::endl;
    
    return 0;
}
