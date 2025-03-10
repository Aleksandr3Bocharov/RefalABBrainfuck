// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-03-10
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

extern uint8_t refalab_true, refalab_false;

static char fileName[255] = {'\0'};
static char *errors = NULL;

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
    else
        clearerr(stdin);
    return;
}
char getchar_0[] = {Z7 'G', 'E', 'T', 'C', 'H', 'A', 'R', '\007'};
G_L_B uint8_t refalab_getchar = '\122';
void (*getchar_1)(void) = getchar_;

// <GInit> ==
static void ginit_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    fileName[254] = '\0';
    guiInit();
    return;
}
char ginit_0[] = {Z5 'G', 'I', 'N', 'I', 'T', '\005'};
G_L_B uint8_t refalab_ginit = '\122';
void (*ginit_1)(void) = ginit_;

// <GClose> ==
static void gclose_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    guiClose();
    return;
}
char gclose_0[] = {Z6 'G', 'C', 'L', 'O', 'S', 'E', '\006'};
G_L_B uint8_t refalab_gclose = '\122';
void (*gclose_1)(void) = gclose_;

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
G_L_B uint8_t refalab_filename = '\122';
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
G_L_B uint8_t refalab_errclear = '\122';
void (*errclear_1)(void) = errclear_;

// <ErrAdd E(O)E> ==
static void erradd_(void)
{
    char error[256];
    const T_LINKCB *p = refal.preva->next;
    do
    {
        bool neot = false;
        size_t i;
        for (i = 0; p != refal.nexta; i++)
        {
            if (p->tag != TAGO || i == 255)
            {
                neot = true;
                break;
            }
            error[i] = p->info.infoc;
            p = p->next;
        }
        if (neot)
            break;
        error[i] = '\0';
        if (errors == NULL)
        {
            errors = (char *)malloc((strlen(error) + 1) * NMBL);
            if (errors == NULL)
                rfabe("erradd: error");
            strcpy(errors, error);
        }
        else
        {
            errors = (char *)realloc(errors, (strlen(errors) + strlen(error) + 2) * NMBL);
            if (errors == NULL)
                rfabe("erradd: error");
            strcat(strcat(errors, ";"), error);
        }
        return;
    } while (false);
    refal.upshot = 2;
    return;
}
char erradd_0[] = {Z6 'E', 'R', 'R', 'A', 'D', 'D', '\006'};
G_L_B uint8_t refalab_erradd = '\122';
void (*erradd_1)(void) = erradd_;

// <ErrView> == /True/ | /False/
static void errview_(void)
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
    p->tag = TAGF;
    p->info.codep = NULL;
    p->info.codef = &refalab_true;
    if (!guiErrView(errors))
        p->info.codef = &refalab_false;
    return;
}
char errors_0[] = {Z7 'E', 'R', 'R', 'V', 'I', 'E', 'W', '\007'};
G_L_B uint8_t refalab_errview = '\122';
void (*errview_1)(void) = errview_;

// <IsExit> == /True/ | /False/
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
    p->tag = TAGF;
    p->info.codep = NULL;
    p->info.codef = &refalab_true;
    if (!guiIsExit())
        p->info.codef = &refalab_false;
    return;
}
char isexit_0[] = {Z6 'I', 'S', 'E', 'X', 'I', 'T', '\006'};
G_L_B uint8_t refalab_isexit = '\122';
void (*isexit_1)(void) = isexit_;
