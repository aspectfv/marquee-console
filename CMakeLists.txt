cmake_minimum_required(VERSION 3.10)
project(OSEmulator VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(OSEmulator PRIVATE include)

add_executable(OSEmulator 
    src/main.cpp
    src/MarqueeState.cpp
    src/KeyboardHandler.cpp
    src/CommandInterpreter.cpp
    src/MarqueeLogic.cpp
    src/DisplayHandler.cpp
)
