# BarbelEngine - Modern CMake Build System

## Overview
BarbelEngine uses modern CMake (3.25+) with C++23 standard for game engine development.

## Quick Start

### Using CMakePresets.json (Recommended)

#### Windows + Visual Studio
```bash
# Configure
cmake --preset windows-msvc-debug

# Build
cmake --build --preset windows-msvc-debug

# Release build
cmake --preset windows-msvc-release
cmake --build --preset windows-msvc-release
```

#### Windows + Clang
```bash
cmake --preset windows-clang-debug
cmake --build --preset windows-clang-debug
```

#### Linux
```bash
# GCC
cmake --preset linux-gcc-debug
cmake --build --preset linux-gcc-debug

# Clang
cmake --preset linux-clang-debug
cmake --build --preset linux-clang-debug
```

### Traditional CMake (Manual)

```bash
# Create build directory
mkdir build
cd build

# Configure (Debug)
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug

# Configure (Release with optimizations)
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DBARBEL_ENABLE_LTO=ON

# Build
cmake --build .

# Run
./bin/Debug/Sandbox
```

## Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `BARBEL_BUILD_TESTS` | OFF | Build unit tests |
| `BARBEL_ENABLE_WARNINGS_AS_ERRORS` | ON | Treat compiler warnings as errors |
| `BARBEL_ENABLE_SANITIZERS` | OFF | Enable sanitizers (ASan, UBSan) in Debug |
| `BARBEL_ENABLE_LTO` | ON | Enable Link Time Optimization in Release |

### Example with Options
```bash
cmake -B build -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DBARBEL_BUILD_TESTS=ON \
  -DBARBEL_ENABLE_SANITIZERS=ON
```

## Project Structure

```
BarbelEngine/
├── CMakeLists.txt              # Root CMake configuration
├── CMakePresets.json           # CMake presets for easy configuration
├── cmake/
│   ├── CompilerWarnings.cmake  # Compiler warning settings
│   └── Sanitizers.cmake        # Sanitizer configuration
├── Engine/
│   ├── CMakeLists.txt          # Engine library configuration
│   ├── include/
│   │   └── Engine.h
│   └── src/
│       └── Engine.cpp
└── Sandbox/
    ├── CMakeLists.txt          # Sandbox application configuration
    └── src/
        └── Main.cpp
```

## CMake Features

### Modern Target-Based Approach
- Uses `target_*` commands instead of global variables
- Proper PUBLIC/PRIVATE/INTERFACE visibility
- Alias targets (`Barbel::Engine`) for consistent naming

### Compiler Settings
- **MSVC**: `/W4`, `/permissive-`, `/Zc:__cplusplus`, multi-processor compilation
- **GCC/Clang**: `-Wall -Wextra -Wpedantic` with additional warnings
- **Release**: Aggressive optimizations (`/O2`, `-O3`, LTO)
- **Debug**: Full debug info, runtime checks

### Platform Detection
Automatically defines:
- `BARBEL_PLATFORM_WINDOWS` on Windows
- `BARBEL_PLATFORM_LINUX` on Linux
- `BARBEL_PLATFORM_MACOS` on macOS

### Build Type Definitions
- `BARBEL_DEBUG` in Debug builds
- `BARBEL_RELEASE` in Release/RelWithDebInfo/MinSizeRel builds

## IDE Integration

### Visual Studio
Open folder or use:
```bash
cmake -B build -G "Visual Studio 17 2022"
# Open build/BarbelEngine.sln
```

### Visual Studio Code
1. Install CMake Tools extension
2. Select preset from status bar
3. Build and debug using UI

### CLion
Automatically detects CMakePresets.json

## Advanced Usage

### Adding External Libraries
Edit `Engine/CMakeLists.txt`:
```cmake
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Engine PUBLIC glfw)
```

### Precompiled Headers
Uncomment in `Engine/CMakeLists.txt`:
```cmake
target_precompile_headers(Engine
    PRIVATE
        <iostream>
        <memory>
        <vector>
)
```

### Custom Build Types
```bash
# Profile build with debug info and optimizations
cmake -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
```

## Troubleshooting

### Ninja not found
Install Ninja: `choco install ninja` (Windows) or `apt install ninja-build` (Linux)

### C++23 not supported
Update your compiler:
- **MSVC**: Visual Studio 2022 17.5+
- **GCC**: 11+
- **Clang**: 15+

### Sanitizer issues on Windows
Use `windows-clang-debug` preset with clang-cl

## Best Practices

1. **Always use presets** for consistent builds
2. **Enable warnings as errors** during development
3. **Use sanitizers** in Debug builds to catch bugs early
4. **Enable LTO** for Release builds for maximum performance
5. **Keep CMake files modular** - one target per CMakeLists.txt

## Next Steps

- Add unit testing framework (Google Test, Catch2)
- Set up continuous integration (GitHub Actions)
- Add clang-format and clang-tidy
- Configure package management (vcpkg, Conan)
