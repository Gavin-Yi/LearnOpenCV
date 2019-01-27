#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


//-----全局函数声明-----
static void on_ContrastAndBright(int, void *);
static void ShowHelpText();

//-----全局变量声明-----
int g_nContrastValue; //对比值
int g_nBrightValue; //亮度值
Mat g_srcImage, g_dstImage;

//-----函数定义-----
static void on_ContrastAndBright(int, void *)
{
    namedWindow("原始图", 1);

    for(int y=0; y<g_srcImage.rows; y++)
    {
        for(int x=0; x<g_srcImage.cols; x++)
        {
            for(int c=0; c<3; c++)
            {
                g_dstImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y,x)[c]) + g_nBrightValue);
            }
        }
    }

    imshow("原始图", g_srcImage);
    imshow("效果图", g_dstImage);
}

//-----主程序-----
int main()
{
    g_srcImage = imread("thersh.jpg");
    g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type() );

    g_nContrastValue = 80;
    g_nBrightValue = 80;

    namedWindow("效果图", 1);

    createTrackbar("对比度:", "效果图", &g_nContrastValue, 300, on_ContrastAndBright);
    createTrackbar("亮度:", "效果图", &g_nBrightValue, 200, on_ContrastAndBright);

    on_ContrastAndBright(g_nContrastValue, 0);
    on_ContrastAndBright(g_nBrightValue, 0);

    waitKey(0);
    return 0;
}  
