@echo off

rem Copyright 2025 Aleksandr Bocharov
rem Distributed under the Boost Software License, Version 1.0.
rem See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
rem 2025-10-07
rem https://github.com/Aleksandr3Bocharov/RefalAB

if not exist bin mkdir bin
%REFALABBIN%\RefalAB src\RefalABBrainfuck > RefalABBrainfuck.log
as -o src\RefalABBrainfuck.o src\RefalABBrainfuck.s >> RefalABBrainfuck.log
%REFALABBIN%\RefalAB src\Interpretator >> RefalABBrainfuck.log
as -o src\Interpretator.o src\Interpretator.s >> RefalABBrainfuck.log
clang %REFALABCFLAGS% -I%REFALABINCLUDE% -c src\Interpretatorc.c -o src\Interpretatorc.o >> RefalABBrainfuck.log
clang -o bin\RefalABBrainfuck.exe src\RefalABBrainfuck.o src\Interpretator.o src\Interpretatorc.o %REFALABLIB%\obj\mainrf.o -L%REFALABLIB% -lRefalAB >> RefalABBrainfuck.log
bin\RefalABBrainfuck %1
