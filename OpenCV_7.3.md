# **重映射**

## ***重映射的概念***
&ensp;&ensp;重映射，就是吧一幅图像中某位置的像素放置到另一幅图像指定的位置。因为源图像与目标图像的像素坐标不是一一对应的，所以一般是需要经过函数变化。

## ***实现重映射：remap()函数***
```c
    void remap(
        InputArray src, // 输入原图像
        OutputArray dst, // 函数输出结果
        InputArray map1, // 点(x,y)的一个映射，或者类型值
        InputArray map2,
        int interpolation, // 插值方式
        int borderMode = BORDER_CONSTANT, // 边界模式，默认即可
        const Scalar& borderValue = Scalar()
    )
```
# **仿射变换**
&ensp;&ensp;&ensp;&ensp;仿射变换，一个向量空间进行一次向量变换再接上一个平移，变换为另一个向量空间的过程。

&ensp;&ensp;&ensp;&ensp;一个任意的仿射变换都可以表示为乘上一个矩阵（线性变换），接着再加上一个向量（平移）的形式。

&ensp;&ensp;&ensp;&ensp;与机器人学的位姿变换、齐次变换矩阵有着极大的相似。

&ensp;&ensp;&ensp;&ensp;用仿射变换可以表示如下三种常见的变换形式：
- 旋转，$Rotation$(线性变换)
- 平移，$Translation$(向量加)
- 缩放，$Scale$(线性变换)

## ***进行仿射变换:warpAffine()函数***
```c
    void warpAffine(
        InputArray src,
        OutputArray dst,
        InputArray M, // 2x3的变换矩阵（即旋转矩阵+平移向量）
        Size dsize, // 输出图像的尺寸
        int flags = INTER_LINEAR, 
        int borderMode = BORDER_CONSTANT,
        const &Scalar borderValue = Scalar()
    )
```

## ***计算二维旋转变换矩阵:getRotationMatrix2D()函数***
```c
    Mat getRotationMatrix2D(
        Point2f center, // 源图像的旋转中心
        double angle, //逆时针的旋转角度
        double scale //缩放系数
    )
```
# **直方图的均衡化**

## ***直方图均衡化的概念与特点***
&ensp;&ensp;&ensp;&ensp;直方图均衡化是灰度变换的一个重要应用。图像的像素灰度变化是随机的,直方图的图形高低不齐，直方图均衡化就是用一定的算法使直方图大致平和的方法.

&ensp;&ensp;&ensp;&ensp;直方图均衡化是通过拉伸像素强度的分布范围，来增强图像的对比度的一种方法。经过均衡化的直方图，频谱更加舒展（傅里叶变换）。

## ***实现直方图均衡化:equalizeHist()函数***
```c
    void equalizeHist(
        InputArray src, // 8位单通道图像
        OuputArray dst
    )
```
