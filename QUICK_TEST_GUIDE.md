# Quick Test Guide - Testing POW Optimization Safely

## ✅ Best Method: Regtest Mode (Completely Isolated)

**Regtest** is perfect for testing - it creates a completely isolated local blockchain that:
- ✅ **Never connects to any network**
- ✅ **Won't interfere with mainnet or testnet**
- ✅ **Allows instant block generation**
- ✅ **Easy to clean up** (just delete the data directory)

---

## 🚀 Quick Start (Windows)

### Option 1: Use the Test Script

1. **Compile the project first:**
```bash
cd "C:\Users\thest\Desktop\HMNY2 - Copy\HashmonkeyCoin"
# Follow your normal build process
```

2. **Run the test script:**
```bash
# Double-click or run:
test_regtest.bat
```

The script will:
- Create a test directory
- Start the daemon in regtest mode
- Generate test blocks
- Show block information
- Test the new POW algorithm

### Option 2: Manual Testing

1. **Create a test directory:**
```powershell
mkdir C:\Users\thest\Desktop\HMNY2-Copy-Test
```

2. **Start daemon in regtest mode:**
```bash
cd "C:\Users\thest\Desktop\HMNY2 - Copy\HashmonkeyCoin\src"

# Start daemon (background)
.\hashmonkeycoind.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" -daemon

# Or start in foreground to see output:
.\hashmonkeycoind.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test"
```

3. **Generate test blocks:**
```bash
# Generate 10 blocks instantly
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" generate 10

# Check blockchain info
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" getblockchaininfo

# Get a block hash to verify POW
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" getblockhash 1

# Get block details
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" getblock <hash>
```

4. **Test mining:**
```bash
# Get mining info
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" getmininginfo

# Start mining (if configured)
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" setgenerate true 1
```

5. **Stop daemon:**
```bash
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" stop
```

---

## 📊 What to Verify

### 1. **Block Generation Works**
- Blocks should generate instantly in regtest
- Block hashes should be valid
- Block count should increase

### 2. **POW Hash is Correct**
- Check block hashes are valid (not all zeros)
- Verify hash format is correct
- Compare with expected format

### 3. **Block Validation Works**
- Blocks should validate correctly
- Chain should be valid
- No errors in debug.log

### 4. **Performance (Optional)**
- Time how long hash calculation takes
- Compare with old algorithm (if you have reference)
- Verify it's faster on Intel/GPU

---

## 🧪 Unit Tests

Run unit tests to verify hash function:

```bash
cd "C:\Users\thest\Desktop\HMNY2 - Copy\HashmonkeyCoin"

# Run all tests
make check

# Or run specific test
.\src\test\test_hashmonkeycoin.exe --log_level=all
```

---

## 🔍 Debugging

### Check Logs
```bash
# View debug log
type "C:\Users\thest\Desktop\HMNY2-Copy-Test\regtest\debug.log"

# Or tail it (if you have tail command)
tail -f "C:\Users\thest\Desktop\HMNY2-Copy-Test\regtest\debug.log"
```

### Common Issues

**Daemon won't start:**
- Check if port 19995 is already in use
- Check data directory permissions
- Look at debug.log for errors

**Blocks won't generate:**
- Ensure daemon is fully started (wait 5-10 seconds)
- Check RPC connection
- Verify regtest mode is active

**Hash validation fails:**
- Check if hash function is correct
- Verify block header format
- Compare with reference implementation

---

## 🧹 Cleanup

After testing:

```bash
# Stop daemon
.\hashmonkeycoin-cli.exe -regtest -datadir="C:\Users\thest\Desktop\HMNY2-Copy-Test" stop

# Delete test data (optional)
Remove-Item -Recurse -Force "C:\Users\thest\Desktop\HMNY2-Copy-Test"
```

---

## ⚠️ Important Notes

1. **Regtest is completely isolated** - It will NEVER affect mainnet or testnet
2. **Use separate data directory** - Prevents any accidental conflicts
3. **Test thoroughly** - Don't deploy to mainnet until all tests pass
4. **Compare results** - Verify new algorithm produces valid hashes
5. **Performance benchmarks** - Ensure improvements match expectations

---

## 📝 Testing Checklist

- [ ] Code compiles without errors
- [ ] Daemon starts in regtest mode
- [ ] Blocks generate successfully
- [ ] Block hashes are valid
- [ ] Block validation works
- [ ] Mining works (if applicable)
- [ ] Unit tests pass
- [ ] Performance is acceptable
- [ ] No errors in debug.log

---

## 🎯 Next Steps After Testing

Once regtest testing is successful:

1. **Test on testnet** (if you have a private testnet)
2. **Benchmark performance** on different hardware
3. **Coordinate network upgrade** (if deploying to mainnet)
4. **Update miner software** to match new algorithm
5. **Monitor network** after deployment

---

## 💡 Tips

- **Start small**: Test with a few blocks first
- **Check logs**: Always check debug.log for errors
- **Verify hashes**: Make sure block hashes look correct
- **Test edge cases**: Try generating many blocks, reorgs, etc.
- **Compare**: If possible, compare with old algorithm output

