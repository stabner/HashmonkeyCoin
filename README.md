# HashmonkeyCoin

A cryptocurrency fork of Raptoreum with enhanced features and community-driven development.

## 🚀 Quick Start

### Prerequisites

- **Linux/Unix**: GCC 7.4+, CMake 3.16+, Boost 1.70+
- **Windows**: Visual Studio 2019+, vcpkg
- **macOS**: Xcode 12+, Homebrew

### Building from Source

```bash
# Clone the repository
git clone https://github.com/stabner/HashmonkeyCoin.git
cd HashmonkeyCoin

# Initialize and build
./autogen.sh
./configure
make -j$(nproc)

# Run tests
make check
```

### Docker Build (Alternative)

```bash
docker build -t hashmonkeycoin .
docker run -it hashmonkeycoin
```

## 🏗️ Development Workflow

### Simple Branch Strategy

- **`master`**: Single development branch - all work happens here
- **Direct development**: Make changes directly to master branch
- **No complex branching**: Keep it simple and straightforward

### Contributing

1. Fork the repository
2. Make your changes directly on `master`
3. Test your changes thoroughly
4. Commit with conventional messages: `git commit -m "feat: add your feature"`
5. Push directly to master: `git push origin master`

### Pull Request Process (Optional)

- If collaborating, create PRs targeting `master` branch
- Include tests for new functionality
- Ensure all CI checks pass
- Link related issues in PR description
- Follow the PR template guidelines

## 🧪 Testing

### Running Tests

```bash
# Unit tests
make check

# Functional tests
test/functional/test_runner.py

# Specific test
src/test/test_raptoreum
```

### Test Coverage

We maintain high test coverage. New features must include:
- Unit tests for core functionality
- Integration tests for complex workflows
- Performance benchmarks where applicable

## 📋 Project Phases

### Phase 1: Foundation
- [x] Repository setup and CI/CD
- [ ] Basic branding and naming
- [ ] Core consensus mechanism

### Phase 2: Core Features
- [ ] Enhanced mining algorithm
- [ ] Smart contract support
- [ ] Governance system

### Phase 3: Advanced Features
- [ ] Cross-chain compatibility
- [ ] Advanced privacy features
- [ ] Mobile wallet support

## 🔧 Configuration

### Network Configuration

```bash
# Mainnet
./raptoreumd -daemon

# Testnet
./raptoreumd -testnet -daemon

# Regtest (for development)
./raptoreumd -regtest -daemon
```

### RPC Configuration

```bash
# Enable RPC
./raptoreumd -server -rpcuser=user -rpcpassword=pass

# RPC examples
raptoreum-cli getblockchaininfo
raptoreum-cli getnetworkinfo
```

## 📚 Documentation

- [API Documentation](docs/api.md)
- [Development Guide](docs/development.md)
- [Deployment Guide](docs/deployment.md)
- [Contributing Guidelines](CONTRIBUTING.md)

## 🤝 Community

- **Discord**: [Join our Discord](https://discord.gg/hashmonkeycoin)
- **Telegram**: [Join our Telegram](https://t.me/hashmonkeycoin)
- **Twitter**: [@HashmonkeyCoin](https://twitter.com/hashmonkeycoin)
- **Website**: [hashmonkeycoin.com](https://hashmonkeycoin.com)

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Based on [Raptoreum](https://github.com/Raptoreum/raptoreum)
- Built on Bitcoin Core architecture
- Community contributions and feedback

## 📊 Project Status

![CI Status](https://github.com/stabner/HashmonkeyCoin/workflows/CI/badge.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Version](https://img.shields.io/badge/version-0.1.0-green.svg)

---

**Note**: This is an experimental cryptocurrency project. Use at your own risk.