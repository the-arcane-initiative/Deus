cmake_minimum_required(VERSION 3.2)
project(Deus)

# TODO: compiler flags should be triggered on compiler
# TODO: sort out flags bsaed on the release mode
IF(WIN32)

    # TODO: control based on architecture?
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/windows)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/windows)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/windows)

ELSEIF(APPLE)

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/mac)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/mac)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/mac)

    # TODO: apple compiler flags? should probably just use clang
    set(CMAKE_CXX_FLAGS "-std=c++11")

# TODO: linux if
ELSE()

    # TODO: control based on architecture?
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/linux)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/linux)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/linux)

    # TODO: clean up compiler flags
    set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -fPIC -Ofast -msse4.2")

ENDIF()

# TODO: should just write a gtest find_package for windows
IF(NOT WIN32)
    find_package(GTest REQUIRED)
    find_package(benchmark REQUIRED)
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

#-----------------------------U N I T    T E S T S------------------------------

# TODO: sort out
if(WIN32)
    set(DEUS_UNIT_INCLUDES
        "C:/Program Files/googletest-distribution/include"
    )
    set(DEUS_UNIT_LIBPATHS
        "C:/Program Files/googletest-distribution/lib"
    )
    set(DEUS_UNIT_LIBS
        gtest
    )
ELSE()
    set(DEUS_UNIT_INCLUDES
        ${GTEST_INCLUDE_DIRS}
    )
    set(DEUS_UNIT_LIBPATHS
        ""
    )
    set(DEUS_UNIT_LIBS
        ${GTEST_LIBRARIES}
        pthread
    )
ENDIF()

include_directories(
    ${INCLUDE_DIRECTORIES}
    ${DEUS_UNIT_INCLUDES}
    tests/unit/cpp
)

link_directories(
    ${LINK_DIRECTORIES}
    ${DEUS_UNIT_LIBPATHS}
)

set(DEUS_UNIT_TESTS_SRC
    tests/unit/cpp/UnicodeView_UnitTest.cpp
    tests/unit/cpp/compute_byte_length/ASCIIComputeByteLength_UnitTest.cpp
    tests/unit/cpp/compute_byte_length/UTF8ComputeByteLength_UnitTest.cpp
    tests/unit/cpp/compute_symbol_length/UTF8ComputeSymbolLength_UnitTest.cpp
    tests/unit/cpp/from_code_point/ASCIIFromCodePoint_UnitTest.cpp
    tests/unit/cpp/from_code_point/UTF8FromCodePoint_UnitTest.cpp
    tests/unit/cpp/UnitTestsMain.cpp
)

add_executable(unit_tests ${DEUS_UNIT_TESTS_SRC})

target_link_libraries(unit_tests
    deus
    ${DEUS_UNIT_LIBS}
)

#-----------------------P E R F O R M A N C E    T E S T S----------------------

# TODO: sort out
if(WIN32)
    set(DEUS_PERFORMANCE_INCLUDES
        "C:/Program Files/benchmark/include"
    )
    set(DEUS_PERFORMANCE_LIBPATHS
        "C:/Program Files/benchmark/lib"
    )
    set(DEUS_PERFORMANCE_LIBS
        shlwapi
    )
ELSE()
    set(DEUS_PERFORMANCE_INCLUDES
        ${BENCHMARK_INCLUDE_DIRS}
    )
    set(DEUS_PERFORMANCE_LIBPATHS
        ""
    )
    set(DEUS_PERFORMANCE_LIBS
        ${GTEST_LIBRARIES}
        pthread
    )
ENDIF()

include_directories(
    ${INCLUDE_DIRECTORIES}
    ${DEUS_PERFORMANCE_INCLUDES}
    tests/performance/cpp
)

link_directories(
    ${LINK_DIRECTORIES}
    ${DEUS_PERFORMANCE_LIBPATHS}
)

set(DEUS_PERFORMANCE_TESTS_SRC
    tests/performance/cpp/compute_byte_length/ASCIIComputeByteLength_PerformanceTest.cpp
    tests/performance/cpp/compute_byte_length/UTF8ComputeByteLength_PerformanceTest.cpp
    tests/performance/cpp/compute_symbol_length/UTF8ComputeSymbolLength_PerformanceTest.cpp
    tests/performance/cpp/PerformanceTestsMain.cpp
    tests/performance/cpp/PerformanceTestsUtil.cpp
)

add_executable(performance_tests ${DEUS_PERFORMANCE_TESTS_SRC})

# TODO: SORT OUT
target_link_libraries(performance_tests
    deus
    benchmark
    ${DEUS_PERFORMANCE_LIBS}
)
