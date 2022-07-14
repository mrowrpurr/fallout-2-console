#pragma once

procedure ConsoleRuntime_InitializeHooks begin
    register_hook_proc(HOOK_KEYPRESS, ConsoleRuntime_Hooks_Keypress);
    register_hook_proc(HOOK_MOUSECLICK, ConsoleRuntime_Hooks_MouseClick);
    return true;
end
