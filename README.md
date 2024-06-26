# README

---

2024.5 数学建模大赛 ZJU

---

## Problem1

### AreaSplit.cpp

用于将一个凸多边形的搜索范围等面积划分为若干区域

#### 输入

1. 输入凸多边形顶点个数`nPoints`和划分区域个数`nAreas`
2. 输入无人机飞行速度`V`和搜索半径`d`
3. 输入`nPoints`个点的坐标，形式为`x y`

 
#### 输出

搜索用时`t`

#### 实现

首先对输入的一组点进行排序，使得点根据下标递增表现为凸多边形的逆时针点序列

之后对凸多边形进行分割，利用向量差积和最左下角点进行面积计算

根据总的无人机数量分割大面积为小块，每块区域面积相等，用于无人机搜索

忽略无人机搜索的细节，得出对这一大区域的总搜索时间

## Problem2-1

### <a id="Problem2.cpp">Problem2.cpp</a>

对问题2进行暴力搜索，寻找所有可能的解并通过比较得到最大值

#### 输入

输入速度、探测时间

输入`nPoints`个点，形式为`(x,y,w)`

#### 输出

返回总最大权重，返回最大权重对应路径

#### 实现

注意到这个问题可以划分为`N`个相同的子问题，`N`为无人机的数量

对于每个子问题，实际上就是给定目标点的坐标及其权重，从一个点出发寻找所有的可能路径使得总权重最大

整个问题其实就是规划`N`条路径，原理一致，只不过一个子问题实现时要把前面已经实现的路径中的点去掉，再对剩下没有被纳入路径的所有店进行同样的操作

采用暴力搜索遍历所有的可能路径，使用深度优先搜索策略，从起始点开始搜索，并逐步更新这条路上的权重和

搜索终止条件为时间超过给定的时间限制`maxTime`，此时停止递归并回溯

对于每一个节点，采用贪婪策略，比较它所有的相邻节点路径上的最大值，并选取最大值作为这个节点的下一步路径

起始点的选择可以是任意的，本部分程序设计采用的是直接从节点开始，因此对于每个子问题，需要考虑所有节点都作为起始点的情况的路径，并比较这些路径的最大权重和，相当于递归增加一层

> 如果起始点位置给定，其实相当于增加一个节点，从这个节点开始采用上述方法进行搜索，实现较为简单

### RandomData.py

用于生成随机测试数据

#### 输入

`n`个测试点

#### 输出

输出`n`个测试点的坐标和权重，形式为`(x, y, w)`

### formatPrint.py

将算法结果读取并绘制线路图

### test.sh

自动化测试脚本

#### 输入

根据提示词进行输入

#### 输出

生成随机测试点数据，将结果保存在`input.txt`中

利用随机测试点作为输入运行`Problem.cpp`，结果保存在`output.txt`中

利用运行结果绘制路径图，保存在`res.png`中

## Problem2-2

### 2.cpp

对输入的整个区域进行栅格化，后进行搜索最大权值路径

#### 输入

* `maxTime`最大时间
* `speed`无人机速度
* `r`搜索半径
* `nPoints`目标点个数
* `nPoints`个目标点参数，形式为`(x, y, w)`

#### 输出

最大权值和

#### 实现

[Problem2.cpp](#Problem2.cpp)的进阶版

由于Problem2.cpp没有考虑搜索半径的问题，因此在此例中加入搜索半径

对于整个区域采用栅格化方法将目标区域划分为若干区域，每个区域符合无人机的搜索半径`r`，使得无人机搜索符合题目要求

计算整个区域的最大横向跨度和纵向跨度，然后根据搜索半径`r`对区域划分为变成为`2r`的正方形栅格，并计算每个方格内包含的所有的目标点的权重和

然后就是类似于迷宫寻找出路的问题，对整个栅格化的区域进行**DFS**，记录并比较最大权重和的路径

> 栅格化的好处就是遍历更加方便，因为直接对节点遍历相当于对一个拥有很稠密的邻接矩阵的图进行遍历，每对点都是相邻的，遍历时间开销就会很大，而栅格化后更像迷宫，只需要对一个栅格的周围格子进行遍历即可

### path.cpp

打印所有的搜索路径

#### 输入

与`2.cpp`相同

#### 输出

与`2.cpp`相同

#### 细节

暴力搜索