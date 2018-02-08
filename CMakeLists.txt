cmake_minimum_required(VERSION 3.2)
project(Deus)

IF(WIN32)

    # TODO: control based on architecture?
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/win_x86)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/win_x86)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/win_x86)

# TODO: linux if
ELSE()

    # TODO: control based on architecture?
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/linux_x86)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/linux_x86)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/linux_x86)

    # TODO: sort out flags
    #   - might want: -Ofast (or -O3) and -msse4.1
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c++11 -fPIC")

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

include_directories(
    ${INCLUDE_DIRECTORIES}
    ext/catch
    tests/unit/cpp
)

set(DEUS_UNIT_TESTS_SRC
    tests/unit/cpp/ASCIIImpl_TestSuite.cpp
    tests/unit/cpp/TestsMain.cpp
    tests/unit/cpp/UTF8Impl_TestSuite.cpp
    tests/unit/cpp/UnicodeView_TestSuite.cpp
)

add_executable(tests ${DEUS_UNIT_TESTS_SRC})

target_link_libraries(tests
    deus
)
