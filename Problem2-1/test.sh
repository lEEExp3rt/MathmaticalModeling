#!/usr/bin/fish

# This script is used to test the program.
rm -f exe
rm -f res/*
g++ Problem2.cpp -o exe -g
read -P "Input n: " n
read -P "Input speed: " speed
read -P "Input time: " time
echo $speed $time $n > res/input.txt
echo $n > tmp.txt
python3 RandomData.py < tmp.txt >> res/input.txt
rm tmp.txt
./exe < res/input.txt > res/output.txt
python3 formatPrint.py < res/output.txt