#pragma once

// Keycode to return when we want to hijack keys and not send
// then to be processed by Fallout
#define KEYCODE_THAT_DOES_NOTHING 255

// Hardcoded Shift keycodes
#define KEYCODE_LEFT_SHIFT  42
#define KEYCODE_RIGHT_SHIFT 54

// Tracked whether SHIFT in currently pressed because key_pressed()
// doesn't capture SHIFT in the *pressed* event (which we use)
// it only works in the *released* event (which we don't use)
variable is_shift_pressed = false;

procedure on_enter begin
    // call ConsoleUI_ExecuteCurrentCommand;
end

procedure on_delete begin
    // console_data.command_text = substr(console_data.command_text, 0, strlen(console_data.command_text) - 2);
    // call ConsoleUI_Refresh;
end

procedure on_spacebar begin
    // call ConsoleUI_TypeText(" ");
end

procedure on_pageup begin
end

procedure on_pagedown begin
end

procedure on_home begin
end

procedure on_end begin
end

procedure on_tab begin
end

procedure on_up begin
end

procedure on_down begin
end

procedure on_left begin
end

procedure on_right begin
end

// int     arg0 - event type: 1 - pressed, 0 - released
// int     arg1 - key DX scancode
// int     arg2 - key VK code (very similar to ASCII codes)
// int     ret0 - overrides the pressed key (a new key DX scancode or 0 for no override)
procedure ConsoleRuntime_Hooks_Keypress begin
    variable pressed = get_sfall_arg,
             keycode = get_sfall_arg;

    // We only care about the *pressed* event, not *released*
    if not pressed then return;

    // Track SHIFT
    if keycode == KEYCODE_LEFT_SHIFT or keycode == KEYCODE_RIGHT_SHIFT then begin
        is_shift_pressed = pressed;
        return;
    end

    // TODO - return unless the console is open
    return;

    // The .ini configuration file uses string keys.
    // So get a string representation of the keycode.
    variable string_keycode = sprintf("%s", keycode);

    // Handle visibility toggle shortcuts
    switch string_keycode begin
        case data.config.Shortcuts.toggle_console: begin
            // call ConsoleUI_ToggleOpen;
            set_sfall_return(KEYCODE_THAT_DOES_NOTHING);
            return;
        end
        case data.config.Shortcuts.open_console: begin
            // call ConsoleUI_Show;
            set_sfall_return(KEYCODE_THAT_DOES_NOTHING);
            return;
        end
        case data.config.Shortcuts.close_console: begin
            // call ConsoleUI_Hide;
            set_sfall_return(KEYCODE_THAT_DOES_NOTHING);
            return;
        end
    end

    // Handle special keys
    if map_contains_key(data.config.SpecialKeys, string_keycode) then begin
        variable special_key_name = data.config.SpecialKeys[string_keycode];
        switch special_key_name begin
            case "SPACE": call on_spacebar;
            case "DEL":   call on_delete;
            case "TAB":   call on_tab;
            case "ENTER": call on_enter;
            case "HOME":  call on_home;
            case "END":   call on_end;
            case "UP":    call on_up;
            case "DOWN":  call on_down;
            case "LEFT":  call on_left;
            case "RIGHT": call on_right;
            case "PGUP":  call on_pagedown;
            case "PGDN":  call on_pageup;
        end
        set_sfall_return(KEYCODE_THAT_DOES_NOTHING);
        return;
    end

    // Handle regular keys
    if map_contains_key(data.config.Keys, string_keycode) then begin
        variable character;
        if is_shift_pressed then
            character = substr(data.config.Keys[string_keycode], 1, 1);
        else
            character = substr(data.config.Keys[string_keycode], 0, 1);
        set_sfall_return(KEYCODE_THAT_DOES_NOTHING);
        return;
    end
end
