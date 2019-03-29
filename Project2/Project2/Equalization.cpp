#include "Equalization.h"



Equalization::Equalization()//初始化各个私有成员。
{
	memset(statistic_R, 0, 256 * sizeof(int));
	memset(statistic_G, 0, 256 * sizeof(int));
	memset(statistic_B, 0, 256 * sizeof(int));

}

void Equalization::setImage(Mat & image_in)//设置要处理的图片的路径
{
	image = image_in;
}

void Equalization::statistic()//分别对图片的RGB值进行直方图统计
{
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			//数组下标代表灰度值，里面存储的数是该灰度值对应的像素数
			if (image.channels() == 1)//如果是灰度图像
			{
				statistic_R[image.at<uchar>(i, j)]++;
			}
		}
	}
}

Mat Equalization::queProcess()
{
	return Mat();
}


Equalization::~Equalization()
{
}
