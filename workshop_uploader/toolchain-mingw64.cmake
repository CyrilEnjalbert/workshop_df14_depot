# toolchain-mingw64.cmake
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)


## rm -rf build-win
## mkdir build-win && cd build-win
## 
##cmake .. \
##  -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw64.cmake \
##  -DCMAKE_BUILD_TYPE=Release \
##  -DQt6_DIR=/home/c-enjalbert/Qt/6.9.3/mingw_64/lib/cmake/Qt6
##
## 
## cmake --build . --config Release


