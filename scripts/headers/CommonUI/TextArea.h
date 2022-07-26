#pragma once

/*
    Represents a single, scrollable text area which displays read-only text.

    Individual lines can be different colors.
    
    Does not support different colors for charcters in the same line.
*/

#include "CommonUI/RGBColor.h"

// Private field accessors

#define __TextArea_width(text_area)               text_area.width
#define __TextArea_height(text_area)              text_area.height
#define __TextArea_background_color(text_area)    text_area.background_color
#define __TextArea_all_lines(text_area)           text_area.all_lines
#define __TextArea_all_line_colors(text_area)     text_area.all_line_colors
#define __TextArea_visible_lines(text_area)       text_area.visible_lines
#define __TextArea_visible_line_colors(text_area) text_area.visible_line_colors

// Getters and setters

#define TextArea_getWidth(text_area) (text_area.width = width)
#define TextArea_setWidth(text_area, width) text_area.width = width

#define TextArea_getHeight(text_area) (text_area.height)
#define TextArea_setHeight(text_area, height) text_area.height = height

// #define TextArea_setBackgroundColor(text_area, color)    text_area.background_color

procedure TextArea_Create begin
    variable text_area = {};
    fix_array(text_area);

    // Stores all lines 
    TextArea_all_lines(text_area) = [];
    fix_array(TextArea_all_lines(text_area));

    // Stores colors of each line (shares index of all_lines)
    TextArea_all_line_colors(text_area) = [];
    fix_array(TextArea_all_line_colors(text_area));

    // Stores visible lines 
    TextArea_visible_lines(text_area) = [];
    fix_array(TextArea_visible_lines(text_area));

    // Stores colors of each line (shares index of visible_lines)
    TextArea_visible_line_colors(text_area) = [];
    fix_array(TextArea_visible_line_colors(text_area));

    return text_area;
end

