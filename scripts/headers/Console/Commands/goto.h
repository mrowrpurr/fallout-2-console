#pragma once

procedure ConsoleCommand_goto begin
    load_map(get_console_arg + ".map", 1);
end
