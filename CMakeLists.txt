cmake_minimum_required(VERSION 3.25)

# Modern CMake policies
cmake_policy(SET CMP0091 NEW) # MSVC runtime library flags
cmake_policy(SET CMP0092 NEW) # MSVC warning flags

project(MyGameEngine 
    VERSION 0.1.0 
    LANGUAGES CXX
    DESCRIPTION "Modern C++23 Game Engine"
)

# ============================================================================
# Global Settings
# ============================================================================

# C++23 standard requirement
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories for better organization
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Multi-config generators support (Debug/Release/etc.)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_BINARY_DIR}/lib/${OUTPUTCONFIG})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_BINARY_DIR}/lib/${OUTPUTCONFIG})
endforeach()

# ============================================================================
# Build Options
# ============================================================================

option(BARBEL_BUILD_TESTS "Build unit tests" OFF)
option(BARBEL_ENABLE_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)
option(BARBEL_ENABLE_SANITIZERS "Enable sanitizers in Debug builds" OFF)
option(BARBEL_ENABLE_LTO "Enable Link Time Optimization in Release builds" ON)

# ============================================================================
# Compiler Settings
# ============================================================================

# Create interface library for common compiler settings
add_library(barbel_compiler_options INTERFACE)

# MSVC specific settings
if(MSVC)
    target_compile_options(barbel_compiler_options INTERFACE
        /W4                     # Warning level 4
        /permissive-           # Standards conformance mode
        /Zc:__cplusplus        # Enable updated __cplusplus macro
        /Zc:preprocessor       # Enable conforming preprocessor
        /MP                     # Multi-processor compilation
        /utf-8                  # UTF-8 source and execution charset
    )
    
    if(BARBEL_ENABLE_WARNINGS_AS_ERRORS)
        target_compile_options(barbel_compiler_options INTERFACE /WX)
    endif()
    
    # Release optimizations
    target_compile_options(barbel_compiler_options INTERFACE
        $<$<CONFIG:Release>:/O2>           # Maximum optimization
        $<$<CONFIG:Release>:/Ob3>          # Aggressive inlining
        $<$<CONFIG:Release>:/GL>           # Whole program optimization
    )
    
    # Link-time optimization
    if(BARBEL_ENABLE_LTO)
        target_link_options(barbel_compiler_options INTERFACE
            $<$<CONFIG:Release>:/LTCG>     # Link-time code generation
            $<$<CONFIG:Release>:/OPT:REF>  # Remove unreferenced functions/data
            $<$<CONFIG:Release>:/OPT:ICF>  # Identical COMDAT folding
        )
    endif()
    
    # Debug settings
    target_compile_options(barbel_compiler_options INTERFACE
        $<$<CONFIG:Debug>:/Od>             # Disable optimization
        $<$<CONFIG:Debug>:/Zi>             # Debug information
        $<$<CONFIG:Debug>:/RTC1>           # Runtime checks
    )
    
# GCC/Clang settings
else()
    target_compile_options(barbel_compiler_options INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wnull-dereference
    )
    
    if(BARBEL_ENABLE_WARNINGS_AS_ERRORS)
        target_compile_options(barbel_compiler_options INTERFACE -Werror)
    endif()
    
    # Release optimizations
    target_compile_options(barbel_compiler_options INTERFACE
        $<$<CONFIG:Release>:-O3>
        $<$<CONFIG:Release>:-march=native>
    )
    
    # Link-time optimization
    if(BARBEL_ENABLE_LTO)
        target_compile_options(barbel_compiler_options INTERFACE
            $<$<CONFIG:Release>:-flto>
        )
        target_link_options(barbel_compiler_options INTERFACE
            $<$<CONFIG:Release>:-flto>
        )
    endif()
endif()

# ============================================================================
# Sanitizers (Debug builds)
# ============================================================================

if(BARBEL_ENABLE_SANITIZERS AND NOT MSVC)
    target_compile_options(barbel_compiler_options INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address>
        $<$<CONFIG:Debug>:-fsanitize=undefined>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
    )
    target_link_options(barbel_compiler_options INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address>
        $<$<CONFIG:Debug>:-fsanitize=undefined>
    )
endif()

# ============================================================================
# Subdirectories
# ============================================================================

add_subdirectory(Engine)
add_subdirectory(Sandbox)

# ============================================================================
# IDE Support
# ============================================================================

# Set Sandbox as startup project in Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

# Organize targets into folders in IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON)