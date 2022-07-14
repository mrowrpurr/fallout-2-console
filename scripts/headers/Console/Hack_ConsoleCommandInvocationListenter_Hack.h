#pragma once

/*
    HACK until this sfall bug is resolved:
    https://github.com/sfall-team/sfall/issues/440
*/

#include "InvokeProc.h"

/*
    Invoked via setup_console_commands in `start` of any global
    script which registers console commands.

    The first time that it is run, it sets up the global repeat.
*/

//
#define __console_command_global_script_repeat_time (100)

//
#define enable_console_commands call __console_command_script_global_repeat_command_invocation_checker

//
variable __console_command_map_of_command_names;

//
variable __console_command_global_script_first_run = true;

//
procedure __console_command_script_global_repeat_command_invocation_checker begin
    if __console_command_global_script_first_run then begin
        // This is the first run, so we simply setup a timer.
        set_global_script_repeat(__console_command_global_script_repeat_time);
        __console_command_map_of_command_names = {};
        fix_array(__console_command_map_of_command_names);
    end else begin
        // This is the timer. So! Let's CHECK to see if a console command
        // which this global script has registered was recently invoked!
        // ****************** TODO ***********************
    end
end


#define register_console_command setup_invoke_procs

// #define console_command_name(command_name) \
//     __console_command_map_of_command_names[command_name] = true
