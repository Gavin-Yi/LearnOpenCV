# **ROI区域图像叠加&图像混合**
##  ***感兴趣区域:ROI***
&ensp;&ensp;&ensp;&ensp;定义ROI的方式由两种：
```c
    //方法一
    Mat imgROI;
    imgROI = image(Rect(500, 250, logo.cols, logo.rows))
    //Rect()指定矩形的左上角坐标和矩形的长宽.先长后宽
```
```c
    //方法二
    imgROI = image(Range(250,250+logo.rows), Range(200,200+logo.cols));
    //先行后列
```

## ***计算数组加权和:addWeighted()函数***
```
    void(ImputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype=-1)
```
&ensp;&ensp;&ensp;&ensp;两个图形矩阵必须具有相同的尺寸和类型，不然做加权求和时多余部分无法配对，肯定会出问题。

## ***高级图像融合和初级图像融合***
&ensp;&ensp;&ensp;&ensp;初级图像融合直接使用ROI和``addWeighted()``函数，高级图像融合使用``mask``掩膜，用``bitwise_not()``函数将白色背景变黑，而``(0, 0, 0)``在求和时不影响原图。
```c
    Mat srcImage1 = imread("thersh.jpg");
    Mat srcImage2 = imread("logo.jpg");

    Mat imgROI = srcImage1(Rect(200,250,srcImage2.cols,srcImage2.rows));
    Mat mask = imread("logo.jpg",0); //必须是灰度图
    bitwise_not(mask,mask); //黑色变白色
    srcImage2.copyTo(imgROI,mask); //掩膜复制到ROI

    namedWindow("高级融合");
    imshow("高级融合",srcImage1);
```

# **分离颜色通道、多通道图像混合**
&ensp;&ensp;&ensp;&ensp;有时需要对RGB三个颜色通通道的分量进行分别显示和调整，通过OpenCV的``split``和``merge``方法可以很方便地达到目的。

## ***通道分离:split()函数***
&ensp;&ensp;&ensp;&ensp;``split()``函数的C++版本有两个原型：
```c
    void split(const Mat& , Mat* ); //常用
    void split(InputArray , OutputArrays );
```
&ensp;&ensp;&ensp;&ensp;示例:
```c
    Mat imgROI;
    vector<Mat> channels;
    
    split(srcImage, channels); // 分离色彩通道
    imgROI = channels.at(0); //选取B(blue)通道
```

## ***通道合并:merge()函数***
&ensp;&ensp;&ensp;&ensp;将多个数组合并成一个多通道数组，C++函数原型为：
```c
    void merge(const Mat* mv, size_t count, OutputArray dst);
```
- 第一个参数,``mv``。填需要被合并的输入矩阵或``vector``容器的阵列。这个``mv``参数中所有矩阵的尺寸必须一样。
- ``count``代表输入矩阵的个数，必须大于等于1.
- ``dst``代表输出矩阵，和``mv[0]``具有一样的尺寸和深度，通道数量是矩阵阵列中的通道总数.
```c
    split(srcImage, channels); 
    imgBlue = channels.at[0]; // 注意:这里是引用，也就是一个改变，另一个会跟着改变

    addWeighted(imgBlue(Rect(500,300,logo.cols,logo.rows)), 0.5, logo, 0.5, 0.0, imgBlue(Rect(500,300,logo.cols,logo.rows))); //对蓝色通道进行加权求和操作

    merge(channels,srcImage); // 将三个单通道合并为一个三通道
```

# **图像对比度、亮度值调整**
&ensp;&ensp;&ensp;&ensp; ***算子***：一般的图像处理算子都是一个函数，它接受一个或多个输入图像，并产生输入图像.

$$ g(x) = a*f(x)+b $$
