#include<iostream>
#include<string>
#include<opencv2/opencv.hpp>

using namespace cv;



int DFT_IDFT()
{
	Mat input = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 0);
	imshow("input", input);//��ʾԭͼ
	int w = getOptimalDFTSize(input.cols);//�������ظ��������ߴ�ĸ���Ҷ���ųߴ��С��
	int h = getOptimalDFTSize(input.rows);//����ӽ���һ������2^n�η����������߿��Էֽ�Ϊ2��3��5�����������������
	Mat padded;
	//�������ͼ��I���������Ϊpadded���Ϸ����󷽲�����䴦��
	copyMakeBorder(input, padded, 0, h - input.rows, 0, w - input.cols, BORDER_CONSTANT, Scalar::all(0));//���ͼ�񱣴浽padded��
	//CV_32F�Ǹ������������ؿ�����0-1.0֮����κ�ֵ�������ĳЩ���ݼ��ļ�������á������Ǳ��뽫��ת��Ϊ8λ���������ʾ�������ǽ�ÿ�����س���255��
	//�������ͼ��I���������Ϊpadded���Ϸ����󷽲�����䴦��
	Mat plane[] = { Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F) };//����ͨ��
	Mat complexIm;
	merge(plane, 2, complexIm);//�ϲ�ͨ��/��planes�ںϺϲ���һ����ͨ������complexI
	dft(complexIm, complexIm);//���и���Ҷ�任���������������
	split(complexIm, plane);//����ͨ��
	magnitude(plane[0], plane[1], plane[0]);//��ȡ����ͼ��0ͨ��Ϊʵ��ͨ����1Ϊ��������Ϊ��ά����Ҷ�任����Ǹ���
	int cx = padded.cols / 2; int cy = padded.rows / 2;//һ�µĲ������ƶ�ͼ�����������½���λ�ã����������½���λ��
	Mat temp;

	//�������и���Ҷͼ���е����ޣ�ʹ��ԭ��λ��ͼ�����ģ����������ԵĴ��ڣ��׵��ĸ��ǰ������Ƶĸ�ֵ
	Mat part1(plane[0], Rect(0, 0, cx, cy));  //���Ͻ�ͼ�񻮶�ROI����
	Mat part2(plane[0], Rect(cx, 0, cx, cy));   //���Ͻ�ͼ��
	Mat part3(plane[0], Rect(0, cy, cx, cy));	//���½�ͼ��
	Mat part4(plane[0], Rect(cx, cy, cx, cy));  //���½�ͼ��

	//�任���ϽǺ����½�����
	part1.copyTo(temp);
	part4.copyTo(part1);
	temp.copyTo(part4);
	part2.copyTo(temp);

	//�任���ϽǺ����½�����
	part3.copyTo(part2);
	temp.copyTo(part3);
	//���仯
	Mat _complexim;
	complexIm.copyTo(_complexim);//�ѱ任�������һ�ݣ�������任��Ҳ���ǻָ�ԭͼ
	Mat iDft[] = { Mat::zeros(plane[0].size(),CV_32F),Mat::zeros(plane[0].size(),CV_32F) };//��������ͨ��������Ϊfloat����СΪ����ĳߴ�
	idft(_complexim, _complexim);//����Ҷ��任
	split(_complexim, iDft);//���Ҳ�Ǹ���
	magnitude(iDft[0], iDft[1], iDft[0]);//����ͨ������Ҫ��ȡ0ͨ��
	normalize(iDft[0], iDft[0], 1, 0, NORM_MINMAX);//��һ������float���͵���ʾ��ΧΪ0-1,����1Ϊ��ɫ��С��0Ϊ��ɫ
	imshow("idft", iDft[0]);//��ʾ��任
	

	plane[0] += Scalar::all(1);//�����ֵ��ת���������߶�(logarithmic scale)������ֱ����֧�����׵�ֵ������ʾ��ͼ���У������ҶȵĶ�̬��Χ
	//��ѹ���ˡ�
	log(plane[0], plane[0]);

	//��һ��������0-1֮��ĸ�����������任Ϊ���ӵ�ͼ���ʽ
	normalize(plane[0], plane[0], 1, 0, NORM_MINMAX);
	imshow("dft", plane[0]);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

//�����ͨ�˲���
void ideal_Low_Pass_Filter(double D0 = 60)
{
	Mat src, fourier, res;
	src = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 0); // Read the file
	imshow("ԭʼͼ��", src);
	Mat img = src.clone();
	//����ͼ����ٸ���Ҷ�任
	int M = getOptimalDFTSize(img.rows);
	int N = getOptimalDFTSize(img.cols);
	Mat padded;
	copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));
	//��¼����Ҷ�任��ʵ�����鲿
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexImg;
	merge(planes, 2, complexImg);
	//���и���Ҷ�任
	dft(complexImg, complexImg);
	//��ȡͼ��
	Mat mag = complexImg;
	mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));//
	//��ʵ��Ϊ�˰��к��б��ż�� -2�Ķ�������11111111.......10 ���һλ��0
	//��ȡ���ĵ�����
	int cx = mag.cols / 2;
	int cy = mag.rows / 2;
	//����Ƶ��
	Mat tmp;
	Mat q0(mag, Rect(0, 0, cx, cy));
	Mat q1(mag, Rect(cx, 0, cx, cy));
	Mat q2(mag, Rect(0, cy, cx, cy));
	Mat q3(mag, Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	//DoΪ�Լ��趨�ķ�ֵ���忴��ʽ

	//������ʽ�������Ĳ���
	for (int y = 0; y < mag.rows; y++) {
		double* data = mag.ptr<double>(y);
		for (int x = 0; x < mag.cols; x++) {
			double d = sqrt(pow((y - cy), 2) + pow((x - cx), 2));
			if (d <= D0)
			{

			}
			else {
				data[x] = 0;
			}
		}
	}
	//�ٵ���Ƶ��
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	//��任
	Mat invDFT, invDFTcvt;
	idft(mag, invDFT, DFT_SCALE | DFT_REAL_OUTPUT); // Applying IDFT
	invDFT.convertTo(invDFTcvt, CV_8U);
	imshow("�����ͨ�˲���", invDFTcvt);
	waitKey(0);
	destroyAllWindows();
	return;
}

void ideal_High_Pass_Filter(double D0 = 60)
{
	Mat src, fourier, res;
	src = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 0); // Read the file
	imshow("ԭʼͼ��", src);
	Mat img = src.clone();
	//cvtColor(src, img, CV_BGR2GRAY);
	//����ͼ����ٸ���Ҷ�任
	int M = getOptimalDFTSize(img.rows);
	int N = getOptimalDFTSize(img.cols);
	Mat padded;
	copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));
	//��¼����Ҷ�任��ʵ�����鲿
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexImg;
	merge(planes, 2, complexImg);
	//���и���Ҷ�任
	dft(complexImg, complexImg);
	//��ȡͼ��
	Mat mag = complexImg;
	mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));//
	//��ʵ��Ϊ�˰��к��б��ż�� -2�Ķ�������11111111.......10 ���һλ��0
	//��ȡ���ĵ�����
	int cx = mag.cols / 2;
	int cy = mag.rows / 2;
	//����Ƶ��
	Mat tmp;
	Mat q0(mag, Rect(0, 0, cx, cy));
	Mat q1(mag, Rect(cx, 0, cx, cy));
	Mat q2(mag, Rect(0, cy, cx, cy));
	Mat q3(mag, Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	//DoΪ�Լ��趨�ķ�ֵ���忴��ʽ
	//������ʽ�������Ĳ���
	for (int y = 0; y < mag.rows; y++) {
		double* data = mag.ptr<double>(y);
		for (int x = 0; x < mag.cols; x++) {
			double d = sqrt(pow((y - cy), 2) + pow((x - cx), 2));
			if (d <= D0)
			{
				data[x] = 0;
			}
			else
			{
				/*�͵�ͨ�෴��ͨ���ߵģ���������ɶ��û��*/
			}
		}
	}
	//�ٵ���Ƶ��
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	//��任
	Mat invDFT, invDFTcvt;
	idft(mag, invDFT, DFT_SCALE | DFT_REAL_OUTPUT); // Applying IDFT
	invDFT.convertTo(invDFTcvt, CV_8U);
	imshow("�����ͨ�˲���", invDFTcvt);
	waitKey(0);
	destroyAllWindows();
	return;
}

void Butterworth_Low_Paass_Filter(double D0 = 60, int n = 2)
{
	Mat src, fourier, res;
	src = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 0); // Read the file
	imshow("ԭʼͼ��", src);

	//H = 1 / (1+(D/D0)^2n)
	Mat img = src.clone();
	//cvtColor(src, img, CV_BGR2GRAY);
	//����ͼ����ٸ���Ҷ�任
	int M = getOptimalDFTSize(img.rows);
	int N = getOptimalDFTSize(img.cols);
	Mat padded;
	copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexImg;
	merge(planes, 2, complexImg);

	dft(complexImg, complexImg);

	Mat mag = complexImg;
	mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));

	int cx = mag.cols / 2;
	int cy = mag.rows / 2;

	Mat tmp;
	Mat q0(mag, Rect(0, 0, cx, cy));
	Mat q1(mag, Rect(cx, 0, cx, cy));
	Mat q2(mag, Rect(0, cy, cx, cy));
	Mat q3(mag, Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);



	for (int y = 0; y < mag.rows; y++)
	{
		double* data = mag.ptr<double>(y);
		for (int x = 0; x < mag.cols; x++)
		{
			//cout << data[x] << endl;
			double d = sqrt(pow((y - cy), 2) + pow((x - cx), 2));
			//cout << d << endl;
			double h = 1.0 / (1 + pow(d / D0, 2 * n));
			if (h <= 0.5)
			{
				data[x] = 0;
			}
			else {
			}

		}
	}
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	//��任
	Mat invDFT, invDFTcvt;
	idft(complexImg, invDFT, DFT_SCALE | DFT_REAL_OUTPUT); // Applying IDFT
	invDFT.convertTo(invDFTcvt, CV_8U);
	imshow("������˹��ͨ�˲���", invDFTcvt);

	waitKey(0);
	destroyAllWindows();
	return;
}

void Butterworth_High_Paass_Filter(double D0 = 60, int n = 2)
{
	Mat src, fourier, res;
	src = imread("G:\\Code\\Digital_image_processing\\images\\2.jpg", 0); // Read the file
	imshow("ԭʼͼ��", src);

	//H = 1 / (1+(D/D0)^2n)
	Mat img = src.clone();
	//cvtColor(src, img, CV_BGR2GRAY);
	//����ͼ����ٸ���Ҷ�任
	int M = getOptimalDFTSize(img.rows);
	int N = getOptimalDFTSize(img.cols);
	Mat padded;
	copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexImg;
	merge(planes, 2, complexImg);

	dft(complexImg, complexImg);

	Mat mag = complexImg;
	mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));

	int cx = mag.cols / 2;
	int cy = mag.rows / 2;

	Mat tmp;
	Mat q0(mag, Rect(0, 0, cx, cy));
	Mat q1(mag, Rect(cx, 0, cx, cy));
	Mat q2(mag, Rect(0, cy, cx, cy));
	Mat q3(mag, Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	for (int y = 0; y < mag.rows; y++)
	{
		double* data = mag.ptr<double>(y);
		for (int x = 0; x < mag.cols; x++)
		{
			//cout << data[x] << endl;
			double d = sqrt(pow((y - cy), 2) + pow((x - cx), 2));
			//cout << d << endl;
			double h = 1.0 / (1 + pow(D0 / d, 2 * n));
			if (h <= 0.5)
			{
				data[x] = 0;
			}
			else {
				//data[x] = data[x]*0.5;
				//cout << h << endl;
			}

			//cout << data[x] << endl;
		}
	}
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	//��任
	Mat invDFT, invDFTcvt;
	idft(complexImg, invDFT, DFT_SCALE | DFT_REAL_OUTPUT); // Applying IDFT
	invDFT.convertTo(invDFTcvt, CV_8U);
	imshow("������˹��ͨ�˲���", invDFTcvt);

	waitKey(0);
	destroyAllWindows();
	return;
}


int main()
{
	DFT_IDFT();
	ideal_Low_Pass_Filter(40.0);
	ideal_High_Pass_Filter(40.0);
	Butterworth_Low_Paass_Filter(40, 2);
	Butterworth_High_Paass_Filter(40, 2);

	return 0;
}