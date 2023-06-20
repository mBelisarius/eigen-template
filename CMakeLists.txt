# =========================================================
# Eigen Template

cmake_minimum_required(VERSION 3.20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(ProjectName "eigen-template")
set(ProjectNamespace "eig_tmpl")

project("${ProjectName}")

set(CMAKE_CXX_STANDARD 14)

# =========================================================
# gtest

include(FetchContent)
FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(GTEST_FORCE_SHARED_CRT ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

set_property(TARGET gmock PROPERTY FOLDER "gtest")
set_property(TARGET gmock_main PROPERTY FOLDER "gtest")
set_property(TARGET gtest PROPERTY FOLDER "gtest")
set_property(TARGET gtest_main PROPERTY FOLDER "gtest")

# =========================================================
# Eigen

include(FetchContent)
FetchContent_Declare(Eigen
        URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(EIGEN_FORCE_SHARED_CRT ON CACHE BOOL "" FORCE)
set(EIGEN_BUILD_DOC OFF)
set(EIGEN_BUILD_PKGCONFIG OFF)
FetchContent_MakeAvailable(Eigen)

# =========================================================
# Targets

# --- main

add_library("${ProjectName}" STATIC
        src/information.cpp
        include/information.h)

target_link_libraries("${ProjectName}" PUBLIC Eigen3::Eigen)

target_include_directories("${ProjectName}" PUBLIC
        dependencies/submodules)

add_subdirectory(dependencies)

target_compile_definitions("${ProjectName}" PRIVATE PROJECT_NAMESPACE=${ProjectNamespace})

add_executable("${ProjectName}-main"
        src/main.cpp)

 target_link_libraries("${ProjectName}-main" PUBLIC "${ProjectName}")

# --- gtest

enable_testing()

add_executable("${ProjectName}-test"
        test/sanity_test.cpp
)

target_link_libraries("${ProjectName}-test"
        gtest_main
        "${ProjectName}")

include(GoogleTest)
gtest_discover_tests("${ProjectName}-test")

# =========================================================