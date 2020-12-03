project(AoC-2020)

#**************************************************************************************************
# General cMake settings
#**************************************************************************************************
cmake_minimum_required(VERSION 3.17)


#**************************************************************************************************
# Find Package ************************************************************************************
find_package(Catch2 CONFIG REQUIRED)

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

#**************************************************************************************************
# Include *****************************************************************************************
include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

#**************************************************************************************************
# Set variable ************************************************************************************
SET(SOURCES

)

#**************************************************************************************************
# Set compiler ************************************************************************************
add_compile_options(-std=c++2a -fPIC) # for all targets in current directory

#**************************************************************************************************
# Linker ******************************************************************************************


#**************************************************************************************************
# Build Example
#**************************************************************************************************
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day1)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day2)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/day3)

SET(TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/catch2-main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/day1-catch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/day2-catch2.cpp
)

add_executable(unit-test ${TEST_SOURCES} ${SOURCES})
set_property(TARGET unit-test PROPERTY CXX_STANDARD 20)
target_link_libraries(unit-test PRIVATE -lstdc++fs Catch2::Catch2)

add_custom_target(test
  COMMAND unit-test
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/input
)
