#!/usr/bin/python3
import random
import numpy as np
import matplotlib.pyplot as plt

n = int(input())
Point = [(random.randint(0, n), random.randint(0, n), random.random()) for i in range(n)]
plt.scatter([i[0] for i in Point], [i[1] for i in Point])
for i in Point:
    plt.text(i[0], i[1], "{:.2f}".format(i[2]), fontsize=10, ha='center')
plt.tight_layout()
plt.savefig('Points.png')
for i in Point:
    print(i[0], i[1], i[2])