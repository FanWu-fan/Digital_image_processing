#include "Spatial_Filtering.h"
#include<opencv2/opencv.hpp>

int main()
{
	//读入灰度图
	Mat image = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 0);
	imshow("source_image", image);

	Spafilt spt;

	//-----------------------------[1] 实验3 --------------------------------
	//利用均值模板平滑灰度图像
	// 3*3 均值模板
	float filter3[9];
	for (int counter = 0; counter < 9; counter++)
		filter3[counter] = (float)1 / 9;
	imshow("linearFilter-3", spt.linearFilter(image, filter3, 3));

	// 5*5 均值模板
	float filter5[25];
	for (int counter = 0; counter < 25; counter++)
		filter5[counter] = (float)1 / 25;
	imshow("linearFilter-5", spt.linearFilter(image, filter5, 5));

	//9*9 均值模板
	float filter9[81];
	for (int counter = 0; counter < 81; counter++)
		filter9[counter] = (float)1 / 81;
	imshow("linearFilter-9", spt.linearFilter(image, filter9, 9));

	//使用高斯滤波模板平滑图像
	//3*3 高斯模板

	imshow("GasssionFilter3", spt.GasssionFilter(image, 3, 1.5));

	//5*5 高斯模板
	imshow("GasssionFilter5", spt.GasssionFilter(image, 5, 1.5));

	//9*9 高斯模板
	imshow("GasssionFilter9", spt.GasssionFilter(image, 9, 1.5));

	//Roberts交叉算子
	imshow("Roberts", spt.roberts(image));

	//prewitt算子
	imshow("Prewitt", spt.prewitt(image));

	//Sobel算子
	imshow("Sobel", spt.sobel(image));

	//Laplacian锐化处理
	imshow("Laplacian", spt.laplacian(image, 3));

	//高提升滤波
	imshow("highBoost", spt.highBoostFilter(image, 1));

	//利用均值模板平滑彩色图像




	////中值滤波器
	//Mat image_noise = spt.addSaltAndPepperNoise(image, 0.2);
	//imshow("beforeMedaiFiltering", image_noise);
	//imshow("afterMedaiFiltering", spt.medianFilter(image_noise, 3));

	////最大值滤波器
	//imshow("maxFilter", spt.maxFilter(image, 3));

	////最小值滤波器
	//imshow("mixFilter", spt.minFilter(image, 3));

	////基本高通滤波器
	//float highFilter[9] = { 1,  1, 1,  1, -8, 1, 1, 1, 1 };
	//imshow("BasicHighPassFilter", spt.basicHighPassFilter(image, highFilter, 3));




	waitKey(0);
	return 0;
}