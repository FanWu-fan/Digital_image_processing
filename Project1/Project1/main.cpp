#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;


float gam = 1.3;

//ͼ����ֵ��ֵ������ cΪ��ֵ
float imgbin(float r, int c) 
{ 
	if (r >= c)
		return 255;
	else
		return 0;
}

//�����任 ��Χ��խ�ĵͻҶ�ֵӳ�䵽��Χ�Ͽ�ĻҶ����䣬ͬʱ����Χ�Ͽ�ĸ߻Ҷ�ֵ����ӳ��Ϊ��խ�ĻҶ����䣬
//�Ӷ���չ�˰����ص�ֵ��ѹ���˸߻Ҷȵ�ֵ���ܹ���ͼ���еͻҶ�ϸ�ڽ�����ǿ��
float imglog(float r, int c) { return c * log(1 + r); }

//٤��仯 
//����<1ʱ���õ�ֵԽС����ͼ��ͻҶ�ֵ����չԽ���ԣ�����>1ʱ���õ�ֵԽ�󣬶�ͼ��߻Ҷ�ֵ���ֵ���չԽ���ԡ��������ܹ���ʾ�����ͼ��ĵͻҶȻ��߸߻Ҷ�ϸ�ڡ�
float imggama(float r, int c) { float temp = pow(r, gam); return c * temp; }

//Fu_Type: 1.ͼ����ֵ�ָ� 2.ͼ������任 3.ͼ��٤��任
void gray_transformation(Mat& inputImage, Mat& outputImage, int Fu_Type, int c)
{
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;
	cout << "rowNumber" << rowNumber << "colNumber" << colNumber << endl;

	//����ָ��
	typedef float(*FP)(float, int);
	FP func_list[] = { imgbin , imglog , imggama };

	for (int i = 0; i < rowNumber; i++)  //��ѭ��
	{
		for (int j = 0; j < colNumber; j++)   //��ѭ��
		{
			
			float num = outputImage.at<uchar>(i, j);///��ȡ����ֵ
			float num2 = func_list[Fu_Type - 1](num, c);
			if (num2 >= 255)
			{
				num2 = 255;
			}
			else  if (num2 <=0)
			{
				num2 = 0;
			}
			outputImage.at<uchar>(i, j) = num2;
		}
	}
}

//��ɫ,��ָ�κ��������ʵ�������Ϻ�����ְ�ɫ���ɫ����ɫ������������ɫ��Ϊ��ɫ�����ǳɶԳ��֡�ɫ��������ɫ�����Բ�ܣ���λ�ڶԲ���κ�������ɫ��Ϊ��ɫ��
//��ɫ������ǿǶ�ڲ�ɫͼ������ϸ�ں����ã�RGBת��ΪCMY
//CMYģ�������ļ�ɫ���ģ�����������ڲ�ɫ��ӡ���͸�ӡ��������Ҫ��ֽ�ϳ�����ɫ���ϵ��豸����Ϊ���ϲ�������ʾ������������ɫ�����Ƿ�����ɫ��

//����HSI��HSVͼ��H������Ҫ���ж�Ӧ����ת�������ȷ���Ҳ��Ҫ��Ӧ�ķ�ת�������ͶȲ��䣬���Եõ����ƵĲ�ɫЧ����
void imgRGB2CMY(Mat& inputImage, Mat& outputImage)
{
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;
	cout << "rowNumber" << rowNumber << "colNumber" << colNumber << endl;

	for (int i = 0; i < rowNumber; i++)  //��ѭ��
	{
		for (int j = 0; j < colNumber; j++)   //��ѭ��
		{

			float dB = outputImage.at<Vec3b>(i, j)[0];
			float dG = outputImage.at<Vec3b>(i, j)[1];
			float dR = outputImage.at<Vec3b>(i, j)[2];

			float dC = 255 - dB;
			float dM = 255 - dG;
			float dY = 255 - dR;


			outputImage.at<Vec3b>(i, j)[0] = dY;
			outputImage.at<Vec3b>(i, j)[1] = dM;
			outputImage.at<Vec3b>(i, j)[2] = dC;
		}
	}
}




int main()
{
	Mat srcImage_gray, srcImage_color,rstImage1, rstImage2, rstImage3, rstimage4;
	srcImage_gray = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg",0);
	srcImage_color = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg",1);

	imshow("�Ҷ�ͼ", srcImage_gray);

	gray_transformation(srcImage_gray, rstImage1, 1, 200);
	gray_transformation(srcImage_gray, rstImage2, 2, 50);
	gray_transformation(srcImage_gray, rstImage3, 3, 1);

	imgRGB2CMY(srcImage_color, rstimage4);

	imshow("��ֵ������", rstImage1);
	imshow("�����任", rstImage2);
	imshow("٤��任", rstImage3);
	imshow("��ɫ�任", rstimage4);

	//���Ӵ����ͼƬ��һ������
	waitKey(0);

	return 0;
}
