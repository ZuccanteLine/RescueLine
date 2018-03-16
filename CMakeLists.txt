cmake_minimum_required(VERSION 3.8)
project(RescueLine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS -lpython2.7)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp communication/UartPY.cpp LineFollower.cpp LineFollower.h communication/Uart.cpp communication/Uart.h communication/Buffer.cpp communication/Buffer.h test/Cerchietti.cpp test/TestColorsTracking.cpp)
add_executable(RescueLine ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_FILES})
target_link_libraries(RescueLine ${OpenCV_LIBS})