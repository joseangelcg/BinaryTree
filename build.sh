#!/usr/bin/env bash

cmake -C initial_cache.cmake -B build &&
cmake --build build/

cp build/main.exe ./
