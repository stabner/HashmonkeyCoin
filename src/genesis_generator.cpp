// HashmonkeyCoin Genesis Block Generator
// Based on Raptoreum's approach but with our unique values

#include <chainparams.h>
#include <consensus/merkle.h>
#include <arith_uint256.h>
#include <iostream>
#include <string>

// Copy of CreateGenesisBlock function from chainparams.cpp
static CBlock CreateGenesisBlock(const char *pszTimestamp, const CScript &genesisOutputScript, uint32_t nTime, uint32_t nNonce,
                   uint32_t nBits, int32_t nVersion, const CAmount &genesisReward) {
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4)
                                       << std::vector<unsigned char>((const unsigned char *) pszTimestamp,
                                                                     (const unsigned char *) pszTimestamp +
                                                                     strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount &genesisReward) {
    const char *pszTimestamp = "The Times 06/Sep/2025 HashMonkey awakens";
    const CScript genesisOutputScript = CScript() << ParseHex(
            "040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9")
                                                  << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

// Genesis block finder function
static uint32_t FindGenesisNonce(uint32_t nTime, uint32_t nBits, int32_t nVersion, const CAmount &genesisReward) {
    std::cout << "🔍 Mining genesis block..." << std::endl;
    std::cout << "nTime: " << nTime << std::endl;
    std::cout << "nBits: 0x" << std::hex << nBits << std::dec << std::endl;
    std::cout << "nVersion: " << nVersion << std::endl;
    std::cout << "genesisReward: " << genesisReward << std::endl;
    
    arith_uint256 bnTarget;
    bnTarget.SetCompact(nBits);
    
    CBlock genesis = CreateGenesisBlock(nTime, 0, nBits, nVersion, genesisReward);
    
    uint32_t nonce = 0;
    while (true) {
        genesis.nNonce = nonce;
        uint256 hash = genesis.GetHash();
        
        if (UintToArith256(hash) <= bnTarget) {
            std::cout << "\n✅ FOUND GENESIS BLOCK!" << std::endl;
            std::cout << "nTime: " << genesis.nTime << std::endl;
            std::cout << "nNonce: " << genesis.nNonce << std::endl;
            std::cout << "nBits: 0x" << std::hex << genesis.nBits << std::dec << std::endl;
            std::cout << "hashGenesisBlock: " << genesis.GetHash().ToString() << std::endl;
            std::cout << "hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << std::endl;
            return nonce;
        }
        
        ++nonce;
        if (nonce == 0) {
            std::cout << "⚠️ Nonce wrapped, incrementing time" << std::endl;
            ++nTime;
            genesis.nTime = nTime;
        }
        
        // Progress indicator
        if (nonce % 100000 == 0) {
            std::cout << "Mining... nonce: " << nonce << std::endl;
        }
    }
}

int main() {
    std::cout << "🚀 HashmonkeyCoin Genesis Block Generator" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // HashmonkeyCoin specific parameters
    const uint32_t nBits = 0x20001fff;
    const int32_t nVersion = 4;
    const CAmount genesisReward = 500 * COIN;
    
    // Our unique timestamps (100 second intervals)
    const uint32_t mainnetTime = 1755295200;  // Our mainnet timestamp
    const uint32_t testnetTime = 1755295300;  // Our testnet timestamp  
    const uint32_t devnetTime = 1755295400;   // Our devnet timestamp
    
    std::cout << "\n🔷 MAINNET GENESIS BLOCK:" << std::endl;
    std::cout << "=========================" << std::endl;
    uint32_t mainnetNonce = FindGenesisNonce(mainnetTime, nBits, nVersion, genesisReward);
    
    std::cout << "\n🔶 TESTNET GENESIS BLOCK:" << std::endl;
    std::cout << "=========================" << std::endl;
    uint32_t testnetNonce = FindGenesisNonce(testnetTime, nBits, nVersion, genesisReward);
    
    std::cout << "\n🟣 DEVNET GENESIS BLOCK:" << std::endl;
    std::cout << "========================" << std::endl;
    uint32_t devnetNonce = FindGenesisNonce(devnetTime, nBits, nVersion, genesisReward);
    
    std::cout << "\n📋 FINAL VALUES FOR chainparams.cpp:" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "MAINNET: CreateGenesisBlock(" << mainnetTime << ", " << mainnetNonce << ", 0x" << std::hex << nBits << std::dec << ", " << nVersion << ", " << genesisReward << " * COIN);" << std::endl;
    std::cout << "TESTNET: CreateGenesisBlock(" << testnetTime << ", " << testnetNonce << ", 0x" << std::hex << nBits << std::dec << ", " << nVersion << ", " << genesisReward << " * COIN);" << std::endl;
    std::cout << "DEVNET:  CreateGenesisBlock(" << devnetTime << ", " << devnetNonce << ", 0x" << std::hex << nBits << std::dec << ", " << nVersion << ", " << genesisReward << " * COIN);" << std::endl;
    
    return 0;
}
