# Genesis Block Mining Guide for HashmonkeyCoin

## Overview

This guide explains how to mine new genesis blocks for all networks (Mainnet, Testnet, Regtest) using the new **GhostRiderV2 POW algorithm**.

## Why New Genesis Blocks?

Since we've changed the POW algorithm from the original 18-round GhostRider to the optimized 12-round GhostRiderV2, the old genesis block hashes are no longer valid. We need to mine new genesis blocks that are valid under the new algorithm.

## Prerequisites

1. **Updated Code**: All code changes for GhostRiderV2 must be complete
2. **Build Environment**: The project must compile successfully
3. **Current Timestamp**: We'll use the current Unix timestamp for the genesis blocks

## Step-by-Step Process

### Step 1: Update Timestamps

Update the timestamps in `src/chainparams.cpp` to the current time:

1. **Get current Unix timestamp:**
   ```bash
   date +%s
   ```

2. **Update timestamps in chainparams.cpp:**
   - **Mainnet**: Use current timestamp
   - **Testnet**: Use current timestamp + 1 second
   - **Regtest**: Use current timestamp + 2 seconds

   Example (if current timestamp is 1738368000):
   ```cpp
   // Mainnet
   genesis = CreateGenesisBlock(1738368000, 0, 0x207fffff, 4, 500 * COIN);
   
   // Testnet
   genesis = CreateTestnetGenesisBlock(1738368001, 0, 0x207fffff, 4, 500 * COIN);
   
   // Regtest
   genesis = CreateRegtestGenesisBlock(1738368002, 0, 0x207fffff, 4, 5000 * COIN);
   ```

### Step 2: Prepare for Mining

The assert statements for genesis hash verification are already commented out in the code. This allows the `VerifyGenesisPOW` function to automatically find valid nonces.

### Step 3: Build the Project

```bash
cd HashmonkeyCoin
./autogen.sh
./configure
make
```

### Step 4: Mine Genesis Blocks

The `VerifyGenesisPOW` function will automatically find valid nonces when the daemon starts. Here's how to mine for each network:

#### Option A: Mine All Networks in Regtest Mode

1. **Start regtest daemon:**
   ```bash
   ./src/hashmonkeycoind -regtest -printtoconsole
   ```

2. **Check the console output** for messages like:
   ```
   VerifyGenesisPOW: Hash doesn't match expected. Searching for valid POW nonce...
   VerifyGenesisPOW: Found valid POW nonce: 12345
      Block hash: 0x...
      POW hash: 0x...
   ```

3. **Get the genesis block info:**
   ```bash
   ./src/hashmonkeycoin-cli -regtest getblockhash 0
   ./src/hashmonkeycoin-cli -regtest getblock $(./src/hashmonkeycoin-cli -regtest getblockhash 0)
   ```

4. **Extract the genesis hash and merkle root** from the output

#### Option B: Use a Custom Mining Script

You can create a simple C++ program that uses the same genesis block creation logic to mine genesis blocks faster. The `VerifyGenesisPOW` function in `chainparams.cpp` already contains the mining logic.

### Step 5: Update chainparams.cpp with New Genesis Hashes

After mining, update `src/chainparams.cpp` with the new genesis block information:

1. **Update expected hashes:**
   ```cpp
   // Mainnet
   const uint256 expectedMainnetHash = uint256S("0x..."); // Your mined hash
   
   // Testnet
   const uint256 expectedTestnetHash = uint256S("0x..."); // Your mined hash
   
   // Regtest
   const uint256 expectedRegtestHash = uint256S("0x..."); // Your mined hash
   ```

2. **Update merkle roots:**
   ```cpp
   // Mainnet
   assert(genesis.hashMerkleRoot == uint256S("0x...")); // Your mined merkle root
   
   // Testnet
   assert(genesis.hashMerkleRoot == uint256S("0x...")); // Your mined merkle root
   ```

3. **Uncomment the assert statements** that verify genesis block hashes

4. **Update the nonce values** in the CreateGenesisBlock calls to match the found nonces

### Step 6: Verify Genesis Blocks

After updating the code:

1. **Rebuild the project:**
   ```bash
   make clean
   make
   ```

2. **Test each network:**
   ```bash
   # Test mainnet
   ./src/hashmonkeycoind -printtoconsole
   # Check that it starts without errors
   
   # Test testnet
   ./src/hashmonkeycoind -testnet -printtoconsole
   # Check that it starts without errors
   
   # Test regtest
   ./src/hashmonkeycoind -regtest -printtoconsole
   # Check that it starts without errors
   ```

3. **Verify genesis block info:**
   ```bash
   # For each network, verify:
   ./src/hashmonkeycoin-cli getblockhash 0
   ./src/hashmonkeycoin-cli getblock $(./src/hashmonkeycoin-cli getblockhash 0)
   ```

## Genesis Block Parameters

### Mainnet
- **Message**: "HashmonkeyCoin Mainnet Genesis Block - GhostRiderV2 POW - The beginning of HMNY blockchain - https://hashmonkeys.cloud/ - January 2025"
- **Difficulty**: 0x207fffff (easier for genesis)
- **Reward**: 500 HMNY
- **Version**: 4

### Testnet
- **Message**: "HashmonkeyCoin Testnet Genesis Block - GhostRiderV2 POW - Testing the HMNY blockchain - https://hashmonkeys.cloud/ - January 2025"
- **Difficulty**: 0x207fffff (easier for genesis)
- **Reward**: 500 HMNY
- **Version**: 4

### Regtest
- **Message**: "HashmonkeyCoin Regtest Genesis Block - GhostRiderV2 POW - Local testing network - https://hashmonkeys.cloud/ - January 2025"
- **Difficulty**: 0x207fffff (easier for genesis)
- **Reward**: 5000 HMNY (higher for testing)
- **Version**: 4

## Troubleshooting

### Issue: Genesis block hash doesn't match

**Solution**: The `VerifyGenesisPOW` function will automatically search for a valid nonce. Just let it run - it will find one eventually (with difficulty 0x207fffff, it should be quick).

### Issue: Daemon crashes on startup

**Solution**: Make sure all assert statements are commented out during mining. After mining, update the expected hashes and uncomment the asserts.

### Issue: Can't find valid nonce

**Solution**: With difficulty 0x207fffff, finding a valid nonce should be very fast (seconds to minutes). If it's taking too long, check that:
- The POW algorithm is correctly implemented
- The timestamp is valid
- The difficulty bits are correct

## Notes

- The genesis block messages have been updated to reflect GhostRiderV2
- All networks use the same genesis output script (public key)
- The difficulty is set low (0x207fffff) to make genesis block mining fast
- After genesis, difficulty adjusts normally according to the consensus rules

## Next Steps After Mining

1. ✅ Update genesis block hashes in chainparams.cpp
2. ✅ Update merkle roots in chainparams.cpp
3. ✅ Uncomment assert statements
4. ✅ Test all networks
5. ✅ Commit the changes
6. ✅ Document the genesis block information

## Example Output

After successful mining, you should see output like:

```
VerifyGenesisPOW: Found valid POW nonce: 12345
   Block hash: 0xabc123def456...
   POW hash: 0x789abc123def...
```

Then update chainparams.cpp with:
```cpp
genesis = CreateGenesisBlock(1738368000, 12345, 0x207fffff, 4, 500 * COIN);
const uint256 expectedMainnetHash = uint256S("0xabc123def456...");
```

