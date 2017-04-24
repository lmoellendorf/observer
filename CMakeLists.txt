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
SET(${PROJECT_NAME}_VERSION_STRING ${LISA_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})
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
)

#---------------------------------------------------------------------------------------
# libobserver target
#---------------------------------------------------------------------------------------
add_library(observer ${${PROJECT_NAME}_SOURCES})
set_target_properties(observer PROPERTIES VERSION ${${PROJECT_NAME}_VERSION_STRING})

#---------------------------------------------------------------------------------------
# libobserver includes
#---------------------------------------------------------------------------------------
target_include_directories(observer INTERFACE
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sfobserver>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

#---------------------------------------------------------------------------------------
# install targets
#---------------------------------------------------------------------------------------
install(TARGETS observer
		EXPORT libobserver-config
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sfobserver)
install(EXPORT libobserver-config DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libobserver)
export(TARGETS observer FILE libobserver-config.cmake)
export(PACKAGE libobserver)
