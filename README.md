HashmonkeyCoin Core Latest v2.0.3
==================================

|CI|master|develop|
|-|-|-|

HashmonkeyCoin is a cryptocurrency fork of Raptoreum, designed to provide a fun and engaging digital currency experience. The name "HashmonkeyCoin" reflects the playful and energetic nature of the project while maintaining the robust technical foundation of the Raptoreum codebase.

Introduction
HashmonkeyCoin is built on the proven Raptoreum codebase, which itself is a fork of Dash. This provides HashmonkeyCoin with a solid foundation including:

- **Smart Contracts**: On-chain, trustless transfers without centralized marketplaces
- **Asset Layer**: Unique asset management capabilities
- **Chain Locks**: Enhanced security through chain lock technology
- **Smartnodes**: Decentralized network infrastructure
- **InstantSend**: Fast transaction confirmation
- **Privacy Features**: Enhanced transaction privacy

Key Features:
A) The deployment of a unique asset layer for token creation and management
B) The option to lock coins or assets into time-locked transactions
C) Trustless on-chain transfers of assets and native coins via Smart Contracts
D) Support for multiple programming languages in smart contract development

These features make HashmonkeyCoin suitable for a wide variety of applications in the decentralized application (DApp) ecosystem, providing developers with powerful tools for blockchain innovation.

Project Goals:
- Provide a fun and accessible cryptocurrency experience
- Maintain the robust technical foundation of Raptoreum
- Contribute to the broader crypto community through open-source development
- Enable innovative blockchain applications and use cases

License
-------

HashmonkeyCoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is meant to be stable. Development is done in separate branches.
Tags are created to indicate new official, stable release versions of HashmonkeyCoin Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

Testing
-------

Testing and code review is the bottleneck for development; we get more pull requests than we can review and test on short notice. Please be patient and help out by testing other people's pull requests, and remember this is a security-critical project where any mistake might cost people lots of money.

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to submit new unit tests for old code. Unit tests can be compiled and run (assuming they weren't disabled in configure) with: `make check`. Further details on running and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also regression and integration tests, written in Python, that are run automatically on the build server. These tests can be run (if the test dependencies are installed) with: `test/functional/test_runner.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the code. This is especially important for large or high-risk changes. It is useful to add a test plan to the pull request description if testing the changes is not straightforward.

About
-----

HashmonkeyCoin Core is a fork of Raptoreum Core, which is itself a fork of Dash Core. It inherits the robust technical foundation while providing a unique and engaging user experience.

### Resources

- [Website](https://hashmonkeycoin.com/)
- [GitHub Repository](https://github.com/stabner/HashmonkeyCoin)
- [Documentation](https://github.com/stabner/HashmonkeyCoin/wiki)

### License

MIT license

### Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for contribution guidelines.