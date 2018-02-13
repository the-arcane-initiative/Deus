cmake_minimum_required(VERSION 3.2)
project(Deus)

IF(WIN32)

    # TODO: control based on architecture?
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/win_x64)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/win_x64)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/win_x64)

# TODO: linux if
ELSE()

    # TODO: control based on architecture?
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/linux_x86)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/linux_x86)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/linux_x86)

    # TODO: sort out flags
    #   - might want: -Ofast (or -O3) and -msse4.1
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c++11 -fPIC -Ofast -msse4.1")

ENDIF()

# TODO: SORT OUT
# locate gtest
IF(WIN32)
ELSE()
    find_package(GTest REQUIRED)
ENDIF()



#---------------------------------L I B R A R Y---------------------------------

include_directories(
    ${INCLUDE_DIRECTORIES}
    src/cpp
)

set(DEUS_SRC
    src/cpp/deus/Constants.cpp
    src/cpp/deus/UnicodeStorage.cpp
    src/cpp/deus/UnicodeView.cpp
    src/cpp/deus/unicode_view_impl/ASCIIImpl.cpp
    src/cpp/deus/unicode_view_impl/EncodingImpl.cpp
    src/cpp/deus/unicode_view_impl/UTF8Impl.cpp
)

# TODO: also build a shared version
add_library(deus STATIC ${DEUS_SRC})

#-----------------------------U N I T    T E S T S-----------------------------

# TODO: SORT OUT
include_directories(
    ${INCLUDE_DIRECTORIES}
    #${GTEST_INCLUDE_DIRS}
    "C:/Program Files/googletest-distribution/include"
    tests/unit/cpp
)

# TODO: SORT OUT
link_directories(
    ${LINK_DIRECTORIES}
    "C:/Program Files/googletest-distribution/lib"
)

set(DEUS_UNIT_TESTS_SRC
    tests/unit/cpp/ComputeByteLength_UnitTest.cpp
    tests/unit/cpp/UnitTestsMain.cpp
)

add_executable(unit_tests ${DEUS_UNIT_TESTS_SRC})

# TODO: SORT OUT
target_link_libraries(unit_tests
    deus
    gtest
    gtest_main
    gmock
    #${GTEST_LIBRARIES}
    #pthread
)

#-----------------------P E R F O R M A N C E    T E S T S----------------------

# TODO: SORT OUT
include_directories(
    ${INCLUDE_DIRECTORIES}
    "C:/Program Files/benchmark/include"
    tests/performance/cpp
)

set(DEUS_PERFORMANCE_TESTS_SRC
    tests/performance/cpp/ComputeByteLength_PerformanceTest.cpp
    tests/performance/cpp/PerformanceTestsMain.cpp
    tests/performance/cpp/PerformanceTestsUtil.cpp
)

# TODO: SORT OUT
link_directories(
    ${LINK_DIRECTORIES}
    "C:/Program Files/benchmark/lib"
)

add_executable(performance_tests ${DEUS_PERFORMANCE_TESTS_SRC})

# TODO: SORT OUT
target_link_libraries(performance_tests
    deus
    benchmark
    shlwapi
    #pthread
)
