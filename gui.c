// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-02-25
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "gui" (GUI raygui raylib версия)
//====================================================================

#include <string.h>
#include <stdbool.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

#define GUI_WINDOW_FILE_DIALOG_IMPLEMENTATION
#include "gui_window_file_dialog.h"

#include "gui.h"

bool guiFileName(char *fileName)
{
    bool ok = false;
    // Initialization
    //---------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 340;
    InitWindow(screenWidth, screenHeight, "RefalABBrainfuck (GUI версия)");
    SetExitKey(0);
    // Custom file dialog
    GuiWindowFileDialogState fileDialogState = InitGuiWindowFileDialog(GetWorkingDirectory());
    bool exitWindow = false;
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    // Main loop
    while (!exitWindow) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        exitWindow = WindowShouldClose();
        if (fileDialogState.SelectFilePressed)
        {
            // Get Brainfuck's source file name
            if (fileDialogState.fileNameText[0] != '\0')
                strcpy(fileName, TextFormat("%s" PATH_SEPERATOR "%s", fileDialogState.dirPathText, fileDialogState.fileNameText));
            fileDialogState.SelectFilePressed = false;
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        DrawText(fileName, 10, 60, 20, GRAY);
        // raygui: controls drawing
        //----------------------------------------------------------------------------------
        if (fileDialogState.windowActive)
            GuiLock();
        if (GuiButton((Rectangle){screenWidth / 2 - 90, 20, 180, 30}, GuiIconText(ICON_FILE_OPEN, "Open Brainfuck's source file")))
            fileDialogState.windowActive = true;
        if (GuiButton((Rectangle){screenWidth / 2 - 80, screenHeight - 50, 160, 30}, "Run Brainfuck Interpretator"))
            if (*fileName != '\0')
            {
                ok = true;
                exitWindow = true;
            }
        GuiUnlock();
        // GUI: Dialog Window
        //--------------------------------------------------------------------------------
        GuiWindowFileDialog(&fileDialogState);
        //--------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return ok;
}