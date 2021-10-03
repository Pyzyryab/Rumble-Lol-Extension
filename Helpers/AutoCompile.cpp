#include <iostream>

using namespace std;

/*
    Helper that creates an executable for compile the Rumble Lol Extension C++ code when runned
*/
int main() {
    // When use VSCE instead Visual Studio, normally I compile with g++, and 
    // I need to manually link the above libraries
    system("g++ main.cpp WindowCapture/WindowCapture.cpp -o RumbleLolExtension -lgdi32 -I\"C:/vcpkg/installed/x64-windows/include\"");
    system("RumbleLolExtension.exe");
    return 0;
}