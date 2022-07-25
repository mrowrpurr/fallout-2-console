#pragma once

// Note: [section names] in these .ini files MUST be all uppercase, e.g. [ITEMS]
#define CONSOLE_SEARCH_INI_ETTU "ConsoleSearch.ettu.ini"
#define CONSOLE_SEARCH_INI_FO2  "ConsoleSearch.FO2.ini"
#define CONSOLE_SEARCH_INI (CONSOLE_SEARCH_INI_ETTU if is_running_ettu else CONSOLE_SEARCH_INI_FO2)

// Helper macros
#define console_search_multi(query)                    console_search(query, { "multiple": true })
#define console_search_category(query, category)       console_search(query, { "category": category })
#define console_search_category_multi(query, category) console_search(query, { "category": category, "multiple": true })

/*
    Available options: multiple, category, case_sensitive, starts_with.

    Fastest option: Provide a category and use case_sensitive.
                    There is no speed improvement when using starts_with.
*/
procedure console_search(variable query, variable options = 0) begin
    if not options then options = {};
    variable return_multiple     = options.multiple;
    variable search_category     = options.category;
    variable case_sensitive      = options.case_sensitive;
    variable search_string_start = options.starts_with;
    variable return_permanent    = options.permanent;

    // .ini will either be for Fallout 2 or Fallout et tu
    variable ini_path = CONSOLE_SEARCH_INI;

    debug1f("Searching .ini: %s", ini_path);

    // Read the search .ini section names into memory
    variable ini_sections = get_ini_sections(CONSOLE_SEARCH_INI);

    if search_category then begin
        search_category = string_toupper(search_category);
        if scan_array(ini_sections, search_category) == -1 then begin
            debug_msg(sprintf("Category '%s' not found in search ini: ", search_category) + ini_path);
            return {};
        end
    end

    // Map of PID to name
    variable results = {};

    // Fixed arrays while we search
    fix_array(ini_sections);
    fix_array(results);

    variable entry_pid, entry_name,
             comparison_name,         // for case insensitive searching
             category_search_entries; // entry array for given category

    // TODO - See if we can refactor below to use any macros.
    //        Do NOT refactor into procedures, keep everything inlined.

    // Branches for case sensitivity and string start and category so that
    // we don't evaluate these conditinals O(n) times in this slow engine.
    if search_category then begin
        category_search_entries = get_ini_section(ini_path, search_category);
        fix_array(category_search_entries);

        if case_sensitive then begin
            // case sensitive - this category - starts with
            if search_string_start then begin
                foreach entry_pid: entry_name in category_search_entries begin
                    if string_starts_with(entry_name, query) then begin
                        results[entry_pid] = entry_name;
                        if not return_multiple then break;
                    end
                end
            // case sensitive - this category - string contains
            end else begin
                foreach entry_pid: entry_name in category_search_entries begin
                    if is_in_string(entry_name, query) then begin
                        results[entry_pid] = entry_name;
                        if not return_multiple then break;
                    end
                end
            end
        end else begin
            query = string_tolower(query);

            // case insensitive - this category - starts with
            if search_string_start then begin
                foreach entry_pid: entry_name in category_search_entries begin
                    comparison_name = string_tolower(entry_name);
                    if string_starts_with(comparison_name, query) then begin
                        results[entry_pid] = entry_name;
                        if not return_multiple then break;
                    end
                end

            // case insensitive - this category - string contains
            end else begin
                foreach entry_pid: entry_name in category_search_entries begin
                    comparison_name = string_tolower(entry_name);
                    if is_in_string(comparison_name, query) then begin
                        results[entry_pid] = entry_name;
                        if not return_multiple then break;
                    end
                end
            end
        end

        free_array(category_search_entries);

    // Search across all categories
    end else begin
        variable current_category_name; // name of category currently being searched
        variable found_result;          // foreach break control for single result queries

        if case_sensitive then begin
            // case sensitive - any category - starts with
            if search_string_start then begin
                foreach current_category_name in ini_sections begin
                    category_search_entries = get_ini_section(ini_path, current_category_name);
                    fix_array(category_search_entries);

                    foreach entry_pid: entry_name in category_search_entries begin
                        if string_starts_with(entry_name, query) then begin
                            results[entry_pid] = entry_name;
                            if not return_multiple then begin
                                found_result = true;
                                break;
                            end
                        end
                    end

                    free_array(category_search_entries);
                    if not return_multiple and found_result then break;
                end

            // case sensitive - any category - string contains
            end else begin
                foreach current_category_name in ini_sections begin
                    category_search_entries = get_ini_section(ini_path, current_category_name);
                    fix_array(category_search_entries);

                    foreach entry_pid: entry_name in category_search_entries begin
                        if is_in_string(entry_name, query) then begin
                            results[entry_pid] = entry_name;
                            if not return_multiple then begin
                                found_result = true;
                                break;
                            end
                        end
                    end

                    free_array(category_search_entries);
                    if not return_multiple and found_result then break;
                end
            end

        end else begin
            query = string_tolower(query);

            // case insensitive - any category - starts with
            if search_string_start then begin
                foreach current_category_name in ini_sections begin
                    category_search_entries = get_ini_section(ini_path, current_category_name);
                    fix_array(category_search_entries);

                    foreach entry_pid: entry_name in category_search_entries begin
                        comparison_name = string_tolower(entry_name);
                        if string_starts_with(comparison_name, query) then begin
                            results[entry_pid] = entry_name;
                            if not return_multiple then begin
                                found_result = true;
                                break;
                            end
                        end
                    end

                    free_array(category_search_entries);
                    if not return_multiple and found_result then break;
                end

            // case insensitive - any category - string contains
            end else begin
                foreach current_category_name in ini_sections begin
                    category_search_entries = get_ini_section(ini_path, current_category_name);
                    fix_array(category_search_entries);

                    foreach entry_pid: entry_name in category_search_entries begin
                        comparison_name = string_tolower(entry_name);
                        if is_in_string(comparison_name, query) then begin
                            results[entry_pid] = entry_name;
                            if not return_multiple then begin
                                found_result = true;
                                break;
                            end
                        end
                    end

                    free_array(category_search_entries);
                    if not return_multiple and found_result then break;
                end
            end
        end
    end
    
    if return_permanent then begin
        // Keep results, free ini_sections
        free_array(ini_sections);

        return results;

    end else begin
        // Copy discovered results into a temp array
        variable return_results = clone_array(results);

        // Free the arrays
        free_array(ini_sections);
        free_array(results);

        return return_results;
    end
end
