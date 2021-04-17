cmake_minimum_required(VERSION 3.14)
project(RipeMD_3DES)

set(CMAKE_CXX_STANDARD 17)

add_executable(RipeMD_3DES Run.cpp Key.cpp Key.h Run.h TripleDes.cpp TripleDes.h File_IO.cpp File_IO.h RipeMD_256.cpp RipeMD_256.h)