#pragma once

#define CONSOLE_WINDOW_NAME                            "ConsoleWindow"
#define CONSOLE_BACKGROUND_FRM                         "art\\intrface\\Console\\ConsoleBackground.frm"
#define CONSOLE_PROMPT_CHARACTER                       "$"
#define CONSOLE_BACKGROUND_WIDTH                       640
#define CONSOLE_BACKGROUND_HEIGHT                      206
#define CONSOLE_COMMAND_ENTRY_PROMPT_X_OFFSET          46
#define CONSOLE_COMMAND_ENTRY_TEXT_X_OFFSET            57
#define CONSOLE_COMMAND_ENTRY_TEXT_Y_OFFSET            40
#define CONSOLE_COMMAND_ENTRY_TEXT_WIDTH               548 // 640 - (x offset * 2)
#define CONSOLE_COMMAND_ENTRY_TEXT_DEFAULT_FONT        101
#define CONSOLE_COMMAND_ENTRY_TEXT_DEFAULT_LINE_HEIGHT 12
#define CONSOLE_COMMAND_ENTRY_TEXT_ATTRIBUTE           justifyleft
#define ConsoleUI_CommandEntryText_Append(text)        console_data.ui.command_entry_text += text
#define ConsoleUI_CommandEntryText_Clear()             console_data.ui.command_entry_text = ""

// Try to make this work?
// #define CONSOLE_COMMAND_ENTRY_FONT_COLOR     (0.0, 1.0, 0.0)
// #define CONSOLE_COMMAND_OUTPUT_FONT_COLOR    (1.0, 1.0, 1.0)

// NEXT - MAKE COMMAND WORK AGAIN :)

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
    SetTextColor(1.0, 1.0, 0.0);
    SetFont(CONSOLE_COMMAND_ENTRY_TEXT_DEFAULT_FONT);
    Format(
        CONSOLE_PROMPT_CHARACTER,
        CONSOLE_COMMAND_ENTRY_PROMPT_X_OFFSET,
        CONSOLE_COMMAND_ENTRY_TEXT_Y_OFFSET,
        CONSOLE_COMMAND_ENTRY_TEXT_WIDTH,
        CONSOLE_COMMAND_ENTRY_TEXT_DEFAULT_LINE_HEIGHT,
        CONSOLE_COMMAND_ENTRY_TEXT_ATTRIBUTE
    );
    if console_data.ui.command_entry_text then begin
        Format(
            console_data.ui.command_entry_text,
            CONSOLE_COMMAND_ENTRY_TEXT_X_OFFSET,
            CONSOLE_COMMAND_ENTRY_TEXT_Y_OFFSET,
            CONSOLE_COMMAND_ENTRY_TEXT_WIDTH,
            CONSOLE_COMMAND_ENTRY_TEXT_DEFAULT_LINE_HEIGHT,
            CONSOLE_COMMAND_ENTRY_TEXT_ATTRIBUTE
        );
    end
end

procedure ConsoleUI_Refresh begin
    if console_data.ui.visible then begin
        call ConsoleUI_Render;
        show_window(CONSOLE_WINDOW_NAME);
    end
end

procedure ConsoleUI_Show begin
    if is_console_busy then return;
    is_console_busy = true;
    if not console_data.ui.visible then begin
        console_data.ui.visible = true; // set to visible or it won't render
        call ConsoleUI_Refresh;
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

procedure ConsoleUI_TypeKey(variable character) begin
    if console_data.ui.visible then begin
        ConsoleUI_CommandEntryText_Append(character);
        call ConsoleUI_Refresh;
    end
end
