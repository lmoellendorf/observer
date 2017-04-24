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

cmake_minimum_required(VERSION 3.2)
project(observer)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

#---------------------------------------------------------------------------------------
# OBSERVER VERSION
#---------------------------------------------------------------------------------------
SET(${PROJECT_NAME}_VERSION_MAJOR                  1               CACHE STRING "mayor version")
SET(${PROJECT_NAME}_VERSION_MINOR                  0               CACHE STRING "minor version")
SET(${PROJECT_NAME}_VERSION_PATCH                  0               CACHE STRING "patch version")
SET(${PROJECT_NAME}_VERSION_RELEASE_TYPE           "alpha"         CACHE STRING "version type")
SET(${PROJECT_NAME}_VERSION_RELEASE_TYPE_VERSION   4               CACHE STRING "version type version")
SET(${PROJECT_NAME}_PRODUCT_COMPANY                "STACKFORCE"    CACHE STRING "company name")
SET(${PROJECT_NAME}_PRODUCT_NAME                   "OBSERVER"          CACHE STRING "product name")
SET(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -fmessage-length=0")


#---------------------------------------------------------------------------------------
# libobserver sources and headers
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
# libobserver target
#---------------------------------------------------------------------------------------
add_library(observer ${${PROJECT_NAME}_SOURCES})
set_target_properties(observer PROPERTIES VERSION ${${PROJECT_NAME}_VERSION})

#---------------------------------------------------------------------------------------
# libobserver includes
#---------------------------------------------------------------------------------------
target_include_directories(observer INTERFACE
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sfobserver>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

#---------------------------------------------------------------------------------------
# install/export targets
#---------------------------------------------------------------------------------------
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(PROJECT_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")

install(TARGETS observer
		EXPORT ${TARGETS_EXPORT_NAME}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

write_basic_package_version_file(
	${PROJECT_VERSION_FILE}
	VERSION ${${PROJECT_NAME}_VERSION}
	COMPATIBILITY AnyNewerVersion
)

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sfobserver)
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
