#!/bin/sh 

# Copyright 2025 Aleksandr Bocharov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
# 2025-04-20
# https://github.com/Aleksandr3Bocharov/RefalAB

RAYLIBCFLAGS="-Wall -O2"
RAYLIBLFLAGS="-lraylib -lm"

$REFALABBIN/RefalAB RefalABBrainfuck_gui > RefalABBrainfuck_gui.log
as -o RefalABBrainfuck_gui.o RefalABBrainfuck_gui.s >> RefalABBrainfuck_gui.log
$REFALABBIN/RefalAB Interpretator >> RefalABBrainfuck_gui.log
as -o Interpretator.o Interpretator.s >> RefalABBrainfuck_gui.log
clang $REFALABCFLAGS -I$REFALABINCLUDE -c Interpretatorc.c -o Interpretatorc.o >> RefalABBrainfuck_gui.log
clang $REFALABCFLAGS -I$REFALABINCLUDE -c RefalABBrainfuckc_gui.c -o RefalABBrainfuckc_gui.o >> RefalABBrainfuck_gui.log
clang $RAYLIBCFLAGS -c gui.c -o gui.o >> RefalABBrainfuck_gui.log
clang -o RefalABBrainfuck_gui RefalABBrainfuck_gui.o RefalABBrainfuckc_gui.o Interpretator.o Interpretatorc.o $REFALABLIB/mainrf.o -L$REFALABLIB -lRefalAB gui.o $RAYLIBLFLAGS >> RefalABBrainfuck_gui.log
./RefalABBrainfuck_gui
