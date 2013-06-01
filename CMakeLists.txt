project(MauiInstaller)

cmake_minimum_required(VERSION 2.8.9)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Set version
set(INSTALLER_VERSION_MAJOR 0)
set(INSTALLER_VERSION_MINOR 0)
set(INSTALLER_VERSION_PATCH 0)
set(INSTALLER_VERSION_STRING "${INSTALLER_VERSION_MAJOR}.${INSTALLER_VERSION_MINOR}.${INSTALLER_VERSION_PATCH}")

# Installation directories
include(HawaiiInstallDirs)

# Log features
include(MacroLogFeature)

# Add custom uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

# Set up packaging
set(CPACK_PACKAGE_NAME maui-installer)
set(CPACK_PACKAGE_VERSION ${INSTALLER_VERSION_STRING})
set(CPACK_SYSTEM_NAME "generic")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SET_DESTDIR FALSE)
include(CPack)

# Build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden -Wall -std=c++0x")

# Assume release build by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "" FORCE)
endif()

# Disable debug output for release builds
if(CMAKE_BUILD_TYPE MATCHES "^[Rr]elease$")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

# Find Qt
find_package(Qt5 REQUIRED COMPONENTS Qml Quick)
macro_log_feature(Qt5Qml_FOUND "Qt5Qml" "Support for Qt5Qml" "http://qt-project.org" "")
macro_log_feature(Qt5Quick_FOUND "Qt5Quick" "Support for Qt5Quick" "http://qt-project.org" "")
macro_log_feature(Qt5LinguistTools_FOUND "Qt5LinguistTools" "Support for Qt5LinguistTools" "http://qt-project.org" "")

# Find Solid
find_package(Solid "5.0.0" REQUIRED)
if(NOT Solid_FOUND)
    message(FATAL_ERROR "Solid module is required!")
endif()
macro_log_feature(Solid_FOUND "Solid" "Support for Solid" "http://solid.kde.org" "")

# Find pkg-config executable
find_program(PKGCONFIG_EXECUTABLE pkg-config)
if(NOT PKGCONFIG_EXECUTABLE)
    message(FATAL_ERROR "pkg-config is not installed!")
endif()

# Subdirectories
#add_subdirectory(data)
add_subdirectory(src)

# Display featute log
macro_display_feature_log()
