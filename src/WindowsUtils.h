#pragma once
#include <string>

#ifdef _WIN32
void Windows_CheckSingleInstance(int argc, char* argv[]);
void Windows_SetupCustomWndProc();
bool Windows_HasNewUri();
std::string Windows_GetNewUri();
void Windows_ClearNewUri();
#endif
