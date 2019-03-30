#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include<cstring>

using namespace std;
using namespace cv;

#define LEVEL 256//灰度级别


class Equalization
{
public:

	Equalization();
	void setImage(Mat &image_in);//设置要处理的图片
	void statistic();//对图片的RGB值进行直方图统计
	Mat  queProcess();//对原图进行均衡处理
	Mat returnHistogram();//返回归一化后的直方图
	~Equalization();

private:
	//三个私有变量分别统计channel 0, 1,2的灰度级的像素个数
	int statistic_R[LEVEL];
	int statistic_G[LEVEL];
	int statistic_B[LEVEL];
	//将要处理的图像
	Mat image;

};

