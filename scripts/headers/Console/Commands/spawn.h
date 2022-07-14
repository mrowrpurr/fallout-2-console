#pragma once

procedure ConsoleCommand_spawn begin
    variable target = get_console_target;
    debug_msg("spawn Target " + target);

    // debug_msg("TYPE: " + obj_type(target));

    variable tile = target;
    // variable tile = tile_num(target);
    // debug_msg("spawn Target tile " + tile);

    if console_arg_count == 1 then begin
        variable pid = get_console_arg_int;
        if pid then begin
            debug_msg("Create " + pid + " " + tile + " " + dude_elevation);
            create_object(pid, tile, dude_elevation);
        end
    end else
        PrintConsole1("spawn expected 1 argument, got %s", console_arg_count);
end
