# **第四章 OpenCV数据结构与基本绘图(二)**

## **基本图形的绘制**
- 用于绘制直线的``line``函数
- 用于绘制椭圆的``ellipse``函数
- 用于绘制矩形的``rectangle``函数
- 用于绘制圆的``cirlce``函数
- 用于绘制填充的多边形的``fillPoly``函数

## **DrawEllipse()函数的写法**
```c
//  自定义的绘制函数，实现绘制不同角度，相同尺寸的椭圆
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
```
## **DrawFilledCircle()函数的写法**
```c
//自定义的绘制函数，实现实心圆的绘制
void DrawFilledCircle(Mat img, Point center)
{
    int thcikness = -1; //由线粗定义的实心
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
```

## **DrawLine()函数的写法**
```c
//自定义的绘制函数，实现线的绘制
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
```