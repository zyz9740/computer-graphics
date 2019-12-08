## 音乐可视化

运行方式：网页打开index.html，选中一首音乐歌曲即可

编程语言：Javascript

效果：

![image-20191206135645746](https://tva1.sinaimg.cn/large/006tNbRwly1g9mynad1x5j30cy0d1755.jpg)

算法：

- 使用audioContext获取音频信息并进行FFT变换
- 按照希望绘制的片段数进行采样，数值的大小决定音乐柱的高度
- 使用canvas进行画图，在每次绘制完成之后将画布旋转一定角度，即可完成圆形构图