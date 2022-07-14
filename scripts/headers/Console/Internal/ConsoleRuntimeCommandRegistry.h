#pragma once

procedure ConsoleRuntime_InitializeCommandRegistry begin
    console_data.registered_console_command_names = [];
    fix_array(console_data.registered_console_command_names);
    console_data.most_recent_command_name_ready_for_execution = 0;
    console_data.most_recent_command_line_arguments = 0;
    return true;
end
