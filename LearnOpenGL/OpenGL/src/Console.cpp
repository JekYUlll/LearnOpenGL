#include "Console.h"

#if defined(_WIN32) || defined(_WIN64)
void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void ClearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten)) {
        return;
    }
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) {
        return;
    }
    SetConsoleCursorPosition(hConsole, coordScreen);
}
#else
// Dummy implementations for non-Windows platforms
void SetConsoleColor(int color) {
    // No-op on non-Windows platforms
}
void ClearConsole() {
    // Use ANSI escape codes to clear console on Unix-like systems
    std::cout << "\033[2J\033[1;1H";
}
#endif
