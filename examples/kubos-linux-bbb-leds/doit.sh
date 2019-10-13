mkdir build
cd build
export CC=/usr/bin/bbb_toolchain/usr/bin/arm-linux-gcc
export CXX=/usr/bin/bbb_toolchain/usr/bin/arm-linux-g++
cmake .. && make
make

