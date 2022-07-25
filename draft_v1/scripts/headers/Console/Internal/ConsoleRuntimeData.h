#pragma once

// Variable to share console's data state from this global script (runtime)
// with other scripts, e.g. other global scripts implementing console commands.
//
// Note: this data is only for the local game session, this data is not saved.
//
export variable __console_data;

// Local variable for accessing __console_data using map/array syntax
// which exported variables don't currently support.
variable console_data;

procedure ConsoleRuntime_InitializeData begin
    __console_data = {};
    fix_array(__console_data);
    console_data = __console_data;
    return true;
end
