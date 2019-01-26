# **操作像素**
## ***颜色空间的缩减***
&ensp;&ensp;Examples:

&ensp;0～9范围的像素值为0

&ensp;10～19范围的像素值为10

&ensp;20～29范围的像素值为20

&ensp;&ensp;将0～255的256种像素情况，提前计算好放入表``table``中。
```c
    int divideWith = 10; //可以按要求修改，如果要64种颜色，取 256/64
    uchar table[256];
    for(int i = 0; i<256; ++i)
    {
        table[i] = divideWith* (i/divideWith);
        //C++的除法会自动截余
    }
```
## ***访问图像像素的方法***
- 用指针访问元素
&ensp;&ensp;``Mat``类若干成员函数可以获取图形的属性。公有成员变量``cols``和``rows``给出了图像的宽和高，而成员函数``channels()``用于返回图像的通道数。灰度图的通道数为1,彩色图的通道数为3。

&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;每行的像素值用以下语句得到：
```c
    int colNumber = outputImage.cols * outputImage.channels();
    //行数X通道数=每一行元素的个数
```
&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;``Mat``类提供了``ptr``函数可以获得图像任意行的首地址。
```c
    uchar* data = outputImage.ptr(i);
    //获取第i行的首地址
```

- 使用迭代器操作像素
&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;在迭代法中，仅需要获得图像矩阵的``begin``和``end``,然后递增迭代从``begin``到``end``。将``*``操作符添加在迭代指针前，即可访问当前指向内容。
&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;相比用指针访问可能出现越界的问题，迭代器是非常安全的办法。
```c
//  使用迭代器的 颜色空间缩减函数
void colrReduce(Mat& inputImage, Mat& outputImage, int div)
{
    outputImage = inputImage.clone();

    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>(); //初始位置的迭代器
    Mat_<Vec3b>::iterator itend = ouputImage.end<Vec3b>(); //终止位置的迭代器

    for( ; it!=itend; ++it)
    {
        (*it)[0]=(*it)[0]/div*div + div/2;
        (*it)[1]=(*it)[1]/div*div + div/2;
        (*it)[2]=(*it)[2]/div*div + div/2;
    }
}

```

- 使用``at``的动态地址访问
&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;与数组访问类似