# =====================================================
#  Public Domain: Inspired by github.com/KjellKod/g3log/CMakeLists.cmake
#  2015, April 30, @author Kjell.Hedstrom
# =====================================================



set(GTEST_DIR ${DIR_3RDPARTY}/gtest-1.7.0)
SET(PROJECT_SRC ${StringFix_SOURCE_DIR}/src)
set(GTEST_INCLUDE_DIRECTORIES ${GTEST_DIR}/include ${GTEST_DIR} ${GTEST_DIR}/src)
include_directories(${GTEST_INCLUDE_DIRECTORIES})
add_library(gtest_170_lib ${GTEST_DIR}/src/gtest-all.cc)
set_target_properties(gtest_170_lib PROPERTIES COMPILE_DEFINITIONS "GTEST_HAS_RTTI=0")
enable_testing(true)

include_directories(test)
include_directories(${PROJECT_SRC})
include_directories(${PROJECT_SRC}/test)
include_directories(SYSTEM /usr/local/probe/include /usr/local/gcc/include)

file(GLOB TEST_SRC_FILES "test/*.cpp")

MESSAGE("Test files are ${TEST_SRC_FILES}")


 
set(StringFixTests StringFixTests)


# build the unit tests   
SET(CMAKE_CXX_FLAGS "-Wall -Wno-sign-compare -rdynamic -Wunused -std=c++14 -pthread -D_GLIBCXX_USE_NANOSLEEP")
add_executable(${StringFixTests} thirdparty/test_main.cpp ${TEST_SRC_FILES} )
set_target_properties(${StringFixTests} PROPERTIES COMPILE_DEFINITIONS "GTEST_HAS_TR1_TUPLE=0")
set_target_properties(${StringFixTests} PROPERTIES COMPILE_DEFINITIONS "GTEST_HAS_RTTI=0")
set_target_properties(${StringFixTests} PROPERTIES COMPILE_FLAGS "-isystem -pthread ")
target_link_libraries(${StringFixTests} ${LIBRARY_TO_BUILD} gtest_170_lib ${FILEIO} -lstdc++ ${PLATFORM_LINK_LIBRIES} -Wl,-rpath,. -Wl,-rpath,/usr/local/probe/lib  -Wl,-rpath,/usr/local/probe/lib64 )

