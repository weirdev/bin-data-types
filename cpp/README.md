Currently only working in linux

Building:

In rust project:
    cargo build

In cpp project
clang++ main.cpp -o main.exe -lbin_data_types_rust -L../rust/target/debug -std=c++20

Running:
    One time:
        LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/c/Users/weswe/dev/bin-data-types/rust/target/debug
        export LD_LIBRARY_PATH
        sudo ldconfig
    ./main.exe
