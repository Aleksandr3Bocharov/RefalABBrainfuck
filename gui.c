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
    // Initialization
    //---------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 560;
    InitWindow(screenWidth, screenHeight, "RefalABBrainfuck (GUI версия)");
    SetExitKey(0);
    // Custom file dialog
    GuiWindowFileDialogState fileDialogState = InitGuiWindowFileDialog(GetWorkingDirectory());
    bool exitWindow = false;
    char fileName[512] = {'\0'};
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
            // Get Brainfuck's source file nmae
            strcpy(fileName, TextFormat("%s" PATH_SEPERATOR "%s", fileDialogState.dirPathText, fileDialogState.fileNameText));
            fileDialogState.SelectFilePressed = false;
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        DrawText(fileName, 210, 20, 20, GRAY);
        // raygui: controls drawing
        //----------------------------------------------------------------------------------
        if (fileDialogState.windowActive)
            GuiLock();
        if (GuiButton((Rectangle){20, 20, 180, 30}, GuiIconText(ICON_FILE_OPEN, "Open Brainfuck's source file")))
            fileDialogState.windowActive = true;
        if (GuiButton((Rectangle){screenWidth / 2 - 80, screenHeight - 60, 160, 30}, "Run Brainfuck Interpretator"))
            exitWindow = true;
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
}