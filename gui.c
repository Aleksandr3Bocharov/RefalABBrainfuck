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
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
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
    float sizeCyrillicFont = (float)cyrillicFont.baseSize + 1.0f;
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
        DrawTextEx(cyrillicFont, "The programm ""RefalABBrainfuck (GUI version)""", (Vector2){10.0f, 20.0f}, sizeCyrillicFont, 1.0f, DARKGRAY);
        DrawTextEx(cyrillicFont, "interprets code on the language Brainfuck from source file.", (Vector2){10.0f, 60.0f}, sizeCyrillicFont, 1.0f, DARKGRAY);
        DrawTextEx(cyrillicFont, "The opening of the source file", (Vector2){10.0f, 150.0f}, sizeCyrillicFont, 1.0f, DARKGRAY);
        DrawTextEx(cyrillicFont, TextFormat("""%s""", fileName), (Vector2){10.0f, 190.0f}, sizeCyrillicFont, 1.0f, GRAY);
        DrawTextEx(cyrillicFont, "with code on the Brainfuck language.", (Vector2){10.0f, 230.0f}, sizeCyrillicFont, 1.0f, DARKGRAY);
        DrawTextEx(cyrillicFont, "The running of the interpretator of the code on the Brainfuck language.", (Vector2){10.0f, 320.0f}, sizeCyrillicFont, 1.0f, DARKGRAY);
        if (fileDialogState.windowActive)
            GuiLock();
        if (GuiButton((Rectangle){screenWidth / 2 - 210, 100, 420, 30}, GuiIconText(ICON_FILE_OPEN, "Открыть файл с исходником Brainfuck")))
            fileDialogState.windowActive = true;
        if (GuiButton((Rectangle){screenWidth / 2 - 190, 270, 380, 30}, "Запустить интерпретатор Brainfuck"))
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
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
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
        if (GuiButton((Rectangle){screenWidth / 2 - 20, screenHeight - 50, 40, 30}, "ОК"))
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
        int result = GuiMessageBox((Rectangle){screenWidth / 2 - 180, screenHeight / 2 - 50, 360, 100}, GuiIconText(ICON_EXIT, "Выход"), "Вы действительно хотите выйти?", "Да;Нет");
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
