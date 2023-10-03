#!/bin/bash
#
#if [[ $(realpath "$(dirname "$0")") != "$PWD" ]]; then
#	echo "Please run script from its own direcory"
#	exit 1
#fi
#
#cd ../.. || exit
#
## Удаление предыдущего файла .gcda
#./clean.sh
#
## Компилируем программу
#./build_debug.sh
#
## Запуск функциональных тестов
#./func_tests/scripts/func_tests.sh

echo -e "\n"

# Проверяем покрытие кода для каждого файла

for file in ./src/*.c; do
  name="$(basename "$file")"
  gcov "$name" -o ./out -t > ./out/"$name.gcov"
  coverage=$(gcov "$name" -o ./out -n | tail -1 | sed "s/.*://g" | sed "s/%.*//g")
  echo -e "\e[35mThe lines coverage for $name is ${coverage}%\e[0m"
done
echo -e "\n"

