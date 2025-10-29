// src/genesis_miner.cpp
// Minimal genesis miner for Raptoreum-based forks.
// Build this inside the project's src/ tree and link with the project objects.

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

#include "chainparams.h"
#include "primitives/block.h"
#include "primitives/transaction.h"
#include "consensus/params.h"
#include "pubkey.h"
#include "streams.h"
#include "util/strencodings.h"
#include "util/system.h"
#include "crypto/common.h"
#include "hash.h"
#include "arith_uint256.h"
#include "consensus/merkle.h"

using namespace std;

// Utility: create a coinbase transaction with pszTimestamp in scriptSig
CTransaction CreateGenesisCoinbaseTx(const string& pszTimestamp, const CScript& genesisOutputScript, const CAmount genesisReward)
{
    CMutableTransaction tx;
    tx.nVersion = 1;
    tx.vin.resize(1);
    tx.vout.resize(1);

    // scriptSig: <difficulty> <pszTimestamp>
    CScript scriptSig;
    scriptSig << OP_0 << std::vector<unsigned char>(pszTimestamp.begin(), pszTimestamp.end());
    tx.vin[0].scriptSig = scriptSig;

    tx.vout[0].nValue = genesisReward;
    tx.vout[0].scriptPubKey = genesisOutputScript;

    return CTransaction(tx);
}

// Build a genesis block (similar to CreateGenesisBlock found in many coin sources)
CBlock CreateGenesisBlock(const string& pszTimestamp, const CScript& genesisOutputScript,
                          uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount genesisReward)
{
    CTransaction txNew = CreateGenesisCoinbaseTx(pszTimestamp, genesisOutputScript, genesisReward);

    CBlock genesis;
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(txNew));
    genesis.hashPrevBlock.SetNull();

    // compute merkle root
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);

    return genesis;
}

int main(int argc, char** argv)
{
    // --- CONFIGURE THESE for HashmonkeyCoin (or accept via args) ---
    string pszTimestamp = "HashmonkeyCoin Genesis Block - October 28, 2024 - The future of decentralized finance";
    // Use the same pubkey as in chainparams.cpp
    std::vector<unsigned char> pubkeyBytes = ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9");
    CScript genesisOutputScript = CScript() << pubkeyBytes << OP_CHECKSIG;

    uint32_t startTime = 1730070000;  // October 28, 2024
    uint32_t nTime = startTime;       // initial time
    uint32_t nNonce = 0;              // start nonce
    uint32_t nBits  = 0x20001fff;     // HashmonkeyCoin difficulty bits
    int32_t nVersion = 4;
    CAmount genesisReward = 500 * COIN; // 500 HMNY

    // Optionally get params from argv (timestamp text, time, bits)
    for (int i = 1; i < argc; ++i) {
        string a = argv[i];
        if (a == "-t" && i+1 < argc) { pszTimestamp = argv[++i]; }
        else if (a == "-time" && i+1 < argc) { nTime = (uint32_t)atoi(argv[++i]); }
        else if (a == "-bits" && i+1 < argc) { nBits = (uint32_t)strtoul(argv[++i], nullptr, 0); }
        else if (a == "-nonce" && i+1 < argc) { nNonce = (uint32_t)strtoul(argv[++i], nullptr, 0); }
    }

    cout << "Starting HashmonkeyCoin genesis miner\n";
    cout << "pszTimestamp: " << pszTimestamp << "\n";
    cout << "start time: " << nTime << " bits: 0x" << hex << nBits << dec << "\n";

    // Convert bits to target
    arith_uint256 target;
    target.SetCompact(nBits);

    uint64_t total = 0;
    while (true) {
        CBlock genesis = CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
        // IMPORTANT: GetHash() should use the coin's PoW (GhostRider) if this program is built against the main project.
        uint256 hash = genesis.GetHash(); // uses underlying PoW implementation in the project
        arith_uint256 ahash = UintToArith256(hash);

        if (ahash <= target) {
            cout << "FOUND genesis!\n";
            cout << "nTime: " << nTime << "\n";
            cout << "nNonce: " << nNonce << "\n";
            cout << "hash: " << hash.ToString() << "\n";
            cout << "merkle: " << genesis.hashMerkleRoot.ToString() << "\n";
            break;
        }

        ++nNonce;
        ++total;
        if ((total & 0xFFFFF) == 0) {
            cout << "nNonce=" << nNonce << "  hash=" << hash.ToString().substr(0,12) << "  targetPrefix=" << target.GetHex().substr(0,8) << "\r" << flush;
        }

        // Optional: bump time periodically to avoid stuck on same time (many genesis scripts do this)
        if (nNonce == 0xFFFFFFFFu) {
            nTime += 1;
            nNonce = 0;
        }
    }

    return 0;
}
