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
