cmake -DCMAKE_BUILT_TYPE=Debug -S . -B cmake
cmake --build cmake
gdb bin/c-chess
