// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-03-25
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "RefalABBrainfuckc" (GUI версия)
//====================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "refalab.h"
#include "gui.h"

extern uint8_t refalab_true, refalab_false;

static char fileName[255] = {'\0'};
static char *errors = NULL;

// <Put_Char S(N)C> ==
static void put_char_(void)
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

// <GUI_Init> ==
static void gui_init_(void)
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
char gui_init_0[] = {Z0 'G', 'U', 'I', '_', 'I', 'N', 'I', 'T', (char)8};
G_L_B uint8_t refalab_gui_init = '\122';
void (*gui_init_1)(void) = gui_init_;

// <GUI_Close> ==
static void gui_close_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    guiClose();
    return;
}
char gui_close_0[] = {Z1 'G', 'U', 'I', '_', 'C', 'L', 'O', 'S', 'E', (char)9};
G_L_B uint8_t refalab_gui_close = '\122';
void (*gui_close_1)(void) = gui_close_;

// <Dialog_FileName> == E(O)F
static void dialog_filename_(void)
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
char doalog_filename_0[] = {Z7 'D', 'I', 'A', 'L', 'O', 'G', '_', 'F', 'I', 'L', 'E', 'N', 'A', 'M', 'E', (char)15};
G_L_B uint8_t refalab_dialog_filename = '\122';
void (*dialog_filename_1)(void) = dialog_filename_;

// <View_Errors_Clear> ==
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
char errclear_0[] = {Z0 'E', 'R', 'R', 'C', 'L', 'E', 'A', 'R', '\010'};
G_L_B uint8_t refalab_errclear = '\122';
void (*errclear_1)(void) = errclear_;

// <View_Errors_Add E(O)E> ==
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

// <View_Errors_Show> == /True/ | /False/
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

// <Dialog_Is_Exit> == /True/ | /False/
static void dialog_is_exit_(void)
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
char dialog_is_exit_0[] = {Z6 'D', 'I', 'A', 'L', 'O', 'G', '_', 'I', 'S', '_', 'E', 'X', 'I', 'T', (char)14};
G_L_B uint8_t refalab_dialog_is_exit = '\122';
void (*dialog_is_exit_1)(void) = dialog_is_exit_;
