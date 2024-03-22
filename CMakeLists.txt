cmake_minimum_required(VERSION 3.14)

project(NetWorkMod LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(NetWorkMod SHARED
  TypeRename.h

  NetWorkMod_global.h
  NetWorkMod.cpp
  NetWorkMod.h

  ./Socket/BaseSocket.h
  ./Socket/BaseSocket.cpp
  ./Socket/UdpSocket.h
  ./Socket/UdpSocket.cpp
)

target_compile_definitions(NetWorkMod PRIVATE NETWORKMOD_LIBRARY)
