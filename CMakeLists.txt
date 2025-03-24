cmake_minimum_required(VERSION 3.15...3.31)

project(
    DonkByDaylight
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

#set(SW_BUILD_SHARED_LIBS 1)
#set(DEPENDENCIES
#    org.sw.demo.google.tesseract.libtesseract-5.4.0
#)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/share)
set(CURL_LIBRARY vcpkg_installed/x64-windows/lib)
set(CURL_INCLUDE_DIR vcpkg_installed/x64-windows/share/curl)
set(Tesseract_DIR vcpkg_installed/x64-windows/share/tesseract)
set(ZLIB_LIBRARY vcpkg_installed/x64-windows/share/zlib)
set(ZLIB_INCLUDE_DIR vcpkg_installed/x64-windows/share/zlib)
set(LibArchive_LIBRARY vcpkg_installed/x64-windows/share/libarchive)
set(LibArchive_INCLUDE_DIR vcpkg_installed/x64-windows/share/libarchive)

set(TESSDATA_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/tessdata)

find_package(Tesseract CONFIG REQUIRED)
# sw_add_package(${DEPENDENCIES})
# sw_execute()

add_library(KeyHandlerLib include/shared/KeyHandler.h src/KeyHandler.cpp)
add_library(ScreenHandlerLib include/shared/ScreenHandler.h src/ScreenHandler.cpp)
add_library(SettingsLib include/shared/Settings.h src/Settings.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/img DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tessdata DESTINATION .)

add_custom_target(copy_tessdata
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/tessdata ${CMAKE_CURRENT_BINARY_DIR}/tessdata
)

add_executable(TestExample src/main.cpp)

add_dependencies(TestExample copy_tessdata)

target_link_libraries(TestExample KeyHandlerLib ScreenHandlerLib SettingsLib Tesseract::libtesseract)

set(TESSDATA_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/tessdata)

enable_testing()
add_test(NAME TestExample COMMAND TestExample)