#include "Equalization.h"



HistogramEqualization::HistogramEqualization()//��ʼ������˽�г�Ա��
{
	memset(statistic_R, 0, LEVEL * sizeof(int));
	memset(statistic_G, 0, LEVEL * sizeof(int));
	memset(statistic_B, 0, LEVEL * sizeof(int));

}

void HistogramEqualization::setImage(Mat & image_in)//����Ҫ�����ͼƬ��·��
{
	image = image_in;
}

void HistogramEqualization::statistic()//�ֱ��ͼƬ��RGBֵ����ֱ��ͼͳ��
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

Mat HistogramEqualization::equProcess()//��ԭͼ���о��⴦��
{
	/*����ԭ���ĸ����Ҷ�ֵ���������Ժ�Ӧ�ñ�ɶ���
	temp�����±����ԭ��ͼ��ĻҶ�ֵ
	temp�д洢�����Ǳ任������Ҷ�ֵ��Ӧ�ĻҶ�ֵ
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
		Mat imEqu1(image.rows, image.cols, CV_8UC1);//8λ�޷��ŵĵ�ͨ��---�Ҷ�ͼƬ
		imEqu1.copyTo(imEqu);
	}
	else
	{
		Mat imEqu1(image.rows, image.cols, CV_8UC3);//8λ�޷��ŵ���ͨ��---RGB��ɫͼ��
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
	double temp_R[LEVEL];//��һ����ĸ���
	double max=statistic_R[0];
	memset(temp_R, 0, LEVEL * sizeof(double));
	Mat dstImage = Mat::zeros(Size(LEVEL, LEVEL), CV_8UC1);//����ֱ��ͼ,�����ȴ���һ���ڵ׵�ͼ��Ϊ�˿�����ʾ��ɫ�����Ըû���ͼ����һ��8λ��3ͨ��ͼ��
	
	for (int i = 0; i < LEVEL; i++)//�������ֵ
	{
		if (statistic_R[i] >= max)
			max = statistic_R[i];
	}
	max = (double)max / (double)(image.cols*image.rows);

	for (int i = 0; i < LEVEL; i++)
	{
		temp_R[i] = (double)statistic_R[i] / (double)(image.cols*image.rows);
		temp_R[i] = temp_R[i] * (double)LEVEL*0.9 / max;//�����ֵ��ʾ��0.9��λ�ã��������ձ�������

		rectangle(dstImage, Point(i, LEVEL-1), Point(i, LEVEL-temp_R[i]), Scalar(255));//ע������point��x��y)��(cols,rows),�� .at�����෴
	}
	
	return dstImage;
}


HistogramEqualization::~HistogramEqualization()
{
}
