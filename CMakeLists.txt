cmake_minimum_required(VERSION 3.16)

project(box_with_molecules)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#======================= INCLUSION OF Qt =======================#
option(WITH_QT "Include Qt in the build" ON)

if(WITH_QT)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    if(NOT "$ENV{Qt6_DIR}" STREQUAL "")
        set(CMAKE_PREFIX_PATH "$ENV{Qt6_DIR}")
    endif()

    find_package(Qt6 REQUIRED COMPONENTS Widgets Core)
    qt_standard_project_setup()
endif()

#=================== INCLUSION OF Project Files ====================#
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(FORMS_DIR ${PROJECT_SOURCE_DIR}/forms)

include_directories(${INCLUDE_DIR})
# include_directories(${SOURCE_DIR})
include_directories(${FORMS_DIR})

file(GLOB_RECURSE SOURCES
    ${FORMS_DIR}/*.ui
    ${INCLUDE_DIR}/*.h
    ${SOURCE_DIR}/*.cpp
)

#=================== SETUP EXECTUABLE ====================#
# Add the forms directory to the AUTOUIC search paths
if(WITH_QT)
    set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})
endif()

add_executable(box_with_molecules ${SOURCES})

#===================== LINKING LIBRARIES =======================#
if(WITH_QT)
    target_link_libraries(box_with_molecules Qt6::Widgets Qt6::Core)
endif()

#=================== SETUP TESTS ====================#
include(FetchContent)
set(DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  box_test
  tests/box_test.cpp
  ${SOURCE_DIR}/Vector.cpp
  ${SOURCE_DIR}/Box.cpp
  ${SOURCE_DIR}/Particle.cpp
  ${SOURCE_DIR}/Simulation.cpp
)

target_include_directories(box_test PUBLIC ${INCLUDE_DIR})

target_link_libraries(
  box_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(box_test)
