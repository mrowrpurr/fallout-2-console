#pragma once

#define DEBUG_NAME "Console"

#include "Console/DebugHelper.h"
#include "Console/Internal/ConsoleRuntimeIncludes.h"
#include "Console/Internal/ConsoleRuntimeData.h"
#include "Console/Internal/ConsoleRuntimeConfig.h"
#include "Console/ConsoleDefines.h"
#include "Console/ConsoleEvents.h"
#include "Console/ConsoleCommandRegistry.h"
#include "Console/PrintConsole.h"
#include "Console/ConsoleUI.h"
#include "Console/ConsoleVisibility.h"
#include "Console/Internal/ConsoleRuntimeKeyboardBindings.h"
#include "Console/Internal/ConsoleRuntimeMouseBindings.h"
#include "Console/Internal/ConsoleRuntimeHooks.h"
#include "Console/Internal/ConsoleRuntimeCommandRegistry.h"
#include "Console/Internal/ConsoleRuntimeConsoleEventHandlers.h"
#include "Console/Internal/ConsoleRuntimeTargets.h"
#include "Console/FalloutEtTu.h"

procedure start begin
    if game_loaded then begin
        debug("starting...");
        set_global_script_type(1); // <--- UI script type
        if ConsoleRuntime_InitializeData then
            if ConsoleRuntime_InitializeConfig then
                if ConsoleUI_Initialize then
                    if ConsoleRuntime_InitializeTargets then
                        if ConsoleRuntime_InitializeCommandRegistry then
                            if ConsoleRuntime_InitializeConsoleEventHandlers then
                                if ConsoleRuntime_InitializeHooks then
                                    debug("started ok.");
    end
end
