#pragma once

#include "Common/UI/TextArea.h"
#include "Common/UI/TextInput.h"

procedure new_console_object begin
    variable console = {};
    //     "visible": false
    // };
    fix_array(console);

    // A bunch of hard-coded stuffs!
    variable full_width = get_screen_width;
    variable background_height = ceil(get_screen_height / 2);

    console.background_width = full_width;
    console.background_height = background_height;

    console.input = TextInput_Create({
        "font": 103,
        "color": "hot pink",
        "width": full_width
    });

    console.input.text = "Hello, this is the input!";

    // variable input_y = background_height + console.input.line_height
    // console.input.y = input_y;

    // console.textarea = TextArea_Create({
    //     "height": half_screen_height,
    //     "y": input_y
    // });

    return console;
end

procedure destroy_console_object(variable console) begin
    if not console then return;
    free_array(console);
end

procedure toggle_console_visibility(variable console) begin
    if not console then return;
    console.visible = not console.visible;
    // call TextArea_ToggleVisibility(console.textarea);
    call TextInput_ToggleVisibility(console.input);
end

procedure console_handle_keypress(variable console, variable is_pressed, variable dx_scan_code) begin
    return TextInput_OnKeypress(console.input, is_pressed, dx_scan_code);
end
