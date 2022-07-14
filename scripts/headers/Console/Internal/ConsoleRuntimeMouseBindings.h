#pragma once

// int arg0 - event type: 1 - pressed, 0 - released
// int arg1 - button number (0 - left, 1 - right, up to 7)
procedure ConsoleRuntime_Hooks_MouseClick begin
    variable pressed    = get_sfall_arg,
             left_click = (get_sfall_arg == 0);
    if pressed and left_click and is_console_open then begin
        variable target;
        debug_msg("CLICK!");
        if key_pressed(KEYCODE_LEFT_SHIFT) or key_pressed(KEYCODE_RIGHT_SHIFT) then // Tile
            target = tile_under_cursor;
        else if key_pressed(KEYCODE_LEFT_CTRL) or key_pressed(KEYCODE_RIGHT_CTRL) then // Critters only
            target = obj_under_cursor(true, true);
        else
            target = obj_under_cursor(false, true); // Anything (not tile)
        debug_msg(sprintf("TARGET: %s", target));
        PrintConsole(sprintf("TARGET: %s", target));
        if target then
            console_data.selected_target = target;
    end
end
