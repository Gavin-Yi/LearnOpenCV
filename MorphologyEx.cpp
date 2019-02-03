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
    Mat image = imread("mo.jpg");

    namedWindow("原图");
    namedWindow("开运算");
    namedWindow("闭运算");
    namedWindow("形态学梯度");
    namedWindow("顶帽");
    namedWindow("黑帽");
    namedWindow("腐蚀");
    namedWindow("膨胀");

    imshow("原图",image);

    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));

    Mat out1;
    Mat out2;
    Mat out3;
    Mat out4;
    Mat out5;
    Mat out6;
    Mat out7;
    morphologyEx(image,out1,MORPH_OPEN,element);
    morphologyEx(image,out2,MORPH_CLOSE,element);
    morphologyEx(image,out3,MORPH_GRADIENT,element);
    morphologyEx(image,out4,MORPH_TOPHAT,element);
    morphologyEx(image,out5,MORPH_BLACKHAT,element);
    morphologyEx(image,out6,MORPH_ERODE,element);
    morphologyEx(image,out7,MORPH_DILATE,element);

    imshow("开运算",out1);
    imshow("闭运算",out2);
    imshow("形态学梯度",out3);
    imshow("顶帽",out4);
    imshow("黑帽",out5);
    imshow("腐蚀",out6);
    imshow("膨胀",out7);

    waitKey(0);
    return 0;
}  
