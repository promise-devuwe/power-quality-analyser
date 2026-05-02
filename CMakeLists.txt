cmake_minimum_required(VERSION 4.2)
project(power_quality_analyser C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled8 main.c
        waveform.c
        io.c)
