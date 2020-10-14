#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    Mat pic= imread("../apple.png");
    Mat pic1,pic2,pict1,pict2;
    imshow("img1",pic);

    cvtColor(pic, pic1, COLOR_BGR2HSV);
    Scalar RedLo( 0,  43,  46);
    Scalar RedHi(21, 255, 255);
    inRange(pic1, RedLo, RedHi, pict1);
    Mat kernel=getStructuringElement(MORPH_RECT,Size(25,25));
    morphologyEx(pict1, pict1, MORPH_OPEN, kernel);
    imshow("threshold1",pict1);

    RedLo.val[0]=156;
    RedHi.val[0]=180;
    inRange(pic1,RedLo,RedHi,pict2);
    morphologyEx(pict2, pict2, cv::MORPH_OPEN, kernel);
    imshow("threshold2",pict2);

    Mat pict=((pict1+pict2)>0);
    Mat kernel2=getStructuringElement(MORPH_RECT,Size(125,125));
    morphologyEx(pict,pict,MORPH_CLOSE,kernel2);
    imshow("threshold",pict);

    //find outline
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    findContours(pict, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0, 0));

    Mat output=pic.clone();
    RotatedRect minEllipse;
    for (int i=0; i<contours.size(); i++)
    {
        minEllipse=fitEllipse(Mat(contours[i]));
        ellipse(output, minEllipse, Scalar(120,0,255), 10);
    }
    imshow("output",output);
    imwrite("output.png",output);

    waitKey(0);
    return 0;
}