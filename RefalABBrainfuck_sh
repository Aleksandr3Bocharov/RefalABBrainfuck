#!/bin/sh 

# Copyright 2024 Aleksandr Bocharov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
# 2024-10-22
# https://github.com/Aleksandr3Bocharov/RefalAB

REFAL=/media/alexb/F/Programming/Projects/RefalAB

$REFAL/bin/RefalAB RefalABBrainfuck > RefalABBrainfuck.log
as -o RefalABBrainfuck.o RefalABBrainfuck.asm >> RefalABBrainfuck.log
clang -pipe -Wall -O2 -I$REFAL/include -c RefalABBrainfuckc.c -o RefalABBrainfuckc.o >> RefalABBrainfuck.log
clang -o RefalABBrainfuck $REFAL/lib/mainrf.o RefalABBrainfuck.o RefalABBrainfuckc.o -L$REFAL/lib -lRefalAB >> RefalABBrainfuck.log
./RefalABBrainfuck
