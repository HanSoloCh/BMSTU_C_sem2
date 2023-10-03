#!/bin/bash

# Проверяем, запущен ли скрипт из его собственной директории
if [[ $(realpath "$(dirname "$0")") != "$PWD" ]]; then
	echo "Please run script from its own direcory"
else
	clang -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -Wpedantic -Wvla \
-fsanitize=address -fno-omit-frame-pointer -O0 -c -g3 ./*.c
	clang -o app.exe ./*.o -fsanitize=address -lm
fi



