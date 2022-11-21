https://blog.csdn.net/Newbie___/article/details/104898436

https://lesscss.org/functions/  官方
npm i -D less
lessc index.less index.css
或 npx lessc index.less index.css

定义变量 @width:  100px;
&  是 父级拼接的意思


#### 函数篇
less 内置函数，有很多可以查看
```css
//if:如果2大于1,则显示0,否则3px.和三目运算符有些类似
//iscolor:传入一个值,判断是否是颜色。
@some: foo;
div {
    margin: if((2 > 1), 0, 3px);
    color:  if((iscolor(@some)), @some, black);
}
//会被编译为:
div {
  margin: 0;
  color: black;
}

```
作用域
```css
@color: red; 
.box { 
	@color: white; 
	.content {
		 color: @color; // white 
	}
 } 
 //会被编译为: 

 .box .content { color: white; }
```
可以把 注释写在  块注释内  编译会保留
```css
/* 
 * 块注释
 */
 @color: red;

 // 行注释
 @color: white;
 .box{
   color: @color;
 }

//会被编译为------------------------
/* 
 * 块注释
 */
.box {
  color: white;
}
```

引入
```css
base.less文件
@color:red;

index.less文件
@import "./base.less"; .box{ color: @color; }

.box { color: red; }
```