cmake_minimum_required(VERSION 2.8)
project(inkscape_prototype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES src/*.h src/*.cpp)

include(FindPkgConfig)
pkg_check_modules(DEPS REQUIRED sigc++-2.0)
include_directories(${DEPS_INCLUDE_DIRS})

add_library(inkscape_prototype STATIC ${SOURCE_FILES})
target_link_libraries(inkscape_prototype ${DEPS_LIBRARIES})

enable_testing()

add_subdirectory(test)