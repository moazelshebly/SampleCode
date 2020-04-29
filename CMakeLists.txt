cmake_minimum_required(VERSION 3.15)
project(Material)

set(CMAKE_CXX_STANDARD 17)

add_executable(Material main.cpp AtomicData.cpp Spectrum.cpp AtomicData.h Material.cpp Material.h Spectrum.h)