#!/usr/bin/python3
import random

n = int(input())
Point = [(random.randint(0, n), random.randint(0, n), random.random()) for i in range(n)]
for i in Point:
    print(i[0], i[1], i[2])