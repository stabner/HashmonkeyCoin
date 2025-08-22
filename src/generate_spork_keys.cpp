#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <iomanip>
#include <sstream>

// Include HashmonkeyCoin headers
#include "key.h"
#include "base58.h"
#include "chainparams.h"
#include "utilstrencodings.h"

// Generate a valid HashmonkeyCoin spork keypair
std::pair<std::string, std::string> generate_spork_keypair() {
    // Generate a new private key
    CKey key;
    key.MakeNewKey(true); // compressed key
    
    // Get the private key in WIF format
    CBitcoinSecret secret(key);
    std::string privateKey = secret.ToString();
    
    // Get the public key hash and create address
    CPubKey pubKey = key.GetPubKey();
    CKeyID keyID = pubKey.GetID();
    
    // Encode as HashmonkeyCoin address (H prefix)
    std::string address = EncodeDestination(keyID);
    
    return std::make_pair(address, privateKey);
}

int main() {
    std::cout << "Generating valid HashmonkeyCoin spork keypairs..." << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << std::endl;
    
    // Generate keypairs for each network
    std::vector<std::string> networks = {"Mainnet", "Testnet", "Devnet", "Regtest"};
    std::vector<std::pair<std::string, std::string>> keypairs;
    
    for (const auto& network : networks) {
        auto keypair = generate_spork_keypair();
        keypairs.push_back(keypair);
        
        std::cout << network << ":" << std::endl;
        std::cout << "  Public Address: " << keypair.first << std::endl;
        std::cout << "  Private Key (WIF): " << keypair.second << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << "Copy these addresses to your chainparams.cpp:" << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << std::endl;
    
    std::cout << "// Mainnet" << std::endl;
    std::cout << "vSporkAddresses = {\"" << keypairs[0].first << "\"};" << std::endl;
    std::cout << "nMinSporkKeys = 1;" << std::endl;
    std::cout << std::endl;
    
    std::cout << "// Testnet" << std::endl;
    std::cout << "vSporkAddresses = {\"" << keypairs[1].first << "\"};" << std::endl;
    std::cout << "nMinSporkKeys = 1;" << std::endl;
    std::cout << std::endl;
    
    std::cout << "// Devnet" << std::endl;
    std::cout << "vSporkAddresses = {\"" << keypairs[2].first << "\"};" << std::endl;
    std::cout << "nMinSporkKeys = 1;" << std::endl;
    std::cout << std::endl;
    
    std::cout << "// Regtest" << std::endl;
    std::cout << "vSporkAddresses = {\"" << keypairs[3].first << "\"};" << std::endl;
    std::cout << "nMinSporkKeys = 1;" << std::endl;
    std::cout << std::endl;
    
    std::cout << "IMPORTANT: Save these private keys securely!" << std::endl;
    std::cout << "You'll need them to sign spork messages later." << std::endl;
    std::cout << std::endl;
    
    for (size_t i = 0; i < networks.size(); i++) {
        std::cout << networks[i] << " Private Key: " << keypairs[i].second << std::endl;
    }
    
    return 0;
}
