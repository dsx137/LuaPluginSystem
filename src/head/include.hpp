#pragma once
#include <filesystem>

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <memory>
#include <stdexcept>
#include <map>
#include <optional>

#include <lua.hpp>
#include <sol.hpp>

#ifdef _WIN32 // Windows系统
#include <Windows.h>
#elif __linux__ // Linux系统
#include <unistd.h>
#include <limits.h>
#elif __APPLE__ // macOS系统
#include <mach-o/dyld.h>
#endif