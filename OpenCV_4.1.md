# **第四章 OpenCV数据结构与基本绘图(一)**
## ***图像容器Mat***
- OpenCV的C++接口不需要考虑内存释放问题
- 使用 clone()或者 copyTo()来复制图像的矩阵
## ***像素值的存储方法***
- RGB方式，对应红绿蓝，有时加入Alpha（透明度）
- HSV和HLS方式，对应色调、饱和度和亮度/明度。
## ***创建Mat对象的方法***
- 使用构造函数
```c
    Mat  M(2, 2, CV_8UC3, Ssclar(0,0,255));
    //8UC3 8位unsigned char,3通道
```
- 复制
```c
    Mat M = N.clone();
    //使用clone()或者copy To()
```
## ***常用数据结构和函数***
- Point类 ***点的表示***
```c
    Point point;
    point.x=10;
    point.y=8;
```
或者
```c
    Point point = Point(10,8);
```
- Scalar类 ***颜色的表示***
    
    ``Scalar()``表示具有4个元素的数组，用于传递像素值，如RGB颜色值。
```c
    Scalar(a, b, c)
    //常用的是 Scalar_<double> ,这就是为什么很多函数的参数输入可以是 Mat，也可以是 Scalar
```
- Size类 ***尺寸的表示***
```
    Size(width, height)
```
- Rect类 ***矩形的表示***
```c
    Rect(x, y, width, height)
    //分别为左上角的坐标和矩形的宽和高
```

&ensp;常用的成员函数有：

``Size()`` 返回值Size;
    
``area()`` 返回矩形的面积

``contains(Point)`` 判断点是否在矩形内

- 颜色空间转换：``cvtColor()``函数    
```c
    cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
    //OpenCV默认的图片存储顺序是BGR，即蓝绿红，而不是RGB
```
