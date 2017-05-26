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
## @author     STACKFORCE
## @brief      Generic implementation of the Oberserver pattern.
##

cmake_minimum_required(VERSION 3.6)
project(sfobserver)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

#---------------------------------------------------------------------------------------
# OBSERVER VERSION
#---------------------------------------------------------------------------------------
SET(${PROJECT_NAME}_VERSION_MAJOR                  2                CACHE STRING "mayor version")
SET(${PROJECT_NAME}_VERSION_MINOR                  0                CACHE STRING "minor version")
SET(${PROJECT_NAME}_VERSION_PATCH                  0                CACHE STRING "patch version")
SET(${PROJECT_NAME}_VERSION_RELEASE_TYPE           "rc"             CACHE STRING "version type")
SET(${PROJECT_NAME}_VERSION_RELEASE_TYPE_VERSION   1                CACHE STRING "version type version")
SET(${PROJECT_NAME}_PRODUCT_COMPANY                "STACKFORCE"     CACHE STRING "company name")
SET(${PROJECT_NAME}_PRODUCT_NAME                   "OBSERVER"       CACHE STRING "product name")
SET(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -fmessage-length=0")


#---------------------------------------------------------------------------------------
# libsfobserver sources and headers
#---------------------------------------------------------------------------------------
set(${PROJECT_NAME}_SOURCES
    ${PROJECT_SOURCE_DIR}/sf_subject.cpp
    ${PROJECT_SOURCE_DIR}/sf_event.cpp
)

set(${PROJECT_NAME}_HEADERS
	${PROJECT_SOURCE_DIR}/sf_observer.h
	${PROJECT_SOURCE_DIR}/sf_subject.h
	${PROJECT_SOURCE_DIR}/sf_event.h
)

#---------------------------------------------------------------------------------------
# libsfobserver target
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

set_target_properties(sfobserver PROPERTIES VERSION ${${PROJECT_NAME}_VERSION})
set_target_properties(sfobserver-static PROPERTIES VERSION ${${PROJECT_NAME}_VERSION})

#---------------------------------------------------------------------------------------
# libsfobserver includes
#---------------------------------------------------------------------------------------
target_include_directories(sfobserver INTERFACE
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sfobserver>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_include_directories(sfobserver-static INTERFACE
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sfobserver>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

#---------------------------------------------------------------------------------------
# install/export targets
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
	VERSION ${${PROJECT_NAME}_VERSION}
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
# CREATE DEB PACKAGE
#---------------------------------------------------------------------------------------
set(CPACK_GENERATOR "DEB")

# check if command dpkg is available
find_program(DPKG_CMD dpkg)
if(DPKG_CMD)
	message(STATUS "DEB Generator: Found dpkg: ${DPKG_CMD}")
else()
	message(WARNING "DEB Generator: dpkg not found")
endif()

# inform about package naming issues for cmake<3.6
if(CMAKE_VERSION VERSION_LESS 3.6)
	message(WARNING "DEB Generator: CMake/CPack 3.6 or higher is needed to produce correctly named packages.")
endif()

# set packaging dir
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/packages)
message(STATUS "DEB Generator: debian packages will be generated under ${CPACK_PACKAGE_DIRECTORY}")

# force CPack generated DEBs to use the same path as CMAKE_INSTALL_PREFIX
#set(CPACK_SET_DESTDIR true)

# manually set system arch if dpkg is not found or cmake version<3.6
if(NOT DPKG_CMD OR CMAKE_VERSION VERSION_LESS 3.6)
	if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL x86_64)
		set(CPACK_SYSTEM_NAME amd64)
	else()
		set(CPACK_SYSTEM_NAME i386)
	endif()
endif()

set(CPACK_DEBIAN_PACKAGE_NAME "libsfobserver")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT) # if cmake<3.6 this is not respected
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "STACKFORCE callback observer")
set(CPACK_PACKAGE_VENDOR "STACKFORCE GmbH")
set(CPACK_PACKAGE_CONTACT "info@stackforce.de")
set(CPACK_DEBIAN_PACKAGE_VERSION ${${PROJECT_NAME}_VERSION})
set(CPACK_DEBIAN_PACKAGE_SECTION "Development")
set(CPACK_STRIP_FILES TRUE)

# TODO handle license and readme
#set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.rst")
#set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE-MIT")

include(CPack)
