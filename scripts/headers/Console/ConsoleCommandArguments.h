#pragma once

#define get_console_args console_data.most_recent_command_line_arguments

procedure get_console_arg begin
    variable arg;
    if len_array(console_data.most_recent_command_line_arguments) > 0 then begin
        arg = console_data.most_recent_command_line_arguments[0];
        call array_cut(console_data.most_recent_command_line_arguments, 0, 1);
    end
    return arg;
end

procedure get_console_arg_at(variable index) begin
    variable arg;
    if len_array(console_data.most_recent_command_line_arguments) >= (index + 1) then
        arg = console_data.most_recent_command_line_arguments[index];
    return arg;
end
