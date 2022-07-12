#pragma once

/*
    Header for the Fallout 2 ~ console
    
    by Mrowr Purr

    Usage:

        #include "Console.h"

        procedure give_item_command begin
            get_console_args;
            get_console_arg_at();
            console_print("");
        end

        procedure start begin
            if game_loaded then register_console_command("giveitem", give_item_command);
        end

    Note: this file assumes that your sfall headers are accessible via the path:
    
        #include "sfall/sfall.h"

    If your sfall headers are located elsewhere and you would prefer not to move them:

        // Define the paths to your sfall headers
        #define SFALL_HEADER_SFALL        "sfall_headers/sfall.h"
        #define SFALL_HEADER_DEFINE_EXTRA "sfall_headers/define_extra.h"
        #define SFALL_HEADER_LIB_STRINGS  "sfall_headers/lib.strings.h"
        #define SFALL_HEADER_LIB_ARRAYS   "sfall_headers/lib.arrays.h"

        // Include Console/Console which allows you to set these headers yourself.
        #include "Console/Console.h"

*/

#define SFALL_HEADER_SFALL        "sfall/sfall.h"
#define SFALL_HEADER_DEFINE_EXTRA "sfall/define_extra.h"
#define SFALL_HEADER_LIB_STRINGS  "sfall/lib.strings.h"
#define SFALL_HEADER_LIB_ARRAYS   "sfall/lib.arrays.h"

#include "Console/Console.h"
