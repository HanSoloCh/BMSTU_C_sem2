#!/bin/bash
# Флаг -v указывает на то, что нужно печатать дополнительную информацию
VERBOSE=false
LEAKS=false
# Обработка аргументов командной строки
while getopts "vl" opt; do
	case ${opt} in
  		v )
  			VERBOSE=true
  			shift $((OPTIND -1))
  	  		;;
  	  l )
  	    LEAKS=true
  	    shift $((OPTIND -1))
  	      ;;
  		\? )
  	  		exit 1
  	  		;;
  	esac
done

# Проверяем, что было передано ровно три аргумента
if [ $# -ne 2 ]; then
	if [ "$VERBOSE" == "true" ]; then
    		echo "Usage: $0 <expected_output_file> <file_args>"
  	fi
    exit 1
fi

expected_output_file="$1"
file_args="$2"

# Определяем путь к директории скрипта и к исполняемому файлу
script_dir=$(realpath "$(dirname "$0")")
app_path="$(realpath "$script_dir/../../app.exe")"

# Проверяем, существует ли файл эталонных выходных данных
if [ ! -f "$script_dir"/../data/"$expected_output_file" ]; then
  	if [ "$VERBOSE" == "true" ]; then
    		echo "Expected output file $expected_output_file not found"
  	fi
  	exit 1
fi

# Проверяем, существует ли файл аргуметов
if [ ! -f "$script_dir"/../data/"$file_args" ]; then
	if [ "$VERBOSE" == "true" ]; then
    		echo "Input file $file_args not found"
  	fi
  	exit 1
fi

args=$(cat "$(realpath "$script_dir"/../data/"$file_args")")

# Файл, в который будет произведена печать. В файлах args указан именно этот файл
actual_output_file="./out/program_output.txt"

# Временная переменная для хранения вывод valgrind
tmp_file=$(mktemp)

# Запускаем программу
if [ "$LEAKS" == true ]; then
  eval valgrind --leak-check=yes "$app_path $args" 2> "$tmp_file"

  # Ошибки, обнаруженные valgrind
  errors=$(grep -cE ".*ERROR SUMMARY: [1-9]" "$tmp_file")

  # Если были ошибки,то выводим все, что нам выдал valgrind
  if [ "$errors" -ne 0 ]; then
    cat "$tmp_file"
  fi
else
  eval "$app_path $args"
fi


# Сравниваем выход программы с эталонным выходом с помощью comparator.sh
if "$script_dir"/comparator.sh "$actual_output_file" "$script_dir"/../data/"$expected_output_file"; then
	if [ "$VERBOSE" == "true" ]; then
		echo "Test passed"
	fi
	exit 0
else
	if [ "$VERBOSE" == "true" ]; then
		echo "Test failed"
	fi
	exit 1
fi
