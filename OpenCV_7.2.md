# **霍夫变换**
&ensp;&ensp;霍夫变换(Hough Transform)是图像处理中的一种特征提取技术，该过程在一个参数空间中通过计算累计结果的局部最大值得到一个符合该特定形状的集合来作为霍夫变换的结果。

## ***OpenCV中的霍夫线变换***
&ensp;&ensp;OpenCV中的霍夫线变换有如下三种:
- 标准霍夫变换(Standard Hough Transform, SHT),由``HoughLines``调用。
- 多尺度霍夫变换(Muti-Scale Hough Transform, MSHT),由``HoughLines``调用
- 累计概率霍夫变换(Progressive-Propability Hough Transform， PPHT),由``HoughLinesP``调用。
&ensp;&ensp;PPHT的执行效率更高，所以更倾向于使用``HoughLinesP``函数。

## ***霍夫线变换的原理***
&ensp;&ensp;在极坐标中，直线的方程可以表示为：
$$r=xcos\theta+ysin\theta$$
&ensp;&ensp;对于一个特定的点$(x_{0},y_{0})$,可以将通过这一点的一族直线定义为:
$$r_{\theta}=x_{0}cos\theta+y_{0}sin\theta$$
&ensp;&ensp;在极径-极角平面绘制这一族直线，可以得到一条正弦曲线。我们可以对图像中的所有点都进行这一操作。
&ensp;&ensp;如果两个曲线交于一个点，说明这两个点通过同一条直线。而越多的曲线交于一点，表示这条直线由更多的点组成。
&ensp;&ensp;这就是霍夫线变换要做的。追踪图像中每个点对应曲线区间的交点，如果交于一点的曲线数量超过了阈值，那么可以认为这个交点所代表的参数$(\theta,r)$在原图像中为一条直线。

## ***标准霍夫变换：HoughLines()函数***
```c
    void HoughLines(
        InputArray image, // 需要8位单通道二进制图像
        OutputArray lines,
        double rho,
        double theta,
        int threshold, // 累计平面的阈值参数
        double srn = 0,
        double stn = 0
    )
```

## ***累计概率霍夫变换：HoughLinesP()函数***
```c
    void HoughLinesP(
        InputArray image,
        OutputArray lines,
        double rho,
        double theta,
        int threshold,
        double minLineLength = 0, // 最低线段的长度
        double maxLineGap = 0 // 允许将同一行点与点之间连接起来的最大距离 
    )
```
## ***霍夫圆变换***
&ensp;&ensp;对霍夫圆变换，与线变换相比，由二维的极径极角空间变为三维的圆心点$x$、$y$和半径$r$空间取代。在$OpenCV$中，我们通过一种叫做”霍夫梯度法“的方法解决圆变换的问题。

## ***霍夫圆变换:HoughCircles()函数***
&ensp;&ensp;霍夫圆变换和线变换相比，比较明显的一个区别是不需要源图像是二值的，而``HoughLines``和``HoughLinesP``都需要源图像为二值图像。
```c
    void HoughCircles(
        InputArray image,
        OutputArray circles, // 圆的输出矢量，每个矢量由包含3个元素的浮点矢量表示
        int method, // 目前OpenCV中就只有霍夫梯度法可用，标识符为HOUGH_GRADIENT
        double dp,
        double minDist, // 区分霍夫变换检测到的圆的圆心之间的最小距离
        double param1 = 100, // 表示传递给canny算子的高阈值
        double param2 = 100, // (累加器阈值)越小，可以检测到更多根本不存在的圆，越大，检测到的更接近完美的圆形。
        int minRadius = 0,
        int maxRadius = 0
    )
```
