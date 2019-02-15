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
    Mat src = imread("thersh.jpg");

    Mat dst, gray, edge;

    dst.create(src.size(), src.type());

    cvtColor(src, gray, COLOR_BGR2GRAY);

    blur(gray, edge, Size(3,3));

    Canny(edge, edge, 3, 9, 3);

    dst =  Scalar::all(0);

    src.copyTo(dst, edge);

    imshow("原图", src);
    imshow("效果图", dst);
    
    waitKey(0);
    return 0;
}  
