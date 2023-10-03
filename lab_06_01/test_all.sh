#!/bin/bash

if [[ $(realpath "$(dirname "$0")") != "$PWD" ]]; then
	echo "Please run script from its own direcory"
	exit 1
fi

error_file="$(mktemp)"
echo -e "\n\e[34mTesting with asan\e[0m"
./build_debug_asan.sh > "$error_file"

if [ -s "$error_file" ]; then
  echo -e "\e[31mBuild error\e[0m"
else
  ./func_tests/scripts/func_tests.sh
fi


echo -e "\n\e[34mTesting with msan\e[0m"
./build_debug_msan.sh > "$error_file"

if [ -s "$error_file" ]; then
  echo -e "\e[31mBuild error\e[0m"
else
  ./func_tests/scripts/func_tests.sh
fi

echo -e "\n\e[34mTesting with ubsan\e[0m"
./build_debug_ubsan.sh > "$error_file"

if [ -s "$error_file" ]; then
  echo -e "\e[31mBuild error\e[0m"
else
  ./func_tests/scripts/func_tests.sh
fi

echo -e "\n\e[34mCoverage testing\e[0m"
./collect_coverage.sh

./clean.sh
