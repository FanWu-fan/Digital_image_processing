#include "Equalization.h"



Equalization::Equalization()//��ʼ������˽�г�Ա��
{
	memset(statistic_R, 0, 256 * sizeof(int));
	memset(statistic_G, 0, 256 * sizeof(int));
	memset(statistic_B, 0, 256 * sizeof(int));

}

void Equalization::setImage(Mat & image_in)//����Ҫ�����ͼƬ��·��
{
	image = image_in;
}

void Equalization::statistic()//�ֱ��ͼƬ��RGBֵ����ֱ��ͼͳ��
{
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			//�����±����Ҷ�ֵ������洢�����ǸûҶ�ֵ��Ӧ��������
			if (image.channels() == 1)//����ǻҶ�ͼ��
			{
				statistic_R[image.at<uchar>(i, j)]++;
			}
			else//����ǲ�ɫͼ��
			{
				statistic_B[image.at<Vec3b>(i, j)[0]]++;
				statistic_G[image.at<Vec3b>(i, j)[1]]++;
				statistic_R[image.at<Vec3b>(i, j)[2]]++;

			}
		}
	}
}

Mat Equalization::queProcess()//��ԭͼ���о��⴦��
{
	/*����ԭ���ĸ����Ҷ�ֵ���������Ժ�Ӧ�ñ�ɶ���
	temp�����±����ԭ��ͼ��ĻҶ�ֵ
	temp�д洢�����Ǳ任������Ҷ�ֵ��Ӧ�ĻҶ�ֵ
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
		Mat imEqu1(image.rows, image.cols, CV_8UC1);//8λ�޷��ŵĵ�ͨ��---�Ҷ�ͼƬ
		imEqu1.copyTo(imEqu);
	}
	else
	{
		Mat imEqu1(image.rows, image.cols, CV_8UC3);//8λ�޷��ŵ���ͨ��---RGB��ɫͼ��
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
