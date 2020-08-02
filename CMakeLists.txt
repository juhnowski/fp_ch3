 cmake_minimum_required(VERSION 2.8.12)
 project(fp_ch3)

 add_definitions("-std=c++17")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()

 add_executable(fp_ch3 main.cpp)
 target_link_libraries(fp_ch3 ${CONAN_LIBS})