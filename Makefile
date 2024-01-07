clean:
	rm -rf build
	rm -rf install
	mkdir build

configure:
	cmake -S . -B ./build -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=./clang-x86_64_windows_gnu.cmake

configure_r:
	cmake -S . -B ./build -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=./clang-x86_64_windows_gnu.cmake

compile:
	cmake --build ./build -j8

run: # Care. This assumes that you followed the documentation instructions and configured MSYS2 as discussed
	/c/msys64/clang64/bin/python ./python/run_rlp.py
