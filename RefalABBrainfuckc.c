// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-03-10
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "RefalABBrainfuckc"
//====================================================================

#include <stdio.h>
#include <stdint.h>
#include "refal.def"

// <PutChar S(N)C> ==
static void putchar_(void)
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
char putchar_0[] = {Z7 'P', 'U', 'T', 'C', 'H', 'A', 'R', '\007'};
G_L_B uint8_t refalab_putchar = '\122';
void (*putchar_1)(void) = putchar_;

// <GetChar> == S(/0/../255/)C
static void getchar_(void)
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
char getchar_0[] = {Z7 'G', 'E', 'T', 'C', 'H', 'A', 'R', '\007'};
G_L_B uint8_t refalab_getchar = '\122';
void (*getchar_1)(void) = getchar_;
