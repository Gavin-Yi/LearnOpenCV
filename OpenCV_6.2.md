# ***非线性滤波***
&ensp;&ensp;&ensp;&ensp;在很多情况下，使用邻域像素的非线性滤波会得到很好的效果。
&ensp;&ensp;&ensp;&ensp;比如在图像的噪声是散粒噪声而不是高斯噪声，即图像偶尔会出现很大的值的时候，用高斯滤波器对图像进行模糊的话，噪声颗粒是不会被去除的，它们只会转化为更为柔和但仍然可见的散粒。这就到了中值滤波上场的时候。
## ***中值滤波***
&ensp;&ensp;&ensp;&ensp;中值滤波的基本思想:用像素点邻域灰度值的中值来代替该像素点的灰度值。该方法在去除脉冲噪声、椒盐噪声的同时又能保留图像的边缘细节。
- 中值滤波与均值滤波的区别
**优势**：在均值滤波器中，由于噪声成分被放入平均计算中，所以输出受到了噪声的影响。但是在中值滤波器中，由于噪声成分很难被选上，所以几乎不会影响到输出。因此同样用``3x3``区域进行处理，中值滤波消除噪声的能力更胜一筹。中值滤波无论是在消除噪声还是在保存边缘方面都是一个不错的办法。
**劣势**：中值滤波花费的时间是均值滤波的5倍以上。

## ***双边滤波***
&ensp;&ensp;&ensp;&ensp;在双边滤波器中，输出像素的值依赖于邻域像素值的加权组合。
&ensp;&ensp;&ensp;&ensp;加权系数取决于定义域核和值域核的乘积。

## ***非线性滤波的API函数***
- 中值滤波:``medianBlur``函数
```c
    void medianBlur(InputArray src, OutputArray dst, int ksize);
```
&ensp;&ensp;&ensp;&ensp;第三个参数,``int``类型的``ksize``,孔径的线性尺寸，必须是大于1的奇数。
```c
    //示例
    Mat image = imread("1.jpg");
    Mat out;
    medianBlur(image, out, 7);
```
- 双边滤波:``bilateralFilter``函数
```c
    void vilateralBlur(InputArray src, OutputArray dst, int d, double sigmaColor, double sigmaSpace, int borderType=BORDER_DEFAULT);
```
&ensp;&ensp;&ensp;&ensp;第三个参数，``int``类型的``d``，表示每个像素邻域的直径。
&ensp;&ensp;&ensp;&ensp;第四个参数，``double``类型的``sigmaColor``，表示颜色空间滤波器的``sigma``值。
&ensp;&ensp;&ensp;&ensp;第五个参数，``double``类型的``sigmaSpace``，表示坐标空间滤波器的``sigma``值。

## ***五种图像滤波的比较***
&ensp;&ensp;&ensp;&ensp;方框滤波和均值滤波效果很相似，中值滤波对原图颠覆很大，而双边滤波和原图差别不大。