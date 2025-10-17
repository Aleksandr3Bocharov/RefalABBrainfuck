@echo off

rem Copyright 2025 Aleksandr Bocharov
rem Distributed under the Boost Software License, Version 1.0.
rem See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
rem 2025-10-17
rem https://github.com/Aleksandr3Bocharov/refalabbrainfuck

set RAYLIB=F:\Programming\raylib-5.5_win64_mingw-w64
set RAYLIBCFLAGS=-Wall -O2 -I%RAYLIB%\include
set RAYLIBLFLAGS=-L%RAYLIB%\lib -lraylib -lgdi32 -lwinmm

if not exist bin mkdir bin
%REFALABBIN%\refalabc src\refalabbrainfuck_gui -a,"-o src\refalabbrainfuck_gui.o" > refalabbrainfuck_gui.log
as -o src\refalabbrainfuck_gui.o src\refalabbrainfuck_gui.s -a,"-o src\interpretator.o" >> refalabbrainfuck_gui.log
%REFALABBIN%\refalabc src\interpretator >> refalabbrainfuck_gui.log
as -o src\interpretator.o src\interpretator.s >> refalabbrainfuck_gui.log
clang %REFALABCFLAGS% -I%REFALABINCLUDE% -c src\interpretatorc.c -o src\interpretatorc.o >> refalabbrainfuck_gui.log
clang %REFALABCFLAGS% -I%REFALABINCLUDE% -c src\refalabbrainfuckc_gui.c -o src\refalabbrainfuckc_gui.o >> refalabbrainfuck_gui.log
clang %RAYLIBCFLAGS% -c src\gui.c -o src\gui.o >> refalabbrainfuck_gui.log
clang -o bin\refalabbrainfuck_gui.exe src\refalabbrainfuck_gui.o src\refalabbrainfuckc_gui.o src\interpretator.o src\interpretatorc.o %REFALABLIB%\obj\mainrf.o -L%REFALABLIB% -lrefalab src\gui.o %RAYLIBLFLAGS% >> refalabbrainfuck_gui.log
bin\refalabbrainfuck_gui
