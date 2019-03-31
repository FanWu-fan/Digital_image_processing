#include "Equalization.h"
#include <opencv2/highgui/highgui.hpp>

int main()
{
	Mat srcImage_gray, srcImage_color, gray2_equ, srcgray_Histogram,gray2_equ_Histogram,color2_equ;
	srcImage_gray = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 0);
	srcImage_color = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 1);

	imshow("原始图像的灰度图", srcImage_gray);
	imshow("原始图像的彩色图", srcImage_color);

	HistogramEqualization equ1,equ2;

	equ1.setImage(srcImage_gray);
	equ1.statistic();
	gray2_equ = equ1.equProcess();//直方图均衡
	srcgray_Histogram = equ1.returnHistogram();

	equ1.setImage(gray2_equ);
	equ1.statistic();
	gray2_equ_Histogram = equ1.returnHistogram();
	

	imshow("变换后灰度图像", gray2_equ);
	imshow("初始灰度图像的直方图", srcgray_Histogram);
	//imshow("变换后灰度图像的直方图", gray2_equ_Histogram);



	equ2.setImage(srcImage_color);
	equ2.statistic();
	color2_equ = equ2.equProcess();
	imshow("变换后彩色图像", color2_equ);

	waitKey(0);
	return 0;
}