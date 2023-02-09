cmake_minimum_required(VERSION 3.21)
project(CMakeSFMLProject LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)" OFF)

include(FetchContent)

# Download SFML
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

# Download Box2D
FetchContent_Declare(
  box2d
  GIT_REPOSITORY https://github.com/erincatto/box2d.git
  GIT_TAG main
)
FetchContent_MakeAvailable(box2d)

# Add the Box2D headers to the include directories
include_directories(${box2d_SOURCE_DIR}/include/Box2D)

# Add the executable target
add_executable(CMakeSFMLProject src/main.cpp)

# Link SFML and Box2D to the target
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics box2d)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

# Copy shared libraries on Windows
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET CMakeSFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:CMakeSFMLProject> $<TARGET_FILE_DIR:CMakeSFMLProject> COMMAND_EXPAND_LISTS)
endif()

# Install the target
install(TARGETS CMakeSFMLProject)

