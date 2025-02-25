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

static const int screenWidth = 800;
static const int screenHeight = 340;

void guiInit(void)
{
    InitWindow(screenWidth, screenHeight, "RefalABBrainfuck (GUI версия)");
    SetExitKey(0);
    SetTargetFPS(60);
}

void guiClose(void)
{
    CloseWindow();
}

bool guiFileName(char *fileName)
{
    bool ok = false;
    GuiWindowFileDialogState fileDialogState = InitGuiWindowFileDialog(GetWorkingDirectory());
    bool exitWindow = false;
    while (!exitWindow)
    {
        exitWindow = WindowShouldClose();
        if (fileDialogState.SelectFilePressed)
        {
            if (fileDialogState.fileNameText[0] != '\0')
                strcpy(fileName, TextFormat("%s" PATH_SEPERATOR "%s", fileDialogState.dirPathText, fileDialogState.fileNameText));
            fileDialogState.SelectFilePressed = false;
        }
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        DrawText(fileName, 10, 60, 20, GRAY);
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
        GuiWindowFileDialog(&fileDialogState);
        EndDrawing();
    }
    return ok;
}

void guiMessage(const char *message)
{
    bool exitWindow = false;
    while (!exitWindow)
    {
        exitWindow = WindowShouldClose();
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(RAYWHITE, 0.8f));
        int result = GuiMessageBox((Rectangle){screenWidth / 2 - 125, screenHeight / 2 - 50, 250, 100}, GuiIconText(ICON_EXIT, "Exit"), message, "OK");
        if (result == 0 || result == 1)
            exitWindow = true;
        EndDrawing();
    }
}

bool guiIsExit(void)
{
    bool isExit = true;
    bool exitWindow = false;
    while (!exitWindow)
    {
        exitWindow = WindowShouldClose();
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(RAYWHITE, 0.8f));
        int result = GuiMessageBox((Rectangle){screenWidth / 2 - 125, screenHeight / 2 - 50, 250, 100}, GuiIconText(ICON_EXIT, "Exit"), "Do you really want to exit?", "Yes;No");
        if (result == 0 || result == 1 || result == 2)
        {
            exitWindow = true;
            if (result == 0 || result == 2)
                isExit = false;
        }
        EndDrawing();
    }
    return isExit;
}
