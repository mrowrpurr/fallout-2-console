/*
    Shared header for the Fallout 2 ~ console by Mrowr Purr

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

*/

#include "sfall/define_extra.h"
#include "sfall/sfall.h"
#include "sfall/lib.strings.h"

#define CONSOLE_DEBUG_NAME     "Console"
#define CONSOLE_WINDOW_NAME    "ConsoleWin"
#define CONSOLE_BACKGROUND_FRM "art\\intrface\\Console\\ConsoleBackground.frm"
#define CONSOLE_INI_FILEPATH   "Console.ini"

// TODO - remove these from the final product?
// TODO - add a `console_debug` macro that prints out to the actual console
//        like console_print but maybe with a prefix? I dunno.
#define _console_debug(text)                          debug_msg("[" CONSOLE_DEBUG_NAME "] " + text)
#define _console_debug1(text, arg)                    _console_debug(sprintf_array(text, [arg]))
#define _console_debug2(text, arg1, arg2)             _console_debug(sprintf_array(text, [arg1, arg2]))
#define _console_debug3(text, arg1, arg2, arg3)       _console_debug(sprintf_array(text, [arg1, arg2, arg3]))
#define _console_debug4(text, arg1, arg2, arg3, arg4) _console_debug(sprintf_array(text, [arg1, arg2, arg3, arg4]))

procedure ConsoleShow begin
    display_msg("... we will now show the console ...");
    _console_debug2("x %s y %s", get_interface_x(WINTYPE_DIALOG), get_interface_y(WINTYPE_DIALOG));
    _console_debug2("width %s height %s", get_interface_width(WINTYPE_DIALOG), get_interface_height(WINTYPE_DIALOG));

    variable width = 444;
    variable height = 206;

    create_win_flag(CONSOLE_WINDOW_NAME, 0, 0, width, height, WIN_FLAG_HIDDEN + WIN_FLAG_MOVEONTOP);
    // create_win_flag(CONSOLE_WINDOW_NAME, 0, 0, width, height, WIN_FLAG_MOVEONTOP);
    SelectWin(CONSOLE_WINDOW_NAME);
    draw_image(CONSOLE_BACKGROUND_FRM, 0, 0, 0, true);
    show_window(CONSOLE_WINDOW_NAME);
end

procedure ConsoleHide begin
    hide_window(CONSOLE_WINDOW_NAME);
end
