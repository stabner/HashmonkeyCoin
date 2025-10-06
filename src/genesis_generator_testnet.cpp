#include <iostream>
#include <chainparams.h>
#include <consensus/merkle.h>
#include <util/strencodings.h>
#include <primitives/block.h>
#include <primitives/transaction.h>
#include <script/script.h>
#include <arith_uint256.h>

int main() {
    const char* pszTimestamp = "HashmonkeyCoin Testnet Genesis Block - October 2025";
    
    // Create the genesis transaction
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4)
        << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = 500 * COIN; // HashmonkeyCoin testnet genesis reward
    txNew.vout[0].scriptPubKey = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;

    // Create the genesis block
    CBlock genesis;
    genesis.nTime = 1759752916; // Current timestamp
    genesis.nBits = 0x20001fff; // Raptoreum testnet difficulty target
    genesis.nNonce = 0;
    genesis.nVersion = 4; // Raptoreum version
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);

    // Set the target
    arith_uint256 hashTarget;
    hashTarget.SetCompact(genesis.nBits);

    std::cout << "HashmonkeyCoin Testnet Genesis Block Generator" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "Timestamp: " << pszTimestamp << std::endl;
    std::cout << "nTime: " << genesis.nTime << std::endl;
    std::cout << "nBits: 0x" << std::hex << genesis.nBits << std::endl;
    std::cout << "nVersion: " << std::dec << genesis.nVersion << std::endl;
    std::cout << "Genesis Reward: " << 500 * COIN << " satoshis" << std::endl;
    std::cout << std::endl;
    std::cout << "Searching for testnet genesis block..." << std::endl;

    // Mine for a valid nonce
    while (true) {
        genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
        uint256 hash = genesis.GetPOWHash(); // Use POW hash for Raptoreum

        if (UintToArith256(hash) <= hashTarget) {
            std::cout << std::endl;
            std::cout << "Found testnet genesis block!" << std::endl;
            std::cout << "============================" << std::endl;
            std::cout << "nTime: " << genesis.nTime << std::endl;
            std::cout << "nNonce: " << genesis.nNonce << std::endl;
            std::cout << "nBits: 0x" << std::hex << genesis.nBits << std::endl;
            std::cout << "nVersion: " << std::dec << genesis.nVersion << std::endl;
            std::cout << "hashGenesisBlock: " << hash.GetHex() << std::endl;
            std::cout << "hashMerkleRoot: " << genesis.hashMerkleRoot.GetHex() << std::endl;
            std::cout << std::endl;
            std::cout << "Copy these values to chainparams.cpp (testnet section):" << std::endl;
            std::cout << "genesis = CreateGenesisBlock(" << genesis.nTime << ", " << genesis.nNonce << ", 0x" << std::hex << genesis.nBits << ", " << std::dec << genesis.nVersion << ", 500 * COIN);" << std::endl;
            std::cout << "assert(consensus.hashGenesisBlock == uint256S(\"" << hash.GetHex() << "\"));" << std::endl;
            std::cout << "assert(genesis.hashMerkleRoot == uint256S(\"" << genesis.hashMerkleRoot.GetHex() << "\"));" << std::endl;
            break;
        }

        genesis.nNonce++;
        if (genesis.nNonce % 1000000 == 0) {
            std::cout << "Tried " << genesis.nNonce << " nonces...\r" << std::flush;
        }
        
        // Safety check to prevent infinite loop
        if (genesis.nNonce == 0) {
            std::cout << "Error: Nonce overflow! Try different parameters." << std::endl;
            break;
        }
    }

    return 0;
}
