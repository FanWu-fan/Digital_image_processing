#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void help(char **argv){
    std::cout<<"\n"
    << "A simple OpenCV program that loads and displays an image from disk\n"
	<< argv[0] <<" <path/filename>\n"
	<< "For example:\n"
	<< argv[0] << " ../fruits.jpg\n"
	<< std::endl;
}

int main(int argc, char** argv)
{
    if(argc != 2){
        help(argv);
        return 0;
    }
    Mat img = imread(argv[1],IMREAD_GRAYSCALE);

    if(img.empty()) return -1;

    std::cout<<img.depth()<<img.size<<std::endl;
    // Mat img(3,4,CV_16UC4,Scalar_<uchar>(1,2,3,4));
    cout << img << endl;
    cout << "dims:" << img.dims << endl;
    cout << "rows:" << img.rows << endl;
    cout << "cols:" << img.cols << endl;
    cout << "channels:" << img.channels() << endl;
    cout << "type:" << img.type() << endl;
    cout << "depth:" << img.depth() << endl;
    cout << "elemSize:" << img.elemSize() << endl;
    cout << "elemSize1:" << img.elemSize1() << endl;

}