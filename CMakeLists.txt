cmake_minimum_required(VERSION 3.15...3.31)

project(
    DonkByDaylight
    VERSION 1.0
    LANGUAGES CXX
)

add_library(KeyHandlerLib include/shared/KeyHandler.h src/KeyHandler.cpp)
add_library(ScreenHandlerLib include/shared/ScreenHandler.h src/ScreenHandler.cpp)
add_library(SettingsLib include/shared/Settings.h src/Settings.cpp)

add_executable(TestExample src/main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

target_link_libraries(TestExample KeyHandlerLib ScreenHandlerLib SettingsLib)

enable_testing()
add_test(NAME TestExample COMMAND TestExample)