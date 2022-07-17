#pragma once

procedure ConsoleRuntime_InitializeHooks begin
    // TODO - research why we don't seem to be able to override keys for other mods (?????)
    register_hook_proc_spec(HOOK_KEYPRESS, ConsoleRuntime_Hooks_Keypress);
    register_hook_proc(HOOK_MOUSECLICK, ConsoleRuntime_Hooks_MouseClick);
    return true;
end
