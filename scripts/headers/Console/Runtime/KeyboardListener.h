#pragma once

/*
    Contains the main HOOK_KEYPRESS listener used
    by the console application
*/

#include "Console/SDK/ConsoleConfig.h"
#include "Console/SDK/ConsoleSingleton.h"
#include "Common/Keyboard/TextToScanCode.h"

procedure ConsoleRuntimeKeypressListener(variable is_pressed, variable dx_scancode) begin
    init_console_data;

    if is_pressed then begin
        variable toggle_console_scancode = get_console_ini_keyboard_shortcut("toggle_console");
        if dx_scancode == toggle_console_scancode.keycode then begin
            init_console_singleton;
            // toggle_console_visibility;
        end
    end
end

procedure ConsoleRuntimeKeypressListener_Hook begin
    variable pressed = get_sfall_arg,
             keycode = get_sfall_arg;

    call ConsoleRuntimeKeypressListener(pressed, keycode);
end
