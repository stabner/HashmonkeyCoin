# HashmonkeyCoin (HMNY) - Community-Driven Cryptocurrency

[![CI](https://github.com/stabner/HashmonkeyCoin/workflows/CI/badge.svg)](https://github.com/stabner/HashmonkeyCoin/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**HashmonkeyCoin (HMNY)** is a community-driven, decentralized cryptocurrency built on the proven Raptoreum codebase. Designed with fairness and transparency at its core, HashmonkeyCoin eliminates smartnode fees and simplifies the mining experience while maintaining robust security features.

## 🚀 Key Features

### **Mining & Economics**
- **Block Reward**: 500 HMNY per block
- **Halving Schedule**: Bitcoin-style halving every 210,000 blocks (~4 years)
- **Block Time**: 2-minute blocks for fast confirmations
- **No Smartnode Fees**: 100% of mining rewards go directly to miners
- **Fair Distribution**: No pre-mine, no ICO, community-driven launch

### **Network & Security**
- **Consensus Algorithm**: GhostRider (RandomX + SHA256)
- **Smartnodes**: Disabled for simplified, fair mining
- **Network Ports**: 
  - Mainnet: 10226
  - Testnet: 10230
- **Seed Node**: seednode.hashmonkeys.cloud
- **Address Prefix**: 'H' for mainnet addresses

### **Technical Specifications**
- **Genesis Block**: December 19, 2024
- **Message Start**: 0x68, 0x6d, 0x6e, 0x79 (hmny)
- **BIP44 Coin Type**: 200
- **Base58 Prefixes**: 
  - Public Key: 40 ('H')
  - Script: 16 ('7')
- **Network Status**: 
  - ✅ Mainnet: Ready for launch
  - ✅ Testnet: Ready for testing
  - ✅ Regtest: Available for development

## 🚀 Launch Information

### **Current Status**
HashmonkeyCoin is now ready for launch! All genesis blocks have been properly mined and configured:

- **Mainnet Genesis**: `05e068211cad9f331f89eaccb9c6ec3f3a7d29c0c5ec5bd9e349e6c97bae0300`
- **Testnet Genesis**: `de794c643c1c13d88f2b4b49604a6d831ea3bf5a5dd401b11a520681ea371000`
- **Devnet Genesis**: `5791143b3b02b4b82f2bf6b4ffe68b49eeea5c1237231210810896a72fd00a00`
- **Regtest Genesis**: `26ce8027902b999d1cd5e0217cf725133f2b00b77b13f414998ef1f701907c1a`

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

# Configuration file: hashmonkeycoin.conf
# Default data directory: ~/.hashmonkeycoin/
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
