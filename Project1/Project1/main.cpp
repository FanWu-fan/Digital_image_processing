#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;


float gam = 1.3;

//图像阈值二值化处理 c为阈值
float imgbin(float r, int c) 
{ 
	if (r >= c)
		return 255;
	else
		return 0;
}

//对数变换 范围较窄的低灰度值映射到范围较宽的灰度区间，同时将范围较宽的高灰度值区间映射为较窄的灰度区间，
//从而扩展了暗像素的值，压缩了高灰度的值，能够对图像中低灰度细节进行增强。
float imglog(float r, int c) { return c * log(1 + r); }

//伽马变化 
//当γ<1时，γ的值越小，对图像低灰度值的扩展越明显；当γ>1时，γ的值越大，对图像高灰度值部分的扩展越明显。这样就能够显示更多的图像的低灰度或者高灰度细节。
float imggama(float r, int c) { float temp = pow(r, gam); return c * temp; }

//Fu_Type: 1.图像阈值分割 2.图像对数变换 3.图像伽马变换
void gray_transformation(Mat& inputImage, Mat& outputImage, int Fu_Type, int c)
{
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;
	cout << "rowNumber" << rowNumber << "colNumber" << colNumber << endl;

	//函数指针
	typedef float(*FP)(float, int);
	FP func_list[] = { imgbin , imglog , imggama };

	for (int i = 0; i < rowNumber; i++)  //行循环
	{
		for (int j = 0; j < colNumber; j++)   //列循环
		{
			
			float num = outputImage.at<uchar>(i, j);///提取像素值
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

//补色,是指任何两种以适当比例混合后而呈现白色或灰色的颜色，即这两种颜色互为补色。总是成对出现。色调环（颜色立体的圆周）上位于对侧的任何两种颜色互为补色。
//补色对于增强嵌在彩色图像暗区的细节很有用，RGB转换为CMY
//CMY模型这样的减色混合模型正好适用于彩色打印机和复印机这类需要在纸上沉积彩色颜料的设备，因为颜料不是像显示器那样发出颜色，而是反射颜色。

//对于HSI和HSV图像，H分量须要进行对应的旋转，而亮度分量也须要对应的反转。而饱和度不变，可以得到相似的补色效果。
void imgRGB2CMY(Mat& inputImage, Mat& outputImage)
{
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;
	cout << "rowNumber" << rowNumber << "colNumber" << colNumber << endl;

	for (int i = 0; i < rowNumber; i++)  //行循环
	{
		for (int j = 0; j < colNumber; j++)   //列循环
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

	imshow("灰度图", srcImage_gray);

	gray_transformation(srcImage_gray, rstImage1, 1, 200);
	gray_transformation(srcImage_gray, rstImage2, 2, 50);
	gray_transformation(srcImage_gray, rstImage3, 3, 1);

	imgRGB2CMY(srcImage_color, rstimage4);

	imshow("二值化处理", rstImage1);
	imshow("对数变换", rstImage2);
	imshow("伽马变换", rstImage3);
	imshow("补色变换", rstimage4);

	//不加此语句图片会一闪而过
	waitKey(0);

	return 0;
}
