#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


//-----全局函数声明-----


//-----全局变量声明-----


//-----函数定义-----


//-----主程序-----
int main()
{
    Mat srcImage, dstImage;
    Mat Map_x, Map_y;

    srcImage = imread("thersh.jpg");
    if(!srcImage.data) {printf("图片读取错误！ \n"); return false; }

    dstImage.create(srcImage.size(), srcImage.type() );
    Map_x.create(srcImage.size(), CV_32FC1 );
    Map_y.create(srcImage.size(), CV_32FC1 );

    for(int j=0; j<srcImage.rows; j++)
    {
        for(int i=0; i<srcImage.cols; i++)
        {
            Map_x.at<float>(j,i) = static_cast<float>(i);
            Map_y.at<float>(j,i) = static_cast<float>(srcImage.rows-j);
        }
    }

    remap(srcImage, dstImage, Map_x, Map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0,0) );

    imshow("效果图",dstImage);

    waitKey(0);
    return 0;
}  
