HashmonkeyCoin Core Latest v2.0.3
==================================

|CI|master|develop|
|-|-|-|

HashmonkeyCoin (HMNY) is a cryptocurrency fork of Raptoreum, built for the development of the crypto mining pool at https://hashmonkeys.cloud/. The project inherits Raptoreum's robust features including smart contracts, asset layer capabilities, and masternode functionality.

Introduction
HashmonkeyCoin is based on the Raptoreum codebase, which itself is a fork of Dash. The project inherits current and future features such as chain locks, oracles, and smart contract capabilities. HashmonkeyCoin maintains and expands these capabilities:
A)	The deployment of a unique asset layer.
B)	The option to lock X amount of coins or assets into a special transaction. Coins are unlocked at a block number of choice or timestamp.
C)	Trustless on chain transfers of assets and native coins VIA Smart Contracts.
D)	Integrating, developing and deploying a VM protocol that would allow for smart contracts in 4 major programming languages as opposed to the situation with Ethereum being limited to solidity.

These additional features open up the power and ease of use of HashmonkeyCoin's features to a greater variety of industries under the Distributed Application umbrella. DAPP's are a critical part of driving widespread adoption as recently seen with DEFI.

HashmonkeyCoin Network Parameters:
- **Block Reward:** 500 HMNY
- **Smartnode Collateral:** 100,000 HMNY
- **Ticker:** HMNY
- **Website:** https://hashmonkeys.cloud/

License
-------

HashmonkeyCoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is meant to be stable. Development is done in separate branches.
[Tags](https://github.com/stabner/HashmonkeyCoin/tags) are created to indicate new official,
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
