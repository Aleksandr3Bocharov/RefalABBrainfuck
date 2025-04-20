@echo off

rem Copyright 2025 Aleksandr Bocharov
rem Distributed under the Boost Software License, Version 1.0.
rem See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
rem 2025-04-20
rem https://github.com/Aleksandr3Bocharov/RefalAB

set RAYLIB=F:\Programming\raylib-5.5_win64_mingw-w64
set RAYLIBCFLAGS=-Wall -O2 -I%RAYLIB%\include
set RAYLIBLFLAGS=-L%RAYLIB%\lib -lraylib -lgdi32 -lwinmm

%REFALABBIN%\RefalAB RefalABBrainfuck_gui > RefalABBrainfuck_gui.log
as -o RefalABBrainfuck_gui.o RefalABBrainfuck_gui.s >> RefalABBrainfuck_gui.log
%REFALABBIN%\RefalAB Interpretator >> RefalABBrainfuck_gui.log
as -o Interpretator.o Interpretator.s >> RefalABBrainfuck_gui.log
clang %REFALABCFLAGS% -I%REFALABINCLUDE% -c Interpretatorc.c -o Interpretatorc.o >> RefalABBrainfuck_gui.log
clang %REFALABCFLAGS% -I%REFALABINCLUDE% -c RefalABBrainfuckc_gui.c -o RefalABBrainfuckc_gui.o >> RefalABBrainfuck_gui.log
clang %RAYLIBCFLAGS% -c gui.c -o gui.o >> RefalABBrainfuck_gui.log
clang -o RefalABBrainfuck_gui.exe RefalABBrainfuck_gui.o RefalABBrainfuckc_gui.o Interpretator.o Interpretatorc.o %REFALABLIB%\mainrf.o -L%REFALABLIB% -lRefalAB gui.o %RAYLIBLFLAGS% >> RefalABBrainfuck_gui.log
RefalABBrainfuck_gui
