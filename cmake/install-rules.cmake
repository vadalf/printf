if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/printf-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package printf)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT printf_Development
)

install(
    TARGETS printf_printf
    EXPORT printfTargets
    RUNTIME #
    COMPONENT printf_Runtime
    LIBRARY #
    COMPONENT printf_Runtime
    NAMELINK_COMPONENT printf_Development
    ARCHIVE #
    COMPONENT printf_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    printf_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(printf_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${printf_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT printf_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${printf_INSTALL_CMAKEDIR}"
    COMPONENT printf_Development
)

install(
    EXPORT printfTargets
    NAMESPACE printf::
    DESTINATION "${printf_INSTALL_CMAKEDIR}"
    COMPONENT printf_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
