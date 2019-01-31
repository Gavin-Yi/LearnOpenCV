#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


//-----全局函数声明-----


//-----全局变量声明-----


//-----函数定义-----


//-----主程序-----
int main()
{
    Mat image = imread("thersh.jpg");

    namedWindow("原图");
    namedWindow("效果图");

    imshow("原图",image);

    Mat out;
    GaussianBlur(image, out, Size(7,7), 0, 0);

    imshow("效果图",out);

    waitKey(0);
    return 0;
}  
