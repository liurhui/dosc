  flex布局后，  子元素 float \cleare  \vertical-align  属性讲失效。

文本的位置是基线的位置，当不同宽高容器的文本对齐后，会显示宽高不一样。

order 排序  常用于浏览器记录 值越大越靠前默认0


###### 参考博主
 [http://www.ruanyifeng.com/blog/2015/07/flex-grammar.html](http://www.ruanyifeng.com/blog/2015/07/flex-grammar.html)

demo [https://github.com/JailBreakC/flex-box-demo](https://github.com/JailBreakC/flex-box-demo)
[http://static.vgee.cn/static/index.html](http://static.vgee.cn/static/index.html)  

flex     是 flex-grow  flex-shrink   flex-basis   默认  0 1 auto     浏览器自带推算

1、flex-warp:wrap; // 拆行换行    升序 或降序排放
`nowarp默认   warp换行 升序多行1始终在第一行    warp-reverse降序多行1始终在最后行`
2、分配剩余的空间
flex-grow:0   占用剩余的  几份空间

3、水平排列不压缩按 宽度高度显示
flex-shrink:0     0是不压缩 1是压缩
	常见： 元素的某一个不压缩 选择器 .xxxx:first-of-type{ }
```css
display: flex;
flex-shrink:0


固定高度 不固定宽度 设置宽度的方法

第一种： 采用自动计算 width:50%;

第二种： 每份元素占一份空间 flex:1;

单独 配置宽度 用选择器 1表示当前class里的第一个元素 
.xxxx:ntn-of-type(1){ 
	
}
```
 
4、flex-flow 是 direction 和 warp综合
`默认 row  nowarp`

  
内层div容器 只想水平居中  不 垂直居中
```css
.child{ 
	width: 100px; // 容器必须有宽度
	margin:0 auto; //容器水平方向居中 
}
```
内层div容器  只想 垂直居中
```css
1.父元素需要设定为相对定位 
.content {
	width:500px; 
	height:500px; 
	border :1px solid #000; 
	position:relative; 
} 
.child{ 
	width: 100px; 
	height:100px; 
	border: 1px solid #999;
	position:absolute;  
	top:50%;
	margin-top: -50px;
	left:50%; 
	margin-left: -50px; 
}
```


5、flex-direction  //决定是x 还y 主导方向   布局排列方向
` column //y    row   //x `

6、justify-content  //    横向对齐方式
	元素长度值 给x 宽度值 给y 整行元素横着放
	 
	 flex-start  默认 
		 // x轴 左对齐，左顶格  间隔值一致  右侧留出大量空间
	 flex-end 
		 // x轴 右对齐，右顶格  间隔值一致  左侧留出大量空间
	 center 
		 // x轴 中心对齐， 间隔值一致 留出的大量空间 等分给左右
	 space-between 
		 // x轴  均匀分布对齐 间隔值一致  left 和right 是顶格 center 是居中  
	 space-around 
		 //x轴   均匀分布对齐 间隔值一致  left和right 是不顶格 center是居中  left和right 对边框间隔值相同。三者之间的间隔值的一半作为 left和right 对边框的间隔值

7、align-items  //   纵向对齐方式
	元素长度值 给y 宽度值 给x 整行元素 竖着放
 
	 flex-start 
		 // left top顶格对齐
	 flex-end 
		 // left bottom顶格对齐
	 center
		 // left 距离 top bottom两边同等值 来对齐 距离top和距离bottom是值是一致的。
	 stretch  默认
		  // left 而top 和 bottom顶格对齐 相当于 y拉满为100%
	 baseline
		 // y 和 x 按照div自己的值 以文本的底边对齐， 不顶格自动调整 y值要是没有给 那么每个div将 占满整个 y。当元素内的文本的fontsize不一致时，且没有高度设定时。才以文本的base对齐。元素根据高度最大的作为整体的bored高度



 8、align-content  强化版 纵向对齐方式 
	 如果很多行多个div时 由于div的x值不同，每行的间隔不一样，也可以让多行的间隔值相同 。
条件：高度要小于内层元素高度之和的时候才会出现居中效果。
原因：y轴线需要超过1条以上。
	
	flex-start  
	flex-end  
	center 
	stretch  默认
	space-between 
		//每列的间隔相等 top bottom 应该是会顶格
	space-around 
		//每列的间隔值相等 且 间隔值的一半 是作为top 和 bottom 的边框间隔值


以y轴时，align-items同行元素对齐方式宽高不一致时，align-content多行元素宽高必须一致时生效，align-self 是align-items的独立元素对齐方式。


9、align-self   纵向对齐方式独立 
	需要配合选择器 子元素布局 就是父元素 布局好了 子元素按自己的布局会覆盖父元素布局
	auto     继承
	stretch   拉伸  没宽度的平分，有宽度的按自己宽度。
	center    中心
	flex-start   开头
	flex-end   尾部
```css
<div class="warp">
	<div>1</div>
	<div>2</div>
	<div>3</div>
	<div>4</div>
</div>
.warp{
	width:600px;
	height:600px;
	border:1px solid #000;
	display:flex;
	align-items:flex-end;
}
.warp>div{
	width:100px;
	height:100px;
	border:1px solid #000;
	background:yelow;
	text-align:center;
	line-height:100px;
	font-size:50px;
}
.warp>:nth-child(2){
	align-self:center;  
}
```

#### 盒子模型

移动端是 怪异盒模型    width+ padding +boder

	也就是设定宽高时候要计算下
pc 是 标准盒模型  

`*{box-sizing:border-box;}`   是固定宽高，自动计算扣边框和padding，使得整体的大小就是宽高值的大小。

