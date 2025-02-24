// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-02-23
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "gui" (GUI raygui raylib версия)
//====================================================================

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION 

#define GUI_WINDOW_FILE_DIALOG_IMPLEMENTATION
#include "gui_window_file_dialog.h"

#include "gui.h"

void guiwindow(void)
{
    InitWindow(400, 200, "raygui - controls test suite");
    SetTargetFPS(60);
    bool showMessageBox = false;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        if (GuiButton((Rectangle){24, 24, 120, 30}, "#191#Show Message"))
            showMessageBox = true;
        if (showMessageBox)
        {
            int result = GuiMessageBox((Rectangle){85, 70, 250, 100},
                                       "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

            if (result >= 0)
                showMessageBox = false;
        }
        EndDrawing();
    }
    CloseWindow();
}