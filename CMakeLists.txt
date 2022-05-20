# Copyright (C) 2018 Fondazione Istituto Italiano di Tecnologia (IIT)  
# All Rights Reserved.
# Authors: Alexandre Antunes <alexandre.gomespereira@iit.it>

cmake_minimum_required(VERSION 3.5)
project(clarionIntegration LANGUAGES CXX C VERSION 0.6.0)

include(GNUInstallDirs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(MSVC)
  set(CMAKE_DEBUG_POSTFIX "d")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
if(UNIX)
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/linux)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(YCM)

# packages that shall come first as they include find_package(YARP)
# otherwise, we might have conflicts when selecting specific YARP components
# find_package(ICUBcontrib REQUIRED)
# find_package(ICUB REQUIRED)

find_package(YARP 3.6 REQUIRED COMPONENTS os dev math cv idl_tools )
find_package(OpenCV REQUIRED)
# list(APPEND CMAKE_MODULE_PATH ${ICUB_MODULE_PATH})
# list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})

# include(ICUBcontribOptions)
# include(ICUBcontribHelpers)

if(NOT CMAKE_CONFIGURATION_TYPES)
  if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Release")
  endif()
endif()

# icubcontrib_set_default_prefix()

include(InstallBasicPackageFiles)
include(AddUninstallTarget)

add_subdirectory(modules)
