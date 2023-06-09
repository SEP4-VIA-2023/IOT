cmake_minimum_required(VERSION 3.14)
set(projectName IOT)
project(${projectName})

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

set(DOWNLOAD_EXTRACT_TIMESTAMP true)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest )

set(SOURCES_TEST
    co2_test.cpp
    hum_and_temp_test.cpp
    servo_test.cpp
    FreeRTOS_defs/FreeRTOS_FFF_MocksDefinitions.cpp
    #../src/task1.c
    ${SRCS}
        ../src/loraWanHandler.c ../src/servo.c ../src/main.c ../src/humidity_and_temperature.c ../src/co2.c ../main.c ../src/semaphores.c)

# This makes the test.cpp files able to #include target libraries without errors.  
include_directories(
  FreeRTOS_defs  # Mock and FreeRTOS definitions
  ../include
  ../lib/drivers
)

# Something to 
enable_testing()

add_executable(
  ${projectName}
  ${SOURCES_TEST}
)
target_link_libraries(
  ${projectName}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${projectName})