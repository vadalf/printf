cmake_minimum_required(VERSION 3.14)

project(printfTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)
include(../cmake/windows-set-path.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(printf REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(printf_test source/printf_test.cpp)
target_link_libraries(printf_test PRIVATE printf::printf)
target_compile_features(printf_test PRIVATE cxx_std_17)

add_test(NAME printf_test COMMAND printf_test)
windows_set_path(printf_test printf::printf)
set_property(TEST printf_test PROPERTY FAIL_REGULAR_EXPRESSION "%[hldu]")

# ---- End-of-file commands ----

add_folders(Test)
