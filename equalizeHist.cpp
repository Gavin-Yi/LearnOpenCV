#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME "[程序窗口]"

//-----全局函数声明-----


//-----全局变量声明-----


//-----主程序-----
int main()
{
    Mat srcImage = imread("thersh.jpg");
    Mat dstImage;


    dstImage.create(srcImage.size(), srcImage.type() );

    cvtColor(srcImage, srcImage, COLOR_BGR2GRAY );
    imshow("原图像", srcImage);

    equalizeHist(srcImage, dstImage );

    imshow(WINDOW_NAME, dstImage);
    
    waitKey(0);
    return 0;
}  

//-----函数定义-----

