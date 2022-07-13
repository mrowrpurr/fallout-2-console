#pragma once

procedure ConsoleRuntime_InitializeCommandRegistry begin
    console_data.registered_console_command_names = [];
    fix_array(console_data.registered_console_command_names);
    return true;
end
