#!/bin/bash

#cd ../../ || exit

echo -e "\n\e[34mTesting with asan\e[0m"
make -s asan_debug
make -s func_tests


echo -e "\n\e[34mTesting with msan\e[0m"
make -s msan_debug
make -s func_tests

echo -e "\n\e[34mTesting with ubsan\e[0m"
make -s msan_debug
make -s func_tests

make -s clean
echo -e "\n\e[34mTesting with valgrind\e[0m"
make -s debug
make -s valgrind

echo -e "\n\e[34mCoverage testing\e[0m"
make -s coverage

make -s clean
