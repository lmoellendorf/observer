##
## @code
##  ___ _____ _   ___ _  _____ ___  ___  ___ ___
## / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
## \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
## |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
## embedded.connectivity.solutions.==============
## @endcode
##
## @file
## @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
## @author     Lars Moellendorf
## @author     Adrian Antonana
## @brief      Generic implementation of the Oberserver pattern.
##
## This file is part of the STACKFORCE Observer pattern library
## (below "libsfobserver").
##
## libsfobserver is free software: you can redistribute it and/or modify
## it under the terms of the GNU Affero General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## libsfobserver is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Affero General Public License for more details.
##
## You should have received a copy of the GNU Affero General Public License
## along with libsfobserver.  If not, see <http://www.gnu.org/licenses/>.
##

#---------------------------------------------------------------------------------------
# libsfobserver sources and headers
#---------------------------------------------------------------------------------------
set(${PROJECT_NAME}_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/sf_subject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sf_event.cpp
)

set(${PROJECT_NAME}_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/sf_observer.h
	${CMAKE_CURRENT_SOURCE_DIR}/sf_subject.h
	${CMAKE_CURRENT_SOURCE_DIR}/sf_event.h
)

#---------------------------------------------------------------------------------------
# Compiler options
#---------------------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -fmessage-length=0")

#---------------------------------------------------------------------------------------
# Targets sfobserver*
#---------------------------------------------------------------------------------------
# intemediate object to avoid compiling sources twice for shared and static lib
add_library(sfobserver_o OBJECT ${${PROJECT_NAME}_SOURCES})
set_target_properties(sfobserver_o PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

# add static and shared libs targets
add_library(sfobserver SHARED $<TARGET_OBJECTS:sfobserver_o>)
add_library(sfobserver-static STATIC $<TARGET_OBJECTS:sfobserver_o>)

# ensure produced static and shared libs have the same name
set_target_properties(sfobserver PROPERTIES OUTPUT_NAME sfobserver)
set_target_properties(sfobserver-static PROPERTIES OUTPUT_NAME sfobserver)

set_target_properties(sfobserver PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(sfobserver-static PROPERTIES VERSION ${PROJECT_VERSION})

#---------------------------------------------------------------------------------------
# Include directories for sfobserver* targets
#---------------------------------------------------------------------------------------
target_include_directories(sfobserver INTERFACE
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sfobserver>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_include_directories(sfobserver-static INTERFACE
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sfobserver>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

#---------------------------------------------------------------------------------------
# Install/export targets
#---------------------------------------------------------------------------------------
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(PROJECT_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")

install(TARGETS sfobserver sfobserver-static
		EXPORT ${TARGETS_EXPORT_NAME}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

write_basic_package_version_file(
	${PROJECT_VERSION_FILE}
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(FILES ${${PROJECT_NAME}_HEADERS}
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sfobserver
)

install(FILES ${PROJECT_VERSION_FILE}
		DESTINATION ${CONFIG_INSTALL_DIR}
)

# build directory package config
export(EXPORT ${TARGETS_EXPORT_NAME}
		FILE ${PROJECT_NAME}-config.cmake
)

# installed package config
install(EXPORT ${PROJECT_NAME}Targets
		DESTINATION ${CONFIG_INSTALL_DIR}
		FILE ${PROJECT_NAME}-config.cmake
)

# add to CMake registry
export(PACKAGE ${PROJECT_NAME})

#---------------------------------------------------------------------------------------
# Create release packages
#---------------------------------------------------------------------------------------
# package release version
set(PACKAGE_RELEASE_VERSION 1)

# determine distribution and architecture
execute_process(COMMAND lsb_release -si OUTPUT_VARIABLE LINUX_DISTRO OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND uname -m OUTPUT_VARIABLE MACHINE_ARCH OUTPUT_STRIP_TRAILING_WHITESPACE)

# determine CPack generators
set(CPACK_GENERATOR TGZ STGZ)

if(LINUX_DISTRO STREQUAL "Debian" OR LINUX_DISTRO STREQUAL "Ubuntu" OR LINUX_DISTRO STREQUAL "LinuxMint")
    list(APPEND CPACK_GENERATOR DEB)
endif()

# general CPack config
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/packages)
message(STATUS "CPack: packages will be generated under ${CPACK_PACKAGE_DIRECTORY}")
set(CPACK_PACKAGE_NAME "lib${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_PRODUCT_COMPANY} ${PROJECT_PRODUCT_NAME}")
set(CPACK_PACKAGE_VENDOR "${PROJECT_PRODUCT_COMPANY} GmbH")
set(CPACK_PACKAGE_CONTACT "info@stackforce.de")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}-${PACKAGE_RELEASE_VERSION}_Linux-${MACHINE_ARCH})
set(CPACK_STRIP_FILES ON)

# debian specific CPack config
set(CPACK_DEBIAN_PACKAGE_RELEASE ${PACKAGE_RELEASE_VERSION})
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/stackforce")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")

include(CPack)
