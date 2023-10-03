#!/bin/bash

# Проверяем, что скрипт запущен из его собственной директории
if [[ $(realpath "$(dirname "$0")") != "$PWD" ]]; then
	echo "Please run script from its own direcory"
else
	gcc -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -Wpedantic -Wvla -c -O0 -g3 --coverage ./*.c
  gcc -o app.exe ./*.o --coverage -lm
fi
