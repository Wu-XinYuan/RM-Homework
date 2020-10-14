#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    Mat img_src=imread("../taxi.png");
    Point2f src[]{
        Point2f (460,254),
        Point2f (588,256),
        Point2f (591,297),
        Point2f (464,297),

    };
    Point2f dst[]{
        Point2f(0,0),
        Point2f(1500,0),
        Point2f(1500,600),
        Point2f(0,600),

    };
    Mat pers=getPerspectiveTransform(src,dst);
    Mat img_dst;
    warpPerspective(img_src,img_dst,pers,Size(1500,600));
    Mat output;
    cvtColor(img_dst,output,COLOR_BGR2GRAY);
    threshold(output,output,100,255,THRESH_BINARY);
    imshow("result",output);
    imwrite("../output.jpg",output);
    waitKey(0);
}
