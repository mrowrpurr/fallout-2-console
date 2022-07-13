#pragma once

#define ConsolePrint(text) \
    display_msg("CONSOLE PRINT and console_data is " + console_data); \
    call array_push(console_data.ui.output_text_lines, text); \
    SignalNamed(CONSOLE_UI_RENDER_NAMED_HANDLER_NAME)
