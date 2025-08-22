# Building HashmonkeyCoin Core for Windows

## Quick Build Commands

### Standard Build (Single Core)
```bash
PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g')
sudo bash -c "echo 0 > /proc/sys/fs/binfmt_misc/status"
cd depends
make HOST=x86_64-w64-mingw32
cd ..
./autogen.sh
CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/
make
sudo bash -c "echo 1 > /proc/sys/fs/binfmt_misc/status"
```

### Fast Build (Multi-Core - Recommended)
```bash
PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g')
sudo bash -c "echo 0 > /proc/sys/fs/binfmt_misc/status"
cd depends
make HOST=x86_64-w64-mingw32 -j$(nproc)
cd ..
./autogen.sh
CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/
make -j$(nproc)
sudo bash -c "echo 1 > /proc/sys/fs/binfmt_misc/status"
```

### Ultra Fast Build (All Cores)
```bash
PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g')
sudo bash -c "echo 0 > /proc/sys/fs/binfmt_misc/status"
cd depends
make HOST=x86_64-w64-mingw32 -j$(nproc)
cd ..
./autogen.sh
CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/
make -j$(nproc) -O
sudo bash -c "echo 1 > /proc/sys/fs/binfmt_misc/status"
```

## Build Speed Optimization Tips

### 1. **Parallel Compilation**
- Use `-j$(nproc)` to use all available CPU cores
- Use `-j4` for 4 cores, `-j8` for 8 cores, etc.
- The `-O` flag enables parallel job scheduling

### 2. **Skip Dependencies (If Already Built)**
If you've already built dependencies, you can skip that step:
```bash
cd depends
make HOST=x86_64-w64-mingw32 -j$(nproc)
cd ..
./autogen.sh
CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/
make -j$(nproc)
```

### 3. **Clean Build vs Incremental**
- **Incremental build** (faster): Just run `make -j$(nproc)` if you only changed source files
- **Clean build**: Run `make clean` first if you changed configuration or dependencies

### 4. **System Optimization**
- Close other applications to free up RAM and CPU
- Ensure you have at least 8GB RAM available
- Use an SSD for faster disk I/O

## Expected Build Times
- **Single core**: 2-4 hours
- **4 cores**: 45-90 minutes  
- **8 cores**: 25-45 minutes
- **16+ cores**: 15-30 minutes

## Troubleshooting
If you get memory errors with high `-j` values, reduce the number:
```bash
make -j4  # Use 4 cores instead
```

## Prerequisites

### Install Required Dependencies

```bash
# Update package list
sudo apt update

# Install cross-compilation toolchain
sudo apt install -y gcc-mingw-w64 g++-mingw-w64 mingw-w64-tools

# Install build dependencies
sudo apt install -y build-essential libtool autotools-dev automake pkg-config bsdmainutils python3

# Install additional dependencies
sudo apt install -y libssl-dev libevent-dev libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev

# Install Qt5 development packages (Ubuntu 24.04 compatible)
sudo apt install -y qtbase5-dev qttools5-dev-tools qt5-qmake

# Install Berkeley DB and other libraries
sudo apt install -y libdb++-dev libminiupnpc-dev libnatpmp-dev
```

## Build Process

### Step 1: Clone the Repository

```bash
git clone https://github.com/stabner/HashmonkeyCoin.git
cd HashmonkeyCoin
```

### Step 2: Clean Environment and Build Dependencies

```bash
# Clean Windows PATH variables that might interfere
export PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g')

# Build dependencies for Windows cross-compilation
cd depends
make HOST=x86_64-w64-mingw32 -j$(nproc)
cd ..
```

### Step 3: Configure and Build

```bash
# Regenerate autotools files
./autogen.sh

# Configure for Windows cross-compilation
CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/ --host=x86_64-w64-mingw32

# Build the project
make -j$(nproc)
```

## Troubleshooting

### Common Issues and Solutions

#### 1. "Cannot determine executable suffix" Error

This error has been fixed in the latest version. If you still encounter it:

```bash
# Clean everything and rebuild
cd depends
make clean
cd ..
make clean

# Rebuild dependencies
cd depends
make HOST=x86_64-w64-mingw32 V=1
cd ..
```

#### 2. Qt5 Not Found

If you get Qt5-related errors:

```bash
# Install Qt5 from universe repository
sudo add-apt-repository universe
sudo apt update
sudo apt install -y qt5-default

# Or use Qt6 (if Qt5 is not available)
sudo apt install -y qt6-base-dev qt6-tools-dev-tools
```

#### 3. Missing Dependencies

If you get missing dependency errors:

```bash
# Install additional packages
sudo apt install -y libminiupnpc-dev libnatpmp-dev libdb++-dev
sudo apt install -y libssl-dev libevent-dev
sudo apt install -y libboost-all-dev
```

#### 4. Build Fails with Compilation Errors

If you encounter compilation errors:

```bash
# Build with verbose output to see detailed errors
make V=1

# Or build with fewer parallel jobs
make -j1
```

## Build Output

After successful build, you should find the following Windows executables in the `src` directory:

- `hashmonkeycoind.exe` - The HashmonkeyCoin daemon
- `hashmonkeycoin-qt.exe` - The HashmonkeyCoin GUI wallet
- `hashmonkeycoin-cli.exe` - The HashmonkeyCoin command-line interface
- `hashmonkeycoin-wallet.exe` - The HashmonkeyCoin wallet tool

## Verification

To verify the build was successful:

```bash
# Check if executables were created
ls -la src/*.exe

# Test the daemon
./src/hashmonkeycoind.exe --version

# Test the GUI
./src/hashmonkeycoin-qt.exe --version
```

## Notes

- The build process may take 30-60 minutes depending on your system
- Make sure you have at least 4GB of free disk space
- The build system has been optimized for WSL Ubuntu 24.04
- All critical build issues have been fixed in the source code

## Support

If you encounter any issues not covered in this guide, please:

1. Check the troubleshooting section above
2. Ensure you're using the latest version from GitHub
3. Report issues on the GitHub repository with detailed error messages
