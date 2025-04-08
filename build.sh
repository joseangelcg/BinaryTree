#!/usr/bin/env bash

if [ ! -d build ];then
    mkdir build
fi

cmake -C initial_cache.cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 &&
cmake --build build/

cp build/main.exe ./
