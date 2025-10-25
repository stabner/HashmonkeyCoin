# Fsociety Fork Analysis: Complete Changes from Raptoreum

## Overview
This document analyzes all the changes made by the successful fsociety fork from the original Raptoreum codebase. Fsociety (FSC) is a working fork that demonstrates the complete process of creating a new cryptocurrency from Raptoreum.

## 1. BRANDING & NAMING CHANGES

### 1.1 Project Name Changes
- **Raptoreum** → **Fsociety**
- **RTM** → **FSC** (ticker symbol)
- **raptoreum** → **fsociety** (all lowercase references)

### 1.2 Copyright & License Headers
```cpp
// Original Raptoreum:
// Copyright (c) 2020-2023 The Raptoreum developers

// Fsociety:
// Copyright (c) 2020-2022 The Fsociety developers
```

### 1.3 Build Properties
```properties
# Original Raptoreum:
snapshot-version=2.0.3.99-SNAPSHOT
release-version=2.0.3.01
candidate-version=2.0.3.01-candidate

# Fsociety:
snapshot-version=0.0.1.01-SNAPSHOT
release-version=0.0.1.01
candidate-version=0.0.1.01-candidate
```

### 1.4 README.md Changes
- **Title**: "Raptoreum Core Latest v2.0.3" → "Fsociety Core Latest v0.0.1.02"
- **Description**: Complete rewrite focusing on fsociety's mission
- **Website**: Links changed to fsocietychain.com
- **Whitepaper**: New whitepaper URL

## 2. GENESIS BLOCK CHANGES

### 2.1 Genesis Block Message
```cpp
// Original Raptoreum:
"The Times 22/Jan/2018 Raptoreum is name of the game for new generation of firms"

// Fsociety:
"[FSC] We are fsociety. We are finally free. A world that belong to us again. [2023]"
```

### 2.2 Genesis Block Parameters

#### Mainnet Genesis:
```cpp
// Original Raptoreum:
genesis = CreateGenesisBlock(1614369600, 1130, 0x20001fff, 4, 5000 * COIN);

// Fsociety:
genesis = CreateGenesisBlock(1678810092, 3024, 0x20001fff, 4, 5000 * COIN);
```

#### Regtest Genesis:
```cpp
// Original Raptoreum:
genesis = CreateGenesisBlock(1614369600, 2, 0x207fffff, 4, 5000 * COIN);

// Fsociety:
genesis = CreateGenesisBlock(1678810092, 1584, 0x20001fff, 4, 5000 * COIN);
```

### 2.3 Genesis Block Validation
```cpp
// Fsociety uses simple approach without complex POW verification:
genesis = CreateGenesisBlock(1678810092, 3024, 0x20001fff, 4, 5000 * COIN);
consensus.hashGenesisBlock = genesis.GetHash();
assert(consensus.hashGenesisBlock == uint256S("0xf59828cf4def471df48f8453a6d22706637456b1f5bda5bc6debf7d6d9583ad9"));
assert(genesis.hashMerkleRoot == uint256S("0x4c230a37cc3633079058a414a5d17bfcb2c0b15cf6e56a41ceff85771b7acd68"));
```

## 3. NETWORK PARAMETER CHANGES

### 3.1 Message Start Magic Bytes
```cpp
// Original Raptoreum:
pchMessageStart[0] = 0x72; // r
pchMessageStart[1] = 0x74; // t
pchMessageStart[2] = 0x6d; // m
pchMessageStart[3] = 0x2e; // .

// Fsociety:
pchMessageStart[0] = 0x75; // u
pchMessageStart[1] = 0x78; // x
pchMessageStart[2] = 0x79; // y
pchMessageStart[3] = 0x71; // q
```

### 3.2 Network Ports
```cpp
// Original Raptoreum:
nDefaultPort = 10226;  // Mainnet
nDefaultPort = 19899;  // Regtest

// Fsociety:
nDefaultPort = 15277;  // Mainnet
nDefaultPort = 17989;  // Regtest
```

### 3.3 Address Prefixes
```cpp
// Original Raptoreum:
base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 60);  // 'r'
base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);  // '7'
base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 128);     // '7' or 'X'

// Fsociety:
base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 35);  // 'F'
base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 95);  // 'f'
base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 18);      // '3'
```

## 4. CONSENSUS PARAMETER CHANGES

### 4.1 Block Rewards
```cpp
// Both use 5000 * COIN for genesis, but different reward structures
// Fsociety maintains similar reward structure to Raptoreum
```

### 4.2 Smartnode Collaterals
```cpp
// Original Raptoreum:
consensus.nCollaterals = SmartnodeCollaterals(
    {{88720, 600000 * COIN},
     {132720, 800000 * COIN},
     {176720, 1000000 * COIN},
     {220720, 1250000 * COIN},
     {264720, 1500000 * COIN},
     {INT_MAX, 1800000 * COIN}},
    {{5761, 0}, {INT_MAX, 20}}
);

// Fsociety:
consensus.nCollaterals = SmartnodeCollaterals(
    {{88580, 700000 * COIN},
     {132580, 900000 * COIN},
     {176580, 1100000 * COIN},
     {220580, 1350000 * COIN},
     {264580, 1600000 * COIN},
     {INT_MAX, 1900000 * COIN}},
    {{8580, 0}, {INT_MAX, 45}}
);
```

### 4.3 Founder/Dev Fees
```cpp
// Original Raptoreum:
std::vector<FounderRewardStructure> rewardStructures = {{INT_MAX, 5}}; // 5% forever
consensus.nFounderPayment = FounderPayment(rewardStructures, 250);

// Fsociety:
std::vector<FounderRewardStructure> rewardStructures = {{INT_MAX, 20}}; // 20% forever
consensus.nFounderPayment = FounderPayment(rewardStructures, 250);
```

### 4.4 Future Reward Share
```cpp
// Both use the same structure:
consensus.nFutureRewardShare = Consensus::FutureRewardShare(0.8, 0.2, 0.0);
// 80% miners, 20% smartnodes, 0% dev
```

## 5. SEED NODES & DNS

### 5.1 Mainnet Seed Nodes
```cpp
// Original Raptoreum:
vSeeds.emplace_back("lbdn.raptoreum.com");
vSeeds.emplace_back("51.89.21.112");

// Fsociety:
vSeeds.emplace_back("ns1.fsocietychain.com");
vSeeds.emplace_back("ns2.fsocietychain.com");
vSeeds.emplace_back("ns3.fsocietychain.com");
vSeeds.emplace_back("ns4.fsocietychain.com");
vSeeds.emplace_back("ns5.fsocietychain.com");
vSeeds.emplace_back("ns6.fsocietychain.com");
vSeeds.emplace_back("ns7.fsocietychain.com");
vSeeds.emplace_back("ns8.fsocietychain.com");
vSeeds.emplace_back("ns9.fsocietychain.com");
vSeeds.emplace_back("ns10.fsocietychain.com");
```

## 6. SPORK ADDRESSES

### 6.1 Mainnet Spork Addresses
```cpp
// Original Raptoreum:
vSporkAddresses = {"rSporkAddress..."};

// Fsociety:
vSporkAddresses = {"F9MADUJXkDWj3r5BQoyZozjYXbgvxAR8sA"};
```

## 7. CHECKPOINT DATA

### 7.1 Mainnet Checkpoints
```cpp
// Fsociety has extensive checkpoint data:
checkpointData = {
    {{10, uint256S("0x3c64db6a5c8a1594bb077c2d764b3066e31e703b4ebfea29ecb146087fbbd14e")},
     {100, uint256S("0x296f91907fba832b1155e34fafa111764400de6656a30293a37b99541584c2de")},
     {1000, uint256S("0x39d2ade77baa33dc9293ba897a70d80d6262db342d84012099c0caef250022df")},
     {5000, uint256S("0xf7c822b5eb91eee35570b4035708ecac12965321b1bbba8ce217f5e9f234ee81")},
     {10000, uint256S("0x3ae1a0dbeb895b50270df81a8ec345ab7d64f90a3b27329c3c691b25d993d00e")},
     {40000, uint256S("0x347fbbf59e840438e39dfbe15ad7a3237f2f9b5e211261e73137fac089a76dff")},
     {60000, uint256S("0xab7dba6b5debc53190d1b3347a40024e4e495c78f2c44dbe63e0f479a6082cf0")},
     {200000, uint256S("0x5a2de375120cd1e3592cf29986a1d073a07e046c7553d13b6f27f82202cac9e6")}}
};
```

## 8. CHAIN WORK & ASSUME VALID

### 8.1 Minimum Chain Work
```cpp
// Original Raptoreum:
consensus.nMinimumChainWork = uint256S("000000000000000000000000000000000000000000000000000eead474ccbc59");

// Fsociety:
consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // 0
```

### 8.2 Default Assume Valid
```cpp
// Original Raptoreum:
consensus.defaultAssumeValid = uint256S("ox6fb0b649723f51b67484019409fef94d077f17c8d88645e08c000b2e4fd3e28a");

// Fsociety:
consensus.defaultAssumeValid = uint256S("0x0008ac817801e43863d2c3fd53e4d3690536f01a938ac6199ab354a74e81bc92");
```

## 9. KEY SUCCESS FACTORS

### 9.1 Simple Genesis Block Approach
- **No complex POW verification** - Fsociety uses simple nonce values
- **Pre-calculated hashes** - Uses assert statements with known valid hashes
- **Debug printf statements** - Includes printf for troubleshooting

### 9.2 Complete Network Isolation
- **Unique magic bytes** - Completely different message start
- **Different ports** - No port conflicts with original
- **Different address prefixes** - No address confusion

### 9.3 Proper Seed Node Setup
- **Multiple DNS seeds** - 10 different seed nodes
- **Proper domain setup** - fsocietychain.com infrastructure

### 9.4 Conservative Parameter Changes
- **Similar reward structure** - Maintains proven economics
- **Gradual collateral increases** - Similar to original progression
- **Same consensus rules** - Maintains compatibility

## 10. CRITICAL LESSONS FOR HASHMONKEYCOIN

### 10.1 Genesis Block Strategy
1. **Use simple approach** - Don't overcomplicate POW verification
2. **Pre-calculate valid hashes** - Use assert statements with known values
3. **Add debug output** - Include printf statements for troubleshooting

### 10.2 Network Parameters
1. **Unique magic bytes** - Must be completely different
2. **Different ports** - Avoid conflicts
3. **Different address prefixes** - Clear separation

### 10.3 Infrastructure Requirements
1. **Seed nodes** - Need working DNS infrastructure
2. **Checkpoints** - Add checkpoint data for security
3. **Spork addresses** - Need valid spork addresses

### 10.4 Build System
1. **Version numbers** - Start fresh with new versioning
2. **Branding consistency** - Update all references
3. **Documentation** - Complete README and documentation updates

## 11. RECOMMENDED IMPLEMENTATION ORDER

1. **Network Parameters** - Change magic bytes, ports, addresses first
2. **Genesis Blocks** - Create new genesis blocks with simple approach
3. **Seed Nodes** - Set up DNS infrastructure
4. **Consensus Parameters** - Adjust rewards and collaterals
5. **Build System** - Update versioning and branding
6. **Testing** - Test each network (mainnet, testnet, regtest)
7. **Documentation** - Update all documentation

This analysis shows that fsociety successfully forked Raptoreum by making comprehensive but systematic changes while maintaining the core functionality and consensus rules that make the network work.
