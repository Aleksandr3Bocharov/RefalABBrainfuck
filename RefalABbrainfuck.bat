@echo off

rem Copyright 2024 Aleksandr Bocharov
rem Distributed under the Boost Software License, Version 1.0.
rem See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
rem 2024-10-20
rem https://github.com/Aleksandr3Bocharov/RefalAB

SET REFAL=F:\Programming\Projects\RefalAB

%REFAL%\bin\RefalAB RefalABBrainfuck > RefalABBrainfuck.log
as -o RefalABBrainfuck.o RefalABBrainfuck.asm >> RefalABBrainfuck.log
clang -pipe -Wall -O2 -I%REFAL%\include -c RefalABBrainfuckc.c -o RefalABBrainfuckc.o >> RefalABBrainfuck.log
clang -o RefalABBrainfuck.exe %REFAL%\lib\mainrf.o RefalABBrainfuck.o RefalABBrainfuckc.o -Wl,-L%REFAL%\lib -Wl,-lRefalAB >> RefalABBrainfuck.log
RefalABBrainfuck

