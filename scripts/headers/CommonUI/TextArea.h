#pragma once

/*
    Represents a single, scrollable text area which displays read-only text.

    Individual lines can be different colors.
    
    Does not support different colors for charcters in the same line.
*/

#include "sfall/define_extra.h"
#include "CommonUI/RGBColor.h"

// Find out the max length!
// This will be unique for each TextArea
#define WINDOW_NAME "SomeCoolWindow1234567890123456x"

procedure TextArea_Create(variable defaults = 0) begin
    variable text_area = defaults if defaults else {};
    fix_array(text_area);

    // If no name provided, choose a random name. Prefix like _TEXTAREA_ then big number.
    // Use a saved array to store all text area names for checking uniqueness.

    // Stores all lines 
    text_area.all_lines = [];
    fix_array(text_area.all_lines);

    // Stores colors of each line (shares index of all_lines)
    // Stored as 'normalized' RGB colors (use RGB normalize/extract functions)
    text_area.line_colors = [];
    fix_array(text_area.line_colors);

    // Stores visible lines 
    text_area.visible_lines = [];
    fix_array(text_area.visible_lines);

    // Stores colors of each line (shares index of visible_lines)
    // Stored as 'normalized' RGB colors (use RGB normalize/extract functions)
    text_area.visible_line_colors = [];
    fix_array(text_area.visible_line_colors);

    return text_area;
end

// Set a bit to note that it's rendering!
procedure TextArea_Render(variable text_area) begin

end

procedure TextArea_DestroyUI(variable text_area) begin
    
end

procedure TextArea_Show(variable text_area) begin
    text_area.visible = true;
    log_info("SHOW WINDOW '" + WINDOW_NAME + "'");
    create_win_flag(
            WINDOW_NAME,
            10,
            100,
            500,
            400,
            WIN_FLAG_HIDDEN + WIN_FLAG_MOVEONTOP
        );
    SelectWin(WINDOW_NAME);
    FillWin(0.0, 0.0, 0.0);
    SetFont(101);
    SetTextColor(0.988, 0, 0.957);
    Format("Hey wassup? a bunch of text yo!", 5, 10, 240, 12, justifyleft);
    show_window(WINDOW_NAME);
end

procedure TextArea_Hide(variable text_area) begin
    DeleteWin(WINDOW_NAME); // check if it exists first
    text_area.visible = false;
end

procedure TextArea_ToggleVisibility(variable text_area) begin
    if text_area then begin
        if text_area.visible then
            call TextArea_Hide(text_area);
        else
            call TextArea_Show(text_area);
    end
end

procedure TextArea_Destroy(variable text_area) begin

end
