choco install qt6 libgit2 cmake
mkdir build; cd build
cmake .. -G "Ninja"
cmake --build . --config Release
.\Release\WorkshopUploader.exe
