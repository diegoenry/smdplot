cmake_minimum_required(VERSION 3.10)
project(smd_plotter VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add sources
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(smd_plotter ${SOURCES})

# Install targets
install(TARGETS smd_plotter DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)

# Add tests subdirectory
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# Package configuration
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A terminal-based SMD data plotter")
set(CPACK_PACKAGE_VENDOR "Your Name")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
include(CPack)
