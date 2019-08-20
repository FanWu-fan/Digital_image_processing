#pragma once
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


class Spafilt {
public:
	Spafilt();
	~Spafilt();

	/*
	给图片加上椒盐噪声
	@Image_in：将要处理的图片
	@rate:噪声程度，建议（0-0.5）
	@return: 加上噪声后的图片
	*/
	Mat addSaltAndPepperNoise(const Mat &image_in, float rate = 0.4);

	/*
	给图片加上胡椒噪声
	@Image_in：将要处理的图片
	@rate:噪声程度，建议（0-0.5）
	@return: 加上噪声后的图片
	*/
	Mat addPepperNoise(const Mat &image_in, float rate = 0.4);

	/*
	给图片加上盐噪声
	@Image_in：将要处理的图片
	@rate:噪声程度，建议（0-0.5）
	@return: 加上噪声后的图片
	*/
	Mat addSaltNoise(const Mat &image_in, float rate = 0.4);

	/*
	产生高斯噪声
	@mu: 高斯噪声的偏移
	@sigma: 高斯函数的标准差
	*/
	double generateGaussianNoise(double mu, double sigma);

	/*
	给图片加上高斯噪声 Box-Muller方法
	@Image_in:将要处理的图片
	*/
	Mat addGaussianNoise(const Mat & image_in);

	/*
	线性低通滤波器(算数均值滤波）
	@image_in:将要处理的图片。
	@filter_in[]:使用的滤波器模板。
	@sizeOfFilter_in：滤波器大小
	@return：处理后的图片
	*/
	Mat linearFilter(Mat &image_in, float filter_in[], int sizeOfFilter_in);

	/*
	几何均值滤波 滤波器产生的去噪效果可以与算术平均值滤波器基本一样，但是可以更少的丢失细节。
	一旦有0值出现，那么这个像素的值立即被决定为0，几何滤波器不可以去除胡椒噪声。
	@imagein:将要处理的图片
	@sizeOfFilter_in：滤波器大小
	*/
	Mat geoMeanFilter(Mat &image_in, int sizeOfFilter_in);

	/*
	谐波滤波 这个滤波器不但不能去除椒盐噪声，对于灰度过黑的图像而言，也是要坏事的。这个滤波器，擅长于高斯噪声的去噪
	@imagein:将要处理的图片
	@sizeOfFilter_in：滤波器大小
	*/
	Mat harMeanFilter(Mat &image_in, int sizeOfFilter_in);


	/*逆谐波均值滤波
	可以通过Q值的变化，来获得一定的效果。当Q为正，这个滤波器可以去除胡椒噪声，当Q为负，这个滤波器可以去除盐粒噪声。
	@imagein:将要处理的图片
	@sizeOfFilter_in：滤波器大小
	@q:当Q为正，这个滤波器可以去除胡椒噪声，当Q为负，这个滤波器可以去除盐粒噪声
	*/
	Mat conMeanFilter(Mat &image_in, int sizeOfFilter_in,int q);

	/*自适应中值滤波
	@imagein:将要处理的图片
	@sizeOfFilter_in：滤波器大小
	*/
	Mat adaptive_median_filte(const Mat &image_in, int sizeOfFilter_in);


	/*自适应均值滤波  自适应局部降低噪声滤波器
	均值平均灰度的度量，方差该区域的对比度度量,准确预估 噪声方差，如果使用了太低的值，无变化。使用了太高的值，会频繁的减去平均值，而且方差比率再1.0处
	被削平

	@imagein:将要处理的图片
	@sizeOfFilter_in：滤波器大小
	*/
	Mat adaptive_mean_filte(const Mat &image_in, int sizeOfFilter_in, double stdev);



	/*
	生成高斯滤波器模板
	@ksize: 模板大小
	@sigma: 高斯的标准差 建议取值为 1.5
	*/
	float *getGaussionArray(int ksize, double sigma);

	/*
	高斯滤波
	@image_in:将要处理的图片
	@ksize: 模板大小
	@sigma: 高斯的标准差 建议取值为 1.5
	*/
	Mat GasssionFilter( Mat &image_in, int ksize, double sigma);


	/*
	中值滤波器
	@image_in:将要处理的图片。
	@sizeOfFiter_in;滤波器大小
	@return：处理后的图片。
	*/
	Mat medianFilter(Mat &image_in, int sizeOfFilter_in = 3);


	/*
	最大值滤波器
	@image_in:将要处理的图片。
	@sizeOfFiter_in;滤波器大小
	@return：处理后的图片。
	*/
	Mat maxFilter(Mat &image_in, int sizeOfFilter_in = 3);


	/*
	最小值滤波器
	@image_in:将要处理的图片。
	@sizeOfFiter_in;滤波器大小
	@return：处理后的图片。
	*/
	Mat minFilter(Mat &image_in, int sizeOfFilter_in = 3);


	/*
	基本高通滤波器
	@image_in:将要处理的图片。
	@filter_in[]:使用的滤波器模板。
	@sizeOfFilter_in：滤波器大小
	@return：处理后的图片
	*/
	Mat basicHighPassFilter(Mat &image_in, float filter_in[], int sizeOfFilter_in);


	/*
	罗伯特算子
	@image_in:将要处理的图片
	@return：处理后的图片
	*/
	Mat roberts(Mat &image_in);


	/*
	prewitt算子
	@image_in:将要处理的图片
	@return：处理后的图片
	*/
	Mat prewitt(Mat &image_in);


	/*
	Sobel算子
	*/
	Mat sobel(Mat &image_in);


	/*
	@image_in:将要处理的图片
	@id:选择使用哪个模板处理，id应该是1-4中的某一整数，详见实验报告。
	@return： Laplacian处理后的图片
	*/
	Mat laplacian(Mat &image_in, int id);


	/*
	高频补偿滤波器
	@k;高频补偿加模板的权重,默认为1
	*/
	Mat highBoostFilter(Mat &image_in, float k = 1);


	/*
	@原本是一个协助我调试程序的函数
	@但是最终它担任了使用截断方式标定的任务
	@在Mat scale(int k = 255);中调用了
	*/
	Mat Debug();

private:
	Mat imageSource;//待处理的图片
	Mat imageAfterBorderProcess;//对边缘进行处理后的图片。
	int* imageMat;//存放经过某些处理后，灰度值超过0-255区间的图片，等待后续处理或应用
	int filterSize;//滤波器大小
	float *filter;//滤波器模板


	/*
	设置滤波器大小及模板，这里只考虑方形的滤波器（长宽相等）
	@size_i:滤波器大小，只能是方形滤波器，传入任一边长度
	@fil:滤波器模板
	*/
	void setFilter(int size_i, float *fil);


	/*
	设置滤波器大小这里只考虑方形的滤波器（长宽相等）
	@size_i:滤波器大小，只能是方形滤波器，传入任一边长度
	*/
	void setFilterSize(int size_i);


	/*
	设置将要处理的图片
	@image_i:将要处理的图片
	*/
	void setImage(Mat &image_i);


	/*
	对图像的边缘进行处理
	* 处理的是imageSource图片
	* 处理后的结果存放在imageAfterBorderProcess中
	* 采用镜像处理办法，角落处的值设为128
	*/
	void borderProcessing();


	/*
	* 用来求两幅图像的带权的差或者和，
	* 可以在图像和图像或图像和数组之间运算
	* 用一个系数来控制加或者减或者其他系数
	* 结果放在数组imageMat中
	@coefficient:系数，决定两幅图像之间进行怎么样的操作
	@image_in: 若插入该参数，则进行imageSource和image_in之间的运算，
			   否则进行imageSource和imageMat之间运算
	*/
	void addOrSubtractOfTwoImage(float coefficient, Mat* image_in = NULL);


	/*
	* 使用线性滤波器对图片进行滤波
	* 由于高通滤波器模板处理后灰度值有可能溢出，所以结果放在imageMat中，待进一步处理
	* 使用私有变量中的filter对imageSource进行滤波
	*/
	void preHighPassFilter();


	/*
	用来将数组内的所有的灰度值标定到指定灰度区间并以Mat的形式返回出来
	不修改数组内容
	@参数k:表示标定的上界
	下界为零
	@return：返回标定后的图像
	*/
	Mat scale(int k = 255);


	/*
	非线性高通3x3滤波器
	@filterR:大小为3x3的滤波器模板
	@filterC:大小为3x3的滤波器模板
	@return：处理后经过标定的图像
	*/
	Mat nonLinearHighPass3x3filter(float* filterR, float* filterC);

};