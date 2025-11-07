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
- **Mining Algorithm**: GhostRider (ASIC-resistant, CPU/GPU friendly)

### **Network & Security**
- **Consensus Algorithm**: GhostRider (RandomX + SHA256)
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
- **Genesis Block**: January 2025 Launch
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
HashmonkeyCoin is now ready for launch! All genesis blocks have been properly mined and configured:

- **Mainnet Genesis**: `00000244c20bce60d57c422a1b20aa80587cb6d443dd10177be62b7f3ac98550`
- **Testnet Genesis**: `00000e94f50fd37963fb24dc86f3462a0b535b47519517ce6515f7a857da6e88`
- **Devnet Genesis**: `000001250c4a1a43fbf4a169832ad4ac1ef0930c87ac1b27c8f6a06c17c2ed69`
- **Regtest Genesis**: `0a1feaeed6f547dd6da45f62e76aa20c19b7399c4cd0434788d2118a2a8710f0`

### **Recent Updates (v2.0.03.01)**
- ✅ Fixed block reward: Set to 500 HMNY for early blocks (both mainnet and testnet)
- ✅ Updated testnet founder address for proper reward distribution
- ✅ Fixed coinbase transaction structure for MiningCore compatibility
- ✅ Improved blockchain validation and syncing

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
  - MiningCore integration complete
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
- **CPU**: Multi-core recommended for mining (GhostRider algorithm)

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

#### **Pool Mining with MiningCore**
HashmonkeyCoin is compatible with MiningCore. Use the following `coin.json` configuration:

```json
{
  "hashmonkeycoin-testnet": {
    "name": "HashmonkeyCoin Testnet",
    "symbol": "HMNY",
    "family": "bitcoin",
    "coinbaseHasher": { "hash": "sha256d" },
    "headerHasher": { "hash": "ghostrider" },
    "blockHasher": {
      "hash": "reverse",
      "args": [{ "hash": "sha256d" }]
    },
    "hasFounderFee": true,
    "hasMasterNodes": true,
    "hasSmartNodes": true,
    "shareMultiplier": 65536,
    "blockVersion": 536870912,
    "coinbaseTxVersion": 3,
    "coinbaseTxType": 5
  }
}
```

**RPC Configuration for Mining Node:**
```ini
# hashmonkeycoin.conf
testnet=1
server=1
rpcbind=0.0.0.0
rpcport=11230
rpcuser=your_username
rpcpassword=your_secure_password
rpcallowip=127.0.0.1
rpcallowip=YOUR_NETWORK/24
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
- **GhostRider Algorithm**: Combines RandomX and SHA256 for ASIC resistance
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