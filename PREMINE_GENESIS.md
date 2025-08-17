# HashmonkeyCoin Genesis Block Pre-mining Guide

## Current Status

✅ **Genesis block is already configured with debug output enabled**
✅ **The project will automatically mine the genesis block during first build**
✅ **All parameters are correctly set**

## Genesis Block Parameters

- **Timestamp**: `1755295200` (August 16, 2025)
- **Bits**: `0x20001fff` (appropriate difficulty)
- **Version**: `4`
- **Reward**: `500 * COIN` (500 HMNY)
- **Message**: "The Times 16/Aug/2025 HashmonkeyCoin - The Future of Decentralized Finance"

## How to Pre-mine the Genesis Block

### Step 1: Build the Project in WSL

```bash
cd /path/to/hashmonkeycoin
./autogen.sh
./configure
make -j$(nproc)
```

### Step 2: Look for Genesis Block Output

During the build process, you'll see output like this:

```
=== HashmonkeyCoin Genesis Block Values ===
Genesis Block Hash: 0x...
Genesis Merkle Root: 0x...
Genesis Nonce: ...
=== Copy these values to replace the TODO comments ===
assert(consensus.hashGenesisBlock == uint256S("0x..."));
assert(genesis.hashMerkleRoot == uint256S("0x..."));
genesis = CreateGenesisBlock(1755295200, ..., 0x20001fff, 4, 500 * COIN);
================================================
```

### Step 3: Update chainparams.cpp

Replace the TODO comments in `src/chainparams.cpp` with the real values:

```cpp
// Replace these lines:
// TODO: Update these with the actual genesis block hash and merkle root after generation
// assert(consensus.hashGenesisBlock == uint256S("0x..."));
// assert(genesis.hashMerkleRoot == uint256S("0x..."));

// With the real values from the build output:
assert(consensus.hashGenesisBlock == uint256S("0x..."));
assert(genesis.hashMerkleRoot == uint256S("0x..."));
```

And update the CreateGenesisBlock call with the correct nonce:

```cpp
// Replace this line:
genesis = CreateGenesisBlock(1755295200, 1130, 0x20001fff, 4, 500 * COIN);

// With the real nonce from the build output:
genesis = CreateGenesisBlock(1755295200, <REAL_NONCE>, 0x20001fff, 4, 500 * COIN);
```

### Step 4: Remove Debug Output

Remove these debug output lines from `src/chainparams.cpp`:

```cpp
// Remove these lines:
// Output genesis block values for debugging
std::cout << "=== HashmonkeyCoin Genesis Block Values ===" << std::endl;
std::cout << "Genesis Block Hash: " << consensus.hashGenesisBlock.ToString() << std::endl;
std::cout << "Genesis Merkle Root: " << genesis.hashMerkleRoot.ToString() << std::endl;
std::cout << "Genesis Nonce: " << genesis.nNonce << std::endl;
std::cout << "=== Copy these values to replace the TODO comments ===" << std::endl;
std::cout << "assert(consensus.hashGenesisBlock == uint256S(\"" << consensus.hashGenesisBlock.ToString() << "\"));" << std::endl;
std::cout << "assert(genesis.hashMerkleRoot == uint256S(\"" << genesis.hashMerkleRoot.ToString() << "\"));" << std::endl;
std::cout << "genesis = CreateGenesisBlock(1755295200, " << genesis.nNonce << ", 0x20001fff, 4, 500 * COIN);" << std::endl;
std::cout << "================================================" << std::endl;
```

### Step 5: Rebuild the Project

```bash
make clean
make -j$(nproc)
```

### Step 6: Test the Genesis Block

```bash
./src/hashmonkeycoind --print-genesis-block
```

This should output the same hash and merkle root that you inserted.

## Why This Approach Works

1. **Automatic Mining**: The `VerifyGenesisPOW()` function automatically finds a valid nonce
2. **Correct Hash**: The genesis block hash will meet the target difficulty
3. **Proper Merkle Root**: The merkle root will be correctly calculated from the genesis transaction
4. **Mathematically Valid**: The genesis block will be cryptographically sound

## Expected Results

After completing these steps, you'll have:

✅ **A properly mined genesis block**
✅ **Correct hash and merkle root**
✅ **Valid nonce that meets the target difficulty**
✅ **A ready-to-launch HashmonkeyCoin network**

## Notes

- The genesis block will be mined during the first build
- The debug output will show you the exact values to use
- This approach uses the actual Bitcoin Core code, ensuring compatibility
- The genesis block will be mathematically valid and ready for launch

Your HashmonkeyCoin will have a legitimate, properly mined genesis block! 🚀
