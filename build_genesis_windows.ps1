# HashmonkeyCoin Genesis Block Generator for Windows
# This is a simplified version that works without the full Raptoreum build

Write-Host "HashmonkeyCoin Genesis Block Generator (Windows)" -ForegroundColor Green
Write-Host "===============================================" -ForegroundColor Green
Write-Host ""

# Check if g++ is available
try {
    $gppVersion = g++ --version 2>$null
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✅ g++ found. Building genesis generator..." -ForegroundColor Green
        
        # Build the Windows genesis generator
        g++ -std=c++17 -o genesis_generator_windows.exe genesis_generator_windows.cpp
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host "✅ Genesis generator built successfully!" -ForegroundColor Green
            Write-Host ""
            Write-Host "Running genesis block generation..." -ForegroundColor Yellow
            Write-Host ""
            
            # Run the generator
            .\genesis_generator_windows.exe
        } else {
            Write-Host "❌ Failed to build genesis generator" -ForegroundColor Red
        }
    } else {
        throw "g++ not found"
    }
} catch {
    Write-Host "❌ g++ not found. Please install a C++ compiler:" -ForegroundColor Red
    Write-Host ""
    Write-Host "Option 1: Install MinGW-w64" -ForegroundColor Yellow
    Write-Host "  - Download from: https://www.mingw-w64.org/downloads/"
    Write-Host "  - Or use MSYS2: https://www.msys2.org/"
    Write-Host ""
    Write-Host "Option 2: Install Visual Studio Build Tools" -ForegroundColor Yellow
    Write-Host "  - Download from: https://visualstudio.microsoft.com/downloads/"
    Write-Host "  - Install C++ build tools"
    Write-Host ""
    Write-Host "Option 3: Use WSL (Windows Subsystem for Linux)" -ForegroundColor Yellow
    Write-Host "  - Install WSL2 and Ubuntu"
    Write-Host "  - Run the Linux version of the genesis generator"
    Write-Host ""
    Write-Host "Option 4: Use the simplified approach below" -ForegroundColor Yellow
    Write-Host ""
    
    # Provide manual values as fallback
    Write-Host "Manual Genesis Block Parameters (for testing):" -ForegroundColor Cyan
    Write-Host "=============================================" -ForegroundColor Cyan
    Write-Host "nTime: 1759752916" -ForegroundColor White
    Write-Host "nNonce: 12345 (placeholder - needs proper mining)" -ForegroundColor White
    Write-Host "nBits: 0x20001fff" -ForegroundColor White
    Write-Host "nVersion: 4" -ForegroundColor White
    Write-Host "genesisReward: 5000 * COIN" -ForegroundColor White
    Write-Host ""
    Write-Host "For now, you can use these placeholder values to test the daemon startup." -ForegroundColor Yellow
    Write-Host "Later, when you have a proper build environment, generate the real genesis block." -ForegroundColor Yellow
}

Write-Host ""
Write-Host "Next Steps:" -ForegroundColor Green
Write-Host "1. If the generator ran successfully, copy the output values to chainparams.cpp" -ForegroundColor White
Write-Host "2. If not, use the placeholder values above for testing" -ForegroundColor White
Write-Host "3. Build the main HashmonkeyCoin project" -ForegroundColor White
Write-Host "4. Test daemon startup with: ./hashmonkeycoind --daemon" -ForegroundColor White
Write-Host "5. Generate spork keys once the daemon is running" -ForegroundColor White
