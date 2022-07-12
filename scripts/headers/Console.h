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

        // For "ConsoleBase.h" to work, it requires importing console data.
        // You do not need to manually do this when including "Console.h"
        // This variable is exported from gl__fallout_console.int
        import variable CONSOLE_DATA;

        // Include the base shared header for the console
        #include "ConsoleBase.h"

*/

#define SFALL_HEADER_SFALL        "sfall/sfall.h"
#define SFALL_HEADER_DEFINE_EXTRA "sfall/define_extra.h"
#define SFALL_HEADER_LIB_STRINGS  "sfall/lib.strings.h"
#define SFALL_HEADER_LIB_ARRAYS   "sfall/lib.arrays.h"

import variable CONSOLE_DATA;

#include "ConsoleBase.h"
