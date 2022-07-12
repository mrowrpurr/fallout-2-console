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

// TODO - store history in Console.ini using set_ini_setting

// FYI get_text_width

#include "sfall/define_extra.h"
#include "sfall/sfall.h"
#include "sfall/lib.strings.h"
#include "sfall/lib.arrays.h" // remove if not used here
 
#define CONSOLE_WINDOW_NAME                  "ConsoleWin"
#define CONSOLE_BACKGROUND_FRM               "art\\intrface\\Console\\ConsoleBackground.frm"
#define CONSOLE_BACKGROUND_WIDTH             444
#define CONSOLE_BACKGROUND_HEIGHT            206
#define CONSOLE_INI_FILEPATH                 "Console.ini"
#define CONSOLE_DATA_GLOBAL_SFALL_VAR_NAME   "_mp_CNSL"
#define CONSOLE_KEYMAP_GLOBAL_SFALL_VAR_NAME "_mp_CNks"
#define CONSOLE_TEXT_FONT                    101
#define get_console_data_array               get_sfall_global_int(CONSOLE_DATA_GLOBAL_SFALL_VAR_NAME)
#define get_console_keymap_array             get_sfall_global_int(CONSOLE_KEYMAP_GLOBAL_SFALL_VAR_NAME)
#define is_console_initialized               (get_console_data != 0)

procedure ConsoleShow begin
    variable console_data = get_console_data_array;

    if not console_data then begin
        console_data = { "text": "", "visible": false, "initialized": false };
        set_sfall_global(CONSOLE_DATA_GLOBAL_SFALL_VAR_NAME, console_data);
        fix_array(console_data);
        console_data.history = [];
        fix_array(console_data.history);

        variable keymap = {};
        fix_array(keymap);
        set_sfall_global(CONSOLE_KEYMAP_GLOBAL_SFALL_VAR_NAME, keymap);
        keymap.keys = get_ini_section(CONSOLE_INI_FILEPATH, "Keys");
        fix_array(keymap.keys);
        keymap.special_keys = get_ini_section(CONSOLE_INI_FILEPATH, "SpecialKeys");
        fix_array(keymap.special_keys);
    end

    if console_data.initialized then begin
        if not console_data.visible then begin
            show_window(CONSOLE_WINDOW_NAME);
            console_data.visible = true;
        end

    end else begin
        console_data.initialized = true;
        console_data.visible = true;

        create_win_flag(CONSOLE_WINDOW_NAME, 0, 0, CONSOLE_BACKGROUND_WIDTH, CONSOLE_BACKGROUND_HEIGHT, WIN_FLAG_HIDDEN + WIN_FLAG_MOVEONTOP);
        SelectWin(CONSOLE_WINDOW_NAME);
        draw_image(CONSOLE_BACKGROUND_FRM, 0, 0, 0, true);

        SetFont(CONSOLE_TEXT_FONT);
        SetTextColor(0.0, 1.0, 0.0); // Green
        Format("$", 46, 40, 300, 12, justifyleft);

        show_window(CONSOLE_WINDOW_NAME);
    end
end

procedure ConsoleHide begin
    variable console_data = get_console_data_array;
    if console_data and console_data.visible then begin
        console_data.visible = false;
        hide_window(CONSOLE_WINDOW_NAME);
    end
end

procedure ConsoleToggleOpen begin
    variable console_data = get_console_data_array;
    if console_data then begin
        if console_data.visible then call ConsoleHide;
        else call ConsoleShow;
    end else
        call ConsoleShow;
end

procedure ConsoleRefresh begin
    variable console_data = get_console_data_array;
    if console_data and console_data.visible then begin
        hide_window(CONSOLE_WINDOW_NAME);
        SelectWin(CONSOLE_WINDOW_NAME);
        draw_image(CONSOLE_BACKGROUND_FRM, 0, 0, 0, true);
        SetFont(CONSOLE_TEXT_FONT);
        SetTextColor(0.0, 1.0, 0.0); // Green
        Format("$", 46, 40, 300, 12, justifyleft);
        Format(console_data.text, 57, 40, 300, 12, justifyleft);
        show_window(CONSOLE_WINDOW_NAME);
    end
end

procedure ConsoleTypeText(variable character) begin
    variable console_data = get_console_data_array;
    if console_data and console_data.visible then begin
        console_data.text += character;
        call ConsoleRefresh;
    end
end
