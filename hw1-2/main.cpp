#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;

int cnt=41;

int main(){
    std::string fileName;
    int lineNum=6, colNum=9, unit=10;
    std::vector<std::vector<Point3f>> objPoint;
    std::vector<std::vector<Point2f>> imgPoint;
    Size imgSize;
    for(int i=0; i<cnt; ++i){
        fileName="../chess/"+std::to_string(i)+".jpg";
        Mat src=imread(fileName);
        imgSize=src.size();

        Mat grey;
        cvtColor(src,grey,COLOR_BGR2GRAY);
        std::vector<Point2f> corner;
        Size patSize(colNum,lineNum);
        findChessboardCorners(grey,patSize,corner);
        if (corner.size() == 0) {
            std::cout << "corner size 0" << std::endl;
            return 0;
        }
        find4QuadCornerSubpix(grey, corner, Size(1, 1));
        //drawChessboardCorners(src, patSize, corner, true);
        //imshow("pic",src);
        //waitKey(0);

        std::vector<Point3f> obj;
        for(int j=0; j<lineNum; ++j){
            for(int k=0; k<colNum; ++k){
                obj.push_back(Point3f(j*unit,k*unit,0));
            }
        }
        objPoint.push_back(obj);
        imgPoint.push_back(corner);
    }

    Mat cameraMatrix=Mat(3, 3, CV_32FC1, Scalar::all(0));
    Mat distCoeffs=Mat(1, 5, CV_32FC1, Scalar::all(0));
    std::vector<Mat> rvecs;
    std::vector<Mat> tvecs;

    calibrateCamera(objPoint, imgPoint, imgSize, cameraMatrix, distCoeffs, rvecs, tvecs);
    std::cout << "cameraMatrix:" << std::endl << cameraMatrix << std::endl;
    std::cout << "distcoeffs:" << std::endl << distCoeffs << std::endl;

    return 0;
}