cmake_minimum_required(VERSION 3.16)
project(VoleMachineSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(VoleSimulator
    A2-5-20251333-20250857-20250258-20250448.cpp
    Alu.cpp
    CPU.cpp
    instructions.cpp
    Machine.cpp
    MainWindow.cpp
    Memory.cpp
    ProgramLoader.cpp
    Registers.cpp
    Screen.cpp
)

target_link_libraries(VoleSimulator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
