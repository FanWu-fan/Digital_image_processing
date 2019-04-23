#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include<cstring>

using namespace std;
using namespace cv;

#define LEVEL 256//�Ҷȼ���


class HistogramEqualization
{
public:

	HistogramEqualization();
	void setImage(Mat &image_in);//����Ҫ������ͼƬ
	void statistic();//��ͼƬ��RGBֵ����ֱ��ͼͳ��
	Mat  equProcess();//��ԭͼ���о��⴦��
	Mat returnHistogram();//���ع�һ�����ֱ��ͼ
	~HistogramEqualization();

private:
	//����˽�б����ֱ�ͳ��channel 0, 1,2�ĻҶȼ������ظ���
	int statistic_R[LEVEL];
	int statistic_G[LEVEL];
	int statistic_B[LEVEL];
	//��Ҫ������ͼ��
	Mat image;

};
