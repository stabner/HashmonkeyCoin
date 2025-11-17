# Testing Guide - POW Optimization Without Interfering with Main Blockchain

## ✅ Safe Testing Methods

### Method 1: Regtest Mode (RECOMMENDED - Completely Isolated)

**Regtest** creates a completely isolated local blockchain that doesn't connect to any network.

#### Setup Regtest Environment

1. **Create a separate data directory:**
```bash
# Windows PowerShell
mkdir C:\Users\thest\Desktop\HMNY2-Copy-Test
mkdir C:\Users\thest\Desktop\HMNY2-Copy-Test\regtest

# Or use a different path entirely
```

2. **Start hashmonkeycoind in regtest mode:**
```bash
cd "C:\Users\thest\Desktop\HMNY2 - Copy\HashmonkeyCoin\src"

# Start daemon in regtest mode with separate data directory
.\hashmonkeycoind.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" -daemon

# Or if you want to see output:
.\hashmonkeycoind.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test"
```

3. **Use hashmonkeycoin-cli for regtest:**
```bash
# Connect to regtest node
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" getblockchaininfo

# Generate blocks (regtest allows instant block generation)
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" generate 100

# Check block hashes
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" getblockhash 1
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" getblock <hash>
```

4. **Test mining:**
```bash
# Start mining in regtest
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" setgenerate true 1

# Check mining info
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" getmininginfo
```

#### Advantages of Regtest:
- ✅ **Completely isolated** - No network connection
- ✅ **Instant block generation** - Test quickly
- ✅ **No interference** - Won't affect mainnet or testnet
- ✅ **Full control** - You control difficulty, block times, etc.
- ✅ **Easy cleanup** - Just delete the data directory

---

### Method 2: Separate Testnet (If Available)

If you have a separate testnet running, you can test there:

```bash
# Use testnet with separate data directory
.\hashmonkeycoind.exe -testnet -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" -daemon

# Connect to testnet
.\hashmonkeycoin-cli.exe -testnet -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" getblockchaininfo
```

⚠️ **Warning:** This will only work if ALL nodes on testnet upgrade. Otherwise, you'll be on a fork.

---

### Method 3: Unit Tests (Test Hash Function Directly)

Test the hash function itself without running a full node:

#### Run Unit Tests:
```bash
cd "C:\Users\thest\Desktop\HMNY2 - Copy\HashmonkeyCoin"

# Compile tests
make check

# Or run specific test
.\src\test\test_hashmonkeycoin.exe --log_level=all --run_test=hash_tests
```

#### Create a Simple Test Program:

Create `test_pow_hash.cpp`:
```cpp
#include <hash.h>
#include <uint256.h>
#include <iostream>
#include <iomanip>

int main() {
    // Test data (block header)
    std::vector<uint8_t> blockHeader(80, 0);
    blockHeader[0] = 0x01; // Version
    // ... fill with test data
    
    uint256 prevBlockHash = uint256S("0000000000000000000000000000000000000000000000000000000000000000");
    
    // Test new hash function
    uint256 hash = HashGR(blockHeader.begin(), blockHeader.end(), prevBlockHash);
    
    std::cout << "Hash: " << hash.ToString() << std::endl;
    
    // Compare with expected (if you have reference)
    // BOOST_CHECK_EQUAL(hash, expectedHash);
    
    return 0;
}
```

---

### Method 4: Benchmark Tests

Test performance without affecting blockchain:

```bash
# Run benchmarks
cd "C:\Users\thest\Desktop\HMNY2 - Copy\HashmonkeyCoin\src"

# Compile benchmark
make bench

# Run hash benchmark
.\bench\bench_hashmonkeycoin.exe -filter="HASH_GR.*"
```

---

## 📋 Complete Testing Checklist

### Phase 1: Compilation & Unit Tests
- [ ] Code compiles without errors
- [ ] All existing unit tests pass
- [ ] Create new unit test for 12-round hash
- [ ] Verify hash output format is correct

### Phase 2: Regtest Testing
- [ ] Start regtest node
- [ ] Generate blocks successfully
- [ ] Verify block hashes are valid
- [ ] Test block validation
- [ ] Test mining with new algorithm
- [ ] Verify difficulty adjustment works
- [ ] Test reorgs (if applicable)

### Phase 3: Performance Testing
- [ ] Benchmark hash function
- [ ] Compare performance vs old algorithm
- [ ] Test on different hardware:
  - [ ] AMD CPU
  - [ ] Intel CPU
  - [ ] NVIDIA GPU
  - [ ] AMD GPU
- [ ] Verify performance improvements match expectations

### Phase 4: Integration Testing
- [ ] Test with wallet
- [ ] Test RPC commands
- [ ] Test block explorer (if applicable)
- [ ] Test mining pool integration (if applicable)

---

## 🔧 Quick Start: Regtest Testing Script

Create `test_regtest.bat` (Windows):

```batch
@echo off
echo Starting HashmonkeyCoin Regtest Test...

set TEST_DIR=C:\Users\thest\Desktop\HMNY2-Copy-Test
set COIN_DIR=C:\Users\thest\Desktop\HMNY2 - Copy\HashmonkeyCoin\src

REM Create test directory
if not exist "%TEST_DIR%" mkdir "%TEST_DIR%"
if not exist "%TEST_DIR%\regtest" mkdir "%TEST_DIR%\regtest"

REM Start daemon
echo Starting daemon...
start /B "%COIN_DIR%\hashmonkeycoind.exe" -regtest -datadir="%TEST_DIR%" -daemon

REM Wait for daemon to start
timeout /t 5

REM Generate blocks
echo Generating test blocks...
"%COIN_DIR%\hashmonkeycoin-cli.exe" -regtest -datadir="%TEST_DIR%" generate 10

REM Get info
echo Block chain info:
"%COIN_DIR%\hashmonkeycoin-cli.exe" -regtest -datadir="%TEST_DIR%" getblockchaininfo

echo.
echo Testing complete!
echo To stop: "%COIN_DIR%\hashmonkeycoin-cli.exe" -regtest -datadir="%TEST_DIR%" stop
pause
```

---

## 🧹 Cleanup

After testing, clean up:

```bash
# Stop daemon
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" stop

# Delete test data directory (optional)
# Remove-Item -Recurse -Force "C:\Users\thest\Desktop\HMNY2-Copy-Test"
```

---

## ⚠️ Important Notes

1. **Regtest is completely isolated** - It won't affect mainnet or testnet
2. **Use separate data directory** - Prevents any accidental conflicts
3. **Test thoroughly** - Don't deploy to mainnet until all tests pass
4. **Compare hash outputs** - Verify new algorithm produces valid hashes
5. **Performance benchmarks** - Ensure improvements match expectations

---

## 🐛 Troubleshooting

### Daemon won't start:
- Check if port is already in use
- Check data directory permissions
- Look at debug.log in data directory

### Blocks won't generate:
- Ensure daemon is fully started
- Check RPC connection
- Verify regtest mode is active

### Hash validation fails:
- Check if hash function is correct
- Verify block header format
- Compare with reference implementation

