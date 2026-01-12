# BarbelEngine

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![CMake](https://img.shields.io/badge/CMake-3.25%2B-064F8C.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](https://github.com/yourusername/BarbelEngine)

A modern, cross-platform game engine built with C++23.

## 🎯 Features

- **Modern C++23** - Utilizes the latest C++ standard features
- **Cross-Platform** - Support for Windows, Linux, and macOS
- **CMake Build System** - Modern CMake 3.25+ with presets support
- **Modular Architecture** - Separated Engine library and Sandbox application
- **Developer-Friendly** - Comprehensive warnings, sanitizers, and debugging tools
- **Performance Optimized** - Link-Time Optimization (LTO) in Release builds

## Quick Start

### Prerequisites

- **CMake** 3.25 or higher
- **Ninja** build system
- **Compiler** with C++23 support:
  - MSVC 19.35+ (Visual Studio 2022 17.5+)
  - GCC 11+
  - Clang 15+

### Building the Project

#### Using CMake Presets

```bash
# Configure for Debug
cmake --preset windows-msvc-debug

# Build
cmake --build --preset windows-msvc-debug

# Run the Sandbox application
./build/windows-msvc-debug/bin/Debug/Sandbox.exe
```

### Available CMake Presets

| Preset | Platform | Compiler | Configuration |
|--------|----------|----------|---------------|
| `windows-msvc-debug` | Windows | MSVC | Debug |
| `windows-msvc-release` | Windows | MSVC | Release + LTO |
| `windows-msvc-relwithdebinfo` | Windows | MSVC | RelWithDebInfo |
| `windows-clang-debug` | Windows | Clang | Debug + Sanitizers |
| `linux-gcc-debug` | Linux | GCC | Debug + Sanitizers |
| `linux-clang-debug` | Linux | Clang | Debug + Sanitizers |

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `BARBEL_BUILD_TESTS` | OFF | Build unit tests |
| `BARBEL_ENABLE_WARNINGS_AS_ERRORS` | ON | Treat compiler warnings as errors |
| `BARBEL_ENABLE_SANITIZERS` | OFF | Enable sanitizers (ASan, UBSan) |
| `BARBEL_ENABLE_LTO` | ON | Enable Link Time Optimization |
