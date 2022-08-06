#pragma once

#include "Console/SDK/ConsoleData.h"

#define __CONSOLE_DATA__KEY_CONSOLE_INI_PATH "ConsoleIniPath"

#define set_console_ini_path(path) \
    set_array(__CONSOLE_DATA__, __CONSOLE_DATA__KEY_CONSOLE_INI_PATH, path)

#define get_console_ini_path \
    get_array(__CONSOLE_DATA__, __CONSOLE_DATA__KEY_CONSOLE_INI_PATH)
