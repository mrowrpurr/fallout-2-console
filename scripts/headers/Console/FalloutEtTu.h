#pragma once

#define is_running_ettu (get_ini_setting("config\\fo1_settings.ini|Fo1in2|GVAR_ENABLE_MOTORCYCLE") != -1)
#define is_running_fallout1 is_running_ettu
#define is_running_fallout2 (not is_running_ettu)
