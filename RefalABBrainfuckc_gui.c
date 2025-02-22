// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-02-23
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "RefalABBrainfuckc" (GUI raygui raylib версия)
//====================================================================

#include <stdio.h>
#include <stdint.h>
#include "raylib.h"
#include "refal.def"

// <PutCh S(N)C> ==
static void putch_(void)
{
    const T_LINKCB *p = refal.preva->next;
    if (p->next != refal.nexta || p->tag != TAGN)
    {
        refal.upshot = 2;
        return;
    }
    putchar((int)gcoden(p));
    fflush(stdout);
    return;
}
char putch_0[] = {Z5 'P', 'U', 'T', 'C', 'H', '\005'};
G_L_B uint8_t putch = '\122';
void (*putch_1)(void) = putch_;

// <GetCh> == S(/0/../255/)C
static void getch_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    T_LINKCB *p = refal.prevr;
    if (!slins(p, 1))
        return;
    const int c = getchar();
    p = p->next;
    p->tag = TAGN;
    p->info.codep = NULL;
    if (c != EOF)
        pcoden(p, (uint8_t)c);
    return;
}
char getch_0[] = {Z5 'G', 'E', 'T', 'C', 'H', '\005'};
G_L_B uint8_t getch = '\122';
void (*getch_1)(void) = getch_;

// <RayGUI> ==
static void raygui_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    InitWindow(800, 450, "raylib [core] example - basic window");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return;
}
char raygui_0[] = {Z6 'R', 'A', 'Y', 'G', 'U', 'I', '\006'};
G_L_B uint8_t raygui = '\122';
void (*raygui_1)(void) = raygui_;
