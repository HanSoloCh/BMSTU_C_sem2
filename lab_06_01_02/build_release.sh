#!/bin/bash
# Проверяем, запущен ли скрипт из его собственной директории
if [[ $(realpath "$(dirname "$0")") != "$PWD" ]]; then
	echo "Please run script from its own direcory"
else
	gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion \
	-Wvla -c -O3 ./*.c
	gcc ./*.o -o app.exe -lm
fi
