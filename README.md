# HashmonkeyCoin (HMNY) - Community-Driven Cryptocurrency

[![CI](https://github.com/stabner/HashmonkeyCoin/workflows/CI/badge.svg)](https://github.com/stabner/HashmonkeyCoin/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**HashmonkeyCoin (HMNY)** is a community-driven, decentralized cryptocurrency built on the proven Raptoreum codebase. Designed with fairness and transparency at its core, HashmonkeyCoin features a balanced reward distribution system with smartnode support while maintaining robust security features.

## 🚀 Key Features

### **Mining & Economics**
- **Block Reward**: 500 HMNY per block
- **Halving Schedule**: Bitcoin-style halving every 210,240 blocks (~4 years)
- **Block Time**: 2-minute blocks for fast confirmations
- **Reward Distribution**:
  - **Miner**: 450 HMNY (90%)
  - **Smartnode**: 35 HMNY (7%)
  - **Developer**: 15 HMNY (3%)
- **Smartnode Collateral**: 20,000 HMNY
- **Fair Distribution**: No pre-mine, no ICO, community-driven launch

### **Network & Security**
- **Consensus Algorithm**: GhostRider (RandomX + SHA256)
- **Smartnodes**: Enabled with 20,000 HMNY collateral
- **Network Ports**: 
  - Mainnet: 19990 (P2P), 19991 (RPC)
  - Testnet: 29990 (P2P), 29991 (RPC)
  - Devnet: 39990 (P2P), 39991 (RPC)
  - Regtest: 19991 (P2P), 19992 (RPC)
- **Seed Node**: seednode.hashmonkeys.cloud
- **Address Prefixes**: 
  - Mainnet: 'H' (40), Script: 'M' (85)
  - Testnet: 'h' (111), Script: 'm' (19)
  - Devnet: 'd' (30), Script: '8' (19)

### **Technical Specifications**
- **Genesis Block**: January 2025 Launch
- **Message Start**: 
  - Mainnet: 0x4a, 0x73, 0x4d, 0x5a (JSMZ)
  - Testnet: 0x4a, 0x73, 0x4d, 0x5b (JSM[)
  - Devnet: 0x4a, 0x73, 0x4d, 0x5c (JSM\)
  - Regtest: 0x4a, 0x73, 0x4d, 0x5d (JSM])
- **BIP44 Coin Type**: 200
- **Data Directory**: 
  - Windows: `%APPDATA%\HashmonkeyCoinCore\`
  - Linux/macOS: `~/.HashmonkeyCoinCore/`
- **Network Status**: 
  - ✅ Mainnet: Live and operational
  - ✅ Testnet: Ready for launch
  - ✅ Regtest: Available for development

## 🚀 Launch Information

### **Current Status**
HashmonkeyCoin is now ready for launch! All genesis blocks have been properly mined and configured:

- **Mainnet Genesis**: `00000244c20bce60d57c422a1b20aa80587cb6d443dd10177be62b7f3ac98550`
- **Testnet Genesis**: `00000e94f50fd37963fb24dc86f3462a0b535b47519517ce6515f7a857da6e88`
- **Devnet Genesis**: `000001250c4a1a43fbf4a169832ad4ac1ef0930c87ac1b27c8f6a06c17c2ed69`
- **Regtest Genesis**: `0a1feaeed6f547dd6da45f62e76aa20c19b7399c4cd0434788d2118a2a8710f0`

### **Getting Started**
1. **Download** the latest release binaries
2. **Run the daemon**: `./hashmonkeycoind`
3. **Start mining**: Connect to a mining pool or mine solo
4. **Join the community**: Visit hashmonkeys.cloud

## 🏗️ Community Development Roadmap

### **Phase 1: Infrastructure Development**
- [ ] **Hashmonkeys.cloud Platform**
  - Community website and portal
  - Mining pool dashboard
  - Network statistics and monitoring
  - Community forums and communication channels

### **Phase 2: Mining Pool Optimization**
- [ ] **Reduced Pool Fees**
  - Target: 0.5% pool fee (industry standard)
  - Transparent fee structure
  - Community voting on fee changes

- [ ] **Enhanced Stratum Servers**
  - Multiple global stratum servers for low latency
  - Load balancing and failover systems
  - DDoS protection and security measures
  - Real-time server status monitoring

### **Phase 3: Advanced Features**
- [ ] **Mining Pool Features**
  - PPLNS and PPS payment methods
  - Solo mining options
  - Mobile mining app
  - Mining profitability calculator

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
- **OS**: Windows 10+, macOS 10.14+, Ubuntu 18.04+
- **RAM**: 4GB minimum, 8GB recommended
- **Storage**: 10GB free space
- **Network**: Stable internet connection

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

#### **Linux**
```bash
git clone https://github.com/stabner/HashmonkeyCoin.git
cd HashmonkeyCoin
./autogen.sh
./configure
make
sudo make install
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
```bash
# Example mining configuration
./hashmonkeycoind -daemon
./hashmonkeycoin-cli getnewaddress
# Use the generated address in your mining software
```

## 🔧 Development

### **Building from Source**
```bash
git clone https://github.com/stabner/HashmonkeyCoin.git
cd HashmonkeyCoin
./autogen.sh
./configure
make
```

### **Running Tests**
```bash
make check                    # Unit tests
test/functional/test_runner.py # Integration tests
```

### **Contributing**
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new functionality
5. Submit a pull request

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