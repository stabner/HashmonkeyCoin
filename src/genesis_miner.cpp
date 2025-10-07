#include <iostream>
#include "chainparams.h"
#include "primitives/block.h"
#include "consensus/merkle.h"
#include "uint256.h"
#include "arith_uint256.h"
#include "script/script.h"
#include "util/system.h"

int main() {
    const char* pszTimestamp = "HashmonkeyCoin launches October 2025";
    const CScript genesisOutputScript = CScript() << ParseHex(
        "04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f"
    ) << OP_CHECKSIG;

    CAmount genesisReward = 500 * COIN; // HashmonkeyCoin uses 500 coins
    uint32_t nTime = 1759755699;
    uint32_t nNonce = 0;
    uint32_t nBitsMain = 0x20001fff;
    uint32_t nBitsTest = 0x207fffff;
    int32_t nVersion = 4;

    bool mineTestnet = false; // set to true for testnet
    arith_uint256 bnTarget;
    bnTarget.SetCompact(mineTestnet ? nBitsTest : nBitsMain);
    uint32_t nBits = mineTestnet ? nBitsTest : nBitsMain;

    std::cout << "Mining " << (mineTestnet ? "testnet" : "mainnet") << " genesis block..." << std::endl;

    for (uint32_t nNonce = 0; nNonce < UINT32_MAX; nNonce++) {
        CBlock genesis = CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
        uint256 hash = genesis.GetPOWHash(); // Use POW hash for Raptoreum
        if (UintToArith256(hash) <= bnTarget) {
            std::cout << "\n✅ Found genesis block!" << std::endl;
            std::cout << "Hash: " << hash.GetHex() << std::endl;
            std::cout << "Merkle Root: " << genesis.hashMerkleRoot.GetHex() << std::endl;
            std::cout << "Time: " << nTime << std::endl;
            std::cout << "Nonce: " << nNonce << std::endl;
            std::cout << "Bits: 0x" << std::hex << nBits << std::dec << std::endl;
            return 0;
        }
        if (nNonce % 100000 == 0) {
            std::cout << "Nonce: " << nNonce << " | Hash: " << hash.GetHex() << std::endl;
        }
    }

    std::cout << "❌ No valid genesis block found." << std::endl;
    return 0;
}