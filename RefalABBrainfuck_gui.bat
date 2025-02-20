@echo off

rem Copyright 2025 Aleksandr Bocharov
rem Distributed under the Boost Software License, Version 1.0.
rem See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
rem 2025-02-20
rem https://github.com/Aleksandr3Bocharov/RefalAB

set GTK4=D:/Programming/GTK4
set GTK4CFLAGS=-I%GTK4%/include/gtk-4.0 -I%GTK4%/include/pango-1.0 -I%GTK4%/include/fribidi -I%GTK4%/include/harfbuzz -I%GTK4%/include/gdk-pixbuf-2.0 -I%GTK4%/include/cairo -I%GTK4%/include/freetype2 -I%GTK4%/include/libpng16 -I%GTK4%/include/pixman-1 -I%GTK4%/include/graphene-1.0 -I%GTK4%/lib/graphene-1.0/include -I%GTK4%/include -I%GTK4%/include/glib-2.0 -I%GTK4%/lib/glib-2.0/include
set GTK4LFLAGS=-L%GTK4%/lib -lgtk-4 -lpangocairo-1.0 -lpangowin32-1.0 -lpango-1.0 -lharfbuzz -lgdk_pixbuf-2.0 -lcairo-gobject -lcairo -lgraphene-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl

%REFALABBIN%\RefalAB RefalABBrainfuck_gui > RefalABBrainfuck_gui.log
as -o RefalABBrainfuck_gui.o RefalABBrainfuck_gui.asm >> RefalABBrainfuck_gui.log
clang %REFALABCFLAGS% -I%REFALABINCLUDE% %GTK4CFLAGS% -c RefalABBrainfuckc_gui.c -o RefalABBrainfuckc_gui.o >> RefalABBrainfuck_gui.log
clang -o RefalABBrainfuck_gui.exe RefalABBrainfuck_gui.o RefalABBrainfuckc_gui.o %REFALABLIB%\mainrf.o -L%REFALABLIB% -lRefalAB %GTK4LFLAGS% >> RefalABBrainfuck_gui.log
RefalABBrainfuck_gui
