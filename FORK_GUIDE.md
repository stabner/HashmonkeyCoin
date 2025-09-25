# HashmonkeyCoin Fork Guide

**The Ultimate Forking Plan for CursorAI & Developers**

This guide provides a complete, phased approach to forking Raptoreum into HashmonkeyCoin with specific technical parameters and implementation steps.

## 🎯 Project Parameters

- **Initial block reward**: 500 HMNY
- **Total supply cap**: 21,000,000,000 HMNY (same as Raptoreum)
- **Halving interval**: 131,400 blocks (~1 year at 2-minute blocks)
- **Smartnode reward**: 5% of each block reward
- **Genesis message**: "HashmonkeyCoin Genesis: HashmonkeyCoin Launch 25 September 2025 - mainnet"

## 📋 Development Phases

### Phase 0 — Planning & Repository Setup ✅
**Status**: COMPLETED
- [x] Fork repository setup
- [x] GitHub Actions CI/CD pipeline
- [x] Issue and PR templates
- [x] Branch protection strategy
- [x] Documentation structure

### Phase 1 — Branding & Constants
**Deliverables**: String & ticker replaced; constants updated

**Tasks**:
- Replace Raptoreum branding with HashmonkeyCoin/HMNY
- Update `chainparams.cpp` constants (max money, halving interval, block time, default ports)
- Add collateral constants

**Acceptance Criteria**:
- [ ] Builds compile successfully
- [ ] Unit tests for subsidy pass
- [ ] `GetBlockSubsidy` reflects 500 HMNY initial and halving interval

### Phase 2 — Reward Split & Smartnode Logic
**Deliverables**: Smartnode payout = 5%, spork IDs added

**Tasks**:
- Modify subsidy distribution to allocate 5% to smartnode
- Set smartnode collateral constant(s)
- Add spork IDs and defaults

**Acceptance Criteria**:
- [ ] Regtest block tests show correct distribution
- [ ] Smartnode registration flows work in regtest

### Phase 3 — Genesis & Network Parameters
**Deliverables**: Mined genesis with requested message, updated chainparams

**Tasks**:
- Add genesis coinbase message
- Run mining helper
- Update chainparams with hashGenesisBlock, hashMerkleRoot, nTime, nNonce

**Acceptance Criteria**:
- [ ] Node boots and accepts genesis hash
- [ ] `getblockhash(0)` equals your genesis hash

### Phase 4 — UI & Assets
**Deliverables**: Icons added; QT builds

**Tasks**:
- Copy images into Qt resources
- Update `.qrc` files
- Update wallet metadata (name, symbols)

**Acceptance Criteria**:
- [ ] Qt wallet icon/splash show new assets

### Phase 5 — Build & Test
**Deliverables**: Regtest & testnet nodes, CI build passing

**Tasks**:
- Create regtest scripts
- Run automated tests
- Deploy testnet

**Acceptance Criteria**:
- [ ] Testnet runs successfully
- [ ] Validators confirm block rewards & MN payouts
- [ ] CI pipeline passes

### Phase 6 — Launch & Operations
**Deliverables**: Mainnet genesis release, seed node list, explorer

**Tasks**:
- Set up seed nodes
- Create deployment instructions for masternode operators
- Publish genesis data and release binaries

**Acceptance Criteria**:
- [ ] Mainnet launch announced
- [ ] First blocks mined
- [ ] Masternodes connect and receive rewards

### Phase 7 — Post-Launch & Maintenance
**Deliverables**: Monitoring, bugfixes, upgrades

**Tasks**:
- Set up monitoring and alerting
- Update documentation
- Create upgrade plan for future hard/soft forks

**Acceptance Criteria**:
- [ ] Monitoring alerts tested
- [ ] First monthly report produced

## 🔧 Technical Implementation

### 3.1 Branding & Ticker Replacement

**Search & Replace (CASE-SENSITIVE)**:
```
Raptoreum → HashmonkeyCoin
raptoreum → hashmonkeycoin
RTM → HMNY
rtm → hmny (be careful with code variable names)
Raptoreum.conf → HashmonkeyCoin.conf
```

### 3.2 Chain Parameters (`src/chainparams.cpp`)

**Mainnet Constants**:
```cpp
// *** MAINNET ***
pchMessageStart[0] = 0x4b;
pchMessageStart[1] = 0x7f;
pchMessageStart[2] = 0xa1;
pchMessageStart[3] = 0xbc;

nDefaultPort = 28600; // pick an unused port
nRPCPort = 28601;

consensus.nSubsidyHalvingInterval = 131400; // ~1 year at 2 min block time
consensus.nPowTargetSpacing = 120; // 2 minutes
consensus.nPowTargetTimespan = 120 * 2016; // optional, keep similar to base

consensus.nMaxMoney = 21000000000ULL * COIN; // 21 billion HMNY
```

### 3.3 Subsidy Function (`GetBlockSubsidy`)

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

### 3.4 Reward Split — Smartnode Payout = 5%

```cpp
CAmount nSubsidy = GetBlockSubsidy(nHeight, params);

// smartnode gets 5%
CAmount nSmartnodeReward = (nSubsidy * 5) / 100;
CAmount nMinerReward = nSubsidy - nSmartnodeReward;

// Add outputs in the block creation code accordingly
txNew.vout[0].nValue = nMinerReward;
txNew.vout[1].nValue = nSmartnodeReward; // pay to smartnode address selection
```

### 3.5 Smartnode Collateral

```cpp
static const CAmount SMARTNODE_COLLATERAL = 10000 * COIN; // recommended baseline
// optional: higher tiers
static const CAmount SMARTNODE_SUPERNODE_COLLATERAL = 100000 * COIN;
```

**Recommendations**:
- Standard MN: 10,000 HMNY (0.0000476% of supply) — accessible
- Supernode: 100,000 HMNY — stronger stake

### 3.6 Sporks

```cpp
static const int SPORK_17_SMARTNODE_REWARD = 10017; // example ID
mapSporkDefaults[SPORK_17_SMARTNODE_REWARD] = 0; // default off
```

### 3.7 Genesis Block (Placeholder Values)

```cpp
// genesis setup — use the mined values later
consensus.hashGenesisBlock = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
genesis = CreateGenesisBlock(
    1695571200, // example epoch for 25 Sep 2025 00:00:00 UTC (replace with exact)
    0,          // nonce (to be filled)
    0x1e0ffff0, // nBits (difficulty bits)
    1,          // version
    500 * COIN  // genesis block reward
);
consensus.hashGenesisBlock = genesis.GetHash();
assert(consensus.hashGenesisBlock == uint256S("0x...")); // replace after mining
assert(genesis.hashMerkleRoot == uint256S("0x...")); // replace after mining
```

## 🏗️ Genesis Block Creation

### Genesis Coinbase Message
```
"HashmonkeyCoin Genesis: HashmonkeyCoin Launch 25 September 2025 - mainnet"
```

### Mining Helper Approach
1. Create temporary program to loop nonces
2. Call `CreateGenesisBlock()` with the message
3. Increment nNonce and nTime until `genesis.GetHash() < target`
4. Record: hashGenesisBlock, hashMerkleRoot, nTime, nNonce
5. Update chainparams.cpp assertions

## 🎨 UI Assets Integration

**Asset Path**: `C:\Users\thest\Desktop\HashmonkeyCoin\image backup`

**Steps**:
1. Copy files to `src/qt/res/icons/`
2. Update `src/qt/res/icons.qrc`:
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

## 🧪 Build & Testing

### Local Testing (Regtest → Testnet → Mainnet)

```bash
# Configure & build
./autogen.sh
./configure --enable-cxx --with-gui
make -j$(nproc)

# Regtest quick checks
src/hashmonkeycoind -regtest -daemon
src/hashmonkeycoin-cli -regtest generate 150

# Validate reward split
# Mine a block and check coinbase outputs: 95% miner, 5% smartnode
```

## 🚀 Launch Steps

### Final Preparation
1. Finalize and sign spork keys offline
2. Tag v1.0.0 on main
3. Build release binaries for Linux, Windows, macOS
4. Publish release assets with checksums

### Seed Nodes
- Launch 3–5 publicly reachable seed nodes
- Add their IPs to chainparams.cpp vSeeds

### Mainnet Launch
1. Start mainnet seed nodes and miners
2. Start monitoring and ready hotfix branch
3. Publish genesis hash, merkle root, nTime, nNonce

## 🔒 Security & Governance

- Store keys (spork/owner) in secure hardware wallets or HSMs
- Keep backups with multisig
- Prepare recovery plan for genesis or spork errors
- Document Masternode/Smartnode operator guide

## 📝 CursorAI Task List

Copy these commands/tasks into CursorAI (each should be a small PR):

### `feature/branding`
- Replace branding strings (safe replacements)
- Update README

### `feature/consensus-emission`
- Update `src/chainparams.cpp` per constants above
- Update `GetBlockSubsidy` to initial 500 and halving interval 131400

### `feature/reward-split`
- Update payout logic to 5% smartnode share
- Add smartnode collateral constants

### `feature/sporks`
- Add new spork IDs and defaults in `src/spork.*`

### `feature/genesis`
- Add placeholder genesis values
- Create `tools/mine_genesis.cpp` (temporary) to run locally
- PR with mined values

### `feature/ui-assets`
- Add icon files and update `.qrc`

### `ci/add`
- Add `.github/workflows/ci.yml` with make build steps

### `docs/mn-operators`
- Add masternode operator guide to `docs/`

## ✅ Quick Action Checklist

- [ ] Fork Raptoreum / ensure base code in stabner/HashmonkeyCoin
- [ ] Create develop branch; protect main
- [ ] Apply branding PR
- [ ] Change consensus constants (131,400 halving, 21B cap, 2m spacing)
- [ ] Implement subsidy function (500 initial)
- [ ] Implement 5% smartnode payout + collateral constants
- [ ] Add spork IDs & defaults
- [ ] Create genesis helper, mine genesis and update chainparams
- [ ] Add icons, update .qrc
- [ ] Build and run regtest; validate payouts and smartnode logic
- [ ] CI passing; merge to main
- [ ] Build release binaries; prepare seed nodes; publish genesis & launch

## ⚠️ Important Notes

- Don't change too many names in one giant search/replace — make atomic PRs
- Keep nBits and difficulty tuning sensible
- Test smartnode payouts extensively on regtest before mainnet
- Ensure legal compliance in your jurisdictions if planning to list the coin

---

**This guide provides the complete roadmap for forking Raptoreum into HashmonkeyCoin with all technical specifications and implementation steps.**
