@echo off
set "vsPath=C:\Program Files\Microsoft Visual Studio\18\Insiders"
call "%vsPath%\Common7\Tools\VsDevCmd.bat"
cd /d C:\Users\antoi\Desktop\FOCWorld\focworld-client-cpp\build
set VCPKG_ROOT=
cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_TOOLCHAIN_FILE="C:\Program Files\Microsoft Visual Studio\18\Insiders\VC\vcpkg\scripts\buildsystems\vcpkg.cmake" ..
cmake --build .
