cmake_minimum_required(VERSION 3.16)
project(SmartHomeLab01 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(smart_home_lab01
    src/main.cpp
    src/Device.cpp
    src/DeviceManager.cpp
    src/ConsoleInput.cpp
)

target_include_directories(smart_home_lab01 PRIVATE include)

if (MSVC)
    # /utf-8：源码和运行时字符串都按 UTF-8 处理，避免中文乱码
    target_compile_options(smart_home_lab01 PRIVATE /utf-8 /W4)
else()
    target_compile_options(smart_home_lab01 PRIVATE -Wall -Wextra)
endif()
