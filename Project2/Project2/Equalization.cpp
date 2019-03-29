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
			else//如果是彩色图像
			{
				statistic_B[image.at<Vec3b>(i, j)[0]]++;
				statistic_G[image.at<Vec3b>(i, j)[1]]++;
				statistic_R[image.at<Vec3b>(i, j)[2]]++;

			}
		}
	}
}

Mat Equalization::queProcess()//对原图进行均衡处理
{
	/*计算原来的各个灰度值经过均衡以后应该变成多少
	temp数组下标代表原先图像的灰度值
	temp中存储的数是变换后各个灰度值对应的灰度值
	*/
	int temp_R[256], temp_G[256], temp_B[256];
	memset(temp_R, 0, 256 * sizeof(int));
	memset(temp_G, 0, 256 * sizeof(int));
	memset(temp_B, 0, 256 * sizeof(int));

	int sumR = 0, sumB = 0, sumG = 0;
	double const_num = (256.0-1.0) / (double)(image.cols*image.cols);
	for (int counter0 = 0; counter0 < 256; counter0++)
	{
		if (image.channels() == 1) 
		{
			sumR += statistic_R[counter0];
			temp_R[counter0] = (int)(const_num * sumR);
		}
		else
		{
			sumR += statistic_R[counter0];
			sumG += statistic_G[counter0];
			sumB += statistic_B[counter0];

			temp_R[counter0] = (int)(const_num * sumR);
			temp_G[counter0] = (int)(const_num * sumG);
			temp_B[counter0] = (int)(const_num * sumB);
		}
	}

	Mat imEqu;
	if (image.channels() == 1)
	{
		Mat imEqu1(image.rows, image.cols, CV_8UC1);//8位无符号的单通道---灰度图片
		imEqu1.copyTo(imEqu);
	}
	else
	{
		Mat imEqu1(image.rows, image.cols, CV_8UC3);//8位无符号的三通道---RGB彩色图像
		imEqu1.copyTo(imEqu);
	}

	for (int counter1 = 0; counter1 < this->image.rows; counter1++)
	{
		for (int counter2 = 0; counter2 < this->image.cols; counter2++)
		{
			if (this->image.channels() == 1)
			{
				imEqu.at<uchar>(counter1, counter2) = temp_R[image.at<uchar>(counter1, counter2)];
			}
			else
			{
				imEqu.at<Vec3b>(counter1, counter2)[0] = temp_R[image.at<Vec3b>(counter1, counter2)[0]];
				imEqu.at<Vec3b>(counter1, counter2)[1] = temp_G[image.at<Vec3b>(counter1, counter2)[1]];
				imEqu.at<Vec3b>(counter1, counter2)[2] = temp_B[image.at<Vec3b>(counter1, counter2)[2]];
			}
		}
	}

	return imEqu;
}


Equalization::~Equalization()
{
}
