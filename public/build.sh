#!/bin/sh

cmake .. "-DCMAKE_EXE_LINKER_FLAGS=-s USE_GLFW=3" & make
