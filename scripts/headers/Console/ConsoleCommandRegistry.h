#pragma once

#define does_console_command_exist(command_name) ( \
    scan_array( \
        console_data.registered_console_command_names, \
        command_name \
    ) > -1)
