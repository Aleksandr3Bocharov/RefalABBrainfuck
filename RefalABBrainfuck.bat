@echo off

rem Copyright 2024 Aleksandr Bocharov
rem Distributed under the Boost Software License, Version 1.0.
rem See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
rem 2024-10-22
rem https://github.com/Aleksandr3Bocharov/RefalAB

%REFALABBIN%\RefalAB RefalABBrainfuck > RefalABBrainfuck.log
as -o RefalABBrainfuck.o RefalABBrainfuck.asm >> RefalABBrainfuck.log
clang %REFALABCFLAGS% -I%REFALABINCLUDE% -c RefalABBrainfuckc.c -o RefalABBrainfuckc.o >> RefalABBrainfuck.log
clang -o RefalABBrainfuck.exe %REFALABLIB%\mainrf.o RefalABBrainfuck.o RefalABBrainfuckc.o -L%REFALABLIB% -lRefalAB >> RefalABBrainfuck.log
RefalABBrainfuck
