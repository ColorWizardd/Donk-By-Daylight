cmake_minimum_required(VERSION 3.15...3.31)

project(
    DonkByDaylight
    VERSION 1.0
    LANGUAGES CXX
)

# DEVANAGARI_PROCESSING IS BUSTED, SEE ABOUT FIXING LATER

set(CMAKE_CXX_STANDARD 17)
set(SW_BUILD_SHARED_LIBS 1)
set(SW_STORAGE_DIR C:/sw-setup/.sw/storage)
set(DEPENDENCIES
    org.sw.demo.google.tesseract.libtesseract-5.4.0
)

find_package(SW REQUIRED)
sw_add_package(${DEPENDENCIES})
sw_execute()

add_library(KeyHandlerLib include/shared/KeyHandler.h src/KeyHandler.cpp)
add_library(ScreenHandlerLib include/shared/ScreenHandler.h src/ScreenHandler.cpp)
add_library(SettingsLib include/shared/Settings.h src/Settings.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

add_executable(TestExample src/main.cpp)

target_link_libraries(TestExample KeyHandlerLib ScreenHandlerLib SettingsLib ${DEPENDENCIES})

enable_testing()
add_test(NAME TestExample COMMAND TestExample)