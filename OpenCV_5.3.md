# **离散傅里叶变换**
&ensp;&ensp;&ensp;&ensp;离散傅里叶变换（DFT）,是指傅里叶变换在时域和频域上都呈现离散的形式,将时域信号的采样变换为在离散时间傅里叶变换（DTFT）频域的采样。即使对有限长的离散信号做DFT，也应当对其经过周期延拓为周期信号之后再进行变换。在实际应用中，通常采用快速傅里叶变换来高效计算DFT。

## ***离散傅里叶变换的原理***
$$F(k,l)=\sum_{i=0}^{N-1}\sum_{j=0}^{N-1}f(i,j)e^{-i2\pi(\frac{ki}{N}+\frac{lj}{N})} $$
$$ e^ix = cosx+i*sinx$$
&ensp;&ensp;&ensp;&ensp;在实际的图像处理过程中，仅仅使用了幅度图像，因为幅度图像包含了原图像的几乎所有我们需要的集合信息。然而如果想通过修改幅度图像来修改原图像信息，就必须使用逆傅里叶变换得到修改后的图像，这样就必须同时保留幅度图像和相位图像。

&ensp;&ensp;&ensp;&ensp;在频域里面，对于一幅图像，高频部分代表了图像的细节、纹理信息;低频部分代表了图像的轮廓信息。

&ensp;&ensp;&ensp;&ensp;傅里叶变换在图像处理中可以做到图像增强与图像去噪、图像分割之边缘检测、图像特征提取、图像压缩等。

# **输入输出XML和YAML文件**
## ***XML和YAML文件简介***
&ensp;&ensp;&ensp;&ensp;XML，翻译成中文为"可扩展标识语言"。
&ensp;&ensp;&ensp;&ensp;YAML，译为“YAML不是一种置标语言”

## ***FileStorage类操作文件的使用引导***
&ensp;&ensp;&ensp;&ensp;我们一般使用如下过程来写入和读取数据到XML或YAML文件中。

&ensp;&ensp;(1)实例化一个``FileStorage``类的对象，用默认带参数的构造函数完成初始化或者用``FileStorage::open()``成员函数辅助初始化。

&ensp;&ensp;(2)使用流操作符``<<``进行文件写入操作，或者``>>``进行文件读取操作，类似C++的文件输入输出流。

&ensp;&ensp;(3)使用``FileStorage::release()``函数析构掉``FileStorage``类对象，同时关闭文件。

#### 第一步:XML、YAML文件的打开
- 准备文件写操作
&ensp;&ensp;构造函数为``FileStorage::FileStorage``,有如下两个重载：
```c
    FileStorage();
    FileStorage(const string& source, int flags, const string& encoding=string() );
```

&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;对于第二种带参数的重载，有示例：
```c
    FileStorage fs("abc.xml", FileStorage::WRITE );
```
&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;对于第一种不带参数的重载，有示例：
```c
    FileStorage fs;
    fs.open("abc.xml", FileStorage::WRITE);
```
- 准备文件读操作
&ensp;&ensp;将上面标识符``FileStorage::WRITE``改为``FileStorage::READ``即可

### 第二步:进行文件读写操作
- 文本和数字的输入和输出
```c
    fs << "iterationNr" << 100; // 写入文件
```
```c
    int itNr; // 读取文件
    fs["iterationNr"] >> itNr;
    itNr = (int) fs["iterationNr"];
```
### 第三步：文件关闭
&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;文件关闭操作会在FileStorage类销毁时自动进行，也可以显式调用其析构函数``FileStorage::release()``实现。
```c
    fs.release(); // 析构对象，同时关闭文件
```
