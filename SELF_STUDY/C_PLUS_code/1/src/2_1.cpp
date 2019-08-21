#include <opencv2/opencv.hpp>
#include <iostream>
int main(int argc, char** argv)
{
    cv::Mat img = cv::imread(argv[1],-1);
    if(img.empty()) return -1;
    std::cout<<img.depth()<<img.size<<std::endl;
}