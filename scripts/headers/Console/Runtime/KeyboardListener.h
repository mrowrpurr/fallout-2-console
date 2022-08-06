#pragma once

/*
    Contains the main HOOK_KEYPRESS listener used
    by the console application
*/

#include "Common/Keyboard/TextToScanCode.h"

procedure ConsoleRuntimeKeypressListener(variable is_pressed, variable dx_scancode) begin
    // DO SOMETHING
end

procedure ConsoleRuntimeKeypressListener_Hook begin
    variable pressed = get_sfall_arg,
             keycode = get_sfall_arg;

    call ConsoleRuntimeKeypressListener(pressed, keycode);
end
