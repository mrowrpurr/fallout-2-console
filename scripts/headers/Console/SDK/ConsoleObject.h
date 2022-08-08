#pragma once

#include "Common/UI/TextArea.h"

procedure new_console_object begin
    variable console = {};
    fix_array(console);

    variable half_screen_height = ceil(get_screen_height / 2);

    console.textarea = TextArea_Create({
        "height": half_screen_height,
        "y": half_screen_height
    });

    return console;
end

procedure destroy_console_object(variable console) begin
    if not console then return;
    free_array(console);
end

procedure toggle_console_visibility(variable console) begin
    if not console then return;
    call TextArea_AddLine(console.textarea, "Hi, the time is currently " + game_time);
    call TextArea_ToggleVisibility(console.textarea);
end
