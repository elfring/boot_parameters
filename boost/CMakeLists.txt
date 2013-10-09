# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

cmake_minimum_required(VERSION 2.6)

if(DEFINED CMAKE_BUILD_TYPE)
   #set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING
   #    "Choose the build type: None, Debug, Release, RelWithDebInfo or MinSizeRel.")
else()
   # Set the preferred default type for the software generation here.
   set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
       "Choose the build type: None, Debug, Release, RelWithDebInfo or MinSizeRel.")
endif()

project("boot_command-Spirit")

find_package(Boost 1.49 REQUIRED)

set("${CMAKE_PROJECT_NAME}_VERSION_MAJOR" 0)
set("${CMAKE_PROJECT_NAME}_VERSION_MINOR" 1)
set("${CMAKE_PROJECT_NAME}_VERSION_PATCH" 0)

# http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
if(CMAKE_COMPILER_IS_GNUCXX)
   execute_process(COMMAND "${CMAKE_C_COMPILER}" -dumpversion OUTPUT_VARIABLE GCC_VERSION)

   if(GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
      message(STATUS "C++11 support activated.")
      #set(EXTRA_CXXFLAGS "-std=gnu++11")
      set(EXTRA_CXXFLAGS "-std=c++11")
   elseif(GCC_VERSION VERSION_GREATER 4.3 OR GCC_VERSION VERSION_EQUAL 4.3)
      message(WARNING "C++0x activated. If you get any errors, update to a compiler which fully supports C++11.")
      set(EXTRA_CXXFLAGS "-std=gnu++0x")
   else()
      message(WARNING "It seems that your GCC compiler does not support C++11 as expected.
The processing of C++ source files is excluded from this project now.")
   endif()
else()
   # http://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
   if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      set(EXTRA_CXXFLAGS "-std=c++11")
   elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
      set(EXTRA_CXXFLAGS "-std=c++11")
   elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
      set(EXTRA_CXXFLAGS "")
   else()
      message(WARNING "The support of C++11 should be checked in more detail for the compiler \"${CMAKE_CXX_COMPILER_ID}\".
The processing of C++ source files is excluded from this project now.")
   endif()
endif()

configure_file("${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/config.h.in" "${${CMAKE_PROJECT_NAME}_BINARY_DIR}/config.h")
include_directories("${${CMAKE_PROJECT_NAME}_BINARY_DIR}" "${${CMAKE_PROJECT_NAME}_SOURCE_DIR}" "${Boost_INCLUDE_DIRS}")

option("${CMAKE_PROJECT_NAME}_USE_EXPORT_KEY_WORD"
       "Should exportable template definitions be used by the class library?")
option("${CMAKE_PROJECT_NAME}_USE_MULTI_COLUMN_DATA_STORE"
       "Should the extracted data be stored into an object which manages multiple columns?")

if("${CMAKE_PROJECT_NAME}_USE_MULTI_COLUMN_DATA_STORE")
   add_definitions(-DPARAMETER_USE_MultiIndex)
endif()

set(SOURCES parameter_extractor.cpp main.cpp)

if("${CMAKE_PROJECT_NAME}_USE_EXPORT_KEY_WORD")
   list(APPEND SOURCES lexer.cpp parser.cpp)
   add_definitions(-DCXX_USE_EXPORT_KEY_WORD)
endif()

add_executable(boot_command_line-demo2 ${SOURCES})
set_target_properties(boot_command_line-demo2 PROPERTIES COMPILE_FLAGS "${EXTRA_CXXFLAGS}")
target_link_libraries(boot_command_line-demo2 ${Boost_LIBRARIES})

enable_testing()
add_test(t1 boot_command_line-demo2)

install(TARGETS boot_command_line-demo2 RUNTIME DESTINATION bin)

# Tobias Rautenkranz can help to generate some documentation.
# http://tobias.rautenkranz.ch/cmake/doxygen/
include(UseDoxygen OPTIONAL)
