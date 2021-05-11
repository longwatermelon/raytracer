cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(raytracer)

add_executable(raytracer
	src/main.cpp
	src/raytracer.cpp
	src/sphere.cpp
	src/raytracer.h
	src/sphere.h
	src/utils.h
)

set_property(TARGET raytracer PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
