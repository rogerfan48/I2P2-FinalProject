cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM="ninja" -G Ninja -S "$(pwd)" -B "$(pwd)/cmake-build-debug" &&
cmake --build "$(pwd)/cmake-build-debug" --target ArenaLegends &&
"$(pwd)/cmake-build-debug/ArenaLegends"
