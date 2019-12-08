# 地球以内，太阳以外

### 内容

​	该作品描绘了宇宙中太阳及部分行星的静态景物，包括太阳、金星、水星、地球、月球等。

### 工程概览

- 编程语言：OpenGL glew2.1
- 外部链接库：
  - glfw3.3 
  - glad0.1.33 
  - glm
  - stb_image
- 运行环境：
  - Clion IDE
  - C++ 11 standard

### 程序说明

```c
.
├── CMakeLists.txt			// cmake 配置文件
├── Point.cpp						// 坐标点头文件和源文件
├── Point.h
├── camera.h						// 相机类
├── cmake-build-debug		// 可执行目标文存放地
│   └── ...
├── frag.glsl						// 片段着色器
├── glad.c							// glad 库
├── glm									// glm 库
│   └── ...
├── img									// 纹理图片
│   ├── earth.jpg
│   ├── mercury.jpg
│   ├── moon.jpg
│   ├── sun.jpg
│   └── venus.jpg
├── main.cpp						// main 文件
├── shader.h						// 着色器类
├── stb_image.h					// stb_image库
└── vert.glsl						// 顶点着色器

```



### 算法原理

#### 极坐标变换

​	我们在创建球表面上的每一个点的时候都使用 $u, v$ 两个极坐标参数进行球表面上点的表示，然后在 $getpoint$ 函数中使用如下公式进行三维直角坐标系的转换：

- $ x = sin(PI * v)*cos(2 * PI * u) $
- $  y = sin(PI * v)*sin(2 * PI * u) $
- $ z = cos(PI * v) $



#### 用三角形创建球形

一个立体的球型可以由许多三角形拼贴而成，具体的构造方法是：

- 在顶部汇聚点和底部汇聚点使用一个顶点相同的连续拼贴三角形
- 在中部使用每两个三角形拼贴成矩形，进而构成球形

所以，我们先将所有的顶点存放在数组中，然后给片段着色器输入相应的三个顶点。每个三角形的计算方式如下

```
// 图中的数字表示顶点的序号
// j为循环变量，ustepnum+1为一个环上的点的数量,last为最底部的点
/* 顶部三角形
*       0
*       |\
*       | \
*       |__\
*      j+1  j+2
*/
/*	中部左下三角形
*       j
*       |\
*       | \
*       |__\
* j+(ustepnum+1)
* 			j+ ustepnum + 1 + 1
*/
/*	中部右上三角形
*
*     j ___ j + 1
*       \  |
*		     \ |
*		      \|
*          `
*     j + 1 + ustepnum + 1
*/
/* 底部三角形
*
*     i ___ i+1
*       \  |
*		     \ |
*		      \|
*          `
*         last
*/
```



 #### 纹理映射

​	我们需要将每个点对应到相应纹理的2D坐标当中去，只需要在绘制点的时候，按照比例将纹理坐标添加到顶点的属性中即可。



#### OpenGL 原理

​	其余的图形学原理比如顶点着色器、片段着色器、光照、摄像机等涉及到OpenGL原理，不进行过多介绍



### 程序运行

```
cd openGL2/cmake-build-debug
./openGL2
```



### 最终效果

![地球以内，太阳以外](https://tva1.sinaimg.cn/large/006tNbRwly1g9mye87klij30u00n43zp.jpg)