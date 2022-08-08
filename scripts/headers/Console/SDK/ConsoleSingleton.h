#pragma once

#include "Console/SDK/ConsoleData.h"
#include "Console/SDK/ConsoleObject.h"

#define __CONSOLE_DATA__KEY__CONSOLE_SINGLETON_OBJECT "ConsoleSingleton"

#define get_console_singleton \
    (get_array(__CONSOLE_DATA__, __CONSOLE_DATA__KEY__CONSOLE_SINGLETON_OBJECT))

#define init_console_singleton \
    if not get_console_singleton then \
        set_array(__CONSOLE_DATA__, __CONSOLE_DATA__KEY__CONSOLE_SINGLETON_OBJECT, new_console_object)

#define toggle_console_singleton_visibility \
    call toggle_console_visibility(get_console_singleton)

#define is_console_singleton_visible \
    (get_array(get_console_singleton, "visible") if get_console_singleton else false)

#define console_singleton_handle_keypress(is_pressed, dx_scan_code) \
    console_handle_keypress(get_console_singleton, is_pressed, dx_scan_code)

procedure destroy_console_singleton begin
    variable singleton = get_console_singleton;
    if singleton then begin
        call destroy_console_object(singleton);
        set_array(__CONSOLE_DATA__, __CONSOLE_DATA__KEY__CONSOLE_SINGLETON_OBJECT, 0);
    end
end
