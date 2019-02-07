# **形态学滤波:开运算、闭运算、形态学梯度、顶帽、黑帽**
&ensp;&ensp;&ensp;&ensp;本节的主角是``OpenCV``中的``morphologyEX``函数，它利用基本的膨胀和腐蚀操作，来执行更高级的形态学变换。
## ***开运算***
&ensp;&ensp;&ensp;&ensp;开运算(Opening Operation),就是一个先腐蚀后膨胀的过程。
```c
    dst = open(src,element) = dilate(erode(src,element))
    //消除小物体，在纤细点处分离物体，平滑较大物体的边界
```
## ***闭运算***
&ensp;&ensp;&ensp;&ensp;闭运算(Closing Operation),就是一个先膨胀后腐蚀的过程。
```c
    dst = close(src,element) = erode(dilate(src,element))
    //可用来消除小型的黑洞
```
## ***形态学梯度***
&ensp;&ensp;&ensp;&ensp;形态学梯度（Morphological Gradient）是腐蚀图域膨胀图之差。数学表达式如下:
```c
    dst = morph-grad(src,element) = dilate(src,element) - erode(src,element)
```
&ensp;&ensp;&ensp;&ensp;对二值图像采取这一操作可以将团块的边缘突出出来，我们可以用形态学梯度来保留物体的边缘轮廓。

## ***顶帽***
&ensp;&ensp;&ensp;&ensp;顶帽运算(Top Hat)是原图像与开运算的结果图之差，数学表达式如下:
```c
    dst = tophat(src,element) = src - open(src,element)
```
&ensp;&ensp;&ensp;&ensp;因为开运算是放大了裂缝或者局部低亮度的区域，因此，从原图中减去开运算后的图像，得到的效果图也就是 ***突出了比原图轮廓周围的区域更明亮的区域*** ，且这一操作域选择的核的大小有关.
&ensp;&ensp;&ensp;&ensp;顶帽运算往往是用来分离比邻近点凉一点的斑块.

## ***黑帽***
&ensp;&ensp;&ensp;&ensp;黑帽运算(Black Hat)是闭运算的结果图与原图像之差。数学表达式如下:
```c
    dst = blackhat(src,element) = close(src,element) - src
```
&ensp;&ensp;&ensp;&ensp;黑帽运算后的效果图 ***突出了比原图像轮廓周围更暗的区域*** ,所以黑帽用来分离比邻近暗一点的斑块，效果图有着非常完美的轮廓。

## ***源码分析***
&ensp;&ensp;&ensp;&ensp;``morphologyEX``函数内部是一个大的``switch``语句,利用上述的数学表达式分别进行运算，十分简明。

## ***核心API函数: morphologyEX()***
```c
    void morphologyEX(
        InputArray src,
        OutputArray dst,
        int op,
        InputArray kernel,
        Point anchor = Point(-1,-1),
        int interations = 1,
        int borderType = BORDER_CONSTANT,
        const Scalar& borderValue = morphologyDefaultBorderValue()
    )
```
&ensp;&ensp;&ensp;&ensp;第三个参数，``int``类型的``op``，表示形态学运算类型.
|标识符|含义|
|-|-|
|``MORPH_OPEN``|开运算|
|``MORPH_CLOSE``|闭运算|
|``MORPH_GRADIENT``|形态学梯度|
|``MORPH_TOPHAT``|顶帽|
|``MORPH_BLACKHAT``|黑帽|
|``MORPH_ERODE``|腐蚀|
|``MORPH_DILATE``|膨胀|

&ensp;&ensp;&ensp;&ensp;第四个参数，``InputArray``类型的``kernel``，采用与上一节相同的做法，用``getStructuringElement``函数.

# **漫水填充**
## ***漫水填充的基本思想***
&ensp;&ensp;&ensp;&ensp;漫水填充法是一种用特定的颜色填充连通区域,通过设置可连通像素的上下限以及连通方式来达到不同的效果.
&ensp;&ensp;&ensp;&ensp;漫水填充经常用于标记或分离图像的一部分,以便进一步地处理和分析.
&ensp;&ensp;&ensp;&ensp;C++重写过的``FlodFill``函数有两个版本,一个带掩膜``mask``的版本，一个不带``mask``的版本.这个掩膜就是用于进一步控制哪些区域将被填充颜色。

## ***实现漫水填充算法:FlodFill函数***
```c
    int floodFill(
        InputOutputArray image, // 输入/输出1通道或3通道，8位或浮点图像
        InputOutputArray mask, // 单通道，8位，掩膜比原图像大两个像素点，漫水填充不会填充非零像素区域
        Point seedPoint, // 漫水填充算法的起始点
        Scalar newVal, // 像素点被染色的值
        Rect *rect = 0, // 函数将要重绘区域的最小边界矩形区域
        Scalar loDiff = Scalar(),
        Scalar upDiff = Scalar(),
        int flags = 4 // 4表示只考虑当前像素水平方向和垂直方向的相邻点
    )
```
# **图像金字塔与图片尺寸缩放**
## ***关于图像金字塔***
&ensp;&ensp;&ensp;&ensp;图像金字塔是图像中多尺度表达的一种，最主要用于图像的分割，是一种用多分辨率来解释图像的有效但概念简单的结构。

&ensp;&ensp;&ensp;&ensp;图像金字塔最初用于机器视觉和图像压缩，一幅图像的金字塔是一系列以金字塔形状排列的，分辨率逐渐降低且来源于同一张原始图的图像集合。金字塔底部是待处理的高分辨率表示，而顶部是低分辨率的近似。

- 高斯金字塔(GaussianPyramid)——用来向下采样,主要的金字塔
- 拉普拉斯金字塔(LaplacianPyramid)——用来从金字塔底层图像重建上层未采样图像,在数字图像处理中即是预测残差,可以对图像进行最大程度的还原.

&ensp;&ensp;&ensp;&ensp;要从金字塔第``i``层生成第``i+1``层图像，首先要用高斯核对 $G_{i}$进行卷积,然后删除偶数行和偶数列.新得到的图像的面积为原图像的四分之一。

- 对图像向上采样——``pyrUp``函数——将图像的尺寸放大,（实际在金字塔中是向下）
- 对图像向下采样——``pyrDown``函数——将图像的尺寸缩小

## ***高斯金字塔***
&ensp;&ensp;&ensp;&ensp;高斯金字塔是通过**高斯平滑**和**亚采样**获得一系列下采样图像.

- 对图像的下采样
(1)对图像$G_{i}$进行高斯内核卷积
(2)将所有偶数行和列去除

- 对图像的上取样
(1)将图像在每个方向上扩大为原来的两倍,新增的行和列以0填充
(2)使用先前相同的内核(乘以4)与放大后的图像卷积，获得新增元素的近似值
&ensp;&ensp;得到的图像即为放大后的图像，但是会发现新的图像比较模糊,因为在图像缩放的过程中丢失了一些信息.如果想在缩小和放大的过程中减少信息的丢失，这些数据就形成了拉普拉斯金字塔。

## ***拉普拉斯金字塔***
&ensp;&ensp;&ensp;&ensp;拉普拉斯金字塔第``i``层的数学定义：
$$L_{i}=G_{i}-UP(G_{i+1})\bigotimes g_{5x5}$$
&ensp;&ensp;&ensp;&ensp;式中的$G_{i}$表示第$i$层图像。而$UP()$是向上取样操作。符号$\bigotimes$表示卷积。$g_{5x5}$表示高斯内核。
&ensp;&ensp;&ensp;&ensp;也就是说拉普拉斯金字塔是通过源图像减去先缩小后再放大的图像的一系列图像构成的。

## ***尺寸调整:resize()函数***
&ensp;&ensp;&ensp;&ensp;``resize()``函数为专门用来调整图像大小的函数。
&ensp;&ensp;&ensp;&ensp;如果源图像设置了$ROI$，那么``resize()``函数会对源图像的$ROI$区域进行调整尺寸的操作，来输出到目标图像中。
&ensp;&ensp;&ensp;&ensp;如果目标图像中已经设置了$ROI$区域，不难理解``resize()``将会对源图像进行尺寸调整并填充到目标图像的$ROI$中。
```c
    void resize(
        InputArray src, // 输入图像
        OutputArray dst, // 输出图像
        Size dsize, // 输出图像的大小
        double fx = 0,
        double fy = 0,
        int interpolation = INTER_LINEAR // 插值方式
    )
```
```c
    // 示例一
    resize(srcImage, dstImage, dstImage.size())
```
```c
    // 示例二
    resize(srcImage, dstImage, Size(), 0.5, 0.5)
```
## ***图像金字塔相关API函数***
#### ***1.向上采样：pyrUp()函数***
```c
    // 作用是向上采样并模糊一张照片，说白了就是放大一张照片
    void pyrUp(
        InputArray src,
        OutputArray dst,
        const Size& dstsize = Size(),
        int borderType = BORDER_DEFAULT
    )
```
```c
    // 示例
    pyrUp(tmpImage, dstImage, Size(tmpImage.cols*2, tmpImage.rows*2))
```

#### ***2.采样：pyrDowm()函数***
```c
    // 作用是向下采样并模糊一张照片，即缩小一张照片
    void pyrDown(
        InputArray src,
        OutputArray dst,
        const Size& dsize = Size(),
        int borderType = BORDER_DEFAULT
    )
```
```c
    // 示例
    pyrDown(tmpImage, dstImage, Size(tmpImage.cols/2, tmpImage.rows/2))
```
