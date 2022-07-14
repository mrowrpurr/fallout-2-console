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
#define enable_console_commands \
    set_global_script_type(1); \
    console_data = __console_data; \
    call __console_command_script_global_repeat_command_invocation_checker

//
variable __console_command_name_registration_optimizer_trick_variable = true;

//
variable __console_command_name_string_proc_name_variable_for_invocation = true;

//
variable __console_command_name_string_proc_fake_result_variable_for_invocation = true;

//
variable __console_command_map_of_command_names_to_proc_names;

//
variable __console_command_global_script_first_run = true;

//
#define run_console_command_handler(proc_name) \
    __console_command_name_string_proc_name_variable_for_invocation = proc_name; \
    __console_command_name_string_proc_fake_result_variable_for_invocation = __console_command_name_string_proc_name_variable_for_invocation(); \
    __console_command_name_registration_optimizer_trick_variable = false; \
    if __console_command_name_registration_optimizer_trick_variable then \
        debug_msg(__console_command_name_string_proc_fake_result_variable_for_invocation)

//
procedure __console_command_script_global_repeat_command_invocation_checker begin
    if __console_command_global_script_first_run then begin
        __console_command_global_script_first_run = false;
        // This is the first run, so we simply setup a timer.
        set_global_script_repeat(__console_command_global_script_repeat_time);
        __console_command_map_of_command_names_to_proc_names = {};
        fix_array(__console_command_map_of_command_names_to_proc_names);
    end else begin
        // This is the timer. So! Let's CHECK to see if a console command
        // which this global script has registered was recently invoked!
        // if console_data.most_recent_command_name_ready_for_execution and map_contains_key(__console_command_map_of_command_names_to_proc_names, console_data.most_recent_command_name_ready_for_execution) then begin
        if map_contains_key(__console_command_map_of_command_names_to_proc_names, console_data.most_recent_command_name_ready_for_execution) then begin
            variable command_name = console_data.most_recent_command_name_ready_for_execution;
            console_data.most_recent_command_name_ready_for_execution = 0;
            variable proc_name = __console_command_map_of_command_names_to_proc_names[command_name];
            run_console_command_handler(proc_name);
        end
    end
end

//
#define register_console_command(command_name, proc_name, proc) \
    __console_command_map_of_command_names_to_proc_names[command_name] = proc_name; \
    call array_push(console_data.registered_console_command_names, command_name); \
    __console_command_name_registration_optimizer_trick_variable = false; \
    if __console_command_name_registration_optimizer_trick_variable then \
        call proc
