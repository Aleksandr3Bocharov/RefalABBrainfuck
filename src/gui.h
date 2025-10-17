// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-05-17
// https://github.com/Aleksandr3Bocharov/refalabbrainfuck

//====================================================================
// Модуль "gui" (GUI raygui raylib версия)
//====================================================================

#ifndef GUI_H
#define GUI_H

#include <stdbool.h>

typedef enum
{
    OK,
    NOT_EXIST,
    NOT_OPEN
} T_FILE_STATUS;

extern bool dialog_FileName(char *fileName, const char *open_Error, T_FILE_STATUS *file_Status);
extern bool dialog_Is_Exit(void);
extern void gui_Close(void);
extern void gui_Init(void);
extern void view_Errors_Clear(void);
extern bool view_Errors_Show(const char *errors);

#endif
