#pragma once

#include "Console/SearchHelper.h"

procedure ConsoleCommand_search begin
    variable query   = get_console_arg;
    variable results = console_search_multi(query);
    fix_array(results);

    if not len_array(results) then begin
        PrintConsole1("No results found for '%s'", query);
        free_array(results);
        return;
    end

    variable pid, name;
    foreach pid: name in results begin
        PrintConsole2("%s (%s)", name, pid);
    end

    free_array(results);
end
