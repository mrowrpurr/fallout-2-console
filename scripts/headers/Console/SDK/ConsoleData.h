#pragma once

/*
    #include "Console/Data.h" to get __CONSOLE_DATA__ from the Console SDK.

    Reminder: the compiler does not support array/map expressions on imported
              variables, e.g. __CONSOLE_DATA__. To use these expressions,
              make a secondary variable as an alias:

              #include "Console/Data.h"

              variable console_data = __CONSOLE_DATA__;
              console_data.something;
*/

import variable __CONSOLE_DATA__;
