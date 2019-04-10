#include "Spatial_Filtering.h"
#include<opencv2/opencv.hpp>

int main()
{
	//����Ҷ�ͼ
	Mat image = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 0);
	imshow("source_image", image);

	Spafilt spt;

	//-----------------------------[1] ʵ��3 --------------------------------

	//���þ�ֵģ��ƽ���Ҷ�ͼ��


	//���Ե�ͨ�˲���
	float filter[9];
	for (int counter = 0; counter < 9; counter++)
		filter[counter] = (float)1 / 9;
	imshow("linearFilter", spt.linearFilter(image, filter, 3));

	//��ֵ�˲���
	Mat image_noise = spt.addSaltAndPepperNoise(image, 0.2);
	imshow("beforeMedaiFiltering", image_noise);
	imshow("afterMedaiFiltering", spt.medianFilter(image_noise, 3));

	//���ֵ�˲���
	imshow("maxFilter", spt.maxFilter(image, 3));

	//��Сֵ�˲���
	imshow("mixFilter", spt.minFilter(image, 3));

	//������ͨ�˲���
	float highFilter[9] = { 1,  1, 1,  1, -8, 1, 1, 1, 1 };
	imshow("BasicHighPassFilter", spt.basicHighPassFilter(image, highFilter, 3));

	//Roberts��������
	imshow("Roberts", spt.roberts(image));

	//prewitt����
	imshow("Prewitt", spt.prewitt(image));

	//Sobel����
	imshow("Sobel", spt.sobel(image));

	//Laplacian�񻯴���
	imshow("Laplacian", spt.laplacian(image, 3));

	//��Ƶ�����˲���
	imshow("highBoost", spt.highBoostFilter(image, 1));

	waitKey(0);
	return 0;
}