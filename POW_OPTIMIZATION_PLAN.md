# POW Optimization Plan - Reduce AMD Advantage, Boost Intel/GPU

## Current Implementation Analysis

**HashmonkeyCoin uses GhostRiderV2 algorithm (optimized version of GhostRider):**
- **18 rounds total** of hashing
- Pattern: 5 coreHash → 1 CN → 5 coreHash → 1 CN → 5 coreHash → 1 CN
- **3 Cryptonote variants** (memory-intensive, AMD-favored)
- **15 coreHash algorithms** (Blake, BMW, Groestl, JH, Keccak, Skein, Luffa, Cubehash, Shavite, Simd, Echo, Hamsi, Fugue, Shabal, Whirlpool, SHA512)

**Why AMD Dominates:**
1. **Cryptonote variants** use large scratchpads (262KB-2MB) - AMD's large L3 cache excels
2. **Memory latency** - AMD Ryzen has better memory subsystem
3. **Integer operations** - AMD handles Cryptonote's integer math better

## Optimization Strategy

### Method 1: Reduce Rounds & CN Usage (BIGGEST IMPACT)
- **Reduce from 18 to 12 rounds** (33% reduction)
- **Reduce CN variants from 3 to 1** (66% reduction)
- New pattern: 5 coreHash → 1 CN → 5 coreHash → 1 final hash
- **Expected impact:**
  - AMD: -15% to -30%
  - Intel: +20% to +40%
  - GPU: +10% to +25%

### Method 2: Add Intel-Optimized Algorithms
- Add SHA512 step (already available, increase usage)
- Add BLAKE2b (if available)
- Intel has strong SHA extensions and AVX2/AVX512

### Method 3: Reduce CN Scratchpad Sizes
- Modify CN variants to use smaller scratchpads
- Reduce iterations slightly
- This requires modifying `slow-hash.c`

## Implementation Files to Modify

1. **`src/hash.h`** - Modify `HashGR()` function
2. **`src/hash_selection.h`** - Adjust algorithm selection
3. **`src/cryptonote/slow-hash.h`** - Reduce CN scratchpad sizes (optional)

## Recommended Changes

### Change 1: Reduce Rounds (18 → 12)
- Remove last 6 rounds (which include 2 CN variants)
- Keep: 5 coreHash → 1 CN → 5 coreHash → 1 final hash

### Change 2: Prefer Intel-Friendly Algorithms
- Increase SHA512 usage in coreHash selection
- Prefer Groestl, Blake (Intel-friendly)

### Change 3: Use Lighter CN Variants
- Prefer CN_TURTLE or CN_TURTLE_LITE (smaller scratchpad)
- Reduce CN_DARK and CN_FAST usage

