
如果 属性的值 只有1、不写 2、值还是属性。 这种叫做布尔属性。 可以省写值。
空标签就是单标签

#### 1、文本元素

##### 快捷html写法
1、`  h$*6>{内容}  `
$ 自增值符合  //  1 2 3 4 5

paragraphs 段落   // 乱数假文 随机生成无意义的占位文本
2、`  p*6>lorem`     lorem 后面紧跟数字可以规定长度

3、()  内看作整体   + 后跟兄弟    > 下一个嵌套     []  内写属性  {}内写文本
` h2>{章节1}+p>lorem`    生成 h2  和  p   ，h2为父，章节1和 p平级。
` (h2>{章节1})+p>lorem`    生成 h2  和  p 是 平级。
` ((h2>{章节$})+p>lorem1000）*6`    生成 h2 和 p是 平级且 6个每个p内容 1000个
` ((h2[id="aaa$"]>{章节$})+p>lorem1000）*6`    同上 加 属性
```html
ul*5>(li>h3>a>lorem5)+(li*6>a>lorem5)

<ul>
	<li>
		<h3><a>
	</li>
	<li><a></li>
	<li><a></li>
	...
</ul>
<ul>
	<li>
		<h3><a>
	</li>
	<li><a></li>
	<li><a></li>
	...
</ul>
...
```

##### 小技巧细节

1、span  可以当样式万金油  不带任何捕获元素。
	因为 其他元素 是会带有标签，  span 是不会生成标签。

2、行内 被认定是 措辞。    块级 被认定是流式。

3、pre   预格式化文本元素  常用于 页面显示 源代码。保留所有空格 换行  制表符。
	因为：空白折叠 ，代码的连续空白字符（空格 换行 制表符）不管多少，浏览器都被认为是一个空格。pre  是改变 浏览器这么认为，有多少接收多少。
实际上是帮忙加了css样式 。
pre 一般是    code   pre   嵌套使用表明这段是源代码。

 
#### 2、实体文本 （html符号 转义字符）
	百度查   html  Entity   mdn
	https://developer.mozilla.org/en-US/docs/Glossary/Entity

```html
   
-   不可分的空格  &nbsp;
-   `<`（小于符号）&lt;
-   `>`（大于符号）&gt;
-   `&`（与符号）&amp;
-   `″`（双引号）&quot;
-   `'`（单引号）&apos;
-   `©`（版权符号）&copy; 
-   `•` (圆点)   &bull;
-   `®` (注册)   &reg;

//用 he 库
// 实体编码
he.encode('<img src=""></img>') 
	// "&#x3C;img src=&#x22;&#x22;&#x3E;&#x3C;/img&#x3E;"

// 转义
he.escape('<img src=""></img>')
	// "&lt;img src=&quot;&quot;&gt;&lt;/img&gt;"

```

#### 3、a标签 超链接
```html
href 和 tag 区别  tag是不会带动页面刷新，href 会。
tag 是 给url 加了地址 ，由于同页面不刷新 但是跳转了，本质跟href差不多。



1、 href    跳转引用地址
	href="#"  锚点#没跟内容默认是回到顶部。
	
2、 tag="#123"     跳转某个锚点,用于当前页面目录段落绑定.
	被绑的元素加 id="123" 


3、 target="_blank"   跳转窗口位置
	1、_self   默认值 覆盖当前页面
	2、_blank    新窗口

4、 title=""   鼠标放上去的提示文本。




3、 功能链接  点击后，触发某个功能  （了解就好 一般不用了 旧时代常用）
	1、固定以 javascript:  开头
	2、发送邮件 mailto:     废弃了 因为要使用者本地安装exchange来支持
	3、拨号   tel:        使用者本地要安装拨号软件，或移动端
如:
<a href="javascript:alert('你好！')"> 执行js代码 </a>
<a href="mailto:13224@qq.com"> 发送邮件 </a>
<a href="tel:13224111111"> 只能手机端使用拨打电话 </a>


4、 执行js代码   


```
	示例：a页面 跳转到 b页面 的 某个锚点位置 
```javascript

```

#### 4、url路径
#####  站内资源  和 站外资源
	概念：
		站内资源:  项目内的
		站外资源:  别的网站的
经验总结:   站外用绝对路径，站内用相对路径。

Tips: 
	当绝对路径是相同协议时可以省略，**协议名 但是// 要写**。注意文件打开协议名是file 。
	相对路径的  ./   也可以省略。
##### 绝对路径
```html
 协议名://主机名:端口号/路径
 schema://host:port/path

协议名  http、https、 file
主机名    域名、IP地址
端口号   80(http)   443(https)  
路径 
```

##### 相对路径
```html
1、以./开头 ，tab补齐。
2、 ../返回上一级
用法
./../xxx.html

```


#### 5、图片元素
	1、配合a 标签来跳转到相关的具体描述页面。
	2、配合map  可以实现 锚链接跳转的效果。 用子元素划分把图片的不同内容可以划分出来。
	3、配合figure 和 figcaption 可以把 图片跟标题 捆绑一组。避免浏览器不识别。

	Tips: coords 取值可以用 ps  pxcook 这样去截，用截图注意浏览器还原100%大小去拿值。

##### map
```html
  src="来源url"
  alt="图片失效时，显示的文本描述"

<a>
	<img usemap="#aaa">
</a>

<map name="aaa">
	<area shape="形状" coords="坐标" href="跳转的url" alt=""  target="">
	 
</map>

  shape ： circle 圆心(x,y,r)  rect 矩形 (x,y,x,y)   poly 多边形


  coords： 坐标
  //测量起始点是 图片的左上的顶点开始是0，0   所以 x轴y轴值一般为正。
   不同形状参数不一样;
  
	1、圆形 需要 中心点和半径   coords="x,y,r"
	2、矩形 需要  左上角(x,y) 右下角(x,y)  coords="x,y,x,y"
	3、多边形  需要 多个点   coords="x,y,x,y,x,y" 
  ```
 
##### figure    仅仅是语义上 更好
```html
<figure>
	<a>
		<img usemap="#aaa">
	</a>
	<figcaption>
		<h2>太阳系</h2>
	</figcaption>
	<p>
		描述内容
	</p>
</figure>
<map name="aaa">
	<area shape="形状" coords="坐标" href="跳转的url" alt=""  target="">
	 
</map>
```


#### 6、多媒体元素
	常见 mp4 webm \ mp3 格式 
	兼容性 在旧版本无法使用，不同浏览器所支持的格式不一定相同。通常视频备两种格式怎么写法。
```html
	 都是布尔属性, 视频和 音频 属性基本一致。
	controls  显示播放控件栏  
	autoplay    自动播放
	meted   静音播放
	loop   循环播放 

<video controls autoplay meted  loop  src="" style="width:400px;"></video>

<audio controls autoplay  src=""  ></audio>


```

##### 多种格式源写法
```html
<video controls autoplay meted  loop  src="" style="width:400px;">
	<source src="media/open.mp4">
	<source src="media/open.webm">
	<p>你所使用的浏览器不支持，请更换浏览器使用。</p>
</video>
```

#### 7、列表元素
	少用type属性 ，尽量用 css 的 list-style-type  。
	一般用ul -> li 
```html
ol ->li   有序  
ul ->li   无序    ul  即使用  list-style-type 修饰也是 无序列表。
	
dl  -> dt ->dd   自定义   少用不好用没意义。真要写又很麻烦。
 
```

#### 8、容器
	带语义的容器实质上还是div只是语义而已。
	nav 可以替代ul->li。
```html

header  文章头部
	article 文章 
	section  文章章节 有很多文章 每一篇
	aside  侧边栏
footer  文章尾部


<nav>
	<a></a>
	<a></a>
</nav>
替代
<ul>
	<li><a></a></li>
	<li><a></a></li>
	<li><a></a></li>
</ul>



```
#### 9、元素包含关系  （只是这么去理解常识思维上）
	检索关键词，去mdn搜内容类别 。
  a元素 可以包含任何元素，可以当div 看。
  固定 写法 ul ->li  ,   ol  ->li  ,   dl -> dt+dd
  标题和段落 元素不能互相嵌套，不能包含容器元素。
  p元素内不能写 ul li

#### 带有意义的常用 html 
```css
<del></del>加划线   <a></a>下划线
<s></s> 表示过期内容 也是加划线
<strike></strike>
<u></u> <ins></ins> 下划线 表示强调

<strong></strong>  加粗  表示重要不能忽略的内容

<em></em> 斜体 表示强调 <i>倾斜（现在常表示 iconfont）


 <sup></sup>  上标（平方）
 <sub><sub>  下标 （化学）
 
```


### 进阶
#### 1、表单元素 
	readonly属性：布尔属性，是否只读，不会改变表单显示样式 
	disabled属性：布尔属性，是否禁用，会改变表单显示样式
#####  需要其他 子元素 搭配使用。
##### 3、fieldset 表单分组名称
##### 4、form 表单 专用js交互的  其实可以用div配合响应式去做。
	1、根据 name 和value 对应的取出来组成 键值对用 &拼接成一条数据包。
##### 5、datalist 数据列表   input 里的下拉列表
	1、不会显示到页面，通常用于和普通文本框配合做组合选项。
##### 6、textarea 多行文本框, 看作文本框的div
##### 7、select  选择列表，看作选择列表组的div

#####  被上面组件所使用
##### 1、button
	1、可以内部加 img p 等作为内容。
	
##### 2、label   关联某一个表单元素，点击文本也可以选中元素。注意label内无法用div 可以用span替代。
	1、两种写法  分显示写法（嵌套）和隐式写法（id绑定，可以不写一起）

##### 8、input   分键盘输入和选项输入 选择框
```html
<!-- 普通文本输入框 --> 
        <input type="text" placeholder="请输入账号">
<!-- 密码框 -->
        <input type="password" placeholder="请输入密码">
<!-- 日期选择框 -->
		<input type="date">
<!-- 搜索框 -->
		<input type="search">
<!-- 滑块 -->
        <input type="range" min="0" max="5">
<!-- 颜色选择 -->
        <input type="color">
<!-- 数字输入框 -->
        <input type="number" min="0" max="100" step="20">
<!-- 多选框 -->
        爱好：
        <input name="loves" type="checkbox">
        音乐
        <input checked name="loves" type="checkbox">
        电影
        <input name="loves" type="checkbox">
        阅读
        <input name="loves" type="checkbox">
        其他
<!-- 单选框 -->

        性别：
        <input name="gender" type="radio">
        男
        <input checked name="gender" type="radio">
        女
<!-- 文件选择 -->
        <input type="file">
<!-- 提交按钮 -->
        <input type="submit" value="这是一个提交按钮">
```


