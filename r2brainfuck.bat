SET REFAL=D:\Programming\refal2

%REFAL%\bin\refal2 r2brainfuck > r2brainfuck.log
as -o r2brainfuck.o r2brainfuck.asm >> r2brainfuck.log
gcc -std=c89 -pipe -Wall -O2 -c r2brainfuckc.c -o r2brainfuckc.o -I%REFAL%\include
gcc -o r2brainfuck.exe %REFAL%\lib\r2objects\mainrf.o %REFAL%\lib\r2libext\r2libext.o r2brainfuck.o r2brainfuckc.o -Wl,-L%REFAL%\lib -Wl,-lrefal2,-lr2user >> r2brainfuck.log
r2brainfuck

