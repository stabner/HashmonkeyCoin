# MiningCore Compatibility with GhostRiderV2 POW

## Summary

**Short Answer: You WILL need to make changes to MiningCore** (or use a custom fork) because the POW algorithm has been fundamentally modified.

## What We Changed

### Original GhostRider (V1) Algorithm:
- **18 rounds** of hashing
- **3 Cryptonight variants** per block
- Pattern: Multiple coreHash → 3 CN variants → More coreHash → Final hash

### GhostRiderV2 Algorithm:
- **12 rounds** of hashing (33% reduction)
- **1 Cryptonight variant** per block (66% reduction)
- Pattern: **5 coreHash → 1 CN (Turtle/TurtleLite) → 5 coreHash → 1 SHA512**
- Prefers lighter CN variants (Turtle/TurtleLite) for Intel/GPU optimization

## Why MiningCore Needs Updates

MiningCore (or any mining pool software) needs to:

1. **Validate Shares**: The pool must verify that submitted shares meet the difficulty target using the **exact same POW algorithm** as the blockchain
2. **Calculate Difficulty**: The pool needs to understand the new hash pattern to calculate difficulty correctly
3. **Hash Function Implementation**: MiningCore must implement the same `HashGR` function with the new 12-round pattern

### Current Situation:

- **Your blockchain nodes**: Use the new 12-round optimized POW
- **MiningCore (standard)**: Expects the original 18-round GhostRider (V1) algorithm
- **Result**: Shares submitted to a standard MiningCore pool will be **rejected** because:
  - The hash function produces different results
  - The pool's validation will fail
  - Miners won't be able to submit valid shares

## Solutions

### Option 1: Fork and Modify MiningCore (Recommended)

You'll need to:

1. **Fork MiningCore** repository
2. **Update the GhostRider implementation** to match your GhostRiderV2 algorithm:
   - Change from 18 rounds to 12 rounds
   - Update hash pattern to: 5 coreHash → 1 CN → 5 coreHash → 1 SHA512
   - Update CN variant selection to prefer Turtle/TurtleLite
   - Reduce CN variants from 3 to 1

3. **Update share validation** to use the new hash function
4. **Test thoroughly** to ensure shares validate correctly

**Files in MiningCore that likely need modification:**
- GhostRiderV2 hash implementation (usually in a crypto/hash library)
- Share validation logic
- Difficulty calculation (if affected by the algorithm change)

### Option 2: Use a Custom Mining Pool Software

Instead of MiningCore, you could:
- Build a custom pool using your node's RPC interface
- Use a simpler pool implementation that you can modify
- Create a pool that directly uses your node's validation

### Option 3: Keep Original Algorithm for Pool Compatibility

If you want to use standard MiningCore without modifications:
- Keep the original 18-round GhostRider (V1) algorithm
- This means you won't get the Intel/GPU optimization benefits
- But pools will work out of the box

## Technical Details

### Hash Function Signature (Should Remain the Same):
```cpp
uint256 HashGR(const uint8_t* data, size_t len, const uint256& prevBlockHash);
```

### What Changed Internally:
- Number of rounds: 18 → 12
- Hash pattern structure
- CN variant selection and count
- Final hash step (SHA512 instead of previous final step)

### What MiningCore Needs:

1. **Exact HashGR Implementation**: Must match your `src/hash.h` implementation exactly
2. **HashSelection Logic**: Must use the same deterministic algorithm selection based on `prevBlockHash`
3. **CN Variant Support**: Must support CN_Turtle and CN_TurtleLite (which it likely already does)
4. **12-Round Pattern**: Must implement the new 5→1→5→1 pattern

## Testing Strategy

Before deploying to mainnet:

1. **Test with Regtest**: Verify the new POW works correctly
2. **Test Pool Integration**: Set up a test pool with modified MiningCore
3. **Validate Shares**: Ensure miners can submit valid shares
4. **Compare Hash Results**: Verify pool and node produce identical hashes for the same input

## Recommendation

Since you've already modified the POW algorithm for optimization, you should:

1. **Fork MiningCore** and update it to match your new algorithm
2. **Create a custom pool** for HashmonkeyCoin with the modified POW
3. **Document the changes** so other pool operators can update their setups
4. **Provide a reference implementation** of the new HashGR function for pool developers

## Alternative: Stratum Protocol Compatibility

If you're using the Stratum protocol:
- The protocol itself doesn't care about the POW algorithm
- But the pool's share validation must match your node's validation
- Miners can use any miner that implements your new HashGR function
- The pool must validate shares using the same HashGR function

## Conclusion

**Yes, you will need to modify MiningCore** (or use a custom fork) because:
- The POW algorithm is fundamentally different (12 rounds vs 18 rounds)
- The hash pattern has changed
- Share validation will fail with standard MiningCore

The good news is that MiningCore is open source, so you can fork it and make the necessary changes. The changes will primarily be in the hash function implementation and share validation logic.

