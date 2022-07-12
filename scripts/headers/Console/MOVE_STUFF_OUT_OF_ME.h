


procedure Console_Initialize begin
    variable console_data = get_sfall_global_int(CONSOLE_SFALL_GLOBAL_VARIABLE_NAME);

    // Initialize if not present
    if (not console_data) and (len_array(console_data) > 0) then begin
        
        // The console uses a single array to store its state
        console_data = {
            // The current text displayed in the console
            "command_text": "",
            // Is the console currently visible?
            "visible": false,
            // Has the UI window been created?
            "ui_initialized": false
        };

        set_sfall_global(CONSOLE_SFALL_GLOBAL_VARIABLE_NAME, console_data);
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

        //
        console_data.most_recent_command_arguments = [];
        fix_array(console_data.most_recent_command_arguments);

        variable keymap = {};
        fix_array(keymap);
        set_sfall_global(CONSOLE_SFALL_GLOBAL_CONSOLE_KEYMAP, keymap);
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

procedure ConsoleExecuteCommand(variable command_name, variable arguments) begin
    variable console_data = Console_Initialize;
    // console_data.arguments = arguments;

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

    if console_data.ui_initialized then begin
        if not console_data.visible then begin
            show_window(CONSOLE_WINDOW_NAME);
            console_data.visible = true;
        end

    end else begin
        console_data.ui_initialized = true;
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
    variable command_text = console_data.command_text;
    console_data.command_text = "";
    variable arguments = "";
    variable command_space = string_pos(command_text, " ");
    if command_space > -1 and strlen(command_text) > command_space then begin
        arguments = substr(command_text, command_space + 1, 0);
        command_text = substr(command_text, 0, command_space);
    end
    call ConsoleExecuteCommand(command, arguments);
    call ConsoleUI_Refresh;
end

procedure ConsoleUI_TypeText(variable character) begin
    variable console_data = get_console_data_array;
    if console_data and console_data.visible then begin
        console_data.command_text += character;
        call ConsoleUI_Refresh;
    end
end
