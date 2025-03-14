#!/bin/sh 

# Copyright 2024 Aleksandr Bocharov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
# 2024-10-23
# https://github.com/Aleksandr3Bocharov/RefalAB

$REFALABBIN/RefalAB RefalABBrainfuck > RefalABBrainfuck.log
as -o RefalABBrainfuck.o RefalABBrainfuck.s >> RefalABBrainfuck.log
clang $REFALABCFLAGS -I$REFALABINCLUDE -c RefalABBrainfuckc.c -o RefalABBrainfuckc.o >> RefalABBrainfuck.log
clang -o RefalABBrainfuck RefalABBrainfuck.o RefalABBrainfuckc.o $REFALABLIB/mainrf.o -L$REFALABLIB -lRefalAB >> RefalABBrainfuck.log
./RefalABBrainfuck
