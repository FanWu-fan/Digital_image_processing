#include "Equalization.h"
#include <opencv2/highgui/highgui.hpp>

int main()
{
	Mat srcImage_gray, srcImage_color, gray2_equ, color2_equ;
	srcImage_gray = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 0);
	srcImage_color = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 1);

	imshow("原始图像的灰度图", srcImage_gray);
	imshow("原始图像的彩色图", srcImage_color);

	Equalization equ1,equ2;
	equ1.setImage(srcImage_gray);
	equ1.statistic();
	gray2_equ = equ1.queProcess();
	imshow("变换后灰度图像", gray2_equ);

	equ2.setImage(srcImage_gray);
	equ2.statistic();
	color2_equ = equ2.queProcess();
	imshow("变换后彩色图像", gray2_equ);

	waitKey(0);
	return 0;
}