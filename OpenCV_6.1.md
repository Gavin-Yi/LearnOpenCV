# **图像处理**
- 三种均值滤波: 方框滤波、均值滤波、高斯滤波
- 两种非线性滤波: 中值滤波、双边滤波
- 七种图像处理形态学: 腐蚀、膨胀、开运算、闭运算、形态学梯度、顶帽、黑帽
- 满水填充
- 图像缩放
- 图像金字塔
- 阈值化

# **线性滤波**
## ***线性滤波的简介***
&ensp;&ensp;&ensp;&ensp;线性滤波器： 线性滤波器经常用于剔除输入信号中不想要的频率或者从许多频率中选择一个想要的频率。
&ensp;&ensp;&ensp;&ensp;几种常见的线性滤波器:
- 低通滤波器
- 高通滤波器
- 带通滤波器
- 带阻滤波器
- 全通滤波器：允许所有频率通过，仅改变相位关系。
- 陷波滤波器（Band-Stop Filter）:阻止一个狭窄频率通过，是一种特殊的带阻滤波器。
## ***滤波和模糊***
&ensp;&ensp;&ensp;&ensp;滤波是将信号中特定波段频率滤除的操作，是抑制和防止干扰的一项重要措施。
&ensp;&ensp;&ensp;&ensp;以高斯滤波为例。滤波可以分为低通滤波和高通滤波两种：高斯滤波是指用高斯函数作为滤波函数的滤波操作，至于是不是模糊，要看是高斯低通还是高斯高通，**低通就是模糊，高通就是锐化**。
- 高斯滤波是指利用高斯函数作为滤波函数的滤波操作
- 高斯模糊就是高斯低通滤波
## ***线性邻域滤波***
$$ g(i,j)=\sum_{k,l}f(i+k,j+l)h(k,l)$$
$$ g = \sum f*h$$
&ensp;&ensp;&ensp;&ensp;线性滤波处理的输出像素值$g(i,j)$是输入值$f(i+k,j+l)$的加权和。
&ensp;&ensp;&ensp;&ensp;$f$表示输入像素值，$h$表示加权系数“核”,$g$表示输出像素值
&ensp;&ensp;&ensp;&ensp;``OpenCV3``中有三种常用的线性滤波函数:
- 方框滤波——``boxblur``函数
- 均值滤波——``blur``函数
- 高斯函数——``GaussianBlur``函数
## ***方框滤波(box Filter)***
```c
    void boxFilter(InputArray src, OutputAraay dst, int ddepth, Size ksize, Point anchor=Point(-1,-1), boolNormalize=true, int borderType=BORDER_DEFAULT );
```
- 第一个参数,``InputArray``类型的``src``.可以是任意通道数的图片,待处理的图片深度应该为``CV_8U``、``CV_16U``、``CV_16S``、``CV_32F``以及``CV_64F``之一。
- 第二个参数，``OutputArray``类型的``dst``.需要和原图片有一样的尺寸和类型。
- 第三个参数，``int``类型的``ddepth``,输出图像的深度,``-1``表示使用原图的深度。
- 第四个参数，``Size``类型的``ksize``,内核的大小。
- 第五个参数，``Point``类型的``anchor``，表示锚点，即被平滑的那个点,它有默认值``Point(-1,-1)``,表示锚点在核的中心
- 第六个参数，``bool``类型的``Normalize``，默认值为``true``，表示内核区域内是否被 ***归一化*** 。
- 第七个参数，``int``类型的``borderType``，用于推断外部像素的某种边界模式，一般不管这个参数。

&ensp;&ensp;&ensp;&ensp;``BoxFliter()``函数方框滤波所用的核表示如下：
$$ K=\alpha \left[\begin{matrix} 1&1&1&...&...&1&1\\1&1&1&...&...&1&1\\...&...&...&...&...&...&...\\1&1&1&...&...&1&1 \end{matrix}\right]$$
&ensp;&ensp;&ensp;&ensp;其中：
$$ \alpha = \begin{cases}\frac{1}{ksize.width*ksize.height},当normalize=true时\\1,当normalize=false时 \end{cases}$$
&ensp;&ensp;&ensp;&ensp;当``normalize=true``时，方框滤波就变成了均值滤波。归一化就是要把要处理的量缩放到一个范围内。

## ***均值滤波***
```c
    void blur(InputArray src, OutputAraay dst, int ddepth, Size ksize, Point anchor=Point(-1,-1), boolNormalize=true, int borderType=BORDER_DEFAULT );
```
&ensp;&ensp;&ensp;&ensp;均值滤波就是归一化的方框滤波，用模板中全体像素的平均值来替代锚点的像素值。
&ensp;&ensp;&ensp;&ensp;均值滤波在图像去噪的同时，也破坏了图像的细节,从而使图像变得模糊。

## ***高斯滤波***
- 高斯滤波理论简介 
&ensp;&ensp;&ensp;&ensp;一维零均值高斯函数如下:
$$G(x)=exp(-x^2/(2sigma^2))$$
&ensp;&ensp;&ensp;&ensp;其中，高斯分布参数``Sigma``决定了高斯函数的宽度。对于图像处理来说，常用二维零均值离散高斯函数作为平滑滤波器。
$$G_{0}(x,y)=Ae^{\frac{-(x-u_{x})^2}{2(\sigma_{x})^2}+\frac{-(y-u_{y})^2}{2(\sigma_{y})^2}}$$
- 高斯滤波:``GaussianBlur``函数
&ensp;&ensp;&ensp;&ensp;``GaussianBlur``函数的作用是用高斯滤波器来模糊一张照片，对输入的图像``src``进行高斯滤波后用``dst``输出。它将源图像和指定的高斯核函数做卷积运算。
```c
    void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT);
```
- 第三个参数，``Size``类型的``ksize``高斯内核的大小。其中``ksize.width``和``ksize.height``可以不同，但它们必须为正数和奇数,或者是0,这都由``sigma``计算得到。
- 第四个参数，``double``类型的``sigmaX``，表示高斯核函数在X轴方向上的标准偏差。
- 第五个参数，``double``类型的``sigmaY``，表示高斯核函数在Y轴方向上的标准偏差。