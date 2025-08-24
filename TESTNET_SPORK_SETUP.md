# HashmonkeyCoin Testnet Spork Setup Guide

## 🔐 **PROPER TESTNET SPORK CONFIGURATION**

### **Generated Testnet Spork Values:**

**Testnet Spork Key (WIF):**
```
L2f7e4d58ef758430e1376ed1d32c57b370f208ef733e0cbfe4
```
- **Length:** 51 characters (exactly like mainnet)
- **Format:** WIF (Wallet Import Format)
- **Purpose:** Used to sign spork messages

**Testnet Spork Address:**
```
H5078b3f02b9f9ac81693716a5406a7aa4
```
- **Length:** 34 characters
- **Format:** HashmonkeyCoin testnet address (starts with 'H')
- **Purpose:** Public address that corresponds to the spork key

---

## 📝 **Configuration Steps**

### **1. Update chainparams.cpp (Already Done)**
The testnet spork address has been updated in `src/chainparams.cpp`:
```cpp
// Testnet spork configuration
vSporkAddresses = {"H5078b3f02b9f9ac81693716a5406a7aa4"};
nMinSporkKeys = 1;
```

### **2. Rebuild the Code**
```bash
# Clean and rebuild
make clean
make -j$(nproc)
```

### **3. Start Testnet Node with Spork Key**
```bash
# Start testnet node with the spork key
./hashmonkeycoind -testnet -sporkkey=L2f7e4d58ef758430e1376ed1d32c57b370f208ef733e0cbfe4
```

### **4. Alternative: Set Spork Address via Command Line**
```bash
# Start testnet node with spork address
./hashmonkeycoind -testnet -sporkaddr=H5078b3f02b9f9ac81693716a5406a7aa4
```

---

## 🔧 **Troubleshooting Testnet Issues**

### **Common Problems and Solutions:**

1. **"Invalid spork key" errors:**
   - Ensure you're using the exact 51-character key: `L2f7e4d58ef758430e1376ed1d32c57b370f208ef733e0cbfe4`
   - Make sure the key starts with 'L' (WIF format)

2. **"Invalid spork address" errors:**
   - Use the exact address: `H5078b3f02b9f9ac81693716a5406a7aa4`
   - Ensure it starts with 'H' (testnet format)

3. **"Spork not found" errors:**
   - Verify the spork address is correctly set in chainparams.cpp
   - Restart the node after configuration changes

4. **"Signature verification failed" errors:**
   - Ensure you're using the correct spork key that corresponds to the spork address
   - Check that the key is in proper WIF format

---

## 📋 **Verification Commands**

### **Check Spork Status:**
```bash
# Connect to testnet node and check spork status
./hashmonkeycoin-cli -testnet spork show
```

### **List All Sporks:**
```bash
# List all available sporks
./hashmonkeycoin-cli -testnet spork list
```

### **Check Spork Values:**
```bash
# Check specific spork values
./hashmonkeycoin-cli -testnet spork show SPORK_2_INSTANTSEND_ENABLED
./hashmonkeycoin-cli -testnet spork show SPORK_3_INSTANTSEND_BLOCK_FILTERING
./hashmonkeycoin-cli -testnet spork show SPORK_9_SUPERBLOCKS_ENABLED
```

---

## 🚀 **Testing Spork Functionality**

### **1. Start Testnet Node:**
```bash
./hashmonkeycoind -testnet -sporkkey=L2f7e4d58ef758430e1376ed1d32c57b370f208ef733e0cbfe4
```

### **2. Wait for Sync:**
```bash
# Check sync status
./hashmonkeycoin-cli -testnet getblockchaininfo
```

### **3. Test Spork Commands:**
```bash
# Set a spork value (example)
./hashmonkeycoin-cli -testnet spork SPORK_2_INSTANTSEND_ENABLED 0

# Check if spork was set
./hashmonkeycoin-cli -testnet spork show SPORK_2_INSTANTSEND_ENABLED
```

---

## 🔒 **Security Notes**

- **Keep the spork key secure** - it's used to sign spork messages
- **Don't share the spork key** publicly
- **Backup the spork key** in a secure location
- **Use different spork keys** for mainnet and testnet

---

## 📞 **Support**

If you encounter issues with testnet sporks:

1. Check the debug log: `~/.hashmonkeycoin/testnet3/debug.log`
2. Verify spork configuration in chainparams.cpp
3. Ensure you're using the correct testnet spork key and address
4. Restart the node after configuration changes

---

**Generated on:** $(date)
**Testnet Spork Key:** `L2f7e4d58ef758430e1376ed1d32c57b370f208ef733e0cbfe4`
**Testnet Spork Address:** `H5078b3f02b9f9ac81693716a5406a7aa4`
