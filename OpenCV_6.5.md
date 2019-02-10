# **阈值化**
&ensp;&ensp;&ensp;&ensp;图像分割的基本操作，将图像中每一个像素点的灰度值与阈值进行比较,并作出相应的判断。
&ensp;&ensp;&ensp;&ensp;在$OpenCV$中，``Threshold()``函数和``adaptiveThreshold()``函数可以完成这样的操作.它们的基本思想是：给定一个阈值和数组,然后根据数组中的每一个值是高于还是低于阈值进行操作。

## ***固定阈值操作:Threshold()函数***
&ensp;&ensp;&ensp;&ensp;函数``Threshold()``对单通道数组应用固定阈值操作.该函数的典型应用是对灰度图像进行阈值操作得到二值图像,或者是去掉噪声,例如过滤掉很小或者是很大的像素点。
```c
    double threshold(
        InputArray src,
        OutputArray dst,
        double thresh,
        double maxval, // 具体使用方法与type有关
        int type // 阈值类型
    )
```
- **THRESH_BINARY**
$$dst(x,y)=\begin{cases}
maxval & src(x,y) > thresh \\
0 & otherwise \\
\end{cases}
$$

- **THRESH_BINARY_INV**
$$dst(x,y)=\begin{cases}
0 & src(x,y)>thresh \\
maxval & otherwise
\end{cases}
$$

- **THRESH_TRUNC**
$$dst(x,y)=\begin{cases}
threshold & src(x,y)>thresh \\
src(x,y) & otherwise \\
\end{cases}
$$

- **THRESH_TOZERO**
$$dst(x,y)=\begin{cases}
src(x,y) & src(x,y)>thresh \\
0 & otherwise \\
\end{cases}
$$

- **THRESH_TOZERO_INV**
$$dst(x,y)=\begin{cases}
0 & src(x,y)>thresh \\
src(x,y) & otherwise \\
\end{cases}
$$

## ***自适应阈值操作:adaptiveThreshold***
```c
    void adaptiveThreshold(
        InputArray src,
        OutputArray dst,
        double maxValue,
        int adaptiveMethod, // 自适应阈值算法(ADPATIVE_THRESH_MEAN_C和ADAPTIVE_THRESH_GAUSSIAN_C)
        int thresholdType, // 阈值类型
        int blockSize, // 用于计算阈值大小的一个像素的邻域尺寸
        double C // 被减的常数值
    )
```