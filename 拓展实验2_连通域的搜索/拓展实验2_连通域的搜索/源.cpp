#include<opencv2/opencv.hpp>
#include<iostream>
#include<list>
#include<cstring>
#include<stack>

/*Opencv_联通域分析 两遍扫描法

连通区域（Connected Component）一般是指图像中具有相同像素值且位置相邻的前景像素点组成的图像区域（Region，Blob）。

第一遍扫描时赋予每个像素位置一个label，扫描过程中同一个连通区域内的像素集合中可能会被赋予一个或多个不同label，
因此需要将这些属于同一个连通区域但具有不同值的label合并，也就是记录它们之间的相等关系；
第二遍扫描就是将具有相等关系的equal_labels所标记的像素归为一个连通区域并赋予一个相同的label（通常这个label是equal_labels中的最小值）

1）第一次扫描：
访问当前像素B(x,y)，如果B(x,y) == 1：
如果B(x,y)的领域中像素值都为0，则赋予B(x,y)一个新的label：
label += 1， B(x,y) = label；
如果B(x,y)的领域中有像素值 > 1的像素Neighbors：
将Neighbors中的最小值赋予给B(x,y):
B(x,y) = min{Neighbors}
记录Neighbors中各个值（label）之间的相等关系，即这些值（label）同属同一个连通区域；
 labelSet[i] = { label_m, .., label_n }，labelSet[i]中的所有label都属于同一个连通区域
 （注：这里可以有多种实现方式，只要能够记录这些具有相等关系的label之间的关系即可）
 2）第二次扫描：
 找到与label = B(x,y)同属相等关系的一个最小label值，赋予给B(x,y)；
 完成扫描后，图像中具有相同label值的像素就组成了同一个连通区域。
*/

//两遍扫描法

void algorithm_Two_Pass(const cv::Mat& binImg, cv::Mat& lableImg)
{
	if (binImg.empty() ||
		binImg.type() != CV_8UC1)
	{
		return;
	}

	// 第一个通路

	lableImg.release();
	binImg.convertTo(lableImg, CV_32SC1);

	int label = 1;
	std::vector<int> labelSet;
	labelSet.push_back(0);
	labelSet.push_back(1);

	int rows = binImg.rows - 1;
	int cols = binImg.cols - 1;
	for (int i = 1; i < rows; i++)
	{
		int* data_preRow = lableImg.ptr<int>(i - 1);
		int* data_curRow = lableImg.ptr<int>(i);
		for (int j = 1; j < cols; j++)
		{
			if (data_curRow[j] == 1)
			{
				std::vector<int> neighborLabels;
				neighborLabels.reserve(2);
				int leftPixel = data_curRow[j - 1];
				int upPixel = data_preRow[j];
				if (leftPixel > 1)
				{
					neighborLabels.push_back(leftPixel);
				}
				if (upPixel > 1)
				{
					neighborLabels.push_back(upPixel);
				}

				if (neighborLabels.empty())
				{
					labelSet.push_back(++label);  // 不连通，标签+1
					data_curRow[j] = label;
					labelSet[label] = label;
				}
				else
				{
					std::sort(neighborLabels.begin(), neighborLabels.end());
					int smallestLabel = neighborLabels[0];
					data_curRow[j] = smallestLabel;

					// 保存最小等价表
					for (size_t k = 1; k < neighborLabels.size(); k++)
					{
						int tempLabel = neighborLabels[k];
						int& oldSmallestLabel = labelSet[tempLabel];
						if (oldSmallestLabel > smallestLabel)
						{
							labelSet[oldSmallestLabel] = smallestLabel;
							oldSmallestLabel = smallestLabel;
						}
						else if (oldSmallestLabel < smallestLabel)
						{
							labelSet[smallestLabel] = oldSmallestLabel;
						}
					}
				}
			}
		}
	}

	// 更新等价对列表
	// 将最小标号给重复区域
	for (size_t i = 2; i < labelSet.size(); i++)
	{
		int curLabel = labelSet[i];
		int preLabel = labelSet[curLabel];
		while (preLabel != curLabel)
		{
			curLabel = preLabel;
			preLabel = labelSet[preLabel];
		}
		labelSet[i] = curLabel;
	};

	for (int i = 0; i < rows; i++)
	{
		int* data = lableImg.ptr<int>(i);
		for (int j = 0; j < cols; j++)
		{
			int& pixelLabel = data[j];
			pixelLabel = labelSet[pixelLabel];
		}
	}
}

//彩色效果演示
///为不同的连通域分配不同的随机颜色
cv::Scalar GetRandomColor()
{
	uchar r = 255 * (rand() / (1.0 + RAND_MAX));
	uchar g = 255 * (rand() / (1.0 + RAND_MAX));
	uchar b = 255 * (rand() / (1.0 + RAND_MAX));
	return cv::Scalar(b, g, r);
}
void LabelColor(const cv::Mat& labelImg, cv::Mat& colorLabelImg)
{
	if (labelImg.empty() ||
		labelImg.type() != CV_32SC1)
	{
		return;
	}

	std::map<int, cv::Scalar> colors;

	int rows = labelImg.rows;
	int cols = labelImg.cols;

	colorLabelImg.release();
	colorLabelImg.create(rows, cols, CV_8UC3);
	colorLabelImg = cv::Scalar::all(0);

	for (int i = 0; i < rows; i++)
	{
		const int* data_src = (int*)labelImg.ptr<int>(i);
		uchar* data_dst = colorLabelImg.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			int pixelValue = data_src[j];
			if (pixelValue > 1)
			{
				if (colors.count(pixelValue) <= 0)
				{
					colors[pixelValue] = GetRandomColor();
				}

				cv::Scalar color = colors[pixelValue];
				*data_dst++ = color[0];
				*data_dst++ = color[1];
				*data_dst++ = color[2];
			}
			else
			{
				data_dst++;
				data_dst++;
				data_dst++;
			}
		}
	}
}

int main()
{
	//载入图片
	cv::Mat binImage = cv::imread("G:\\Code\\Digital_image_processing\\images\\1.jpg", 0);
	cv::Mat labelImg_Seed;
	cv::Mat labelImg_Two;

	//原图显示
	cv::imshow("srcImg", binImage);


	//二值化
	cv::threshold(binImage, binImage, 50, 1, cv::THRESH_BINARY);

	//
	algorithm_Two_Pass(binImage, labelImg_Two);


	//彩色效果显示

	cv::Mat colorLabelImg_Two;


	LabelColor(labelImg_Two, colorLabelImg_Two);



	cv::imshow("colorLabelImg_Two", colorLabelImg_Two);

	cv::waitKey(0);
	return 0;
}
