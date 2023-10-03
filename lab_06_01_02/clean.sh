#!/bin/bash

# Временные файлы, подлежащие удалению

if [[ $(realpath "$(dirname "$0")") != "$PWD" ]]; then
	echo "Please run script from its own direcory"
else
	rm_files="*.exe *.o *.out *.gcno *.gcda *.gcov ./func_tests/scripts/*.txt"

	for file in $rm_files; do
		rm -f "$file"
	done
fi
