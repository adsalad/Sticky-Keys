cmake_minimum_required(VERSION 3.17)
project(StickyKeys)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "/home/jtorreal/SFML-2.5.1-Compiled/include")
set(SFML_LIBRARY_DIR "/home/jtorreal/SFML-2.5.1-Compiled/lib")
set(SFML_DIR "/home/jtorreal/SFML-2.5.1-Compiled/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(StickyKeys main.cpp Engine.h Bob.h Engine.cpp Bob.cpp Input.cpp Draw.cpp Update.cpp)
target_link_libraries(StickyKeys sfml-graphics sfml-window sfml-system)