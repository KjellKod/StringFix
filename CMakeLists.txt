# =====================================================
#  Public Domain: Inspired by github.com/KjellKod/g3log/CMakeLists.cmake
#  2015, April 30, @author Kjell.Hedstrom
# =====================================================

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
ENABLE_LANGUAGE(CXX)

PROJECT (StringFix)
SET(PROJECT_SRC ${StringFix_SOURCE_DIR}/src)
SET(DIR_UNIT_TEST ${StringFix_SOURCE_DIR}/test)
SET(DIR_3RDPARTY ${StringFix_SOURCE_DIR}/thirdparty)

include_directories(${PROJECT_SRC})

MESSAGE(" PROJECT_SRC = : ${PROJECT_SRC}")
INCLUDE_DIRECTORIES(${PROJECT_SRC})
SET(ACTIVE_CPP0xx_DIR "Release")


IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   MESSAGE("")
   MESSAGE("cmake for GCC ")
   SET(PLATFORM_LINK_LIBRIES rt)
   SET(CMAKE_CXX_FLAGS "-Wall -rdynamic -Wunused -std=c++14 -pthread -D_GLIBCXX_USE_NANOSLEEP")
ENDIF()

# GENERIC STEPS
FILE(GLOB SRC_FILES ${PROJECT_SRC}/*.h ${PROJECT_SRC}/*.hpp ${PROJECT_SRC}/*.cpp) 


# Build the library
SET(LIBRARY_TO_BUILD StringFix)

INCLUDE (${StringFix_SOURCE_DIR}/Version.cmake)

INCLUDE_DIRECTORIES(${PROJECT_SRC})
ADD_LIBRARY(${LIBRARY_TO_BUILD} SHARED ${SRC_FILES})
SET(${LIBRARY_TO_BUILD}_VERSION_STRING ${VERSION})
SET_TARGET_PROPERTIES(${LIBRARY_TO_BUILD} PROPERTIES LINKER_LANGUAGE CXX SOVERSION ${VERSION})
TARGET_LINK_LIBRARIES(${LIBRARY_TO_BUILD} ${LIBS})

# Setup unit tests
INCLUDE (${StringFix_SOURCE_DIR}/Test.cmake)









