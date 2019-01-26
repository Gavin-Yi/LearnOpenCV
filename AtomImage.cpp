#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

#define WINDOW_NAME "[绘制图1]"
#define WINDOW_WIDTH 600

//-----全局函数声明-----
void DrawEllipse(Mat img, double angle);
void DrawFilledCircle(Mat img, Point center);
void Draw(Mat img, Point start, Point end);

//-----全局变量声明-----


//-----函数定义-----
void DrawEllipse(Mat img, double angle)
{
    int thickness = 2; //线宽
    int lineType = 8; //线型，8为联通线型

    ellipse(
        img,
        Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2),  //中心点
        Size(WINDOW_WIDTH/4, WINDOW_WIDTH/16), //大小
        angle, //椭圆旋转角度
        0,
        360, //扩展的弧度从0到360
        Scalar(255, 129, 0), //图形颜色为蓝色
        thickness,
        lineType
    );
}

void DrawFilledCircle(Mat img, Point center)
{
    int thickness = -1; //由线粗定义的实心
    int lineType = 8;

    circle(
        img,
        center,
        WINDOW_WIDTH/32,
        Scalar(0, 0, 255),
        thickness,
        lineType
    );
}

void Draw(Mat img, Point start, Point end)
{
    int thickness = 2;
    int lineType = 8;
    line(
        img,
        start,
        end,
        Scalar(0, 0, 0),
        thickness,
        lineType
    );
}

//-----主程序-----
int main()
{
    Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

    DrawEllipse(atomImage, 90);
    DrawEllipse(atomImage, 0);
    DrawEllipse(atomImage, 45);
    DrawEllipse(atomImage, -45);

    DrawFilledCircle(atomImage, Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2));
    
    imshow(WINDOW_NAME,atomImage);
    waitKey(0);
    
    return 0;
}  
