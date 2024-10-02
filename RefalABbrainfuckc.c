// Copyright 2024 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2024-10-02
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "RefalABBrainfuckc"
//====================================================================

#include <stdio.h>
#include "refal.def"

// <PutCh S(N)C> ==
static void putch_(void)
{
    const T_LINKCB *p = refal.preva->next;
    if (p->tag == TAGN && p->next == refal.nexta)
    {
        putchar((int)gcoden(p));
        fflush(stdout);
    }
    else
        refal.upshot = 2;
    return;
}
void (*putch_1)(void) = putch_;
G_L_B char putch = '\122';
char putch_0[] = {Z5 'P', 'U', 'T', 'C', 'H', '\005'};

// <GetCh> == S(/0/../255/)C
static void getch_(void)
{
    if (refal.preva->next != refal.nexta)
        refal.upshot = 2;
    T_LINKCB *p = refal.prevr;
    const int c = getchar();
    if (slins(p, 1) == 0)
        return;
    p = p->next;
    p->tag = TAGN;
    if (c != EOF)
        pcoden(p, (uint8_t)c);
    return;
}
void (*getch_1)(void) = getch_;
G_L_B char getch = '\122';
char getch_0[] = {Z5 'G', 'E', 'T', 'C', 'H', '\005'};
