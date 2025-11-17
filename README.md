# HashmonkeyCoin (HMNY) - Community-Driven Cryptocurrency

[![CI](https://github.com/stabner/HashmonkeyCoin/workflows/CI/badge.svg)](https://github.com/stabner/HashmonkeyCoin/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**HashmonkeyCoin (HMNY)** is a community-driven, decentralized cryptocurrency built on the proven Raptoreum codebase. Designed with fairness and transparency at its core, HashmonkeyCoin features a balanced reward distribution system with smartnode support while maintaining robust security features.

## 🚀 Key Features

### **Mining & Economics**
- **Block Reward**: 500 HMNY per block (fixed for early blocks, both mainnet and testnet)
- **Total Supply**: 210,034,688 HMNY (finite supply)
- **Halving Schedule**: Every 210,240 blocks (~0.8 years)
- **Block Time**: 2-minute blocks for fast confirmations
- **Reward Distribution**:
  - **Miner**: 450 HMNY (90%)
  - **Smartnode**: 35 HMNY (7%)
  - **Developer/Founder**: 15 HMNY (3%)
- **Smartnode Collateral**: 100,000 HMNY
- **Fair Distribution**: No pre-mine, no ICO, community-driven launch
- **Mining Algorithm**: GhostRiderV2 (ASIC-resistant, CPU/GPU friendly)

### **Network & Security**
- **Consensus Algorithm**: GhostRiderV2 (Optimized multi-algorithm POW)
- **Smartnodes**: Enabled with 100,000 HMNY collateral
- **Network Ports**: 
  - Mainnet: 19990 (P2P), 19991 (RPC)
  - Testnet: 19992 (P2P), 19993 (RPC default, customizable)
  - Devnet: 39990 (P2P), 39991 (RPC)
  - Regtest: 19991 (P2P), 19992 (RPC)
- **Seed Node**: seednode.hashmonkeys.cloud
- **Address Prefixes**: 
  - Mainnet: 'H' (16), Script: 'M' (20), Private: 'N' (21)
  - Testnet: 'h' (111) or 'j' (testnet addresses), Script: 'm' (19), Private: '9' (239)
  - Devnet: 'd' (30), Script: '8' (19), Private: '9' (239)

### **Technical Specifications**
- **Genesis Block**: November 17, 2025 Launch (Mined with GhostRiderV2)
- **Message Start**: 
  - Mainnet: 0x48, 0x4d, 0x4e, 0x59 (HMNY)
  - Testnet: 0x4a, 0x73, 0x4d, 0x5b (JsM[)
  - Devnet: 0x4a, 0x73, 0x4d, 0x5c (JsM\)
  - Regtest: 0x48, 0x4d, 0x4e, 0x59 (HMNY)
- **BIP44 Coin Type**: 200
- **Data Directory**: 
  - Windows: `%APPDATA%\HashmonkeyCoin\` (mainnet) or `%APPDATA%\HashmonkeyCoin\testnet3\` (testnet)
  - Linux/macOS: `~/.hashmonkeycoin/` (mainnet) or `~/.hashmonkeycoin-testnet/` (testnet)
- **Network Status**: 
  - ✅ Mainnet: Live and operational
  - ✅ Testnet: Ready for launch
  - ✅ Regtest: Available for development

## 💰 Supply & Economics

### **Total Supply Breakdown**
HashmonkeyCoin has a **finite total supply of 210,034,688 HMNY** with a deflationary emission schedule:

- **Era 1 (0-0.8 years)**: 500 HMNY/block → 105,120,000 HMNY
- **Era 2 (0.8-1.6 years)**: 250 HMNY/block → 52,560,000 HMNY  
- **Era 3 (1.6-2.4 years)**: 125 HMNY/block → 26,280,000 HMNY
- **Era 4 (2.4-3.2 years)**: 62 HMNY/block → 13,140,000 HMNY
- **Era 5 (3.2-4.0 years)**: 31 HMNY/block → 6,570,000 HMNY
- **Era 6 (4.0-4.8 years)**: 16 HMNY/block → 3,285,000 HMNY
- **Era 7 (4.8-5.6 years)**: 8 HMNY/block → 1,642,500 HMNY
- **Era 8 (5.6-6.4 years)**: 4 HMNY/block → 821,250 HMNY
- **Era 9 (6.4-7.2 years)**: 2 HMNY/block → 410,625 HMNY
- **Final Era**: 0.98 HMNY/block → 205,312 HMNY

### **Key Economic Features**
- **Deflationary**: Supply decreases over time through halvings
- **Predictable**: Fixed emission schedule with known total supply
- **Fair Launch**: No pre-mine, no ICO, community-driven distribution
- **Balanced Rewards**: 90% miners, 7% smartnodes, 3% development

## 🚀 Launch Information

### **Current Status**
HashmonkeyCoin is now ready for launch! All genesis blocks have been properly mined and configured with GhostRiderV2:

- **Mainnet Genesis**: `2d35946991239eeae4971d348968ce60a02907c6fa53c8277858ef741d4f8c1d` (Timestamp: November 17, 2025, Nonce: 1)
- **Testnet Genesis**: `1698f1b1bcf54f11ef070a298d7a9c3e335abbb5cee1ab5bd52106d5af9f3730` (Timestamp: November 17, 2025, Nonce: 1)
- **Regtest Genesis**: `2c4a4a63e70fc32ed1ec94e3e20f2b0e734e7f047085d9d8452b87280ff1dead` (Timestamp: November 17, 2025, Nonce: 3)

### **Recent Updates (v2.0.03.01)**
- ✅ **Algorithm Upgrade**: Migrated to GhostRiderV2 for enhanced security and performance
  - Reduced rounds: 18 → 12 (33% reduction)
  - CN variants: Only Turtle/TurtleLite for better Intel/GPU performance
  - SHA512 final round: Intel-optimized and GPU-friendly
  - Expected performance: AMD -15% to -30%, Intel +20% to +40%, GPU +10% to +25%
- ✅ Fixed block reward: Set to 500 HMNY for early blocks (both mainnet and testnet)
- ✅ Updated testnet founder address for proper reward distribution
- ✅ Improved blockchain validation and syncing

### **Mining Algorithm: GhostRiderV2**

HashmonkeyCoin uses **GhostRiderV2**, an enhanced version of the GhostRider proof-of-work algorithm. Here's what you need to know:

**What is GhostRiderV2?**
- **Enhanced Algorithm**: An improved version of the original GhostRider algorithm with optimized performance and security
- **ASIC-Resistant**: Designed to prevent specialized mining hardware from dominating the network
- **CPU/GPU Friendly**: Optimized for standard computer hardware, making mining accessible to everyone
- **Hybrid Approach**: Combines multiple cryptographic hash algorithms with CryptoNight variants to create a balanced and secure mining experience

**Technical Specifications:**
- **Algorithm Type**: Proof-of-Work (PoW)
- **Hash Function**: GhostRiderV2 (Multi-algorithm rotation with CryptoNight variants)
- **Memory Requirements**: 
  - Minimum: 2GB RAM per mining thread
  - Recommended: 4GB+ RAM per thread for optimal performance
  - Uses memory-hard CryptoNight variants to prevent ASIC optimization
- **CPU Optimization**: 
  - Best performance on modern multi-core CPUs (4+ cores recommended)
  - Supports both x86_64 and ARM architectures
  - Utilizes CPU cache efficiently for faster hashing
- **GPU Support**: 
  - Compatible with modern GPUs (NVIDIA and AMD)
  - GPU mining provides additional hashrate but CPU mining is also viable
  - Memory bandwidth is crucial for GPU performance
- **Block Time**: 2 minutes (120 seconds)
- **Difficulty Adjustment**: Dynamic difficulty adjustment every block

**How GhostRiderV2 Works:**
1. **Optimized Rotation Pattern**: 
   - Reduced from 18 to 12 rounds (33% reduction)
   - Changed from `5-1-5-1-5-1` pattern to `5-1-5-1` with SHA512 final
   - Faster processing with better Intel/GPU performance
2. **CN Variant Selection**: 
   - Only uses lighter CN variants: `{4, 5}` (Turtle/TurtleLite)
   - Removed heavier variants (CNDark, CNDarklite, CNFast, CNLite)
   - Lighter variants favor Intel CPUs and GPUs over AMD
3. **Algorithm Pool Enhancement**: 
   - Includes SHA512 (option 15) in the algorithm pool
   - SHA512 is highly optimized on Intel CPUs and GPUs
   - Final round uses SHA512 instead of a third CN variant
4. **Hybrid Execution**: 
   - Core hash algorithms generate intermediate hash values
   - CN variants provide memory-hard properties
   - SHA512 final round ensures cryptographic security and Intel/GPU optimization

**Why GhostRiderV2?**
- **Better Security**: Enhanced resistance to ASIC mining hardware through memory-hard design
- **Performance Optimization**: Specifically optimized to balance performance across different hardware types
  - **Reduced Rounds**: 18 → 12 rounds (33% reduction) for faster processing
  - **Lighter CN Variants**: Only Turtle/TurtleLite variants for better Intel/GPU performance
  - **SHA512 Final Round**: Intel-optimized and GPU-friendly final hash operation
  - **Algorithm Pool**: Includes SHA512 (option 15) for enhanced Intel/GPU support
- **Expected Performance Impact**:
  - **AMD CPUs**: -15% to -30% (reduced advantage due to lighter CN variants and fewer rounds)
  - **Intel CPUs**: +20% to +40% (better performance with SHA512 and lighter CN variants)
  - **GPUs**: +10% to +25% (more competitive with reduced rounds and SHA512 optimization)
- **Fair Distribution**: Ensures mining rewards are distributed fairly among community miners using different hardware
- **Future-Proof**: Designed to maintain ASIC resistance as technology evolves
- **Energy Efficient**: More efficient than pure SHA256 mining while maintaining security

**For Miners:**
- **Hardware Requirements**:
  - **CPU**: Multi-core processor (4+ cores recommended)
    - **Intel CPUs**: Optimized performance - excellent choice for GhostRiderV2 mining (+20% to +40% performance boost)
    - **AMD CPUs**: Still supported but performance balanced (-15% to -30% compared to original GhostRider)
  - **RAM**: 4GB minimum, 8GB+ recommended for optimal performance
  - **GPU**: Highly recommended for best performance (NVIDIA GTX 1060+ or AMD RX 580+)
    - GPU mining provides significantly better hashrate (+10% to +25% improvement)
    - Both NVIDIA and AMD GPUs are well-supported
    - SHA512 final round is GPU-optimized
- **Software Compatibility**: 
  - Compatible with mining software that supports GhostRiderV2
  - Supports both solo and pool mining
  - Works on Windows, Linux, and macOS
  - **Note**: V2-specific optimizations require miner software updates to fully benefit
- **Mining Efficiency**:
  - **GPU Mining**: Recommended for best performance and profitability
  - **Intel CPU Mining**: Excellent performance with V2 optimizations
  - **AMD CPU Mining**: Supported but performance balanced for fairness
  - No specialized equipment needed - standard hardware works well

### **Getting Started**
1. **Download** the latest release binaries from [GitHub Releases](https://github.com/stabner/HashmonkeyCoin/releases)
2. **Run the daemon**: 
   - Mainnet: `./hashmonkeycoind`
   - Testnet: `./hashmonkeycoind -testnet`
3. **Connect to seed node** (for testnet): Add `addnode=seednode.hashmonkeys.cloud:19992` to your config
4. **Start mining**: Connect to a mining pool or mine solo
5. **Join the community**: Visit hashmonkeys.cloud

## 🏗️ Development Roadmap

### **Phase 1: Mining Pool Infrastructure** ✅ **COMPLETED**
- [x] **Mining Pool Platform**
  - Mining pool infrastructure deployed
  - Mining interface and dashboard operational
  - Testnet mining pool fully functional

### **Phase 2: Exchange Listing** 🎯 **IN PROGRESS**
- [ ] **Market Listing**
  - Get HashmonkeyCoin (HMNY) listed on cryptocurrency exchanges
  - Enable trading pairs for HMNY
  - Establish liquidity and market presence
  - Community support for exchange applications

### **Phase 3: Global Stratum Network** 🚀 **MAIN GOAL**
- [ ] **Worldwide Stratum Server Deployment**
  - Deploy stratum servers across multiple continents
  - North America, Europe, Asia-Pacific, and other regions
  - Low-latency connections for miners worldwide
  - Automatic failover and load balancing

- [ ] **Lowest Fees in Crypto**
  - **Primary Mission**: Achieve the lowest mining pool fees in the cryptocurrency industry
  - Transparent fee structure with competitive rates
  - Continuous optimization to reduce operational costs
  - Pass savings directly to miners
  - Community-driven fee decisions

- [ ] **Enhanced Infrastructure**
  - DDoS protection and security hardening
  - Real-time server status monitoring
  - Advanced load balancing systems
  - High availability and redundancy

### **Future Enhancements**
- [ ] **Advanced Mining Features**
  - PPLNS and PPS payment methods
  - Solo mining options
  - Mining profitability calculator
  - Mobile mining app

- [ ] **Community Tools**
  - Block explorer with advanced features
  - Wallet integration guides
  - Mining setup tutorials
  - Community governance platform

## 🤝 Community-Driven Development

HashmonkeyCoin is built by the community, for the community. We believe in:

- **Transparency**: All development decisions are open for community discussion
- **Fairness**: No hidden fees, no developer rewards, miners come first
- **Innovation**: Community-driven feature development and improvements
- **Accessibility**: Easy-to-use tools and comprehensive documentation

### **Get Involved**
- **Discord**: [Join our community](https://discord.gg/hashmonkeycoin)
- **Telegram**: [HashmonkeyCoin Community](https://t.me/hashmonkeycoin)
- **Reddit**: [r/HashmonkeyCoin](https://reddit.com/r/HashmonkeyCoin)
- **GitHub**: [Contribute to development](https://github.com/stabner/HashmonkeyCoin)

## 📦 Installation & Setup

### **System Requirements**
- **OS**: Windows 10+, macOS 10.14+, Ubuntu 18.04+ (Ubuntu 22.04 recommended)
- **RAM**: 4GB minimum, 8GB recommended
- **Storage**: 10GB free space (more for full node)
- **Network**: Stable internet connection
- **CPU**: Multi-core recommended for mining (GhostRiderV2 algorithm)

### **Quick Start**

#### **Windows**
```bash
# Download the latest release from GitHub
# Extract and run hashmonkeycoin-qt.exe

# Or build from source (WSL Ubuntu 24.04 recommended)
git clone https://github.com/stabner/HashmonkeyCoin.git
cd HashmonkeyCoin

# Install dependencies
sudo apt update
sudo apt install -y gcc-mingw-w64 g++-mingw-w64 mingw-w64-tools build-essential libtool autotools-dev automake pkg-config bsdmainutils python3 libssl-dev libevent-dev libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev qtbase5-dev qttools5-dev-tools qt5-qmake libdb++-dev libminiupnpc-dev libnatpmp-dev

# Build for Windows
export PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g')
cd depends
make HOST=x86_64-w64-mingw32 -j$(nproc)
cd ..
./autogen.sh
CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/ --host=x86_64-w64-mingw32
make -j$(nproc)

# Find Windows executables in src/ directory
ls -la src/*.exe
```

**Note**: For detailed Windows build instructions and troubleshooting, see [doc/build-windows.md](doc/build-windows.md).

#### **Linux (Ubuntu/Debian)**
```bash
# Install dependencies
sudo apt update
sudo apt install -y build-essential libtool autotools-dev automake pkg-config \
  bsdmainutils python3 libssl-dev libevent-dev libboost-system-dev \
  libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev \
  libboost-test-dev libboost-thread-dev qtbase5-dev qttools5-dev-tools \
  qt5-qmake libdb++-dev libminiupnpc-dev libnatpmp-dev

# Clone and build
git clone https://github.com/stabner/HashmonkeyCoin.git
cd HashmonkeyCoin
./autogen.sh
./configure
make -j$(nproc)
sudo make install

# Binaries will be in src/ directory
ls -la src/hashmonkeycoin*
```

#### **macOS**
```bash
# Using Homebrew
brew install hashmonkeycoin

# Or build from source
git clone https://github.com/stabner/HashmonkeyCoin.git
cd HashmonkeyCoin
./autogen.sh
./configure
make
```

### **Mining Setup**

#### **Solo Mining**
```bash
# Start the daemon
./hashmonkeycoind -testnet -daemon

# Get a new address for mining rewards
./hashmonkeycoin-cli -testnet getnewaddress

# Start CPU mining (solo)
./hashmonkeycoin-cli -testnet setgenerate true 1
```


## 🔧 Development

### **Building from Source**
```bash
git clone https://github.com/stabner/HashmonkeyCoin.git
cd HashmonkeyCoin
./autogen.sh
./configure
make -j$(nproc)  # Use all CPU cores for faster compilation
```

### **Running Tests**
```bash
make check                    # Unit tests
test/functional/test_runner.py # Integration tests
```

### **Node Setup for Development**

#### **Testnet Seed Node**
```bash
# Create data directory
mkdir -p ~/.hashmonkeycoin-testnet

# Create config file
cat > ~/.hashmonkeycoin-testnet/hashmonkeycoin.conf <<EOF
testnet=1
server=1
daemon=1
listen=1
bind=0.0.0.0
port=19992
rpcbind=0.0.0.0
rpcport=19993
rpcuser=hashmonkeycoin
rpcpassword=$(openssl rand -hex 32)
rpcallowip=127.0.0.1
rpcallowip=YOUR_NETWORK/24
EOF

# Start seed node
./hashmonkeycoind -testnet -datadir=$HOME/.hashmonkeycoin-testnet
```

#### **Testnet Mining Node**
```bash
# Create data directory
mkdir -p ~/.hashmonkeycoin-mining

# Create config file
cat > ~/.hashmonkeycoin-mining/hashmonkeycoin.conf <<EOF
testnet=1
server=1
daemon=1
rpcbind=0.0.0.0
rpcport=11230
rpcuser=stabner
rpcpassword=your_secure_password
rpcallowip=127.0.0.1
rpcallowip=YOUR_NETWORK/24
connect=seednode.hashmonkeys.cloud:19992
EOF

# Start mining node
./hashmonkeycoind -testnet -datadir=~/.hashmonkeycoin-mining
```

### **Contributing**
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Add tests for new functionality
5. Commit your changes (`git commit -m 'Add amazing feature'`)
6. Push to the branch (`git push origin feature/amazing-feature`)
7. Submit a pull request

## 📊 Network Statistics

- **Current Block Height**: [Check Explorer](https://explorer.hashmonkey.cloud)
- **Network Hashrate**: [Live Stats](https://hashmonkeys.cloud/stats)
- **Difficulty**: [Current Difficulty](https://hashmonkeys.cloud/difficulty)
- **Mining Pools**: [Pool List](https://hashmonkeys.cloud/pools)

## 🛡️ Security

HashmonkeyCoin inherits the robust security features from the Raptoreum codebase:
- **GhostRiderV2 Algorithm**: Optimized 12-round multi-algorithm POW for Intel/GPU performance
- **InstantSend**: Near-instant transaction confirmations
- **ChainLocks**: Protection against 51% attacks
- **LLMQ**: Long Living Masternode Quorums for consensus
- **Smartnode Network**: Decentralized governance and network security

## 📄 License

HashmonkeyCoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more information or see https://opensource.org/licenses/MIT.

## 🙏 Acknowledgments

- **Raptoreum Team**: For the original codebase and innovative features
- **Dash Team**: For the underlying blockchain technology
- **Bitcoin Core**: For the foundational blockchain concepts
- **Community Contributors**: For ongoing development and support

## 📞 Support

- **Documentation**: [docs.hashmonkey.cloud](https://docs.hashmonkey.cloud)
- **Support Forum**: [support.hashmonkey.cloud](https://support.hashmonkey.cloud)
- **Email**: support@hashmonkey.cloud
- **Discord**: [Community Support](https://discord.gg/hashmonkeycoin)

---

**HashmonkeyCoin - Built by the Community, for the Community** 🐒💎

*Join us in building the future of fair and transparent cryptocurrency mining!*