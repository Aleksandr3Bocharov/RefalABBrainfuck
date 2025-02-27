// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-02-27
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "gui" (GUI raygui raylib версия)
//====================================================================

#ifndef GUI_H
#define GUI_H

#include <stdbool.h>

extern void guiClose(void);
extern bool guiErrView(const char *errors);
extern bool guiFileName(char *fileName);
extern void guiInit(void);
extern bool guiIsExit(void);

#endif
