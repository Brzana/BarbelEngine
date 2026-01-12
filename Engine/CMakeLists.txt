# ============================================================================
# Engine Library Target
# ============================================================================

# Collect source files (avoid GLOB_RECURSE in production - list explicitly)
file(GLOB ENGINE_SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
)

file(GLOB ENGINE_HEADERS CONFIGURE_DEPENDS
    "include/*.h"
)

# Create static library target
add_library(Engine STATIC
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

# Add alias for consistent namespacing
add_library(Barbel::Engine ALIAS Engine)

# ============================================================================
# Include Directories
# ============================================================================

target_include_directories(Engine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ============================================================================
# Compiler Features & Options
# ============================================================================

# Require C++23
target_compile_features(Engine PUBLIC cxx_std_23)

# Link common compiler options
target_link_libraries(Engine PUBLIC barbel_compiler_options)

# ============================================================================
# Precompiled Headers (optional - uncomment when needed)
# ============================================================================

# target_precompile_headers(Engine
#     PRIVATE
#         <iostream>
#         <memory>
#         <vector>
#         <string>
# )

# ============================================================================
# Platform-Specific Settings
# ============================================================================

if(WIN32)
    target_compile_definitions(Engine
        PUBLIC
            BARBEL_PLATFORM_WINDOWS
            WIN32_LEAN_AND_MEAN
            NOMINMAX
    )
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(Engine PUBLIC BARBEL_PLATFORM_LINUX)
elseif(APPLE)
    target_compile_definitions(Engine PUBLIC BARBEL_PLATFORM_MACOS)
endif()

# ============================================================================
# Build Type Definitions
# ============================================================================

target_compile_definitions(Engine
    PUBLIC
        $<$<CONFIG:Debug>:BARBEL_DEBUG>
        $<$<CONFIG:Release>:BARBEL_RELEASE>
        $<$<CONFIG:RelWithDebInfo>:BARBEL_RELEASE>
        $<$<CONFIG:MinSizeRel>:BARBEL_RELEASE>
)

# ============================================================================
# IDE Organization
# ============================================================================

# Source groups for better IDE organization
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Header Files" FILES ${ENGINE_HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${ENGINE_SOURCES})

# Set folder in IDE
set_target_properties(Engine PROPERTIES FOLDER "Engine")

# ============================================================================
# External Dependencies (example - uncomment when needed)
# ============================================================================

# find_package(glfw3 CONFIG REQUIRED)
# target_link_libraries(Engine PUBLIC glfw)

# find_package(glad CONFIG REQUIRED)
# target_link_libraries(Engine PRIVATE glad::glad)