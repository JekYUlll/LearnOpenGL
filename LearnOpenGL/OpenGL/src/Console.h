#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

// Function to set console text color (defined differently for Windows and non-Windows platforms)
void SetConsoleColor(int color);

// Function to clear the console
void ClearConsole();

// Macro to simplify setting console text color
#if defined(_WIN32) || defined(_WIN64)
#define SET_CONSOLE_TEXT_COLOR(x) SetConsoleColor(x)
#else
#define SET_CONSOLE_TEXT_COLOR(x) SetConsoleColor(x)
#endif

#endif // CONSOLE_H

