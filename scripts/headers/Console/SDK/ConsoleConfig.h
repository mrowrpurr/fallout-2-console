#pragma once

#include "Console/SDK/ConsoleData.h"
#include "Common/Keyboard/TextToScanCode.h"

#define __CONSOLE_DATA__KEY__CONSOLE_INI_PATH "ConsoleIniPath"

#define set_console_ini_path(path) \
    set_array(__CONSOLE_DATA__, __CONSOLE_DATA__KEY__CONSOLE_INI_PATH, path)

#define get_console_ini_path \
    (get_array(__CONSOLE_DATA__, __CONSOLE_DATA__KEY__CONSOLE_INI_PATH))

#define default_console_ini_path ("mods/Console.ini")

procedure get_console_ini_keyboard_shortcut(variable ini_key, variable ini_section = "KeyboardShortcuts", variable ini_file = 0) begin
    if not ini_file then ini_file = get_console_ini_path;

    display_msg("Get .ini shortcut from: " + ini_file);

    variable shortcut_text = get_ini_string(
        ini_file + "|" + ini_section + "|" + ini_key
    );

    if shortcut_text == "" then return 0;

    variable dx_scancode = text_to_scan_code(shortcut_text);

    variable shortcut = {
        "keycode": dx_scancode
    };

    return shortcut;
end
