/* 
// Copyright 2024 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt
// 2024-10-02
// https://github.com/Aleksandr3Bocharov/r2brainfuck

//====================================================================
// Модуль "r2brainfuckc"
//====================================================================
*/

#include <stdio.h>
#include <string.h>
#include "refal.def"

extern REFAL refal;

/* <PutCh S(N)C> == */
static void putch_()
{
    /* const */
    linkcb *p = refal.preva->next;
    if (p->tag == TAGN && p->next == refal.nexta)
    {
        int c = putchar(gcoden(p));
        if (c == EOF)
            rfabe("putchar: EOF");
    }
    else
        refal.upshot = 2;
    return;
}
void (*putch_1)() = putch_;
G_L_B char putch = '\122';
char putch_0[] = {Z5 'P', 'U', 'T', 'C', 'H', '\005'};

/* <GetCh> == S(/0/../255/)C */
static void getch_()
{
    if (refal.preva->next != refal.nexta)
        refal.upshot = 2;
    linkcb *p = refal.prevr;
    int c = getchar();
    if (slins(p, 1) == 0)
        return;
    p = p->next;
    p->tag = TAGN;
    if (c != EOF)
        pcoden(p, (unsigned char)c);
    return;
}
void (*getch_1)() = getch_;
G_L_B char getch = '\122';
char getch_0[] = {Z5 'G', 'E', 'T', 'C', 'H', '\005'};
