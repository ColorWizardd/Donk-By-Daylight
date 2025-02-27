cmake_minimum_required(VERSION 3.15...3.31)

project(
    DonkByDaylight
    VERSION 0.0
    LANGUAGES CXX
)

add_library(KeyHandlerLib include/shared/KeyHandler.h src/KeyHandler.cpp)
add_library(ScreenHandlerLib include/shared/ScreenHandler.h src/ScreenHandler.cpp)

add_executable(TestExample src/main.cpp)

target_link_libraries(TestExample KeyHandlerLib)

enable_testing()
add_test(NAME TestExample COMMAND TestExample)