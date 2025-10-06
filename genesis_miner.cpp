#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <chrono>

// Include the actual Raptoreum headers
#include "src/chainparams.h"
#include "src/consensus/merkle.h"
#include "src/primitives/block.h"
#include "src/arith_uint256.h"
#include "src/util/strencodings.h"

using namespace std;

void MineGenesisBlock(const string& network, const string& timestamp, const string& scriptHex, 
                     uint32_t nTime, uint32_t nBits, int32_t nVersion, int64_t reward) {
    cout << "=== MINING HASHMONKEYCOIN " << network << " GENESIS BLOCK ===" << endl;
    cout << "Timestamp: " << timestamp << endl;
    cout << "Script: " << scriptHex << endl;
    cout << "nTime: " << nTime << endl;
    cout << "nBits: 0x" << hex << nBits << dec << endl;
    cout << "nVersion: " << nVersion << endl;
    cout << "Reward: " << reward << " satoshis" << endl;
    cout << endl;
    
    // Parse the script
    vector<unsigned char> scriptBytes = ParseHex(scriptHex);
    CScript genesisOutputScript(scriptBytes.begin(), scriptBytes.end());
    
    // Set up difficulty target
    arith_uint256 bnTarget;
    bnTarget.SetCompact(nBits);
    
    cout << "Target: " << bnTarget.ToString() << endl;
    cout << "Mining for valid nonce..." << endl;
    
    auto startTime = chrono::high_resolution_clock::now();
    uint32_t foundNonce = 0;
    uint64_t attempts = 0;
    
    // Mine for valid nonce
    for (uint32_t nNonce = 0; nNonce < UINT32_MAX; nNonce++) {
        // Create genesis block with current nonce
        CBlock genesis = CreateGenesisBlock(timestamp.c_str(), genesisOutputScript, nTime, nNonce, nBits, nVersion, reward);
        
        // Check if POW hash meets target
        uint256 powHash = genesis.GetPOWHash();
        arith_uint256 powHashArith = UintToArith256(powHash);
        
        if (attempts % 100000 == 0) {
            auto currentTime = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::seconds>(currentTime - startTime);
            cout << "Attempt " << attempts << ": nonce=" << nNonce 
                 << ", powHash=" << powHash.ToString() 
                 << ", time=" << duration.count() << "s" << endl;
        }
        
        if (powHashArith <= bnTarget) {
            foundNonce = nNonce;
            auto endTime = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime);
            
            cout << endl;
            cout << "FOUND VALID NONCE!" << endl;
            cout << "==================" << endl;
            cout << "nNonce: " << foundNonce << endl;
            cout << "Block Hash: " << genesis.GetHash().ToString() << endl;
            cout << "Merkle Root: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "POW Hash: " << powHash.ToString() << endl;
            cout << "Attempts: " << attempts << endl;
            cout << "Time: " << duration.count() << " seconds" << endl;
            cout << "===========================================" << endl;
            break;
        }
        
        attempts++;
        
        // Prevent infinite loop
        if (nNonce == UINT32_MAX - 1) {
            cout << "Reached maximum nonce, stopping." << endl;
            break;
        }
    }
    
    if (foundNonce == 0 && attempts == 0) {
        cout << "ERROR: Could not find valid nonce!" << endl;
    }
}

int main() {
    cout << "HashmonkeyCoin Genesis Block Miner" << endl;
    cout << "=================================" << endl;
    cout << "This tool will mine fresh genesis blocks for both mainnet and testnet." << endl;
    cout << "The mining process may take several minutes depending on difficulty." << endl;
    cout << endl;
    
    // Mine mainnet genesis block
    cout << "Starting mainnet genesis block mining..." << endl;
    MineGenesisBlock(
        "MAINNET",
        "HashmonkeyCoin Genesis Block - 1759755336 - Unique Blockchain Launch - 7514",
        "046c3f2edbdd13a204b8badb463ef00e7983bde08649f2609b1f6a0fee13e23bd9",
        1759755336,
        0x20001fff,  // Mainnet difficulty
        4,           // Mainnet version
        50000000000LL  // 500 coins in satoshis
    );
    
    cout << endl;
    cout << "Starting testnet genesis block mining..." << endl;
    
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
    
    cout << endl;
    cout << "Mining complete! Use these values to update chainparams.cpp" << endl;
    cout << "Remember to remove the mining code from the daemon after updating!" << endl;
    
    return 0;
}