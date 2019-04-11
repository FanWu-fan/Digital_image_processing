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
	// 3*3 ��ֵģ��
	float filter3[9];
	for (int counter = 0; counter < 9; counter++)
		filter3[counter] = (float)1 / 9;
	imshow("linearFilter-3", spt.linearFilter(image, filter3, 3));

	// 5*5 ��ֵģ��
	float filter5[25];
	for (int counter = 0; counter < 25; counter++)
		filter5[counter] = (float)1 / 25;
	imshow("linearFilter-5", spt.linearFilter(image, filter5, 5));

	//9*9 ��ֵģ��
	float filter9[81];
	for (int counter = 0; counter < 81; counter++)
		filter9[counter] = (float)1 / 81;
	imshow("linearFilter-9", spt.linearFilter(image, filter9, 9));

	//ʹ�ø�˹�˲�ģ��ƽ��ͼ��
	//3*3 ��˹ģ��

	imshow("GasssionFilter3", spt.GasssionFilter(image, 3, 1.5));

	//5*5 ��˹ģ��
	imshow("GasssionFilter5", spt.GasssionFilter(image, 5, 1.5));

	//9*9 ��˹ģ��
	imshow("GasssionFilter9", spt.GasssionFilter(image, 9, 1.5));

	//Roberts��������
	imshow("Roberts", spt.roberts(image));

	//prewitt����
	imshow("Prewitt", spt.prewitt(image));

	//Sobel����
	imshow("Sobel", spt.sobel(image));

	//Laplacian�񻯴���
	imshow("Laplacian", spt.laplacian(image, 3));

	//�������˲�
	imshow("highBoost", spt.highBoostFilter(image, 1));

	//���þ�ֵģ��ƽ����ɫͼ��




	////��ֵ�˲���
	//Mat image_noise = spt.addSaltAndPepperNoise(image, 0.2);
	//imshow("beforeMedaiFiltering", image_noise);
	//imshow("afterMedaiFiltering", spt.medianFilter(image_noise, 3));

	////���ֵ�˲���
	//imshow("maxFilter", spt.maxFilter(image, 3));

	////��Сֵ�˲���
	//imshow("mixFilter", spt.minFilter(image, 3));

	////������ͨ�˲���
	//float highFilter[9] = { 1,  1, 1,  1, -8, 1, 1, 1, 1 };
	//imshow("BasicHighPassFilter", spt.basicHighPassFilter(image, highFilter, 3));




	waitKey(0);
	return 0;
}