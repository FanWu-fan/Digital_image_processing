#include <opencv2/opencv.hpp>
#include <iostream>
#include<Cstring>
using namespace cv;
using namespace std;


class Equalization
{
public:
	Equalization();
	void setImage(Mat &image);//����Ҫ�����ͼƬ
	void statistic();//��ͼ���RGBֵ����ֱ��ͼͳ��
	Mat euq_process();


	~Equalization();

private:
	int R_Num[256];
	int G_Num[256];
	int B_Num[256];

	Mat image;
};

Equalization::Equalization()
{
}

Equalization::~Equalization()
{
}

