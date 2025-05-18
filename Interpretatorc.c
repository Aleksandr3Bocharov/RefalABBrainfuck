// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-05-17
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "Interpretatorc"
//====================================================================

#include <stdio.h>
#include <stdint.h>
#include "refalab.h"

// <Put_Char S(N)C> ==
static void put_char_(void)
{
    const T_LINKCB *p = refal.preva->next;
    if (p->next != refal.nexta || p->tag != TAGN)
    {
        refal.upshot = 2;
        return;
    }
    if (putchar((int)gcoden(p)) == EOF)
        rfabe("put_char: error");
    fflush(stdout);
    return;
}
char put_char_0[] = {Z0 'P', 'U', 'T', '_', 'C', 'H', 'A', 'R', (char)8};
G_L_B uint8_t refalab_put_char = '\122';
void (*put_char_1)(void) = put_char_;

// <Get_Char> == S(/0/../255/)C
static void get_char_(void)
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
    else
        clearerr(stdin);
    return;
}
char get_char_0[] = {Z0 'G', 'E', 'T', '_', 'C', 'H', 'A', 'R', (char)8};
G_L_B uint8_t refalab_get_char = '\122';
void (*get_char_1)(void) = get_char_;
