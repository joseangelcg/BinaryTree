#!/usr/bin/env bash

if [ ! -d build ];then
    mkdir build
fi

cmake -C initial_cache.cmake -B build &&
cmake --build build/

cp build/main.exe ./
