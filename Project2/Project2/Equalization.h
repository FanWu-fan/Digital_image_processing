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
	void setImage(Mat &image_in);//����Ҫ�����ͼƬ
	void statistic();//��ԭͼ���о��⴦��
	Mat queProcess();
	~Equalization();

private:
	//����˽�б����ֱ�ͳ��channel 0, 1,2�ĻҶȼ������ظ���
	int statistic_R[256];
	int statistic_G[256];
	int statistic_B[256];
	//��Ҫ�����ͼ��
	Mat image;

};

