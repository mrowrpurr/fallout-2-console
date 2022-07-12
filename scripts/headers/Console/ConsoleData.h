#pragma once

// Import shared state of console (comes from the main console global script)
import variable __console_data;

// Local variable for accessing __console_data using map/array syntax
// which exported variables don't currently support.
variable console_data;
