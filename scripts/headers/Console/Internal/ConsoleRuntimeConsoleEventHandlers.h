#pragma once

procedure ConsoleRuntime_OnConsoleOpen begin
    stop_game;
end

procedure ConsoleRuntime_OnConsoleClose begin
    resume_game;
end

procedure ConsoleRuntime_InitializeConsoleEventHandlers begin
    RegisterConsoleEventProc(CONSOLE_EVENT_ON_OPEN, ConsoleRuntime_OnConsoleOpen);
    RegisterConsoleEventProc(CONSOLE_EVENT_ON_CLOSE, ConsoleRuntime_OnConsoleClose);
    return true;
end
