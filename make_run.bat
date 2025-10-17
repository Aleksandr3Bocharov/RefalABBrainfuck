@echo off

rem Copyright 2025 Aleksandr Bocharov
rem Distributed under the Boost Software License, Version 1.0.
rem See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
rem 2025-10-17
rem https://github.com/Aleksandr3Bocharov/refalabbrainfuck

if not exist bin mkdir bin
%REFALABBIN%\refalabc src\refalabbrainfuck -a,"-o src\refalabbrainfuck.o" > refalabbrainfuck.log
%REFALABBIN%\refalabc src\interpretator -a,"-o src\interpretator.o" >> refalabbrainfuck.log
clang %REFALABCFLAGS% -I%REFALABINCLUDE% -c src\interpretatorc.c -o src\interpretatorc.o >> refalabbrainfuck.log
clang -o bin\refalabbrainfuck.exe src\refalabbrainfuck.o src\interpretator.o src\interpretatorc.o %REFALABLIB%\obj\mainrf.o -L%REFALABLIB% -lrefalab >> refalabbrainfuck.log
bin\refalabbrainfuck %1
