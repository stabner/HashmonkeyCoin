# CursorAI Task List for HashmonkeyCoin

This file contains specific, actionable tasks that CursorAI can execute to implement the HashmonkeyCoin fork. Each task is designed to be atomic and result in a small, reviewable PR.

## 🎯 Task Categories

### Phase 1: Branding & Constants

#### Task 1.1: Branding Replacement
**Branch**: `feature/branding`
**Files to modify**: All source files
**Action**: Search and replace branding strings

```bash
# Safe replacements (CASE-SENSITIVE)
Raptoreum → HashmonkeyCoin
raptoreum → hashmonkeycoin
RTM → HMNY
Raptoreum.conf → HashmonkeyCoin.conf
```

**Files to focus on**:
- `README.md`
- `src/qt/*.cpp`, `src/qt/*.h`
- `src/chainparams.cpp`
- `configure.ac`
- `Makefile.am`

**Acceptance**: All instances of "Raptoreum" replaced with "HashmonkeyCoin" in user-facing strings.

#### Task 1.2: Chain Parameters Update
**Branch**: `feature/chain-params`
**Files to modify**: `src/chainparams.cpp`

**Action**: Update mainnet constants

```cpp
// Update in CreateChainParams() for mainnet
pchMessageStart[0] = 0x4b;
pchMessageStart[1] = 0x7f;
pchMessageStart[2] = 0xa1;
pchMessageStart[3] = 0xbc;

nDefaultPort = 28600;
nRPCPort = 28601;

consensus.nSubsidyHalvingInterval = 131400; // ~1 year at 2 min block time
consensus.nPowTargetSpacing = 120; // 2 minutes
consensus.nMaxMoney = 21000000000ULL * COIN; // 21 billion HMNY
```

**Acceptance**: Constants updated, builds successfully.

#### Task 1.3: Subsidy Function Update
**Branch**: `feature/subsidy-function`
**Files to modify**: `src/validation.cpp` or consensus files

**Action**: Update GetBlockSubsidy function

```cpp
CAmount GetBlockSubsidy(int nHeight, const Consensus::Params& params)
{
    CAmount nSubsidy = 500 * COIN; // initial 500 HMNY

    int halvings = nHeight / params.nSubsidyHalvingInterval;
    if (halvings >= 64) return 0;

    nSubsidy >>= halvings; // divide by 2^halvings

    return nSubsidy;
}
```

**Acceptance**: Function updated, unit tests pass.

### Phase 2: Reward Split & Smartnode Logic

#### Task 2.1: Smartnode Reward Split
**Branch**: `feature/reward-split`
**Files to modify**: Block creation and reward distribution code

**Action**: Implement 5% smartnode reward

```cpp
CAmount nSubsidy = GetBlockSubsidy(nHeight, params);

// smartnode gets 5%
CAmount nSmartnodeReward = (nSubsidy * 5) / 100;
CAmount nMinerReward = nSubsidy - nSmartnodeReward;

// Add outputs in the block creation code accordingly
txNew.vout[0].nValue = nMinerReward;
txNew.vout[1].nValue = nSmartnodeReward;
```

**Acceptance**: Reward split logic implemented, regtest tests pass.

#### Task 2.2: Smartnode Collateral Constants
**Branch**: `feature/smartnode-collateral`
**Files to modify**: `src/smartnode/smartnode.h` or `chainparams.h`

**Action**: Add collateral constants

```cpp
static const CAmount SMARTNODE_COLLATERAL = 10000 * COIN; // 10,000 HMNY
static const CAmount SMARTNODE_SUPERNODE_COLLATERAL = 100000 * COIN; // 100,000 HMNY
```

**Acceptance**: Constants added, smartnode registration works.

#### Task 2.3: Spork Configuration
**Branch**: `feature/sporks`
**Files to modify**: `src/spork.h`, `src/spork.cpp`

**Action**: Add new spork IDs

```cpp
static const int SPORK_17_SMARTNODE_REWARD = 10017;
mapSporkDefaults[SPORK_17_SMARTNODE_REWARD] = 0; // default off
```

**Acceptance**: Spork IDs added, no conflicts with existing sporks.

### Phase 3: Genesis & Network Parameters

#### Task 3.1: Genesis Block Placeholder
**Branch**: `feature/genesis-placeholder`
**Files to modify**: `src/chainparams.cpp`

**Action**: Add placeholder genesis values

```cpp
// genesis setup — use the mined values later
consensus.hashGenesisBlock = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
genesis = CreateGenesisBlock(
    1695571200, // 25 Sep 2025 00:00:00 UTC
    0,          // nonce (to be filled)
    0x1e0ffff0, // nBits (difficulty bits)
    1,          // version
    500 * COIN  // genesis block reward
);
```

**Acceptance**: Placeholder values added, node boots.

#### Task 3.2: Genesis Mining Helper
**Branch**: `feature/genesis-miner`
**Files to create**: `tools/mine_genesis.cpp`

**Action**: Create genesis mining utility

```cpp
// Create temporary executable to mine genesis block
// Include coinbase message: "HashmonkeyCoin Genesis: HashmonkeyCoin Launch 25 September 2025 - mainnet"
// Loop nonces until valid hash found
// Output: hashGenesisBlock, hashMerkleRoot, nTime, nNonce
```

**Acceptance**: Mining helper compiles and runs.

#### Task 3.3: Genesis Block Integration
**Branch**: `feature/genesis-integration`
**Files to modify**: `src/chainparams.cpp`

**Action**: Update with mined genesis values

```cpp
// Replace placeholders with actual mined values
consensus.hashGenesisBlock = uint256S("0x[MINED_HASH]");
assert(genesis.hashMerkleRoot == uint256S("0x[MINED_MERKLE]"));
```

**Acceptance**: Genesis block validates, node accepts genesis.

### Phase 4: UI & Assets

#### Task 4.1: Icon Integration
**Branch**: `feature/ui-icons`
**Files to modify**: `src/qt/res/icons.qrc`

**Action**: Add HashmonkeyCoin icons

```xml
<RCC>
  <qresource prefix="/icons">
    <file>hashmonkey-16.png</file>
    <file>hashmonkey-32.png</file>
    <file>hashmonkey-64.png</file>
    <file>hashmonkey-128.png</file>
    <file>hashmonkey-splash.png</file>
  </qresource>
</RCC>
```

**Acceptance**: Icons display in wallet UI.

#### Task 4.2: Wallet Metadata Update
**Branch**: `feature/wallet-metadata`
**Files to modify**: Qt wallet files

**Action**: Update wallet name and symbols

```cpp
// Update wallet window title, about dialog, etc.
// Change "Raptoreum" to "HashmonkeyCoin" in UI strings
```

**Acceptance**: Wallet displays correct branding.

### Phase 5: Build & Testing

#### Task 5.1: CI Pipeline Enhancement
**Branch**: `feature/ci-enhancement`
**Files to modify**: `.github/workflows/ci.yml`

**Action**: Add HashmonkeyCoin-specific tests

```yaml
# Add tests for:
# - GetBlockSubsidy function
# - Reward split validation
# - Smartnode collateral checks
# - Genesis block validation
```

**Acceptance**: CI runs all tests successfully.

#### Task 5.2: Regtest Scripts
**Branch**: `feature/regtest-scripts`
**Files to create**: `test/regtest/`

**Action**: Create regtest validation scripts

```bash
#!/bin/bash
# Test block reward distribution
# Test smartnode registration
# Test genesis block acceptance
```

**Acceptance**: Regtest scripts validate all functionality.

### Phase 6: Documentation

#### Task 6.1: Masternode Operator Guide
**Branch**: `feature/mn-guide`
**Files to create**: `docs/masternode-operators.md`

**Action**: Create comprehensive masternode guide

```markdown
# HashmonkeyCoin Masternode Operator Guide

## Collateral Requirements
- Standard MN: 10,000 HMNY
- Supernode: 100,000 HMNY

## Setup Instructions
[Detailed setup steps]

## Expected Rewards
[Reward calculation and timing]
```

**Acceptance**: Guide is complete and accurate.

#### Task 6.2: API Documentation
**Branch**: `feature/api-docs`
**Files to create**: `docs/api.md`

**Action**: Document new RPC commands and parameters

```markdown
# HashmonkeyCoin API Documentation

## New RPC Commands
- getblocksubsidy
- smartnode status
- [Other HashmonkeyCoin-specific commands]
```

**Acceptance**: API documentation is complete.

## 🚀 Execution Instructions for CursorAI

### How to Use This Task List

1. **Start with Phase 1**: Begin with branding replacement
2. **One task per PR**: Each task should result in a single, focused PR
3. **Test after each task**: Ensure builds and tests pass
4. **Link to issues**: Reference corresponding GitHub issues in PR descriptions

### Task Execution Template

For each task:

```bash
# 1. Make sure you're on master branch
git checkout master
git pull origin master

# 2. Make changes
# [Execute the specific task actions]

# 3. Test changes
make -j$(nproc)
make check

# 4. Commit and push directly to master
git add .
git commit -m "feat: [task description]"
git push origin master

# 5. Optional: Create PR if collaborating
# Link to issue: "Closes #[issue-number]"
```

### Validation Checklist

Before committing each change:

- [ ] Code compiles without errors
- [ ] Unit tests pass
- [ ] No regressions in existing functionality
- [ ] Changes are atomic and focused
- [ ] Documentation updated if needed
- [ ] Commit message follows conventional format

### Priority Order

1. **Phase 1**: Branding & Constants (Foundation)
2. **Phase 2**: Reward Split & Smartnode Logic (Core functionality)
3. **Phase 3**: Genesis & Network Parameters (Network setup)
4. **Phase 4**: UI & Assets (User experience)
5. **Phase 5**: Build & Testing (Quality assurance)
6. **Phase 6**: Documentation (User support)

---

**This task list provides CursorAI with specific, actionable steps to implement the HashmonkeyCoin fork systematically and safely.**
