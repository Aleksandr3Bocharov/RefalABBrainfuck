#!/bin/sh 

# Copyright 2025 Aleksandr Bocharov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
# 2025-04-20
# https://github.com/Aleksandr3Bocharov/RefalAB

$REFALABBIN/RefalAB RefalABBrainfuck > RefalABBrainfuck.log
as -o RefalABBrainfuck.o RefalABBrainfuck.s >> RefalABBrainfuck.log
$REFALABBIN/RefalAB Interpretator >> RefalABBrainfuck.log
as -o Interpretator.o Interpretator.s >> RefalABBrainfuck.log
clang $REFALABCFLAGS -I$REFALABINCLUDE -c Interpretatorc.c -o Interpretatorc.o >> RefalABBrainfuck.log
clang -o RefalABBrainfuck RefalABBrainfuck.o Interpretator.o Interpretatorc.o $REFALABLIB/mainrf.o -L$REFALABLIB -lRefalAB >> RefalABBrainfuck.log
./RefalABBrainfuck $1
