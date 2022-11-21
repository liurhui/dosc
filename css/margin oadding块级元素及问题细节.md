margin遇到的问题
	1、垂直方向外边距合并，在没有浮动的情况下会遇到，以大值为准。
			
```css
	/*问题外边距合并问题 原因 两者之间 谁的间距大以谁的为准*/
.box1{  
	width:400px; 
	height:200px; 
	baground-color:red; 
	margin-bottom:50px; 
} 
.box2{ 
	width:400px; 
	height:200px; 
	baground-color:yellow; 
	margin-top:70px; 
} 

<div class="box1"></div> <div class="box2"></div>

```

2、不能设置尺寸的行内元素（span,a），无法设置垂直方向外边距。
```css
// span a这类的无法设置宽高的元素 即使设置了 上下margin也是无法生效的 
//解决办法在span 外面加一个div 
.box1{ //居中 
	width:400px; 
	height:200px; 
	baground-color:red; 
	margin-bottom:50px; 
} 
.box2{ 
	width:400px; 
	height:200px;
	baground-color:yellow; 
	margin-top:70px; 
} 
span{ 
	magrin:100px; //垂直方向无效 只会左右有效 
	background：pink; 
} 

<div class="box1"></div> 
<span>span</span> 
<div class="box2"></div>
```
	
3、内外嵌套的div，如果不存在浮动，父元素没有边框，给了元素设置上外边距会默认作用与父元素（外边距传递问题）。
		父子元素  如果父元素没边框，则把子元素的margin-top  改为写到父元素paading-top
```css
	嵌套的内外元素 
*{ //清除默认样式 
	margin:0; 
	paddiong:0; 
} 
.father{ //居中 
	width:400px; 
	height:200px; 
	border:solid; //图1父元素是边框的时候 可以看到son margin-top有效 
//当 去掉border 采用baground-color 就出现图2 margin-top就无效了
//原因是子元素的margin-top 传递给了father导致 father下来了,与son顶部平齐了。
// baground-color:red;
//解决办法是 son不去设置margin-top 给father设置上内边距 
	padding-top:70px; // 上内边距 
} 
.son{ 
	width:400px; 
	height:200px; 
	baground-color:yellow; 
	// margin-top:70px; 
}

<div class="father"> <div class="son"></div> </div>
```
