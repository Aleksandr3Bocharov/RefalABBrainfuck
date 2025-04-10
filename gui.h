// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-04-10
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "gui" (GUI raygui raylib версия)
//====================================================================

#ifndef GUI_H
#define GUI_H

#include <stdbool.h>

extern bool dialog_FileName(char *fileName, bool *file_Not_Exist);
extern bool dialog_Is_Exit(void);
extern void gui_Close(void);
extern void gui_Init(void);
extern void view_Errors_Clear(void);
extern bool view_Errors_Show(const char *errors);

#endif
