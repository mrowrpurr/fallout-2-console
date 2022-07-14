#pragma once

#include "Console/ConsoleEvents.h"
#include "Console/ConsoleIncludes.h"
#include "Console/ConsoleDefines.h"
#include "Console/ConsoleData.h"
#include "Console/ConsoleCommandRegistry.h"
#include "Console/ConsoleCommandRegistration.h"
#include "Console/ConsoleCommandArguments.h"
#include "Console/ConsoleCommandTargets.h"
#include "Console/PrintConsole.h"
#include "Console/ConsoleVisibility.h"

// Include this AWFUL hack which sets up global scripts
// to WATCH for console command invocations via
// set_global_script_repeat (~twice a second)
// UNTIL the sfall bug with SignalNamed and temp arrays is fixed
#include "Console/Hack_ConsoleCommandInvocationListenter_Hack.h"
