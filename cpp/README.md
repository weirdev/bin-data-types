Currently only working in linux

Building:

In rust project:
    cargo build

In cpp project:
    build.sh

Running:
    Windows (one time):
        LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/c/Users/weswe/dev/bin-data-types/rust/target/debug
        export LD_LIBRARY_PATH
        sudo ldconfig
    ./main.exe
