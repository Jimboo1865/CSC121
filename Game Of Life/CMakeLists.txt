cmake_minimum_required(VERSION 3.16)
project(GameofLife)

set(CMAKE_CXX_STANDARD 17)

# Create the executable
add_executable(GameofLife GameofLife.cpp)

# Set path to SFML
set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.2/lib/cmake/SFML")

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Explicitly include SFML headers
include_directories("/opt/homebrew/Cellar/sfml/3.0.2/include")

# Link SFML
target_link_libraries(GameofLife PRIVATE SFML::Graphics SFML::Window SFML::System)