# ============================================================================
# Sandbox Application Target
# ============================================================================

# Collect source files
file(GLOB SANDBOX_SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
)

# Create executable target
add_executable(Sandbox
    ${SANDBOX_SOURCES}
)

# ============================================================================
# Link Dependencies
# ============================================================================

# Link Engine library using alias for clarity
target_link_libraries(Sandbox
    PRIVATE
        Barbel::Engine
)

# ============================================================================
# Compiler Features
# ============================================================================

# Require C++23
target_compile_features(Sandbox PRIVATE cxx_std_23)

# ============================================================================
# Application Settings
# ============================================================================

# Set application properties
set_target_properties(Sandbox PROPERTIES
    OUTPUT_NAME "Sandbox"
    DEBUG_POSTFIX "_d"
)

# Windows subsystem (console application)
if(WIN32)
    # Use /SUBSYSTEM:CONSOLE for console output
    # Change to /SUBSYSTEM:WINDOWS for windowed application without console
    set_target_properties(Sandbox PROPERTIES
        WIN32_EXECUTABLE OFF  # Set to ON to hide console window
    )
endif()

# ============================================================================
# IDE Organization
# ============================================================================

# Source groups for IDE
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SANDBOX_SOURCES})

# Set folder in IDE
set_target_properties(Sandbox PROPERTIES FOLDER "Sandbox")

# Set as startup project in Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

# ============================================================================
# Working Directory for Debugging
# ============================================================================

# Set working directory for Visual Studio debugger
set_target_properties(Sandbox PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
)

# ============================================================================
# Asset Copying (example - uncomment when you have assets)
# ============================================================================

# Copy assets to output directory after build
# add_custom_command(TARGET Sandbox POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_CURRENT_SOURCE_DIR}/assets
#         $<TARGET_FILE_DIR:Sandbox>/assets
#     COMMENT "Copying assets to output directory"
# )