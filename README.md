HashmonkeyCoin Core v1.0.0
==========================

|CI|master|develop|
|-|-|-|

HashmonkeyCoin (HMNY) is a decentralized cryptocurrency built on the Raptoreum codebase, designed to provide a fair and transparent mining experience with no developer fees and simplified smartnode functionality.

Introduction
HashmonkeyCoin is a fork of Raptoreum that focuses on simplicity and fairness. The project removes developer fees and simplifies the smartnode system while maintaining the core blockchain functionality and security features.

Key Features:
- **Block Reward**: 500 HMNY per block with Bitcoin-style halving every 210,240 blocks (4 years)
- **No Developer Fees**: 100% of mining rewards go to miners
- **Simplified Smartnodes**: Smartnode functionality is disabled for simplicity
- **Fast Block Time**: 2-minute block time for quick confirmations
- **Secure**: Based on proven Raptoreum/Dash codebase with enhanced security features

HashmonkeyCoin aims to provide a fair and transparent cryptocurrency that puts miners first, with no hidden fees or complex governance structures.

License
-------

HashmonkeyCoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is meant to be stable. Development is done in separate branches.
[Tags](https://github.com/stabner/hashmonkeycoin/tags) are created to indicate new official,
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
