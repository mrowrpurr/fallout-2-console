#pragma once

#include "sfall/define_extra.h"

#include "Common/Color/WebColors.h"
#include "Common/UI/TextArea.h"
#include "Common/UI/TextInput.h"

// TODO - read this stuff from the .ini
#define CONSOLE_BACKGROUND_IMAGE "art/intrface/Console/ConsoleBackground.frm"

procedure new_console_object begin
    variable console = {
        "window": "the_console"
    };
    //     "visible": false
    // };
    fix_array(console);

    // A bunch of hard-coded stuffs!
    variable full_width = get_screen_width;
    variable background_height = ceil(get_screen_height / 2);

    console.background_width = full_width;
    console.background_height = background_height;

    console.input = TextInput_Create({
        "font": 101,
        "color": "lime",
        "width": (full_width - 40),
        "y": background_height + 20,
        "x": 20
    });

    console.textarea = TextArea_Create({
        "font": 101,
        "color": "white",
        "width": (full_width - 40),
        "height": background_height - 50,
        "y": background_height + 35,
        "x": 20
    });

    return console;
end

procedure destroy_console_object(variable console) begin
    if not console then return;
    free_array(console);
end

procedure initialize_console(variable console) begin
    create_win_flag(
        console.window,
        0,
        (get_screen_height / 2),
        get_screen_width,
        ceil(get_screen_height / 2),
        WIN_FLAG_MOVEONTOP + WIN_FLAG_TRANSPARENT
    );
    draw_image_scaled(
        CONSOLE_BACKGROUND_IMAGE,
        0,
        0,
        0,
        get_screen_width,
        (get_screen_height / 2)
    );
end

procedure show_console(variable console) begin
    if not console.initialized then call initialize_console(console);
    SelectWin(console.window);

    // re-render a solid color background
    variable color = webcolor_hex("black");

    FillRect(
        14,
        11,
        get_screen_width - 28,
        (get_screen_height / 2) - 22,
        rgb_red_float_from_hex(color),
        rgb_green_float_from_hex(color),
        rgb_blue_float_from_hex(color)
    );
    // FillRect (int x, int y, int width, int height, int R, int G, int B)

    ShowWin;
    call TextInput_ToggleVisibility(console.input);
    call TextArea_ToggleVisibility(console.textarea);
    console.visible = true;
end

procedure hide_console(variable console) begin
    hide_window(console.window);
    call TextInput_ToggleVisibility(console.input);
    call TextArea_ToggleVisibility(console.textarea);
    console.visible = false;
end

procedure destroy_console(variable console) begin

end

procedure toggle_console_visibility(variable console) begin
    if console.visible then
        call hide_console(console);
    else
        call show_console(console);
end

procedure console_handle_keypress(variable console, variable is_pressed, variable dx_scan_code) begin
    return TextInput_OnKeypress(console.input, is_pressed, dx_scan_code);
end
