// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-04-09
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "gui" (GUI raygui raylib версия)
//====================================================================

#include <string.h>
#include <stdbool.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui/raygui.h"
#undef RAYGUI_IMPLEMENTATION

#define GUI_WINDOW_FILE_DIALOG_IMPLEMENTATION
#include "raygui/gui_window_file_dialog.h"

#include "gui.h"

static const int screenWidth = 1024;
static const int screenHeight = 360;

static int errorsViewScrollIndex = 0;

static Font cyrillicFont;

static GuiWindowFileDialogState fileDialogState;

static void set_Style(void)
{
    GuiSetFont(cyrillicFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(LISTVIEW, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
}

void gui_Init(void)
{
    InitWindow(screenWidth, screenHeight, "Интерпретатор языка программирования Brainfuck на РефалАБ");
    SetExitKey(0);
    cyrillicFont = LoadFont("fonts/dejavu.fnt");
    fileDialogState = InitGuiWindowFileDialog(GetWorkingDirectory());
    SetTargetFPS(60);
    set_Style();
}

void gui_Close(void)
{
    CloseWindow();
}

bool dialog_FileName(char *fileName)
{
    bool ok = false;
    bool exitWindow = false;
    const float sizeCyrillicFont = (float)cyrillicFont.baseSize + 1.0f;
    while (!exitWindow)
    {
        exitWindow = WindowShouldClose();
        if (fileDialogState.SelectFilePressed)
        {
            if (fileDialogState.fileNameText[0] != '\0')
                strncpy(fileName, TextFormat("%s" PATH_SEPERATOR "%s", fileDialogState.dirPathText, fileDialogState.fileNameText), 254);
            fileDialogState.SelectFilePressed = false;
        }
        const bool cntrl_o = IsKeyPressed(KEY_O) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL));
        const bool can_open = cntrl_o && !fileDialogState.windowActive;
        const bool cntrl_r = IsKeyPressed(KEY_R) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL));
        const bool can_run = cntrl_r && !fileDialogState.windowActive;
        const bool enter = IsKeyPressed(KEY_ENTER);
        const bool can_select = enter && fileDialogState.windowActive;
        const bool escape = IsKeyPressed(KEY_ESCAPE);
        const bool can_cancel = escape && fileDialogState.windowActive;
        BeginDrawing();
        ClearBackground(GetColor((unsigned int)GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        DrawTextEx(cyrillicFont, "Программа ''RefalABBrainfuck'' интерпретирует код", (Vector2){10.0f, 20.0f}, sizeCyrillicFont, 1.0f, DARKGRAY);
        DrawTextEx(cyrillicFont, "на  языке программирования Brainfuck из исходного файла.", (Vector2){10.0f, 60.0f}, sizeCyrillicFont, 1.0f, DARKGRAY);
        DrawTextEx(cyrillicFont, "Открытие файла с исходником", (Vector2){10.0f, 150.0f}, sizeCyrillicFont, 1.0f, DARKGRAY);
        DrawTextEx(cyrillicFont, TextFormat("''%s''", fileName), (Vector2){10.0f, 190.0f}, sizeCyrillicFont, 1.0f, GRAY);
        DrawTextEx(cyrillicFont, "с кодом на языке программирования Brainfuck.", (Vector2){10.0f, 230.0f}, sizeCyrillicFont, 1.0f, DARKGRAY);
        DrawTextEx(cyrillicFont, "Запуск интерпретатора кода на языке программирования Brainfuck.", (Vector2){10.0f, 320.0f}, sizeCyrillicFont, 1.0f, DARKGRAY);
        if (fileDialogState.windowActive)
            GuiLock();
        if (GuiButton((Rectangle){screenWidth / 2 - 250, 100, 500, 30}, GuiIconText(ICON_FILE_OPEN, "Открыть файл с исходником Brainfuck (Cntrl+O)")) || can_open)
            fileDialogState.windowActive = true;
        if (GuiButton((Rectangle){screenWidth / 2 - 230, 270, 460, 30}, "Запустить интерпретатор Brainfuck (Cntrl+R)") || can_run)
            if (*fileName != '\0')
            {
                ok = true;
                exitWindow = true;
            }
        GuiUnlock();
        GuiSetFont(GetFontDefault());
        GuiLoadStyleDefault();
        if (can_select)
        {
            fileDialogState.SelectFilePressed = true;
            fileDialogState.windowActive = false;
        }
        if (can_cancel)
            fileDialogState.windowActive = false;
        GuiWindowFileDialog(&fileDialogState);
        set_Style();
        EndDrawing();
    }
    return ok;
}

void view_Errors_Clear(void)
{
    errorsViewScrollIndex = 0;
}

bool view_Errors_Show(const char *errors)
{
    bool exitWindow = false;
    bool ok = false;
    while (!exitWindow)
    {
        exitWindow = WindowShouldClose();
        const bool enter = IsKeyPressed(KEY_ENTER);
        if (IsKeyPressed(KEY_DOWN))
            errorsViewScrollIndex++;
        if (IsKeyPressed(KEY_UP))
            errorsViewScrollIndex--;
        BeginDrawing();
        ClearBackground(GetColor((unsigned int)GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        GuiListView((Rectangle){10, 20, screenWidth - 20, screenHeight - 90}, errors, &errorsViewScrollIndex, NULL);
        if (GuiButton((Rectangle){screenWidth / 2 - 20, screenHeight - 50, 40, 30}, "ОК") || enter)
        {
            ok = true;
            exitWindow = true;
        }
        EndDrawing();
    }
    return ok;
}

bool dialog_Is_Exit(void)
{
    bool isExit = true;
    bool exitWindow = false;
    while (!exitWindow)
    {
        exitWindow = WindowShouldClose();
        const bool enter = IsKeyPressed(KEY_ENTER);
        const bool escape = IsKeyPressed(KEY_ESCAPE);
        BeginDrawing();
        ClearBackground(GetColor((unsigned int)GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(RAYWHITE, 0.8f));
        int result = GuiMessageBox((Rectangle){screenWidth / 2 - 180, screenHeight / 2 - 50, 360, 100}, GuiIconText(ICON_EXIT, "Выход"), "Вы действительно хотите выйти?", "Да;Нет");
        if (result == 0 || result == 1 || result == 2 || enter || escape)
        {
            exitWindow = true;
            if (result == 0 || result == 2 || escape)
                isExit = false;
        }
        EndDrawing();
    }
    return isExit;
}
