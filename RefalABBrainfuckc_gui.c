// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-02-27
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "RefalABBrainfuckc" (GUI версия)
//====================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "refal.def"
#include "gui.h"

static char fileName[254] = {'\0'};
static char *errors = NULL;

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

// <Init> ==
static void init_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    guiInit();
    return;
}
char init_0[] = {Z4 'I', 'N', 'I', 'T', '\004'};
G_L_B uint8_t init = '\122';
void (*init_1)(void) = init_;

// <Close> ==
static void close_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    guiClose();
    return;
}
char close_0[] = {Z5 'C', 'L', 'O', 'S', 'E', '\005'};
G_L_B uint8_t close = '\122';
void (*close_1)(void) = close_;

// <FileName> == E(O)F
static void filename_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    if (guiFileName(fileName))
    {
        T_LINKCB *p = refal.prevr;
        if (!slins(p, strlen(fileName)))
            return;
        for (size_t i = 0; fileName[i] != '\0'; i++)
        {
            p = p->next;
            p->tag = TAGO;
            p->info.codep = NULL;
            p->info.infoc = fileName[i];
        }
    }
    return;
}
char filename_0[] = {Z8 'F', 'I', 'L', 'E', 'N', 'A', 'M', 'E', '\010'};
G_L_B uint8_t filename = '\122';
void (*filename_1)(void) = filename_;

// <ErrClear> ==
static void errclear_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    free(errors);
    errors = NULL;
    guiErrClear();
    return;
}
char errclear_0[] = {Z8 'E', 'R', 'R', 'C', 'L', 'E', 'A', 'R', '\010'};
G_L_B uint8_t errclear = '\122';
void (*errclear_1)(void) = errclear_;

// <ErrView> ==
static void errview_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    guiErrView(errors);
    return;
}
char errors_0[] = {Z7 'E', 'R', 'R', 'V', 'I', 'E', 'W', '\007'};
G_L_B uint8_t errview = '\122';
void (*errview_1)(void) = errview_;

// <IsExit> == 'Y' | 'N'
static void isexit_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    T_LINKCB *p = refal.prevr;
    if (!slins(p, 1))
        return;
    p = p->next;
    p->tag = TAGO;
    p->info.codep = NULL;
    p->info.infoc = 'Y';
    if (!guiIsExit())
        p->info.infoc = 'N';
    return;
}
char isexit_0[] = {Z6 'I', 'S', 'E', 'X', 'I', 'T', '\006'};
G_L_B uint8_t isexit = '\122';
void (*isexit_1)(void) = isexit_;
