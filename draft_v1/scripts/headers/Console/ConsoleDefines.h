#pragma once

// Common #define across console scripts/headers.
//
// Used by both the runtime and console commands alike.
//
// Please:
//  1. Do not add many #define because these will auto-complete in the
//     editors of everyone creating a console command
//  2. Prefix every define with CONSOLE_

#define CONSOLE_COMMAND_NAMED_HANDLER_PREFIX "ConsoleCommand:"

// Hardcoded Shift keycodes
#define KEYCODE_LEFT_SHIFT  42
#define KEYCODE_RIGHT_SHIFT 54

// Hardcoded Shift keycodes
#define KEYCODE_LEFT_CTRL  29
#define KEYCODE_RIGHT_CTRL 157
