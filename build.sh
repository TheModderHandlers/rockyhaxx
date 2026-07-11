rm -rf ./build && mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE="$PWD/../i686-w64-mingw32.cmake" -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"
make -j$(nproc) && cp ./rockyhaxx.dll ~/.local/share/Steam/steamapps/common/My\ Singing\ Monsters/mods/rockyhaxx/rockyhaxx.dll
cp ./rockyhaxx.dll ../rockyhaxx/rockyhaxx.dll
cd ../
