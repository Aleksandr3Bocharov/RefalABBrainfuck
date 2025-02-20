// Copyright 2025 Aleksandr Bocharov
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
// 2025-02-20
// https://github.com/Aleksandr3Bocharov/RefalABBrainfuck

//====================================================================
// Модуль "RefalABBrainfuckc" (GUI GTK4 версия)
//====================================================================

#include <gtk\gtk.h>
#include <stdio.h>
#include <stdint.h>
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

// <GTKInit> ==
static void gtkinit_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    gtk_init();
    return;
}
char gtkinit_0[] = {Z7 'G', 'T', 'K', 'I', 'N', 'I', 'T', '\007'};
G_L_B uint8_t gtkinit = '\122';
void (*gtkinit_1)(void) = gtkinit_;

static void response_open_file_dialog(GObject *gobject, GAsyncResult *result, gpointer open_file_name)
{
    g_autoptr(GError) error = NULL;
    g_autoptr(GFile) open_file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(gobject), result, &error);
    if (error == NULL)
        open_file_name = (gpointer)g_file_get_path(open_file);
}

// <ODialog> == E(O)F
static void odialog_(void)
{
    if (refal.preva->next != refal.nexta)
    {
        refal.upshot = 2;
        return;
    }
    GtkFileDialog *open_file_dialog = gtk_file_dialog_new();
    gtk_file_dialog_set_title(open_file_dialog, "Открыть файл");
    gpointer open_file_name = NULL;
    gtk_file_dialog_open(open_file_dialog, NULL, NULL, response_open_file_dialog, open_file_name);
    if (open_file_name != NULL)
    {
        // r05_alloc_string(filename);
    }
    return;
}
char odialog_0[] = {Z7 'O', 'D', 'I', 'A', 'L', 'O', 'G', '\007'};
G_L_B uint8_t odialog = '\122';
void (*odialog_1)(void) = odialog_;
