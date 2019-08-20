#include "Spatial_Filtering.h"
#include<opencv2/opencv.hpp>

int main()
{
	//读入灰度图
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
	cout << "输入实验编号: " << endl;
	cin >> experment;

	switch (experment)

	{
	case 3:
		//-----------------------------[1] 实验3 ----------------------------------------------------------------
		//利用均值模板平滑灰度图像 彩色和灰度
		// 3*3 均值模板
		imshow("source_image", image);
		imshow("sour_color_image", image_color);
		float filter3[9];
		for (int counter = 0; counter < 9; counter++)
			filter3[counter] = (float)1 / 9;
		imshow("均值模板-3", spt.linearFilter(image, filter3, 3));
		imshow("均值模板-3-color", spt.linearFilter(image_color, filter3, 3));

		waitKey(0);
		destroyAllWindows();

		// 5*5 均值模板
		float filter5[25];
		for (int counter = 0; counter < 25; counter++)
			filter5[counter] = (float)1 / 25;
		imshow("均值模板-5", spt.linearFilter(image, filter5, 5));
		imshow("均值模板-5-color", spt.linearFilter(image_color, filter5, 5));

		//9*9 均值模板
		float filter9[81];
		for (int counter = 0; counter < 81; counter++)
			filter9[counter] = (float)1 / 81;
		imshow("均值模板-9", spt.linearFilter(image, filter9, 9));
		imshow("均值模板-9-color", spt.linearFilter(image_color, filter9, 9));
		waitKey(0);
		destroyAllWindows();

		//使用高斯滤波模板平滑图像
		//3*3 高斯模板

		imshow("3*3 高斯模板", spt.GasssionFilter(image, 3, 1.5));
		imshow("3*3 高斯模板-color", spt.GasssionFilter(image_color, 3, 1.5));

		//5*5 高斯模板
		imshow("5*5 高斯模板", spt.GasssionFilter(image, 5, 1.5));
		imshow("5*5 高斯模板-color", spt.GasssionFilter(image_color, 5, 1.5));


		//9*9 高斯模板
		imshow("9*9 高斯模板", spt.GasssionFilter(image, 9, 1.5));
		imshow("9*9 高斯模板-color", spt.GasssionFilter(image_color, 9, 1.5));
		waitKey(0);
		destroyAllWindows();

		//高提升滤波  原图像减去模糊处理后的图像，再将相减得到的模板乘以一个权重加给原图像。公式表式如下
		imshow("highBoost", spt.highBoostFilter(image, 1));

		//Roberts交叉算子
		imshow("Roberts", spt.roberts(image));

		//prewitt算子
		imshow("Prewitt", spt.prewitt(image));

		//Sobel算子
		imshow("Sobel", spt.sobel(image));

		//Laplacian锐化处理
		imshow("Laplacian", spt.laplacian(image, 3));
		waitKey(0);
		break;

	case 4:
		//-----------------------------[2] 实验4 ---------------------------------------------------------------------------


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

		//5*5的算数均值滤波 灰度加彩色
		float filter_5[25];
		for (int counter = 0; counter < 25; counter++)
			filter_5[counter] = (float)1 / 25;
		imshow("5*5的算数均值滤波-->image_SaltAndPepperNoise", spt.linearFilter(image_SaltAndPepperNoise, filter_5, 5));
		imshow("5*5的算数均值滤波-->image_Salt", spt.linearFilter(image_Salt, filter_5, 5));
		imshow("5*5的算数均值滤波-->image_Pepper", spt.linearFilter(image_Pepper, filter_5, 5));
		imshow("5*5的算数均值滤波-->image_Gaussian", spt.linearFilter(image_Gaussian, filter_5, 5));
		waitKey(0);
		destroyAllWindows();

		imshow("5*5的算数均值滤波-->imageColor_SaltAndPepperNoise", spt.linearFilter(imageColor_SaltAndPepperNoise, filter_5, 5));
		imshow("5*5的算数均值滤波-->imageColor_Salt", spt.linearFilter(imageColor_Salt, filter_5, 5));
		imshow("5*5的算数均值滤波-->imageColor_Pepper", spt.linearFilter(imageColor_Pepper, filter_5, 5));
		imshow("5*5的算数均值滤波-->imageColor_Gaussian", spt.linearFilter(imageColor_Gaussian, filter_5, 5));
		waitKey(0);
		destroyAllWindows();
		
		//5*5的几何均值滤波 
		imshow("5*5的几何均值滤波-->image_SaltAndPepperNoise", spt.geoMeanFilter(image_SaltAndPepperNoise, 5));
		imshow("5*5的几何均值滤波-->image_Salt", spt.geoMeanFilter(image_Salt, 5));
		imshow("5*5的几何均值滤波-->image_Pepper", spt.geoMeanFilter(image_Salt, 5));
		imshow("5*5的几何均值滤波-->image_Gaussian", spt.geoMeanFilter(image_Gaussian, 5));
		waitKey(0);
		destroyAllWindows();



		//5*5谐波滤波
		imshow("5*5谐波滤波-->image_SaltAndPepperNoise", spt.harMeanFilter(image_SaltAndPepperNoise, 5));
		imshow("5*5谐波滤波-->image_Salt", spt.harMeanFilter(image_Salt, 5));
		imshow("5*5谐波滤波-->image_Pepper", spt.harMeanFilter(image_Pepper, 5));
		imshow("5*5谐波滤波-->image_Gaussian", spt.harMeanFilter(image_Gaussian, 5));
		waitKey(0);
		destroyAllWindows();


		//5*5逆谐波滤波
		imshow("5*5逆谐波滤波-->image_SaltAndPepperNoise", spt.conMeanFilter(image_SaltAndPepperNoise, 5, 1));
		imshow("5*5逆谐波滤波-->image_Salt", spt.conMeanFilter(image_Salt, 5, 1));
		imshow("5*5逆谐波滤波-->image_Pepper", spt.conMeanFilter(image_Pepper, 5, 1));
		imshow("5*5逆谐波滤波-->image_Gaussian", spt.conMeanFilter(image_Gaussian, 5, 1));
		waitKey(0);
		destroyAllWindows();



		//中值滤波器 5*5和9*9
		imshow("中值滤波器5-->image_SaltAndPepperNoise", spt.medianFilter(image_SaltAndPepperNoise, 5));
		imshow("中值滤波器5-->image_Salt", spt.medianFilter(image_Salt, 5));
		imshow("中值滤波器5-->image_Pepper", spt.medianFilter(image_Pepper, 5));
		waitKey(0);
		destroyAllWindows();

		imshow("中值滤波器9-->image_SaltAndPepperNoise", spt.medianFilter(image_SaltAndPepperNoise, 9));
		imshow("中值滤波器9-->image_Salt", spt.medianFilter(image_Salt, 9));
		imshow("中值滤波器9-->image_Pepper", spt.medianFilter(image_Pepper, 9));
		waitKey(0);
		destroyAllWindows();


		//自适应中值滤波 7*7
		imshow("自适应中值滤波7-->image_SaltAndPepperNoise", spt.adaptive_median_filte(image_SaltAndPepperNoise, 7));

		//自适应均值滤波 7*7
		imshow("自适应均值滤波7-->image_SaltAndPepperNoise", spt.adaptive_mean_filte(image_SaltAndPepperNoise, 7, 5));
		waitKey(0);
		destroyAllWindows();

		waitKey('0');

	}
}