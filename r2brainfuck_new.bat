SET REFAL=F:\Programming\projects\refal2_new

%REFAL%\bin\refal2 r2brainfuck > r2brainfuck.log
as -o r2brainfuck.o r2brainfuck.asm >> r2brainfuck.log
%REFAL%\bin\refal2 r2libext > r2libext.log
as -o r2libext.o r2libext.asm >> r2libext.log
gcc -o r2brainfuck.exe %REFAL%\lib\mainrf.o r2libext.o r2brainfuck.o -Wl,-L%REFAL%\lib -Wl,-lr2 >> r2brainfuck.log
r2brainfuck

