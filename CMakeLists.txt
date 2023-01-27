cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    printf
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    printf_printf
    source/printf.cpp
)
add_library(printf::printf ALIAS printf_printf)

include(GenerateExportHeader)
generate_export_header(
    printf_printf
    BASE_NAME printf
    EXPORT_FILE_NAME export/printf/printf_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(printf_printf PUBLIC PRINTF_STATIC_DEFINE)
endif()

set_target_properties(
    printf_printf PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME printf
    OUTPUT_NAME printf
)

target_include_directories(
    printf_printf ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    printf_printf SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(printf_printf PUBLIC cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT printf_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of printf"
  )
endif()

include(cmake/dev-mode.cmake)
