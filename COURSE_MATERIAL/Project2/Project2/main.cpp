#include "Equalization.h"
#include <opencv2/highgui/highgui.hpp>

int main()
{
	Mat srcImage_gray, srcImage_color, gray2_equ, srcgray_Histogram,gray2_equ_Histogram,color2_equ;
	srcImage_gray = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 0);
	srcImage_color = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 1);

	imshow("ԭʼͼ��ĻҶ�ͼ", srcImage_gray);
	imshow("ԭʼͼ��Ĳ�ɫͼ", srcImage_color);

	HistogramEqualization equ1,equ2;

	equ1.setImage(srcImage_gray);
	equ1.statistic();
	gray2_equ = equ1.equProcess();//ֱ��ͼ����
	srcgray_Histogram = equ1.returnHistogram();

	equ1.setImage(gray2_equ);
	equ1.statistic();
	gray2_equ_Histogram = equ1.returnHistogram();
	

	imshow("�任��Ҷ�ͼ��", gray2_equ);
	imshow("��ʼ�Ҷ�ͼ���ֱ��ͼ", srcgray_Histogram);
	//imshow("�任��Ҷ�ͼ���ֱ��ͼ", gray2_equ_Histogram);



	equ2.setImage(srcImage_color);
	equ2.statistic();
	color2_equ = equ2.equProcess();
	imshow("�任���ɫͼ��", color2_equ);

	waitKey(0);
	return 0;
}