/*
    Shared header for the Fallout 2 ~ console by Mrowr Purr

    Usage:

        #include "Console.h"

        procedure give_item_command begin
            get_console_args;
            get_console_arg_at();
            console_print("");
        end

        procedure start begin
            if game_loaded then register_console_command("giveitem", give_item_command);
        end

*/

// TODO - store history in Console.ini using set_ini_setting

// FYI get_text_width

#include "sfall/define_extra.h"
#include "sfall/sfall.h"
#include "sfall/lib.strings.h"
#include "sfall/lib.arrays.h" // remove if not used here
 
#define CONSOLE_WINDOW_NAME                  "ConsoleWin"
#define CONSOLE_BACKGROUND_FRM               "art\\intrface\\Console\\ConsoleBackground.frm"
#define CONSOLE_BACKGROUND_WIDTH             444
#define CONSOLE_BACKGROUND_HEIGHT            206
#define CONSOLE_INI_FILEPATH                 "Console.ini"
#define CONSOLE_DATA_GLOBAL_SFALL_VAR_NAME   "_mp_CNSL"
#define CONSOLE_KEYMAP_GLOBAL_SFALL_VAR_NAME "_mp_CNks"
#define CONSOLE_TEXT_FONT                    101
#define get_console_data_array               get_sfall_global_int(CONSOLE_DATA_GLOBAL_SFALL_VAR_NAME)
#define get_console_keymap_array             get_sfall_global_int(CONSOLE_KEYMAP_GLOBAL_SFALL_VAR_NAME)
#define is_console_initialized               (get_console_data != 0)

// TODO make this a macro
procedure ConsolePrint(variable text) begin
    variable console_data = get_console_data_array;
    if console_data then begin
        call array_push(console_data.display_text_lines, text);
    end else
        debug_msg("Cannot print to console, not initialized yet!");
end

// procedure ConsoleSprintf(variable text, variable arg)

procedure ConsoleExecuteCommand(variable command) begin
    display_msg("EXEC " + command);
    call ConsolePrint("I printed this! from exec");
    call ConsolePrint("I printed this too! from exec");
end

procedure ConsoleUI_Show begin
    display_msg("SHOW!");

    variable console_data = get_console_data_array;

    if not console_data then begin
        console_data = {
            "command_text": "",
            "visible": false,
            "initialized": false
        };
        set_sfall_global(CONSOLE_DATA_GLOBAL_SFALL_VAR_NAME, console_data);
        fix_array(console_data);
        
        // History of commands. To be saved in .ini and can get to with UP (and we'll make CTRL-R eventually) 
        console_data.command_history = [];
        fix_array(console_data.command_history);
        
        // The text display output where commands print their output (in white)
        console_data.display_text_lines = [];
        fix_array(console_data.display_text_lines);

        variable keymap = {};
        fix_array(keymap);
        set_sfall_global(CONSOLE_KEYMAP_GLOBAL_SFALL_VAR_NAME, keymap);
        keymap.keys = get_ini_section(CONSOLE_INI_FILEPATH, "Keys");
        fix_array(keymap.keys);
        keymap.special_keys = get_ini_section(CONSOLE_INI_FILEPATH, "SpecialKeys");
        fix_array(keymap.special_keys);
    end

    if console_data.initialized then begin
        if not console_data.visible then begin
            show_window(CONSOLE_WINDOW_NAME);
            console_data.visible = true;
        end

    end else begin
        console_data.initialized = true;
        console_data.visible = true;

        create_win_flag(CONSOLE_WINDOW_NAME, 0, 0, CONSOLE_BACKGROUND_WIDTH, CONSOLE_BACKGROUND_HEIGHT, WIN_FLAG_HIDDEN + WIN_FLAG_MOVEONTOP);
        SelectWin(CONSOLE_WINDOW_NAME);
        draw_image(CONSOLE_BACKGROUND_FRM, 0, 0, 0, true);

        SetFont(CONSOLE_TEXT_FONT);
        SetTextColor(0.0, 1.0, 0.0); // Green
        Format("$", 46, 40, 300, 12, justifyleft);

        show_window(CONSOLE_WINDOW_NAME);
    end
end

procedure ConsoleUI_Hide begin
    variable console_data = get_console_data_array;
    if console_data and console_data.visible then begin
        console_data.visible = false;
        hide_window(CONSOLE_WINDOW_NAME);
    end
end

procedure ConsoleUI_ToggleOpen begin
    variable console_data = get_console_data_array;
    if console_data then begin
        if console_data.visible then call ConsoleUI_Hide;
        else call ConsoleUI_Show;
    end else
        call ConsoleUI_Show;
end

procedure ConsoleUI_Refresh begin
    variable console_data = get_console_data_array;
    if console_data and console_data.visible then begin
        hide_window(CONSOLE_WINDOW_NAME);
        SelectWin(CONSOLE_WINDOW_NAME);
        draw_image(CONSOLE_BACKGROUND_FRM, 0, 0, 0, true);
        SetFont(CONSOLE_TEXT_FONT);

        // Green
        SetTextColor(0.0, 1.0, 0.0);
        Format("$", 46, 40, 300, 12, justifyleft);
        Format(console_data.command_text, 57, 40, 300, 12, justifyleft);
        
        // White
        if len_array(console_data.display_text_lines) > 0 then begin
            SetTextColor(1.0, 1.0, 1.0);
            variable line_height = 14;
            variable height = 55;
            variable line;
            foreach line in (console_data.display_text_lines) begin
                Format(line, 46, height, 300, 12, justifyleft);
                height += line_height;
            end
        end
        
        show_window(CONSOLE_WINDOW_NAME);
    end
end

procedure ConsoleUI_Print(variable text) begin
    display_msg("CONSOLE UI PRINT...");
end

procedure ConsoleUI_ExecuteCurrentCommand begin
    variable console_data = get_console_data_array;
    variable command = console_data.command_text;
    console_data.command_text = "";
    call ConsoleExecuteCommand(command);
    call ConsoleUI_Refresh;
end

procedure ConsoleUI_TypeText(variable character) begin
    variable console_data = get_console_data_array;
    if console_data and console_data.visible then begin
        console_data.command_text += character;
        call ConsoleUI_Refresh;
    end
end
