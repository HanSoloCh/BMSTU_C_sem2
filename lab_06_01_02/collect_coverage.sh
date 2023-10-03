#!/bin/bash

if [[ $(realpath "$(dirname "$0")") != "$PWD" ]]; then
	echo "Please run script from its own direcory"
	exit 1
fi

# Удаление предыдущего файла .gcda
rm -f ./*.gcda

# Компилируем программу
./build_debug.sh

# Запуск функциональных тестов
./func_tests/scripts/func_tests.sh

echo -e "\n"

# Проверяем покрытие кода для каждого файла
for file in *.c; do
  coverage=$(gcov "$file" | tail -1 | sed "s/.*://g" | sed "s/%.*//g")
  echo -e "\e[35mThe lines coverage for $file is ${coverage}%\e[0m"
done
echo -e "\n"

