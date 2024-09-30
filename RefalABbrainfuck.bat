SET REFAL=F:\Programming\Projects\RefalAB

%REFAL%\bin\RefalAB RefalABBrainfuck > RefalABBrainfuck.log
as -o RefalABBrainfuck.o RefalABBrainfuck.asm >> RefalABBrainfuck.log
gcc -o RefalABBrainfuck.exe %REFAL%\lib\mainrf.o RefalABBrainfuck.o -Wl,-L%REFAL%\lib -Wl,-lRefalAB >> RefalABBrainfuck.log
RefalABBrainfuck

