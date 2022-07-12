#pragma once

procedure ConsoleRuntime_InitializeHooks begin
    register_hook_proc(HOOK_KEYPRESS, ConsoleRuntime_Hooks_Keypress);
    return true;
end
