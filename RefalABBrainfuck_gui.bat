@echo off

rem Copyright 2025 Aleksandr Bocharov
rem Distributed under the Boost Software License, Version 1.0.
rem See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
rem 2025-02-20
rem https://github.com/Aleksandr3Bocharov/RefalAB

%REFALABBIN%\RefalAB RefalABBrainfuck_gui > RefalABBrainfuck_gui.log
as -o RefalABBrainfuck_gui.o RefalABBrainfuck_gui.asm >> RefalABBrainfuck_gui.log
clang %REFALABCFLAGS% -I%REFALABINCLUDE% `pkg-config --cflags gtk4` -c RefalABBrainfuckc_gui.c -o RefalABBrainfuckc_gui.o >> RefalABBrainfuck_gui.log
clang -o RefalABBrainfuck_gui.exe RefalABBrainfuck_gui.o RefalABBrainfuckc_gui.o %REFALABLIB%\mainrf.o -L%REFALABLIB% -lRefalAB `pkg-config --libs gtk4` >> RefalABBrainfuck_gui.log
RefalABBrainfuck_gui
