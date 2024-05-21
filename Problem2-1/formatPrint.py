#!/usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt

prompt = input()
n = int(input())
points = []

for i in range(n):
    x, y, w = map(float, input().split())
    points.append((x, y, w))

prompt = input()
n = int(input())
path = []
for i in range(n):
    x, y, w = map(float, input().split())
    path.append((x, y, w))
prompt = input()
weight = float(input())

plt.scatter([i[0] for i in points], [i[1] for i in points])
for i in points:
    plt.text(i[0], i[1], "{:.2f}".format(i[2]), fontsize=10, ha='center')
plt.plot([i[0] for i in path], [i[1] for i in path], label='Path with Max Weight = {:.2f}'.format(weight))
plt.legend()
plt.tight_layout()
plt.savefig('res/res.png')