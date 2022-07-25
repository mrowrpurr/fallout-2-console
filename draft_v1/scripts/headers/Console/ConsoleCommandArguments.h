#pragma once

#define get_console_args      console_data.most_recent_command_line_arguments
#define any_console_args      (len_array(console_data.most_recent_command_line_arguments) > 0)
#define console_arg_count     len_array(console_data.most_recent_command_line_arguments)
#define get_console_arg_int   atoi(get_console_arg)
#define get_console_arg_float atof(get_console_arg)

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
