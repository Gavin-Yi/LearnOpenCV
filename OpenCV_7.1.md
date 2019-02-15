# **图像变换**
##### &ensp;&ensp;&ensp;&ensp;本章关注的重点是图像变换(image transform),即将一张图像转变成图像数据的另一种表现形式。变换最常见的例子就是傅里叶变换，这类操作的结果仍然保存为OpenCV图像结构的形式，但是新图像的每个单独像素表示原始图像输出的频谱分量，而不是通常所考虑的空间分量。
- 基于OpenCV的边缘检测
- 霍夫变换
- 重映射
- 仿射变换
- 直方图均衡化

## **基于OpenCV的边缘检测**
&ensp;&ensp;&ensp;&ensp;边缘检测的各种算子和滤波器——``Canny``算子、``Sobel``算子、``Laplacian``算子以及``Scharr``滤波器。

### ***边缘检测的一般步骤***
- [第一步]滤波
&ensp;&ensp;边缘检测的算法主要是基于图像强度的一阶和二阶导数，但导数通常对噪声很敏感，因此必须采用滤波器来改善与噪声有关的边缘检测器的性能。

- [第二步]增强
&ensp;&ensp;增强边缘的基础是确定图像各点邻域强度的变化值。增强算法可以将图像灰度点邻域强度有显著变化的点凸显出来。

- [第三步]检测
&ensp;&ensp;经过增强的图像，往往邻域中有很多点的梯度值较大，所以应该采用某种方法方法来对这些点进行取舍，实际应用中常用的方法是通过阈值化来检测。

### ***Canny算子***
&ensp;&ensp;&ensp;&ensp;目前最优的边缘检测算法。

- Canny边缘检测的步骤
&ensp;&ensp;(1)消除噪声
&ensp;&ensp;&ensp;&ensp;高斯平滑滤波器卷积降噪
&ensp;&ensp;(2)计算梯度幅值和方向
&ensp;&ensp;&ensp;&ensp;按照``Sobel``滤波器的步骤来操作。（略）
&ensp;&ensp;(3)非极大值抑制
&ensp;&ensp;&ensp;&ensp;这一步排除非边缘像素，仅仅保留一些细线条。
&ensp;&ensp;(4)滞后阈值
&ensp;&ensp;&ensp;&ensp;最后一步，``Canny``使用了滞后阈值，滞后阈值需要两个阈值(高阈值和低阈值)
&ensp;&ensp;&ensp;&ensp;a.若某一像素位置的幅值超过高阈值，该像素被保留为边缘像素。
&ensp;&ensp;&ensp;&ensp;b.若某一像素位置的幅值小于低阈值，该像素被排除。
&ensp;&ensp;&ensp;&ensp;c.若某一像素位置的幅值介于两个阈值之间，该像素仅仅在连接到一个高于高阈值的像素时被保留。

### ***Canny边缘检测：Canny()函数***
```c
// Canny函数原型
    void Canny(
        InputArray image,
        OutputArray edges, // 输出的边缘图
        double threshold1, // 第一个滞后性阈值，推荐的高低阈值比在2:1和3:1之间
        double threshold2, // 第二个滞后性阈值
        int apertureSize = 3, // Sobel算子的孔径大小
        bool L2gradient = false
    )
```

```c
// 最简单的canny用法，拿到原图后直接使用
// 此方法在Opencv3中已禁用，Opencv2中可用
    Canny(srcimage, srcimage, 150, 100 ,3);
```

```c
// 高阶的Canny用法，转换成灰度图，降噪，用canny，最后将得到的边缘作为掩码，拷贝原图到效果图上，
// 得到彩色边缘图
    Mat dst, edge, gray;
    // 将图像转换为灰度图
    cvtColor(src, gray, COLOR_BGR2GRAY);
    // 先使用3x3的内核降噪
    blur(gray, edge ,size(3,3));
    // canny算子
    Canny(edge, edge, 3, 9, 3);

    dst = Scalar::all(0);
    // 用边缘图作为掩码，将原图拷贝至dst
    src.copyTo(dst, edge);
    
```

### ***sobel算子***
&ensp;&ensp;&ensp;&ensp;``Sobel``算子是一个主要用于边缘检测的离散微分算子。它结合了高斯平滑和微分求导，用来计算灰度图像的近似梯度。

### ***Sobel()函数***
```c
// Sobel函数使用扩展的Sobel算子，来计算一阶、二阶、三阶或混合图像差分
    void Sobel(
        InputArray src,
        OutputArray dst,
        int ddepth,
        int dx, // x方向上的差分阶数
        int dy, // y方向上的差分阶数
        int ksize = 3, // Sobel核的大小，必须取奇数，默认为3
        double scale = 1,
        double delta = 0,
        int borderType = BORDER_DEFAULT
    )
```

### ***Laplacian算子***
&ensp;&ensp;``Laplacian``算子是n微欧几里德空间中的一个二阶微分算子。根据图像处理的原理可知，二阶导数可以用来检测边缘。使用Laplacian算子会使求导过程变得简单。让一幅图像减去它的拉普拉斯算子可以增强对比度。

### ***Laplacian()函数***
```c
    void Laplacian(
        InputArray src,
        OutputArray dst,
        int ddepth,
        int ksize = 1, // 用于计算二阶导数到滤波器的孔径大小
        double scale = 1,
        double delta = 0,
        int borderType = BORDER_DEFAULT
    )
```

### ***Scharr滤波器***
&ensp;&ensp;称之为滤波器，而不是算子。它在OpenCV中主要是配合Sobel算子的运算而存在的。
```c
// 计算图像差分:Scharr()函数
    void Scharr(
        InputArray src,
        OutputArray dst,
        int ddepth,
        int dx, // x方向的差分阶数
        int dy, // y方向的差分阶数
        double Scale = 1, // 缩放因数
        double delta = 0,
        int borderType = BORDER_DEFAULT
    )
```
```c
// 示例，分别求x和y方向的梯度，并合并梯度
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y, dst;
    //载入源图像
    Mat src = imread(”1.jpg“);
    //求x方向梯度
    Scharr(src, grad_x, CV_16S, 1, 0);
    convertScaleAbs(grad_x, abs_grad_x);
    imshow("X方向Scharr", abs_grad_x);
    //求y方向梯度
    Scharr(src, grad_y, CV_16S, 1, 0);
    convertScaleAbs(grad_y, abs_grad_y);
    imshow(”Y方向Scharr“, abs_grad_y);
    //合并梯度
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
```
