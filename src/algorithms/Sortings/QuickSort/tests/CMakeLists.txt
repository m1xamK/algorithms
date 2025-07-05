project(QSort)

set(TESTS_NAME ${PROJECT_NAME}_tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
        UPDATE_DISCONNECTED   ON
)
FetchContent_MakeAvailable(googletest)

# for local build
#add_subdirectory(../lib/googletest build)

add_executable(${TESTS_NAME} QSort.tests.cpp)
target_link_libraries(${TESTS_NAME} QSort gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${TESTS_NAME})