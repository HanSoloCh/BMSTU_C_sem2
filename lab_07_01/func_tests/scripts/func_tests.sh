#!/bin/bash

LEAKS=false
# Обработка флага -l для включения проверки на утечки памяти leaks
while getopts "l" opt; do
	case ${opt} in
  	  l )
  	    LEAKS=true
  	    shift $((OPTIND -1))
  	      ;;
  		\? )
  	  		exit 1
  	  		;;
  	esac
done

# Получаем директорию, где находится скрипт
script_dir=$(realpath "$(dirname "$0")")

# Проверяем, существует ли файл app.exe
if [ ! -f "$script_dir/../../app.exe" ]; then
	echo -e "\e[31mNo app.exe file\e[0m"
	exit 100
fi

# Получаем список путей к файлам с тестовыми входными данными для позитивных тестов
mapfile -t pos_tests_in < <(find "$script_dir"/../data \
-type f -name "pos_*_in.txt" | sort)

# Получаем список путей к файлам с тестовыми входными данными для негативных тестов
mapfile -t neg_tests_in < <(find "$script_dir"/../data \
-type f -name "neg_*_in.txt" | sort)

# Инициализируем переменную для хранения кода возврата скрипта
code_return=0

echo -e "\nPositive tests"
# Проверяем, есть ли позитивные тесты
if [ -z "${pos_tests_in[0]}" ]; then
	echo -e "\e[33mNo positive tests\e[0m"
else
	# Проходим по списку путей к входным данным для позитивных тестов
	for test_in in "${pos_tests_in[@]}"; do
		num=$(echo "$test_in" | grep -oE '[^/]*$' | grep -oE '[0-9]+')

		# Получаем путь к файлу с ожидаемыми выходными данными для данного теста
		mapfile -t test_out < <(find "$script_dir"/../data \
	-type f -name "pos_${num}_out.txt" -print0 | xargs -0)

		# Получаем путь к файлу с аргументами для данного теста
	  mapfile -t test_args < <(find "$script_dir"/../data \
    	-type f -name "pos_${num}_args.txt" -print0 | xargs -0)

		# Если эталонных выходных данных нет, значит тест провален
		if [ -z "${test_out[0]}" ] || [ -z "${test_args[0]}" ]; then
			echo -e "Test ${num}: \e[31mno out or args file(s)\e[0m"
			code_return=$((code_return + 1))
		else
			# Вызываем скрипт для запуска позитивного теста c valgrind или без
			if [ "$LEAKS" == "true" ]; then
			  "$script_dir"/pos_case.sh -l "$(basename "$test_out")" "$(basename "$test_args")"
			else
			  "$script_dir"/pos_case.sh "$(basename "$test_out")" "$(basename "$test_args")"
      fi

			exit_code=$?
			# Проверяем код возврата
			if [ "$exit_code" -eq 0 ]; then
				echo -e "Test ${num}: \e[32mpassed\e[0m"
			else
				echo -e "Test ${num}: \e[31mfailed\e[0m"
				code_return=$((code_return + 1))
			fi
		fi
	done
fi

echo -e "\nNegative tests"
# Проверяем, есть ли негативные тесты
if [ -z "${neg_tests_in[0]}" ]; then
	echo -e "\e[33mNo negative tests\e[0m"
else
	# Проходим по списку путей к входным данным для негативных тестов
	for test_in in "${neg_tests_in[@]}"; do
		num=$(echo "$test_in" | grep -oE '[^/]*$' | grep -oE '[0-9]+')
		# Получаем путь к файлу с аргументами для данного теста
    mapfile -t test_args < <(find "$script_dir"/../data \
      -type f -name "neg_${num}_args.txt" -print0 | xargs -0)

    if [ -z "${test_args[0]}" ]; then
      echo -e "Test ${num}: \e[31mno args file\e[0m"
      code_return=$((code_return + 1))

    else
      # Вызываем скрипт для запуска негативного теста с valgrind или без него
      if [ "$LEAKS" == "true" ]; then
        "$script_dir"/neg_case.sh -l "$(basename "$test_args")"
      else
        "$script_dir"/neg_case.sh "$(basename "$test_args")"
      fi
      exit_code=$?
      # Проверяем код возврата
      if [ "$exit_code" -eq 0 ]; then
        echo -e "Test ${num}: \e[32mpassed\e[0m"
      else
        echo -e "Test ${num}: \e[31mfailed\e[0m"
        code_return=$((code_return + 1 ))
      fi
    fi
	done
fi

# Проверка были ли вообще тесты
if [[ -n "$neg_tests_in" && -n "$pos_tests_in" ]]; then
	# Считаем процент прохождения тестов
	total_tests=$(( ${#pos_tests_in[@]} + ${#neg_tests_in[@]} ))
	passed_tests=$(( total_tests - code_return ))
	per=$(( passed_tests * 100 / total_tests ))
	echo -e "\nTest passing percentage is \e[32m${per}%\e[0m"
fi
exit $code_return
