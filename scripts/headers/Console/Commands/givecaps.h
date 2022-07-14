#pragma once

procedure ConsoleCommand_givecaps begin

    display_msg("YOU RAN THE HANDLER!!!");
    return 69;


    // TODO select target!
    variable target = dude_obj;

    if console_arg_count != 1 then begin
        PrintConsole1("givecaps expected 1 argument, received %s", console_arg_count);
        return;
    end

    variable caps = get_console_arg_int;
    PrintConsole1("CAPS: %s", caps);
    variable _ = item_caps_adjust(target, caps);
    PrintConsole("DO WE GET HERE?");

    if caps > 0 then
        PrintConsole2("Added %s caps to %s", caps, obj_name(target));
    else if caps < 0 then
        PrintConsole2("Remove %s caps from %s", caps, obj_name(target));
    else
        PrintConsole("Please specify a number of caps above or below zero.");
end
