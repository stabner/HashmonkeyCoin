HashmonkeyCoin Core Latest v2.0.3
==================================

|CI|master|develop|
|-|-|-|

HashmonkeyCoin (HMNY) is a revolutionary cryptocurrency that combines the best features of modern blockchain technology with a fun and engaging monkey-themed approach to decentralized finance. Built on the proven HashmonkeyCoin codebase, HashmonkeyCoin brings innovation, security, and community-driven development to the crypto space.

Introduction
HashmonkeyCoin is a fork of HashmonkeyCoin, which itself is based on Dash, inheriting all the advanced features such as chain locks, oracles, and smart contracts. The project focuses on creating a user-friendly and accessible cryptocurrency that maintains the technical excellence of its predecessors while adding unique characteristics.

Key Features:
A)	The deployment of a unique asset layer for token creation and management.
B)	The option to lock X amount of coins or assets into special transactions that unlock at predetermined block numbers or timestamps.
C)	Trustless on-chain transfers of assets and native coins via Smart Contracts.
D)	Support for smart contracts in multiple programming languages, expanding beyond Ethereum's Solidity limitation.

HashmonkeyCoin aims to make blockchain technology more accessible to everyday users while maintaining the security and decentralization that makes cryptocurrency valuable. The project emphasizes community involvement and aims to contribute innovative features back to the broader crypto ecosystem.

Block Reward: 500 HMNY per block
Dev Fee: 3%
Smartnode Reward: 7%
Smartnode Collateral: 100,000 HMNY


License
-------

HashmonkeyCoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is meant to be stable. Development is done in separate branches.
[Tags](https://github.com/raptor3um/hashmonkeycoin/tags) are created to indicate new official,
stable release versions of HashmonkeyCoin Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.
