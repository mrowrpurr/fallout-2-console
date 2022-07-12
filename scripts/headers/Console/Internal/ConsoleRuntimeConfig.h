#pragma once

#define CONSOLE_INI_LOOKUP_PATHS "Console.ini,mods\\Console.ini,data\\Console.ini"
#define CONSOLE_INI_REQUIRED_SECTIONS "Shortcuts,Keys,SpecialKeys"

procedure ConsoleRuntime_InitializeConfig begin
    variable lookup_paths = string_split(CONSOLE_INI_LOOKUP_PATHS, ",");
    variable found_path;

    // Find .ini
    variable ini_path;
    foreach ini_path in lookup_paths begin
        // Check for existence of the .ini file in this location.
        // If the file (or setting) does not exist, it will return -1.
        variable shortcut = get_ini_setting(ini_path + "|Shortcuts|toggle_console");
        if shortcut != -1 then begin
            found_path = ini_path;
            break;
        end
    end

    if not found_path then begin
        debug1f(
            "[Error] No .ini configuration file found. Stopping. Search paths: %s",
            CONSOLE_INI_LOOKUP_PATHS
        );
        return false;
    end

    debug1f("Reading .ini %s", found_path);
    variable section_names = get_ini_sections(found_path);

    // Verify .ini
    variable required_sections = string_split(CONSOLE_INI_REQUIRED_SECTIONS, ",");
    variable required_section;
    foreach required_section in required_sections begin
        if scan_array(section_names, required_section) == -1 then begin
            debug2f(
                "[Error] Invalid .ini '%s' Missing required section: [%s]",
                found_path,
                required_section
            );
            return false;
        end
    end

    // Read .ini
    // We currently store the entire .ini in-memory on console data object.
    data.config = {};
    fix_array(data.config);
    variable section_name;
    foreach section_name in section_names begin
        variable section = get_ini_section(found_path, section_name);
        fix_array(section);
        data.config[section_name] = section;
    end

    return true;
end
