// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-10-07
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "Interpretatorc"
//====================================================================

#include <stdio.h>
#include <stdint.h>
#include "refalab.h"

// <Put_Char S(N).Char> ==
static void put_char_(void)
{
    const T_LINKCB *p = refal.preva->next;
    if (p->next != refal.nexta || p->tag != TAGN)
    {
        refal.upshot = 2;
        return;
    }
    if (putchar((int)gcoden(p)) == EOF)
        if (feof(stdout) != 0 || ferror(stdout) != 0)
            rfabe("put_char: error");
    fflush(stdout);
    printf("\n%d\n", MAX_PATHFILENAME);
    return;
}
char put_char_0[] = {Z0 'P', 'U', 'T', '_', 'C', 'H', 'A', 'R', (char)8};
G_L_B uint8_t refalab_put_char = '\122';
void (*put_char_1)(void) = put_char_;

// <Get_Char> == S(0..255).Char
static void get_char_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    T_LINKCB *p = refal.preva;
    const int c = getchar();
    p->tag = TAGN;
    p->info.codep = NULL;
    if (c != EOF)
        pcoden(p, (uint8_t)c);
    else
        clearerr(stdin);
    rftpl(refal.prevr, refal.nextr, refal.nexta);
    return;
}
char get_char_0[] = {Z0 'G', 'E', 'T', '_', 'C', 'H', 'A', 'R', (char)8};
G_L_B uint8_t refalab_get_char = '\122';
void (*get_char_1)(void) = get_char_;
