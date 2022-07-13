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


// TODO make this a macro
procedure PrintConsole(variable text) begin
    variable console_data = get_console_data_array;
    if console_data then begin
        call array_push(console_data.display_text_lines, text);
        call ConsoleUI_Render;
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
        call PrintConsole("Command not found: " + command_name); // <--- TODO! RED!
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
    call ConsoleUI_Render;
end
