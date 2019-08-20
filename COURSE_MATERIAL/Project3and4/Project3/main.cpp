#include "Spatial_Filtering.h"
#include<opencv2/opencv.hpp>

int main()
{
	//����Ҷ�ͼ
	Mat image = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 0);

	Mat image_color = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 1);

	Spafilt spt;
	Mat image_SaltAndPepperNoise = spt.addSaltAndPepperNoise(image, 0.2);
	Mat image_Salt = spt.addSaltNoise(image, 0.2);
	Mat image_Pepper = spt.addPepperNoise(image, 0.2);
	Mat image_Gaussian = spt.addGaussianNoise(image);

	Mat imageColor_SaltAndPepperNoise = spt.addSaltAndPepperNoise(image_color, 0.2);
	Mat imageColor_Salt = spt.addSaltNoise(image_color, 0.2);
	Mat imageColor_Pepper = spt.addPepperNoise(image_color, 0.2);
	Mat imageColor_Gaussian = spt.addGaussianNoise(image_color);

	int experment = 0;
	cout << "����ʵ����: " << endl;
	cin >> experment;

	switch (experment)

	{
	case 3:
		//-----------------------------[1] ʵ��3 ----------------------------------------------------------------
		//���þ�ֵģ��ƽ���Ҷ�ͼ�� ��ɫ�ͻҶ�
		// 3*3 ��ֵģ��
		imshow("source_image", image);
		imshow("sour_color_image", image_color);
		float filter3[9];
		for (int counter = 0; counter < 9; counter++)
			filter3[counter] = (float)1 / 9;
		imshow("��ֵģ��-3", spt.linearFilter(image, filter3, 3));
		imshow("��ֵģ��-3-color", spt.linearFilter(image_color, filter3, 3));

		waitKey(0);
		destroyAllWindows();

		// 5*5 ��ֵģ��
		float filter5[25];
		for (int counter = 0; counter < 25; counter++)
			filter5[counter] = (float)1 / 25;
		imshow("��ֵģ��-5", spt.linearFilter(image, filter5, 5));
		imshow("��ֵģ��-5-color", spt.linearFilter(image_color, filter5, 5));

		//9*9 ��ֵģ��
		float filter9[81];
		for (int counter = 0; counter < 81; counter++)
			filter9[counter] = (float)1 / 81;
		imshow("��ֵģ��-9", spt.linearFilter(image, filter9, 9));
		imshow("��ֵģ��-9-color", spt.linearFilter(image_color, filter9, 9));
		waitKey(0);
		destroyAllWindows();

		//ʹ�ø�˹�˲�ģ��ƽ��ͼ��
		//3*3 ��˹ģ��

		imshow("3*3 ��˹ģ��", spt.GasssionFilter(image, 3, 1.5));
		imshow("3*3 ��˹ģ��-color", spt.GasssionFilter(image_color, 3, 1.5));

		//5*5 ��˹ģ��
		imshow("5*5 ��˹ģ��", spt.GasssionFilter(image, 5, 1.5));
		imshow("5*5 ��˹ģ��-color", spt.GasssionFilter(image_color, 5, 1.5));


		//9*9 ��˹ģ��
		imshow("9*9 ��˹ģ��", spt.GasssionFilter(image, 9, 1.5));
		imshow("9*9 ��˹ģ��-color", spt.GasssionFilter(image_color, 9, 1.5));
		waitKey(0);
		destroyAllWindows();

		//�������˲�  ԭͼ���ȥģ��������ͼ���ٽ�����õ���ģ�����һ��Ȩ�ؼӸ�ԭͼ�񡣹�ʽ��ʽ����
		imshow("highBoost", spt.highBoostFilter(image, 1));

		//Roberts��������
		imshow("Roberts", spt.roberts(image));

		//prewitt����
		imshow("Prewitt", spt.prewitt(image));

		//Sobel����
		imshow("Sobel", spt.sobel(image));

		//Laplacian�񻯴���
		imshow("Laplacian", spt.laplacian(image, 3));
		waitKey(0);
		break;

	case 4:
		//-----------------------------[2] ʵ��4 ---------------------------------------------------------------------------


		imshow("source_image", image);
		imshow("sour_color_image", image_color);

		imshow("image_SaltAndPepperNoise", image_SaltAndPepperNoise);
		imshow("image_Salt", image_Salt);
		imshow("image_Pepper", image_Pepper);
		imshow("image_Gaussian", image_Gaussian);

		imshow("imageColor_SaltAndPepperNoise", imageColor_SaltAndPepperNoise);
		imshow("imageColor_Salt", imageColor_Salt);
		imshow("imageColor_Pepper", imageColor_Pepper);
		imshow("imageColor_Gaussian", imageColor_Gaussian);
		waitKey(0);
		destroyAllWindows();

		//5*5��������ֵ�˲� �ҶȼӲ�ɫ
		float filter_5[25];
		for (int counter = 0; counter < 25; counter++)
			filter_5[counter] = (float)1 / 25;
		imshow("5*5��������ֵ�˲�-->image_SaltAndPepperNoise", spt.linearFilter(image_SaltAndPepperNoise, filter_5, 5));
		imshow("5*5��������ֵ�˲�-->image_Salt", spt.linearFilter(image_Salt, filter_5, 5));
		imshow("5*5��������ֵ�˲�-->image_Pepper", spt.linearFilter(image_Pepper, filter_5, 5));
		imshow("5*5��������ֵ�˲�-->image_Gaussian", spt.linearFilter(image_Gaussian, filter_5, 5));
		waitKey(0);
		destroyAllWindows();

		imshow("5*5��������ֵ�˲�-->imageColor_SaltAndPepperNoise", spt.linearFilter(imageColor_SaltAndPepperNoise, filter_5, 5));
		imshow("5*5��������ֵ�˲�-->imageColor_Salt", spt.linearFilter(imageColor_Salt, filter_5, 5));
		imshow("5*5��������ֵ�˲�-->imageColor_Pepper", spt.linearFilter(imageColor_Pepper, filter_5, 5));
		imshow("5*5��������ֵ�˲�-->imageColor_Gaussian", spt.linearFilter(imageColor_Gaussian, filter_5, 5));
		waitKey(0);
		destroyAllWindows();
		
		//5*5�ļ��ξ�ֵ�˲� 
		imshow("5*5�ļ��ξ�ֵ�˲�-->image_SaltAndPepperNoise", spt.geoMeanFilter(image_SaltAndPepperNoise, 5));
		imshow("5*5�ļ��ξ�ֵ�˲�-->image_Salt", spt.geoMeanFilter(image_Salt, 5));
		imshow("5*5�ļ��ξ�ֵ�˲�-->image_Pepper", spt.geoMeanFilter(image_Salt, 5));
		imshow("5*5�ļ��ξ�ֵ�˲�-->image_Gaussian", spt.geoMeanFilter(image_Gaussian, 5));
		waitKey(0);
		destroyAllWindows();



		//5*5г���˲�
		imshow("5*5г���˲�-->image_SaltAndPepperNoise", spt.harMeanFilter(image_SaltAndPepperNoise, 5));
		imshow("5*5г���˲�-->image_Salt", spt.harMeanFilter(image_Salt, 5));
		imshow("5*5г���˲�-->image_Pepper", spt.harMeanFilter(image_Pepper, 5));
		imshow("5*5г���˲�-->image_Gaussian", spt.harMeanFilter(image_Gaussian, 5));
		waitKey(0);
		destroyAllWindows();


		//5*5��г���˲�
		imshow("5*5��г���˲�-->image_SaltAndPepperNoise", spt.conMeanFilter(image_SaltAndPepperNoise, 5, 1));
		imshow("5*5��г���˲�-->image_Salt", spt.conMeanFilter(image_Salt, 5, 1));
		imshow("5*5��г���˲�-->image_Pepper", spt.conMeanFilter(image_Pepper, 5, 1));
		imshow("5*5��г���˲�-->image_Gaussian", spt.conMeanFilter(image_Gaussian, 5, 1));
		waitKey(0);
		destroyAllWindows();



		//��ֵ�˲��� 5*5��9*9
		imshow("��ֵ�˲���5-->image_SaltAndPepperNoise", spt.medianFilter(image_SaltAndPepperNoise, 5));
		imshow("��ֵ�˲���5-->image_Salt", spt.medianFilter(image_Salt, 5));
		imshow("��ֵ�˲���5-->image_Pepper", spt.medianFilter(image_Pepper, 5));
		waitKey(0);
		destroyAllWindows();

		imshow("��ֵ�˲���9-->image_SaltAndPepperNoise", spt.medianFilter(image_SaltAndPepperNoise, 9));
		imshow("��ֵ�˲���9-->image_Salt", spt.medianFilter(image_Salt, 9));
		imshow("��ֵ�˲���9-->image_Pepper", spt.medianFilter(image_Pepper, 9));
		waitKey(0);
		destroyAllWindows();


		//����Ӧ��ֵ�˲� 7*7
		imshow("����Ӧ��ֵ�˲�7-->image_SaltAndPepperNoise", spt.adaptive_median_filte(image_SaltAndPepperNoise, 7));

		//����Ӧ��ֵ�˲� 7*7
		imshow("����Ӧ��ֵ�˲�7-->image_SaltAndPepperNoise", spt.adaptive_mean_filte(image_SaltAndPepperNoise, 7, 5));
		waitKey(0);
		destroyAllWindows();

		waitKey('0');

	}
}