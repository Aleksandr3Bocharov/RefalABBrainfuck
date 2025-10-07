// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-10-07
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "RefalABBrainfuckc" (GUI версия)
//====================================================================

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "refalab.h"
#include "gui.h"

extern uint8_t refalab_true, refalab_false;

static char fileName[257] = {'\0'};
static T_FILE_STATUS file_Status = OK;
static char open_Error[256] = {'\0'};
static char *errors = NULL;

// <GUI_Init> ==
static void gui_init_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    fileName[256] = '\0';
    gui_Init();
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
    gui_Close();
    return;
}
char gui_close_0[] = {Z1 'G', 'U', 'I', '_', 'C', 'L', 'O', 'S', 'E', (char)9};
G_L_B uint8_t refalab_gui_close = '\122';
void (*gui_close_1)(void) = gui_close_;

// <Dialog_FileName> == E(O).FileName
static void dialog_filename_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    if (dialog_FileName(fileName, open_Error, &file_Status))
        if (slins(refal.nextr, strlen(fileName) - 1))
        {
            rfrstr(fileName, refal.nextr);
            rftpl(refal.prevr, refal.nextr, refal.nexta);
        }
    return;
}
char dialog_filename_0[] = {Z7 'D', 'I', 'A', 'L', 'O', 'G', '_', 'F', 'I', 'L', 'E', 'N', 'A', 'M', 'E', (char)15};
G_L_B uint8_t refalab_dialog_filename = '\122';
void (*dialog_filename_1)(void) = dialog_filename_;

// <Dialog_File_Not_Exist> ==
static void dialog_file_not_exist_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    file_Status = NOT_EXIST;
    return;
}
char dialog_file_not_exist_0[] = {Z5 'D', 'I', 'A', 'L', 'O', 'G', '_', 'F', 'I', 'L', 'E', '_', 'N', 'O', 'T', '_', 'E', 'X', 'I', 'S', 'T', (char)21};
G_L_B uint8_t refalab_dialog_file_not_exist = '\122';
void (*dialog_file_not_exist_1)(void) = dialog_file_not_exist_;

// <Dialog_File_Not_Open V(O).Open_Error> ==
static void dialog_file_not_open_(void)
{
    T_LINKCB *p = refal.preva->next;
    p = rfgstr(open_Error, 255, p);
    if (p != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    file_Status = NOT_OPEN;
    return;
}
char dialog_file_not_open_0[] = {Z4 'D', 'I', 'A', 'L', 'O', 'G', '_', 'F', 'I', 'L', 'E', '_', 'N', 'O', 'T', '_', 'O', 'P', 'E', 'N', (char)20};
G_L_B uint8_t refalab_dialog_file_not_open = '\122';
void (*dialog_file_not_open_1)(void) = dialog_file_not_open_;

// <View_Errors_Clear> ==
static void view_errors_clear_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    free(errors);
    errors = NULL;
    view_Errors_Clear();
    return;
}
char view_errors_clear_0[] = {Z1 'V', 'I', 'E', 'W', '_', 'E', 'R', 'R', 'O', 'R', 'S', '_', 'C', 'L', 'E', 'A', 'R', (char)17};
G_L_B uint8_t refalab_view_errors_clear = '\122';
void (*view_errors_clear_1)(void) = view_errors_clear_;

// <View_Errors_Add V(O).Error> ==
static void view_errors_add_(void)
{
    T_LINKCB *p = refal.preva->next;
    char error[256];
    p = rfgstr(error, 255, p);
    if (p != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    if (errors == NULL)
    {
        errors = (char *)malloc((strlen(error) + 1) * NMBL);
        if (errors == NULL)
            rfabe("view_errors_add: error");
        strcpy(errors, error);
    }
    else
    {
        errors = (char *)realloc(errors, (strlen(errors) + strlen(error) + 2) * NMBL);
        if (errors == NULL)
            rfabe("view_errors_add: error");
        strcat(strcat(errors, ";"), error);
    }
    return;
}
char view_errors_add_0[] = {Z7 'V', 'I', 'E', 'W', '_', 'E', 'R', 'R', 'O', 'R', 'S', '_', 'A', 'D', 'D', (char)15};
G_L_B uint8_t refalab_view_errors_add = '\122';
void (*view_errors_add_1)(void) = view_errors_add_;

// <View_Errors_Show> == &True | &False
static void view_errors_show_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    if (view_Errors_Show(errors))
        refal.preva->info.codef = &refalab_true;
    else
        refal.preva->info.codef = &refalab_false;
    rftpl(refal.prevr, refal.nextr, refal.nexta);
    return;
}
char eview_errors_show_0[] = {Z0 'V', 'I', 'E', 'W', '_', 'E', 'R', 'R', 'O', 'R', 'S', '_', 'S', 'H', 'O', 'W', (char)16};
G_L_B uint8_t refalab_view_errors_show = '\122';
void (*view_errors_show_1)(void) = view_errors_show_;

// <Dialog_Is_Exit> == &True | &False
static void dialog_is_exit_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    if (dialog_Is_Exit())
        refal.preva->info.codef = &refalab_true;
    else
        refal.preva->info.codef = &refalab_false;
    rftpl(refal.prevr, refal.nextr, refal.nexta);
    return;
}
char dialog_is_exit_0[] = {Z6 'D', 'I', 'A', 'L', 'O', 'G', '_', 'I', 'S', '_', 'E', 'X', 'I', 'T', (char)14};
G_L_B uint8_t refalab_dialog_is_exit = '\122';
void (*dialog_is_exit_1)(void) = dialog_is_exit_;
