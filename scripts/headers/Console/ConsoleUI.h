#pragma once

// Useful for getting hex --> float
// Add this to .ini if we don't auto convert 0,255 to floats for you
// (or better yet, hex! Let's support hex OR standard rgb(r, g, b))
// https://corecoding.com/utilities/rgb-or-hex-to-float.php

#define CONSOLE_WINDOW_NAME                            "ConsoleWindow"
#define CONSOLE_BACKGROUND_FRM                         "art\\intrface\\Console\\Console_1024_267.frm"
// #define CONSOLE_BACKGROUND_FRM                         "art\\intrface\\Console\\ConsoleBackground.frm"
#define CONSOLE_PROMPT_CHARACTER                       "$"
// #define CONSOLE_BACKGROUND_WIDTH                       640
// #define CONSOLE_BACKGROUND_HEIGHT                      260
// Current hardcoded design is 1920x500 which is 46.3% of the screen height
#define CONSOLE_COMMAND_DEFAULT_LINE_HEIGHT            (14)
#define CONSOLE_COMMAND_DEFAULT_FONT                   101
#define CONSOLE_COMMAND_TEXT_JUSTIFY                   justifyleft
#define CONSOLE_COMMAND_ENTRY_PROMPT_X_OFFSET          46
#define CONSOLE_COMMAND_ENTRY_TEXT_X_OFFSET            57
#define CONSOLE_COMMAND_ENTRY_TEXT_Y_OFFSET            (40)
#define CONSOLE_COMMAND_ENTRY_TEXT_WIDTH               548 // todo determine
#define CONSOLE_COMMAND_OUTPUT_TEXT_X_OFFSET           45
#define CONSOLE_COMMAND_OUTPUT_TEXT_WIDTH              562
#define CONSOLE_COMMAND_OUTPUT_MAX_LINE_COUNT          11
#define CONSOLE_COMMAND_ENTRY_BACKGROUND_X             40
#define CONSOLE_COMMAND_ENTRY_BACKGROUND_Y             35
#define CONSOLE_COMMAND_ENTRY_BACKGROUND_WIDTH         562
#define CONSOLE_COMMAND_ENTRY_BACKGROUND_HEIGHT        172
#define CONSOLE_COMMAND_ENTRY_BACKGROUND_COLOR         0.016, 0.047, 0.0
#define CONSOLE_RGB_COLOR_GREEN                        0.0, 1.0, 0.0
#define CONSOLE_RGB_COLOR_WHITE                        1.0, 1.0, 1.0
#define CONSOLE_RGB_COLOR_TEXT_AREA_BACKGROUND_COLOR   1.0, 1.0, 1.0
#define ConsoleUI_CommandEntryText_Append(text)        console_data.ui.command_entry_text += text
#define ConsoleUI_CommandEntryText_Clear()             console_data.ui.command_entry_text = ""

variable is_console_busy;
variable console_window_instaniated;

procedure ConsoleUI_Render begin
    debug("ConsoleUI Render");

    variable art_width = 1024;
    variable art_height = 267;

    variable screen_width  = get_screen_width;
    variable screen_height = get_screen_height;
    debug2f("Screen Resolution: %sx%s", screen_width, screen_height);

    variable console_width  = screen_width;
    variable console_height = floor(screen_height * 0.45);
    debug2f("Console Resolution: %sx%s", console_width, console_height);

    variable console_x = 0;
    variable console_y = screen_height - console_height;
    debug2f("Console Position: %sx%s", console_x, console_y);

    if console_window_instaniated then begin

        debug("Console Window Already Instantiated");

        // SelectWin(CONSOLE_WINDOW_NAME);
        // FillRect(
        //     CONSOLE_COMMAND_ENTRY_BACKGROUND_X,
        //     CONSOLE_COMMAND_ENTRY_BACKGROUND_Y,
        //     CONSOLE_COMMAND_ENTRY_BACKGROUND_WIDTH,
        //     CONSOLE_COMMAND_ENTRY_BACKGROUND_HEIGHT,
        //     CONSOLE_COMMAND_ENTRY_BACKGROUND_COLOR
        // );
    end else begin

        debug("Console Window Instantiating...");
        
        console_window_instaniated = true;
        create_win_flag(
            CONSOLE_WINDOW_NAME,
            console_x,
            console_y,
            art_width,
            art_height,
            WIN_FLAG_HIDDEN + WIN_FLAG_MOVEONTOP
        );
        SelectWin(CONSOLE_WINDOW_NAME);

        debug("draw_image");
        draw_image(CONSOLE_BACKGROUND_FRM, 0, 0, 0, true);

        debug("ScaleWin");
        ScaleWin(CONSOLE_WINDOW_NAME, console_x, console_y, console_width, console_height);

    end

    debug("ShowWin...");
    ShowWin;
    debug("Showed.");
end

procedure ConsoleUI_Render_ORIGINAL_DRAFT begin
    // ...

    SetFont(CONSOLE_COMMAND_DEFAULT_FONT);
    SetTextColor(CONSOLE_RGB_COLOR_GREEN);
    Format(
        CONSOLE_PROMPT_CHARACTER,
        CONSOLE_COMMAND_ENTRY_PROMPT_X_OFFSET,
        CONSOLE_COMMAND_ENTRY_TEXT_Y_OFFSET,
        CONSOLE_COMMAND_ENTRY_TEXT_WIDTH,
        CONSOLE_COMMAND_DEFAULT_LINE_HEIGHT,
        CONSOLE_COMMAND_TEXT_JUSTIFY
    );
    if console_data.ui.command_entry_text then begin
        Format(
            console_data.ui.command_entry_text,
            CONSOLE_COMMAND_ENTRY_TEXT_X_OFFSET,
            CONSOLE_COMMAND_ENTRY_TEXT_Y_OFFSET,
            CONSOLE_COMMAND_ENTRY_TEXT_WIDTH,
            CONSOLE_COMMAND_DEFAULT_LINE_HEIGHT,
            CONSOLE_COMMAND_TEXT_JUSTIFY
        );
    end
    if len_array(console_data.ui.output_text_lines) > 0 then begin
        SetTextColor(CONSOLE_RGB_COLOR_WHITE);
        variable y = CONSOLE_COMMAND_ENTRY_TEXT_Y_OFFSET + CONSOLE_COMMAND_DEFAULT_LINE_HEIGHT;
        // Make it auto-scroll down! and only render X lines!
        // Get the last CONSOLE_COMMAND_OUTPUT_MAX_LINE_COUNT in the array.
        // Go backwards in a for()
        variable line;
        foreach line in (console_data.ui.output_text_lines) begin
            Format(
                line,
                CONSOLE_COMMAND_OUTPUT_TEXT_X_OFFSET,
                y,
                CONSOLE_COMMAND_OUTPUT_TEXT_WIDTH,
                CONSOLE_COMMAND_DEFAULT_LINE_HEIGHT,
                CONSOLE_COMMAND_TEXT_JUSTIFY
            );
            y += CONSOLE_COMMAND_DEFAULT_LINE_HEIGHT;
        end
    end
    ShowWin;
end

procedure ConsoleUI_Show begin
    if is_console_busy then return;
    is_console_busy = true;
    if not console_data.ui.visible then begin
        call ConsoleUI_Render;
        show_window(CONSOLE_WINDOW_NAME);
        console_data.ui.visible = true;
        is_console_busy = false;
        SendConsoleEvent(CONSOLE_EVENT_ON_OPEN);
    end
end

procedure ConsoleUI_Hide begin
    if is_console_busy then return;
    is_console_busy = true;
    if console_data.ui.visible then begin
        hide_window(CONSOLE_WINDOW_NAME);
        console_data.ui.visible = false;
        is_console_busy = false;
        SendConsoleEvent(CONSOLE_EVENT_ON_CLOSE);
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
        call ConsoleUI_Render;
    end
end

procedure ConsoleUI_Initialize begin
    console_data.ui = {
        "visible": false,
        "command_entry_text": ""
    };
    fix_array(console_data.ui);

    console_data.ui.output_text_lines = [];
    fix_array(console_data.ui.output_text_lines);

    // console_data.ui.screen_width  = get_screen_width;
    // console_data.ui.screen_height = get_screen_height;

    // if not console_data.ui.screen_width  then console_data.ui.screen_width  = 640;
    // if not console_data.ui.screen_height then console_data.ui.screen_height = 480;

    // // Position at the bottom of the screen by default
    // console_data.ui.x = 0;
    // console_data.ui.y = console_data.ui.screen_height - CONSOLE_BACKGROUND_HEIGHT;

    RegisterConsoleEventProc(CONSOLE_EVENT_RENDER, ConsoleUI_Render);
    RegisterConsoleEventProc(CONSOLE_EVENT_OPEN,   ConsoleUI_Show);
    RegisterConsoleEventProc(CONSOLE_EVENT_CLOSE,  ConsoleUI_Hide);

    return true;
end
