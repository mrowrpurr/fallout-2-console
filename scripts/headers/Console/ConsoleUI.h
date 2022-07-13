#pragma once

#define CONSOLE_WINDOW_NAME                  "ConsoleWindow"
#define CONSOLE_BACKGROUND_FRM               "art\\intrface\\Console\\ConsoleBackground.frm"
#define CONSOLE_BACKGROUND_WIDTH             640
#define CONSOLE_BACKGROUND_HEIGHT            206
#define CONSOLE_TEXT_FONT                    101

// Try to make this work?
// #define CONSOLE_COMMAND_ENTRY_FONT_COLOR     (0.0, 1.0, 0.0)
// #define CONSOLE_COMMAND_OUTPUT_FONT_COLOR     (1.0, 1.0, 1.0)

variable is_console_busy;

procedure ConsoleUI_InitializeData begin
    console_data.ui = {
        "visible": false,
        "command_entry_text": ""
    };
    fix_array(console_data.ui);

    console_data.ui.output_text_lines = [];
    fix_array(console_data.ui.output_text_lines);

    console_data.ui.screen_width  = get_screen_width;
    console_data.ui.screen_height = get_screen_height;

    if not console_data.ui.screen_width  then console_data.ui.screen_width  = 640;
    if not console_data.ui.screen_height then console_data.ui.screen_height = 480;

    // Position at the bottom of the screen by default
    console_data.ui.x = 0;
    console_data.ui.y = console_data.ui.screen_height - CONSOLE_BACKGROUND_HEIGHT;

    return true;
end

procedure ConsoleUI_Render begin
    create_win_flag(CONSOLE_WINDOW_NAME, console_data.ui.x, console_data.ui.y, CONSOLE_BACKGROUND_WIDTH, CONSOLE_BACKGROUND_HEIGHT, WIN_FLAG_HIDDEN + WIN_FLAG_MOVEONTOP);
    SelectWin(CONSOLE_WINDOW_NAME);
    draw_image(CONSOLE_BACKGROUND_FRM, 0, 0, 0, true);
end

procedure ConsoleUI_Show begin
    if is_console_busy then return;
    is_console_busy = true;
    if not console_data.ui.visible then begin
        call ConsoleUI_Render;
        show_window(CONSOLE_WINDOW_NAME);
        console_data.ui.visible = true;
        is_console_busy = false;
    end
end

procedure ConsoleUI_Hide begin
    if is_console_busy then return;
    is_console_busy = true;
    if console_data.ui.visible then begin
        hide_window(CONSOLE_WINDOW_NAME);
        console_data.ui.visible = false;
        is_console_busy = false;
    end
end

procedure ConsoleUI_Toggle begin
    if console_data.ui.visible then
        call ConsoleUI_Hide;
    else
        call ConsoleUI_Show;
end
