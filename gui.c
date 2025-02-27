// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-02-27
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
static const int screenHeight = 360;

static int errorsViewScrollIndex = 0;
static int errorsViewActive = -1;

Font cyrillicFont;

static GuiWindowFileDialogState fileDialogState;

void guiInit(void)
{
    InitWindow(screenWidth, screenHeight, "RefalABBrainfuck (GUI версия)");
    SetExitKey(0);
    cyrillicFont = LoadFont("dejavu.fnt");
    GuiSetFont(cyrillicFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 15);
    fileDialogState = InitGuiWindowFileDialog(GetWorkingDirectory());
    SetTargetFPS(60);
}

void guiClose(void)
{
    CloseWindow();
}

bool guiFileName(char *fileName)
{
    bool ok = false;
    bool exitWindow = false;
    while (!exitWindow)
    {
        exitWindow = WindowShouldClose();
        if (fileDialogState.SelectFilePressed)
        {
            if (fileDialogState.fileNameText[0] != '\0')
                strncpy(fileName, TextFormat("%s" PATH_SEPERATOR "%s", fileDialogState.dirPathText, fileDialogState.fileNameText), 254);
            fileDialogState.SelectFilePressed = false;
        }
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        DrawText("The programm "
                 "RefalABBrainfuck (GUI version)"
                 "",
                 10, 20, 20, DARKGRAY);
        DrawTextEx(cyrillicFont, "ппп", (Vector2){64.0f, 64.0f}, (float)cyrillicFont.baseSize + 5.0f, 1.0f, DARKGRAY);
        DrawText("interprets code on the language Brainfuck from source file.", 10, 60, 20, DARKGRAY);
        DrawText("The opening of the source file", 10, 150, 20, DARKGRAY);
        DrawText(TextFormat(""
                            "%s"
                            "",
                            fileName),
                 10, 190, 20, GRAY);
        DrawText("with code on the Brainfuck language.", 10, 230, 20, DARKGRAY);
        DrawText("The running of the interpretator of the code on the Brainfuck language.", 10, 320, 20, DARKGRAY);
        if (fileDialogState.windowActive)
            GuiLock();
        if (GuiButton((Rectangle){screenWidth / 2 - 170, 100, 340, 30}, GuiIconText(ICON_FILE_OPEN, "Открыть файл с исходником Brainfuck")))
            fileDialogState.windowActive = true;
        if (GuiButton((Rectangle){screenWidth / 2 - 140, 270, 280, 30}, "Запустить интерпретатор Brainfuck"))
            if (*fileName != '\0')
            {
                ok = true;
                exitWindow = true;
            }
        GuiUnlock();
        GuiSetFont(GetFontDefault());
        GuiLoadStyleDefault();
        GuiWindowFileDialog(&fileDialogState);
        GuiSetFont(cyrillicFont);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 15);
        EndDrawing();
    }
    return ok;
}

void guiErrClear(void)
{
    errorsViewScrollIndex = 0;
    errorsViewActive = -1;
}

bool guiErrView(const char *errors)
{
    bool exitWindow = false;
    bool ok = false;
    while (!exitWindow)
    {
        exitWindow = WindowShouldClose();
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        GuiListView((Rectangle){10, 20, screenWidth - 20, screenHeight - 90}, errors, &errorsViewScrollIndex, &errorsViewActive);
        if (GuiButton((Rectangle){screenWidth / 2 - 20, screenHeight - 50, 40, 30}, "OK"))
        {
            ok = true;
            exitWindow = true;
        }
        EndDrawing();
    }
    return ok;
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
