#include "Equalization.h"



HistogramEqualization::HistogramEqualization()//初始化各个私有成员。
{
	memset(statistic_R, 0, LEVEL * sizeof(int));
	memset(statistic_G, 0, LEVEL * sizeof(int));
	memset(statistic_B, 0, LEVEL * sizeof(int));

}

void HistogramEqualization::setImage(Mat & image_in)//设置要处理的图片的路径
{
	image = image_in;
}

void HistogramEqualization::statistic()//分别对图片的RGB值进行直方图统计
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

Mat HistogramEqualization::equProcess()//对原图进行均衡处理
{
	/*计算原来的各个灰度值经过均衡以后应该变成多少
	temp数组下标代表原先图像的灰度值
	temp中存储的数是变换后各个灰度值对应的灰度值
	*/
	int temp_R[LEVEL], temp_G[LEVEL], temp_B[LEVEL];
	memset(temp_R, 0, LEVEL * sizeof(int));
	memset(temp_G, 0, LEVEL * sizeof(int));
	memset(temp_B, 0, LEVEL * sizeof(int));

	int sumR = 0, sumB = 0, sumG = 0;
	double const_num = (double)(LEVEL -1.0) / (double)(image.cols*image.rows);
	for (int counter0 = 0; counter0 < LEVEL; counter0++)
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

			temp_R[counter0] = (int)(const_num * sumR );
			temp_G[counter0] = (int)(const_num * sumG );
			temp_B[counter0] = (int)(const_num * sumB );
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

	for (int counter1 = 0; counter1 < image.rows; counter1++)
	{
		for (int counter2 = 0; counter2 < image.cols; counter2++)
		{
			if (image.channels() == 1)
			{
				imEqu.at<uchar>(counter1, counter2) = temp_R[image.at<uchar>(counter1, counter2)];
			}
			else
			{
				imEqu.at<Vec3b>(counter1, counter2)[0] = temp_B[image.at<Vec3b>(counter1, counter2)[0]];
				imEqu.at<Vec3b>(counter1, counter2)[1] = temp_G[image.at<Vec3b>(counter1, counter2)[1]];
				imEqu.at<Vec3b>(counter1, counter2)[2] = temp_R[image.at<Vec3b>(counter1, counter2)[2]];
			}
		}
	}

	return imEqu;
}

Mat HistogramEqualization::returnHistogram()
{
	double temp_R[LEVEL];//归一化后的概率
	double max=statistic_R[0];
	memset(temp_R, 0, LEVEL * sizeof(double));
	Mat dstImage = Mat::zeros(Size(LEVEL, LEVEL), CV_8UC1);//绘制直方图,首先先创建一个黑底的图像，为了可以显示彩色，所以该绘制图像是一个8位的3通道图像
	
	for (int i = 0; i < LEVEL; i++)//计算最大值
	{
		if (statistic_R[i] >= max)
			max = statistic_R[i];
	}
	max = (double)max / (double)(image.cols*image.rows);

	for (int i = 0; i < LEVEL; i++)
	{
		temp_R[i] = (double)statistic_R[i] / (double)(image.cols*image.rows);
		temp_R[i] = temp_R[i] * (double)LEVEL*0.9 / max;//将最大值显示在0.9的位置，其他按照比例计算

		rectangle(dstImage, Point(i, LEVEL-1), Point(i, LEVEL-temp_R[i]), Scalar(255));//注意这里point（x，y)是(cols,rows),和 .at正好相反
	}
	
	return dstImage;
}


HistogramEqualization::~HistogramEqualization()
{
}
