#ifndef CONFIG_H
#define CONFIG_H

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // !GLEW_STATIC

#ifdef PRINT_SHADER
#undef PRINT_SHADER
#endif // PRINT_SHADER
#ifdef _DEBUG
// #define PRINT_SHADER
#endif // _DEBUG

#define VERSION_1 3
#define VERSION_2 3
#define USE_CORE true

#define ICON_PATH "res/icons/opengl.png"
#define FONT_PATH "res/fonts/ProFontWindowsNerdFontPropo-Regular.ttf"
#define NO_PICTURE "res/textures/NERF"







#endif // !CONFIG_H



