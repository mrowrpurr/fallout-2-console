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

procedure ConsolePrint(variable text);
procedure ConsoleUI_Refresh;


procedure Console_Initialize begin
    variable console_data = get_console_data_array;

    if not console_data then begin
        console_data = {
            "command_text": "",
            "visible": false,
            "initialized": false,
            "arguments_text": "" // <----
        };
        set_sfall_global(CONSOLE_DATA_GLOBAL_SFALL_VAR_NAME, console_data);
        fix_array(console_data);
        
        // Registry of command names
        console_data.registered_command_names = [];
        fix_array(console_data.registered_command_names);

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

    return console_data;
end

procedure __Console_RegisterCommand(variable command_name) begin
    variable console_data = Console_Initialize;
    if scan_array(console_data.registered_command_names, command_name) != -1 then
        return false; // Someone else already registered this command, sorry!
    else begin
        display_msg("REGISTER COMMAND: " + command_name);
        call array_push(console_data.registered_command_names, command_name);
        return true;
    end
end

#define register_console_command(command_name, proc) \
    if __Console_RegisterCommand(command_name) then AddNamedHandler("ConsoleCommand:" + command_name, proc)

// TODO make this a macro
procedure ConsolePrint(variable text) begin
    variable console_data = get_console_data_array;
    if console_data then begin
        call array_push(console_data.display_text_lines, text);
        call ConsoleUI_Refresh;
    end else
        debug_msg("Cannot print to console, not initialized yet!");
end

// procedure ConsoleSprintf(variable text, variable arg)

procedure ConsoleExecuteCommand(variable command_name) begin
    variable console_data = Console_Initialize;

    display_msg("EXEC , here are the commands:");
    display_array(console_data.registered_command_names);

    if scan_array(console_data.registered_command_names, command_name) != -1 then begin
        // Setup some variables to they can get the ARGUMENTS!
        SignalNamed("ConsoleCommand:" + command_name);
    end else begin
        ///...
        // ConsoleError(); // <--- TODO! RED!

        // MAKE THIS A MACRO:
        call ConsolePrint("Command not found: " + command_name); // <--- TODO! RED!
    end
end

procedure ConsoleUI_Show begin
    variable console_data = Console_Initialize;

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
