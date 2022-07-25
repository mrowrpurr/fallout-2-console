#pragma once

procedure ConsoleCommand_destroy begin
    variable target = get_console_target;
    if target != dude_obj then begin
        debug_msg("DESTROY " + target);
        destroy_object(target);
    end
end
