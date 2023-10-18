#pragma once
#include <filesystem>

#include <iostream>
#include <string>
#include <filesystem>

#include <lua.hpp>

#ifdef _WIN32 // Windows系统
#include <Windows.h>
#elif __linux__ // Linux系统
#include <unistd.h>
#include <limits.h>
#elif __APPLE__ // macOS系统
#include <mach-o/dyld.h>
#endif