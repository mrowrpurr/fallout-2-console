#pragma once

#define PrintConsole(text) call __ConsolePrint(text)
    
procedure __ConsolePrint(variable text) begin
    SetFont(101); // TODO - read this from console_data.config.UI !!!
    variable text_width = get_text_width(text);
    variable available_width = 562; // Also get this from config !!!
    if text_width > available_width then begin
        variable current_line = "";
        variable lines_to_add = [];
        fix_array(lines_to_add);
        variable i, chars;
        for (i = 0; i < strlen(text); i = i + 5;) begin
            chars = substr(text, i, 5);
            if get_text_width(current_line + chars) >= available_width then begin
                // It's too long, add this line to the list of lines + continue
                call array_push(lines_to_add, current_line);
                current_line = chars;
            end else begin
                // It's under the limit, add it to the current line
                current_line = current_line + chars;
            end
        end
        if strlen(current_line) > 0 then
            call array_push(lines_to_add, current_line);
        variable line;
        foreach line in lines_to_add begin
            call array_push(console_data.ui.output_text_lines, line);
        end
        free_array(lines_to_add);
        SignalNamed(CONSOLE_UI_RENDER_NAMED_HANDLER_NAME);
    end else begin
        call array_push(console_data.ui.output_text_lines, text);
        SignalNamed(CONSOLE_UI_RENDER_NAMED_HANDLER_NAME);
    end
end
