   ::rm -r build/
   ::mkdir build
   cd build
   cmake .. -G "Visual Studio 14 2015"  -DCMAKE_TOOLCHAIN_FILE=P:/vcpkg/scripts/buildsystems/vcpkg.cmake -DFMT_INSTALL=1
   cmake --build . --config Release --verbose
   cmake --install .