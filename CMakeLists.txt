cmake_minimum_required (VERSION 2.8)

project (Poo)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if (COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message (STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.46.1 COMPONENTS serialization)

if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(Poo poo.cc)
  target_link_libraries(Poo ${Boost_LIBRARIES})
endif()
