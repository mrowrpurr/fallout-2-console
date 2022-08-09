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

    variable is_toggle_console_key;

    if is_pressed then begin
        variable toggle_console_scancode = get_console_ini_keyboard_shortcut("toggle_console");
        if dx_scancode == toggle_console_scancode.code then begin
            is_toggle_console_key = true;
            init_console_singleton;
            toggle_console_singleton_visibility;
        end
    end

    if not is_toggle_console_key and is_console_singleton_visible then begin
        variable new_keycode = console_singleton_handle_keypress(is_pressed, dx_scancode);
        if new_keycode != dx_scancode then return new_keycode;
    end

    return dx_scancode;
end

procedure ConsoleRuntimeKeypressListener_Hook begin
    variable pressed = get_sfall_arg,
             keycode = get_sfall_arg;

    variable new_keycode = ConsoleRuntimeKeypressListener(
        pressed,
        keycode
    );

    if new_keycode != keycode then begin
        set_sfall_return(new_keycode);
        set_sfall_arg(1, new_keycode);
    end
end
