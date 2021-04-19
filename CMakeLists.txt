cmake_minimum_required(VERSION 3.14)
project(RipeMD_3DES)

set(CMAKE_CXX_STANDARD 17)

add_executable(RipeMD_3DES Source/Run.cpp Source/Key.cpp Header/Key.h Header/Run.h Source/TripleDes.cpp Header/TripleDes.h Source/File_IO.cpp Header/File_IO.h Source/RipeMD_256.cpp Header/RipeMD_256.h Source/OPMode.cpp Header/OPMode.h)