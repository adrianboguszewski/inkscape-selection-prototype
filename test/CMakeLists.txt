find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SOURCES
        ObjectSetTest
)

foreach(source ${TEST_SOURCES})
    add_executable(${source} ${source}.cpp ObjectSetTest.cpp)
    target_link_libraries(${source} inkscape_prototype ${GTEST_BOTH_LIBRARIES})
    add_test(NAME ${source} COMMAND ${source})
endforeach()