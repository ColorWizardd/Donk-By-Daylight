# CMake generated Testfile for 
# Source directory: C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight
# Build directory: C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[TestExample]=] "C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/build/bin/Debug/TestExample.exe")
  set_tests_properties([=[TestExample]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/CMakeLists.txt;53;add_test;C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[TestExample]=] "C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/build/bin/Release/TestExample.exe")
  set_tests_properties([=[TestExample]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/CMakeLists.txt;53;add_test;C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[TestExample]=] "C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/build/bin/MinSizeRel/TestExample.exe")
  set_tests_properties([=[TestExample]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/CMakeLists.txt;53;add_test;C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[TestExample]=] "C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/build/bin/RelWithDebInfo/TestExample.exe")
  set_tests_properties([=[TestExample]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/CMakeLists.txt;53;add_test;C:/Users/jacob/OneDrive/Documents/GitHub/Donk-By-Daylight/CMakeLists.txt;0;")
else()
  add_test([=[TestExample]=] NOT_AVAILABLE)
endif()
