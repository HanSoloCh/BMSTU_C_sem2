#!/bin/bash

# Режим verbose
VERBOSE=false

# Режим проверки утечек (проверки с valgrind)
LEAKS=false

# Обработка флагов
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

# Проверяем, что количество аргументов равно 1
if [ $# -ne 1 ]; then
	if [ "$VERBOSE" == "true" ]; then
		echo "Usage: $0 <file_args>"
	fi
	exit 1
fi

file_args="$1"

# Определяем путь к директории скрипта и к исполняемому файлу
script_dir=$(realpath "$(dirname "$0")")
app_path="$(realpath "$script_dir/../../app.exe")"

# Проверяем, существует ли файл аргументов
if [ ! -f "$script_dir"/../data/"$file_args" ]; then
	if [ "$VERBOSE" == "true" ]; then
    		echo "Input file $file_args not found"
  	fi
  	exit 1
fi

args=$(cat "$(realpath "$script_dir"/../data/"$file_args")")

# Временная переменная для хранения вывод valgrind
tmp_file=$(mktemp)

# Запускаем программу
if [ "$LEAKS" == true ]; then
  eval valgrind --leak-check=yes "$app_path $args" 2> "$tmp_file"
  code_return=$?
  # Ошибки, обнаруженные valgrind
  errors=$(grep -cE ".*ERROR SUMMARY: [1-9]" "$tmp_file")
  # Если были ошибки,то выводим все, что нам выдал valgrind
  if [ "$errors" -ne 0 ]; then
    cat "$tmp_file"
  fi
else
  eval "$app_path $args"
  code_return=$?
fi


# Обрабатываем код возврата
if [ "$code_return" -eq 0 ]; then
	if [ "$VERBOSE" == "true" ]; then
		echo "Test failed"
	fi
	exit 1
	
else
	if [ "$VERBOSE" == "true" ]; then
		echo "Test passed"
	fi
	exit 0	
fi
