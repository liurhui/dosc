https://www.cnblogs.com/XJT2018/p/10642583.html#autoid-0-0-0 

block 块级元素  
inline 行内元素   
inline-block 行内块元素  
none 元素消失`

块元素   宽高   margin  padding  单行 。
行内元素只能 左右 margin     padding  无法宽高    不单行 
	 有默认的一个回车 相当于间距，要去掉否则代码压缩后会默认删除间距。（专业叫 空白折叠）
行内块   宽高  margin padding    且不换行


a标签转为块级元素就会和div一样
	常见 导航栏  鼠标 放到li 时 就可以获得 a标签的跳转小手
```css
//  设置block 就可以放到li就相当于放到a标签  

ul{ font-size: 0; }  //去间距
ul,li,a,*{
	padding:0; 
	margin:0;
	list-style: none;
	text-decoration: none;
}
a{ 
	display:inline-block; 
	wdith:200px; 
	height:200px; 
	text-align:center;
	line-height:200px; 
	background-color:red;
	font-size: 15px;
} 
a:hover{
	background-color:#fa6600;
}
<ul>
 <li><a href="#">超链接</a>  </li>
 <li><a href="#">超链接</a>  </li>
 <li><a href="#">超链接</a> </li>
 </ul>
```

a 去掉下划线 text-decroation:none;

删除行内块默认间距的方法
	解决办法是 父元素设置font-size:0; 但是注意font是会继承的 所以子元素要设置字体大小font-size:16px;

	缺陷是 inline-bolck 以基线对齐的。 但凡改变某个基线 就会出现都改变，那么可以改为用浮动。
	浮动一定要设置宽高 否则会塌陷 或者清除浮动解决塌陷。
```css
.pages{ 
	font-size:0; 
} 
.pages a{ 
	display:inline-block; 
	width:60px; 
	height:60px; 
	text-align:center; //文本水平居中 
	line-height:60px; //文本垂直居中 
	background-color:pink; 
	font-size:16px; 
	margin:0 4px; 
} 
<div class="pages"> 
	<a href="#">1</a> 
	<a href="#">2/a> 
	<a href="#">3</a> 
	<a href="#">4</a> 
	<a href="#">5</a> 
	<a href="#">下一页</a> 
</div>
```
