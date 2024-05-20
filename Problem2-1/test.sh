#!/usr/bin/fish

# This script is used to test the program.
rm exe
rm Points.png
rm *.txt
g++ Problem2.cpp -o exe -g
read -P "Input n: " n
read -P "Input speed: " speed
read -P "Input time: " time
echo $speed $time $n > input.txt
echo $n > tmp.txt
python3 RandomData.py <tmp.txt >> input.txt
rm tmp.txt
./exe < input.txt > output.txt