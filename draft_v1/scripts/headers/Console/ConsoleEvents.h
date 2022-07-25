#pragma once

#define CONSOLE_EVENTS_PREFIX    "ConsoleEvent:"
#define CONSOLE_EVENT_ON_OPEN    "OnShowConsole"
#define CONSOLE_EVENT_ON_CLOSE   "OnHideConsole"
#define CONSOLE_EVENT_ON_RENDER  "OnRenderConsole"
#define CONSOLE_EVENT_OPEN       "ShowConsole"
#define CONSOLE_EVENT_CLOSE      "HideConsole"
#define CONSOLE_EVENT_RENDER     "RenderConsole"

#define SendConsoleEvent(event_name) \
    SignalNamed(CONSOLE_EVENTS_PREFIX + event_name)

#define RegisterConsoleEventProc(event_name, proc) \
    AddNamedHandler(CONSOLE_EVENTS_PREFIX + event_name, proc)
