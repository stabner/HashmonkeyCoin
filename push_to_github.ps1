# Script to push HashmonkeyCoin changes to GitHub
# This will commit all changes and push to the master branch

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "HashmonkeyCoin - Push to GitHub" -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host ""

# Change to repository directory
Set-Location "C:\Users\thest\Desktop\HMNY2 - Copy\HashmonkeyCoin"

# Check if we're in a git repository
if (-not (Test-Path .git)) {
    Write-Host "Error: Not a git repository!" -ForegroundColor Red
    exit 1
}

# Show current status
Write-Host "Current git status:" -ForegroundColor Yellow
git status --short
Write-Host ""

# Add all modified and new files (excluding build artifacts)
Write-Host "Adding modified source files..." -ForegroundColor Yellow
git add -u

# Add new documentation and script files
Write-Host "Adding new documentation files..." -ForegroundColor Yellow
git add GENESIS_BLOCK_MINING_GUIDE.md
git add HARD_FORK_GENESIS_BLOCK.md
git add MININGCORE_COMPATIBILITY.md
git add NEXT_STEPS.md
git add POW_OPTIMIZATION_PLAN.md
git add POW_OPTIMIZATION_SUMMARY.md
git add QUICK_TEST_GUIDE.md
git add TESTING_GUIDE.md
git add mine_genesis_blocks.cpp
git add prepare_genesis_mining.sh
git add replace_raptoreum_references.sh

# Don't add build artifacts
Write-Host "Excluding build artifacts..." -ForegroundColor Yellow
git reset HEAD src/config/hashmonkeycoin-config.h 2>$null
git reset HEAD src/config/hashmonkeycoin-config.h.in 2>$null
git reset HEAD src/hashmonkeycoin-cli 2>$null
git reset HEAD src/hashmonkeycoin-wallet 2>$null
git reset HEAD src/hashmonkeycoind 2>$null
git reset HEAD src/qt/hashmonkeycoin-qt 2>$null
git reset HEAD configure~ 2>$null
git reset HEAD src/dashbls/configure~ 2>$null
git reset HEAD .lineno 2>$null
git reset HEAD test_regtest.bat 2>$null

# Show what will be committed
Write-Host ""
Write-Host "Files staged for commit:" -ForegroundColor Green
git status --short
Write-Host ""

# Create commit message
$commitMessage = "Update HashmonkeyCoin with GhostRiderV2 POW and branding changes`n`nMajor Changes:`n- Implemented GhostRiderV2 POW algorithm (optimized 12-round version)`n- Updated all Raptoreum references to HashmonkeyCoin`n- Updated copyright notices (2020-2024 Raptoreum, 2025+ HashmonkeyCoin)`n- Prepared genesis blocks for mining with new POW algorithm`n- Updated version to 1.0.0.0`n- Updated all user-facing strings and error messages`n- Added comprehensive documentation for genesis block mining`n`nPOW Optimization:`n- Reduced from 18 to 12 rounds (33% reduction)`n- Reduced CN variants from 3 to 1 (66% reduction)`n- Prefer lighter CN variants (Turtle/TurtleLite) for Intel/GPU performance`n- New pattern: 5 coreHash -> 1 CN -> 5 coreHash -> 1 SHA512`n`nGenesis Blocks:`n- Updated messages to reflect GhostRiderV2 POW`n- Prepared for mining new genesis blocks for all networks`n- Added CreateRegtestGenesisBlock function`n- Updated timestamps to January 2025`n`nDocumentation:`n- Added GENESIS_BLOCK_MINING_GUIDE.md`n- Added POW optimization documentation`n- Added testing guides`n- Added MiningCore compatibility guide"

# Commit changes
Write-Host "Creating commit..." -ForegroundColor Yellow
git commit -m $commitMessage

if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Write-Host "✓ Commit created successfully!" -ForegroundColor Green
    Write-Host ""
    Write-Host "Ready to push to GitHub. Run the following command:" -ForegroundColor Cyan
    Write-Host "  git push origin master" -ForegroundColor White
    Write-Host ""
    Write-Host "Or press Enter to push now (Ctrl+C to cancel)..." -ForegroundColor Yellow
    Read-Host
    
    Write-Host "Pushing to GitHub..." -ForegroundColor Yellow
    git push origin master
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host ""
        Write-Host "✓ Successfully pushed to GitHub!" -ForegroundColor Green
        Write-Host "  Repository: https://github.com/stabner/HashmonkeyCoin" -ForegroundColor Cyan
    } else {
        Write-Host ""
        Write-Host "✗ Push failed. You may need to authenticate or resolve conflicts." -ForegroundColor Red
        Write-Host "  Check your GitHub credentials or run: git push origin master" -ForegroundColor Yellow
    }
} else {
    Write-Host ""
    Write-Host "✗ Commit failed. Check the error messages above." -ForegroundColor Red
}

