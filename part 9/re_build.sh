#!/bin/bash

# Check if `build` directory exists
if [[ -d build ]] ; then
    rm -r build
    echo "Removed build directory"
fi

# Compile the program
mkdir build && cd build && cmake ../ && make -j4
