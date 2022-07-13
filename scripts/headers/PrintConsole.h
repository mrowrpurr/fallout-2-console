#pragma once

/*
    sprintf-style helper macros for PrintConsole()
*/

#define PrintConsole1(text, arg) PrintConsole(sprintf(text, arg))
#define PrintConsole2(text, arg1, arg2) PrintConsole(sprintf_array(text, [arg1, arg2]))
#define PrintConsole3(text, arg1, arg2, arg3) PrintConsole(sprintf_array(text, [arg1, arg2, arg3]))
#define PrintConsole4(text, arg1, arg2, arg3, arg4) PrintConsole(sprintf_array(text, [arg1, arg2, arg3, arg4]))
#define PrintConsole5(text, arg1, arg2, arg3, arg4, arg5) PrintConsole(sprintf_array(text, [arg1, arg2, arg3, arg4, arg5]))
#define PrintConsole6(text, arg1, arg2, arg3, arg4, arg5, arg6) PrintConsole(sprintf_array(text, [arg1, arg2, arg3, arg4, arg5, arg6]))
#define PrintConsole7(text, arg1, arg2, arg3, arg4, arg5, arg6, arg7) PrintConsole(sprintf_array(text, [arg1, arg2, arg3, arg4, arg5, arg6, arg7]))
#define PrintConsole8(text, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) PrintConsole(sprintf_array(text, [arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8]))
#define PrintConsole9(text, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) PrintConsole(sprintf_array(text, [arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9]))
