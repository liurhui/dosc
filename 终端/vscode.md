---
创建日期:
  -  2022/8/4
---
#### 多关键字检索
	(word1[\s\S]*word2) | (word2[\s\S]*word1)

多行 光标选择    鼠标中间按下 
或
按住shift+alt 多选光标 在第一个元素点一下 最后一个点一下


C+S+K 删除行
C+E   下行插入行
C+S+E  商行插入行
C+ ]/[    缩进/锁进行


#### 安装GCC 运行C++
https://sourceforge.net/projects/mingw-w64/files/
找到# MinGW-W64 GCC-8.1.0 栏  选择  x86_64-win32-seh    下载下来是压缩包，解压后就可以用。  放到c盘去 ， 然后去配置环境变量。
```plaintext
Path 里面 新建 
C:\Program Files\mingw64\bin
```
vscode配置
1、安装扩展 C/C++    显示  IntelliSense, debugging, and code browsing.  的就是
2、运行->添加配置-> c/c++  GDB (启动)  到 launch.json
3、文件夹和文件 都不能带中文  
4、右上角点击 三角形 的 运行c/c++ 文件
