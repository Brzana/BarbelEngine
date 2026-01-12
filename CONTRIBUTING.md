# Contributing to BarbelEngine

First off, thank you for considering contributing to BarbelEngine! 🎉

## Code of Conduct

This project and everyone participating in it is governed by respect and professionalism. Please be kind and constructive in your interactions.

## How Can I Contribute?

### Reporting Bugs

Before creating bug reports, please check existing issues to avoid duplicates. When creating a bug report, include:

- **Clear title and description**
- **Steps to reproduce** the issue
- **Expected vs actual behavior**
- **System information** (OS, compiler, CMake version)
- **Code samples** if applicable
- **Screenshots** if relevant

**Bug Report Template:**
```markdown
**Environment:**
- OS: Windows 11 / Ubuntu 22.04 / macOS 13
- Compiler: MSVC 19.35 / GCC 12 / Clang 15
- CMake Version: 3.25+

**Description:**
A clear description of the bug.

**Steps to Reproduce:**
1. Step one
2. Step two
3. See error

**Expected Behavior:**
What should happen.

**Actual Behavior:**
What actually happens.

**Additional Context:**
Any other relevant information.
```

### Suggesting Enhancements

Enhancement suggestions are tracked as GitHub issues. When creating an enhancement suggestion, include:

- **Clear title and description**
- **Use case** - why is this useful?
- **Alternatives considered**
- **Additional context**

### Pull Requests

#### Before Submitting

1. **Check existing PRs** to avoid duplicates
2. **Discuss major changes** in an issue first
3. **Follow the coding standards** (see below)
4. **Test your changes** on multiple configurations if possible

#### Submitting a Pull Request

1. **Fork the repository** and create your branch from `main`
2. **Follow naming convention:** `feature/your-feature` or `fix/your-fix`
3. **Make your changes:**
   - Write clear, commented code
   - Follow the existing code style
   - Update documentation if needed
4. **Test thoroughly:**
   - Build in Debug and Release
   - Run existing tests
   - Test on Windows/Linux if possible
5. **Commit with meaningful messages:**
   ```
   feat: Add rendering system base
   fix: Resolve memory leak in Engine::cleanup
   docs: Update build instructions
   refactor: Simplify CMake configuration
   ```
6. **Push to your fork** and submit a pull request
7. **Respond to feedback** from reviewers

#### PR Checklist

- [ ] Code builds without warnings
- [ ] Code follows project style (.clang-format)
- [ ] Comments added for complex logic
- [ ] Documentation updated
- [ ] Tests pass (if applicable)
- [ ] Commit messages are clear

## Coding Standards

### C++ Style Guidelines

#### General Rules

- **Use C++23 features** when appropriate
- **Prefer STL containers** over custom implementations
- **Use smart pointers** (`std::unique_ptr`, `std::shared_ptr`) over raw pointers
- **Const correctness** - use `const` wherever possible
- **RAII principles** - manage resources automatically

#### Naming Conventions

```cpp
// Namespaces: PascalCase
namespace Engine {

// Classes/Structs: PascalCase
class RenderSystem {
public:
    // Public methods: camelCase
    void initialize();
    void update(float deltaTime);
    
    // Public members: m_camelCase (if absolutely necessary)
    
private:
    // Private methods: camelCase
    void processCommands();
    
    // Private members: m_camelCase
    int m_frameCount;
    bool m_isInitialized;
};

// Enums: PascalCase with PascalCase values
enum class ShaderType {
    Vertex,
    Fragment,
    Compute
};

// Constants: UPPER_CASE or kPascalCase
constexpr int MAX_LIGHTS = 8;
constexpr float kDefaultFOV = 60.0f;

// Functions: camelCase
void processInput();

// Variables: camelCase
int entityCount = 0;
float deltaTime = 0.016f;

} // namespace Engine
```

#### Code Formatting

Use `.clang-format` file in the repository:

```bash
# Format a single file
clang-format -i path/to/file.cpp

# Format all source files
find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i
```

**Key formatting rules:**
- **Indentation:** Tabs (4 spaces width)
- **Line length:** 120 characters maximum
- **Braces:** Allman style for functions/classes, same line for control flow (as per .clang-format)
- **Includes:** Grouped and sorted (Engine → Project → STL → External)

#### Example Code Style

```cpp
#pragma once

#include "Engine/Core.h"
#include <memory>
#include <vector>

namespace Engine
{

class Entity
{
public:
	Entity(int id, const std::string& name);
	~Entity() = default;

	// Getters
	int getId() const { return m_id; }
	const std::string& getName() const { return m_name; }

	// Methods
	void update(float deltaTime);
	bool isActive() const;

private:
	void processComponents();

	int m_id;
	std::string m_name;
	bool m_isActive{true};
	std::vector<std::shared_ptr<Component>> m_components;
};

} // namespace Engine
```

### CMake Guidelines

- **Modern CMake 3.25+** - use target-based approach
- **Explicit is better** - avoid `GLOB_RECURSE`, list files explicitly in production
- **Properties over variables** - use `target_*` commands
- **Document options** - add descriptions to `option()` commands

```cmake
# Good: Target-based
target_include_directories(Engine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Bad: Global variables
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
```

### Documentation

- **Use clear comments** for complex logic
- **Document public APIs** with brief descriptions
- **Update README.md** when adding features
- **Add examples** for new functionality

```cpp
/**
 * @brief Initializes the rendering system
 * @param width Window width in pixels
 * @param height Window height in pixels
 * @return true if initialization succeeded, false otherwise
 */
bool initialize(int width, int height);
```

## Git Workflow

### Branching Strategy

- `main` - stable, release-ready code
- `develop` - integration branch for features
- `feature/*` - new features
- `fix/*` - bug fixes
- `refactor/*` - code refactoring
- `docs/*` - documentation updates

### Commit Messages

Follow conventional commits:

```
<type>(<scope>): <subject>

<body>

<footer>
```

**Types:**
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes (formatting)
- `refactor`: Code refactoring
- `perf`: Performance improvements
- `test`: Adding tests
- `chore`: Build/tooling changes

**Examples:**
```
feat(renderer): Add Vulkan backend support

Implement basic Vulkan initialization and device selection.
Supports Windows and Linux platforms.

Closes #42
```

```
fix(engine): Resolve memory leak in entity destruction

Entity components were not properly released when entities
were destroyed, causing memory accumulation over time.
```

## Testing

### Building with Tests

```bash
cmake --preset windows-msvc-debug -DBARBEL_BUILD_TESTS=ON
cmake --build --preset windows-msvc-debug
ctest --preset windows-msvc-debug
```

### Writing Tests

- Use Google Test or Catch2 (when testing framework is added)
- Test edge cases and error conditions
- Keep tests fast and isolated
- Name tests clearly: `TestClass_MethodName_Scenario`

## Performance Considerations

- **Profile before optimizing** - use tools like Tracy, Visual Studio Profiler
- **Prefer cache-friendly data structures** - consider data-oriented design
- **Minimize allocations** - use object pools for frequently created/destroyed objects
- **Benchmark changes** - ensure optimizations actually improve performance

## Getting Help

- **GitHub Issues** - for bugs and feature requests
- **GitHub Discussions** - for questions and general discussion
- **Documentation** - check CMAKE_BUILD.md and README.md

## Recognition

Contributors will be recognized in:
- README.md acknowledgments section
- Release notes for significant contributions
- Project documentation

Thank you for contributing to BarbelEngine! 🚀
