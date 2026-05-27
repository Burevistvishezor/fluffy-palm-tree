cmake_minimum_required(VERSION 3.15)
project(fluffy-palm-tree)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(ENABLE_TESTING "Enable testing" ON)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h" "include/*.h")

# Create main library
add_library(${PROJECT_NAME}_lib ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME}_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Add executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

# Testing
if(ENABLE_TESTING)
  enable_testing()
  find_package(GTest CONFIG QUIET)
  
  if(NOT GTest_FOUND)
    message(STATUS "GTest not found, skipping tests")
  else()
    file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_lib GTest::gtest GTest::gtest_main)
    add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)
  endif()
endif()

# Code coverage
if(ENABLE_COVERAGE)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME}_lib PRIVATE --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(${PROJECT_NAME}_lib PRIVATE --coverage)
  endif()
endif()

# Installation
install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_lib
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(DIRECTORY include/ DESTINATION include)
