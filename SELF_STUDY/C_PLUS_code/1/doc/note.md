# Mat的作用

Mat类表示一个多维的单通道或者多通道的稠密数组

## Mat的常见属性

* **data**: uchar型的指针，Mat类分为两个部分：矩阵头和指向矩阵数据部分的指针，data就是指向矩阵数据的指针。

* **dims**: 矩阵的维度，比如 5\*6矩阵是2维，则 dims=2，三维矩阵dims=3

* **rows**: 矩阵的行数

* **cols**: 矩阵的列数

* **size**: 矩阵的大小，size(cols,rows),如果矩阵的维数大于2，那么size(-1,-1)

* **channels**: 矩阵元素拥有的通道数，例如常见的彩色图像，每个像素由RGBz组成，则 channels=3

* **type**: 表示了矩阵中元素的类型以及矩阵的通道个数，它是一系列 **预定义的常量**，命名规则为： CV_(位数) + (数据类型) + (通道数)。

CV_8UC1:8位无符号整数，通道为1....CV_32FC4:32位浮点数，通道4
**type**是创建Mat对象时设定，如果要取得Mat元素类型，使用 **depth**

* **depth**: 将type的预定义值去掉通道信息就是 depth的值。
CV_8U CV_8S

* **elemSize**: 矩阵一个元素占用的字节数，例如：type是 CV_16SC3: elemSize = 3*16 /8=6 bytes

* **elemSize1**: 矩阵元素一个通道占用的字节数，例如：type是CV_16CS3,那么 elemSize1 = 16/8=2 bytes = elemSize/channels