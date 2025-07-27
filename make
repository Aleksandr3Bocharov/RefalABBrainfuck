#!/bin/sh 

# Copyright 2025 Aleksandr Bocharov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
# 2025-07-27
# https://github.com/Aleksandr3Bocharov/RefalAB

mkdir -p bin
$REFALABBIN/RefalAB src/RefalABBrainfuck > RefalABBrainfuck.log
as -o src/RefalABBrainfuck.o src/RefalABBrainfuck.s >> RefalABBrainfuck.log
$REFALABBIN/RefalAB src/Interpretator >> RefalABBrainfuck.log
as -o src/Interpretator.o src/Interpretator.s >> RefalABBrainfuck.log
clang $REFALABCFLAGS -I$REFALABINCLUDE -c src/Interpretatorc.c -o src/Interpretatorc.o >> RefalABBrainfuck.log
clang -o bin/RefalABBrainfuck src/RefalABBrainfuck.o src/Interpretator.o src/Interpretatorc.o $REFALABLIB/mainrf.o -L$REFALABLIB -lRefalAB >> RefalABBrainfuck.log
bin/RefalABBrainfuck $1
