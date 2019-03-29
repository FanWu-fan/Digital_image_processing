#include <opencv2/opencv.hpp>
#include <iostream>
#include<Cstring>
using namespace cv;
using namespace std;


class Equalization
{
public:
	Equalization();
	void setImage(Mat &image);//设置要处理的图片
	void statistic();//对图像的RGB值进行直方图统计
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

