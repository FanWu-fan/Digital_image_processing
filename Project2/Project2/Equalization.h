#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include<cstring>
using namespace std;
using namespace cv;


class Equalization
{
public:
	Equalization();
	void setImage(Mat &image_in);//设置要处理的图片
	void statistic();//对原图进行均衡处理
	Mat queProcess();
	~Equalization();

private:
	//三个私有变量分别统计channel 0, 1,2的灰度级的像素个数
	int statistic_R[256];
	int statistic_G[256];
	int statistic_B[256];
	//将要处理的图像
	Mat image;

};

