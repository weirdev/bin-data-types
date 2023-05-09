#!/usr/bin/env bash

clang++ bstring.cpp -I. -std=c++20 -c
clang++ main.cpp -I. -std=c++20 -c
clang++ main.o bstring.o -o main.exe -lbin_data_types_rust -L../rust/target/debug -std=c++20 -g
