#include<iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;

void help(char** argv)
{
    cout<<"\n"
    << "2-03: play video from disk \n"
	<< argv[0] <<" <path/video>\n"
	<< "For example:\n"
	<< argv[0] << " ../tree.avi\n"
	<< endl;
}

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        help(argv);
        return 0;
    }
    cv::VideoCapture cap;

    // cap.open( string(argv[1]));
    cap.open( argv[1]);

    cout <<"Opened file: " <<string(argv[1]) <<endl;

    cv::Mat frame;

    for(;;){
        cout<<"!!!"<<endl;
        cap>>frame;
        if(frame.empty()) break;

        cout << "dims:" << frame.dims << endl;
        cout << "rows:" << frame.rows << endl;
        cout << "cols:" << frame.cols << endl;
        cout << "channels:" << frame.channels() << endl;
        cout << "type:" << frame.type() << endl;
        cout << "depth:" << frame.depth() << endl;
        cout << "frame[100][100]: " << int(frame.at<cv::Vec3b>(100,100)[0])
                                    <<" "<<int(frame.at<cv::Vec3b>(100,100)[1])
                                    <<" "<<int(frame.at<cv::Vec3b>(100,100)[2]) <<endl;

        if((char)cv::waitKey(33) >=0 ) break;
    }

    return 0;
}