/*
Canny算子是目前找到的一个最优的边缘检测算子。主要通过以下4个步骤：

step1：用高斯滤波器平滑图象；
	边缘检测的算法主要是基于图像强度的一阶和二阶导数，但导数通常对噪声很敏感，因此必须采用滤波器来改善与噪声有关的边缘检测器的性能。
	常见的滤波方法主要有高斯滤波。

step2：用一阶偏导的有限差分来计算梯度的幅值和方向；
	增强边缘的基础是确定图像各点领域强度的变化值。增强算法可以将图像灰度点领域强度值有显著变化的点凸显出来，在具体编程实践中，通过计算
	梯度的幅值来确定。

step3：对梯度幅值进行非极大值抑制；
	仅仅得到全局的梯度并不足以确定边缘，因此为确定边缘，必须保留局部梯度最大的点，而抑制非极大值。（non-maxima suppression,NMS）
	在每一点上，邻域的中心象素M与沿着梯度线的两个象素相比。 如果M的梯度值不比沿梯度线的两个相邻象素梯度值大，则令M=0。

step4：用双阈值算法检测和连接边缘
	对非极大值抑制图像作用两个阈值th1和th2，两者关系th1=0.4th2  。我们把梯度值小于th1的像素的灰度值设为0，得到图像1。
	然后把梯度值小于th2的像素的灰度值设为0，得到图像2。由于图像2的阈值较高，去除大部分噪音，但同时也损失了有用的边缘信息。
	而图像1的阈值较低，保留了较多的信息，我们可以以图像2为基础，以图像1为补充来连结图像的边缘。
*/
#include<iostream>
#include<cstdlib>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("G:\\Code\\Digital_image_processing\\images\\6.jpg",1);
	Mat src1 = src.clone();

	// 显示原图
	imshow("【效果图】Canny边缘检测", src);
	Mat dst, edge, gray;

	// 【1】创建与src同类型和大小的矩阵(dst)
	dst.create(src1.size(), src1.type());
	
	// 【2】将原图转换为灰度图像
	cvtColor(src1, gray, COLOR_BGR2GRAY);

	// 【3】先用3×3的内核来降噪
	blur(gray, edge, Size(3, 3));

	// 【4】运行Canny算子，使用的是 Sobel 算子
	Canny(edge, edge, 3, 9, 3);

	// 【5】将dst内的所有元素都置为0
	dst = Scalar::all(0);

	// 【6】使用Canny算子输出的边缘图edge作为掩码，来讲原图src1拷贝到目标图dst中
	src1.copyTo(dst, edge);

	// 【7】显示效果图
	imshow("【效果图】Canny边缘检测2", dst);

	waitKey(0);

	system("pause");
	return 0;
}