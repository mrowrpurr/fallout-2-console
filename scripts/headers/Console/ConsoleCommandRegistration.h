#pragma once

#define register_console_command(command_name, proc) \
    console_data = __console_data; \
    if not does_console_command_exist(command_name) then begin \
        call array_push(console_data.registered_console_command_names, command_name); \
        AddNamedHandler(CONSOLE_COMMAND_NAMED_HANDLER_PREFIX + command_name, proc); \
    end else \
        debug_msg(sprintf("[Console] [Warning] Console command '%s' already registered.", command_name))
