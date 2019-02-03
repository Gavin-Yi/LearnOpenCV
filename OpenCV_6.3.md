## **形态学滤波：腐蚀与膨胀**
&ensp;&ensp;&ensp;&ensp;形态学操作就是基于形状的一系列图像处理操作。最基本的形态学操作有两种，分别是：``膨胀（dilate）``与``腐蚀（erode）``.
&ensp;&ensp;&ensp;&ensp;腐蚀与膨胀能实现多种多样的功能，主要如下:
- 消除噪声
- 分割（isolate）独立图元，在图像中，连接（join)相邻元素
- 寻找图像中的明显的极大值区域或极小值区域
- 求出图像的梯度

&ensp;&ensp;&ensp;&ensp;注意！腐蚀和膨胀是对白色部分（高亮部分）而言的，不是黑色部分。膨胀是图像中的高亮部分进行膨胀，类似于”领域扩张“，效果图比原图拥有更大的高亮区域;腐蚀是原图中的高亮部分被腐蚀，类似于”领域被蚕食“.

## ***膨胀***
&ensp;&ensp;&ensp;&ensp;``膨胀（dilate）``就是求局部最大值的操作。核B与图形卷积，即计算核B覆盖的区域的像素点的最大值，并把这个最大值赋值给参考点指定的像素。这样图像中的高亮区域会逐渐增长。

## ***腐蚀***
&ensp;&ensp;&ensp;&ensp;``腐蚀(erode)``就是求局部最小值的操作。与``膨胀(dilate)``刚好相反。

## ***相关核心API函数***
### ***膨胀：dilate函数***
```c
    void dilate(
        InputArray src,
        OutputArray dst,
        InpuArray kernel,
        Point anchor=Point(-1,-1),
        int iterations=-1,
        int borderType=BORDER_DEFAULT,
        const Scalar& borderValue=morphologyDefaultBorderValue()
    )
```
&ensp;&ensp;&ensp;&ensp;第三个参数，``InputArray``类型的``kernel``，膨胀操作的核，当为``NULL``时，表示的是使用参考点位于中心的``3x3``的核。
&ensp;&ensp;&ensp;&ensp;一般使用函数``getStructuringElement``配合这个参数的使用。``getStructuringElement``函数会返回指定形状和尺寸的结构元素。
&ensp;&ensp;&ensp;&ensp;``getStructuringElement``函数的第一个参数表示内核的形状，有如下，有如下三种形状可以选择:
- 矩形:MORPH_RECT
- 交叉形:MORPH_CROSS
- 椭圆形:MORPH_ELLIPSE
&ensp;&ensp;&ensp;&ensp;而第二和第三个参数分别是内核的尺寸以及锚点的位置，实际使用时，用一个``Mat``类型的``element``变量来保存上述函数的返回值。

&ensp;&ensp;&ensp;&ensp;使用``dilate``函数，***一般只需要填前面三个参数***，后面的四个参数都有默认值。

### ***腐蚀:erode函数***
```c
    void dilate(
        InputArray src,
        OutputArray dst,
        InpuArray kernel,
        Point anchor=Point(-1,-1),
        int iterations=-1,
        int borderType=BORDER_CONSTANT,
        const Scalar& borderValue=morphologyDefaultBorderValue()
    )
```
&ensp;&ensp;&ensp;&ensp;使用``erode``函数与``dilate``函数大体上完全一致。