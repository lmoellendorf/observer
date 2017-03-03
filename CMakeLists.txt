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
cmake_minimum_required (VERSION 2.8)
project (observer)

#---------------------------------------------------------------------------------------
# OBSERVER VERSION
#---------------------------------------------------------------------------------------
SET(LISA_VERSION_MAJOR                  1               CACHE STRING "mayor version")
SET(OBSERVER_VERSION_MINOR                  0               CACHE STRING "minor version")
SET(OBSERVER_VERSION_PATCH                  0               CACHE STRING "patch version")
SET(OBSERVER_VERSION_RELEASE_TYPE           "alpha"         CACHE STRING "version type")
SET(OBSERVER_VERSION_RELEASE_TYPE_VERSION   4               CACHE STRING "version type version")
SET(OBSERVER_PRODUCT_COMPANY                "STACKFORCE"    CACHE STRING "company name")
SET(OBSERVER_PRODUCT_NAME                   "OBSERVER"          CACHE STRING "product name")
SET(OBSERVER_VERSION_STRING ${LISA_VERSION_MAJOR}.${OBSERVER_VERSION_MINOR}.${OBSERVER_VERSION_PATCH})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -fmessage-length=0")

set (OBSERVER_SOURCES
    ${PROJECT_SOURCE_DIR}/sf_subject.cpp
    ${PROJECT_SOURCE_DIR}/sf_event.cpp
    )

if(STATIC_BUILD)
		add_library(observer STATIC ${OBSERVER_SOURCES})
else()
		add_library(observer SHARED ${OBSERVER_SOURCES})
endif()

set_target_properties(observer PROPERTIES VERSION ${OBSERVER_VERSION_STRING})
# Needed for add_subdirectory() in parent projects
target_include_directories(observer PUBLIC ${PROJECT_SOURCE_DIR})

install (TARGETS observer DESTINATION lib)
install (FILES ${PROJECT_SOURCE_DIR}/sf_observer.h
    ${PROJECT_SOURCE_DIR}/sf_subject.h
    DESTINATION include)
