SET REFAL=F:\Programming\refal2
SET CC=F:\Programming\mingw32\bin

%REFAL%\bin\refal2 r2brainfuck > r2brainfuck.log
%CC%\as -o r2brainfuck.o r2brainfuck.asm >> r2brainfuck.log
%CC%\gcc -o r2brainfuck.exe %REFAL%\lib\r2objects\mainrf.o %REFAL%\lib\r2libext\r2libext.o r2brainfuck.o -Wl,-L%REFAL%\lib -Wl,-lrefal2,-lr2user >> test.log
r2brainfuck

