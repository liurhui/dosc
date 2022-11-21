---
创建日期:
  -  2022/7/4
---


需要安装ruby  进行编译成css文件。
ruby安装速度特别慢。

#### 编译  参考
https://blog.csdn.net/shi__Yu/article/details/103146677

sass 目标文件名.scss    生成结果文件名.css


#### 刚开始学使用
	scss变量
```css
:root {
  --app-container: #f3f6fd;
  --main-color: #1f1c2e;
  --secondary-color: #4A4A4A;
  --link-color: #1f1c2e;
  --link-color-hover: #c3cff4;
  --link-color-active: #fff;
  --link-color-active-bg: #1f1c2e;
  --projects-section: #fff;
  --message-box-hover: #fafcff;
  --message-box-border: #e9ebf0;
  --more-list-bg: #fff;
  --more-list-bg-hover: #f6fbff;
  --more-list-shadow: rgba(209, 209, 209, 0.4);
  --button-bg: #1f1c24;
  --search-area-bg: #fff;
  --star: #1ff1c2e;
  --message-btn: #fff;
}
```
	给值
```
  background-color: var(--app-container);
 
```



https://blog.csdn.net/jiang_fulai/article/details/80134663
#### 引入
```css
    @import "foo.scss"; //都会导入文件 foo.scss
    @import "foo"; //都会导入文件 foo.scss
    @import "http://foo.com/bar";  // 插入外部文件
    @import "foo.css"; // 等同于css的import命令。
```

#### 变量定义
```css
$key: value;

/*默认变量是可以被覆盖的,具体覆盖方法如下 */
$font: 12px; 
$font: 14px!default;
```


&  根less 一样 都是 父级拼接
```css
a{ &:hover{ } } //解析为 css 文件 a{ } a:hover{ }
```

注释
		多行注释 - 这些使用    /*  * / 写入。多行注释都保留在CSS输出。
        单行注释 - 这些是使用 // 跟着注释。单行注释不会保留在CSS输出。

### 其他功能
```css
运算：对于（数字，颜色，变量）的四则（加减乘除）运算,运算符前后各保留一格空格

if判断：@if可以单独使用，也可以配合@else、@else if 一起使用

三目运算符：if(true,1px,2px)，返回的值是1px,if(false,1px,2px),返回的值是2px

for循环，共有两种写法，1：@for $var from through
2：@for $var from to 。两种写法唯一的区别就是，through包括end这个数，to不包括end这个数。

each循环，@each $var in ,list和map分别表示为list和map类型数据。
```


#### 混合 @mixin      
	使用 @mixin 需要用 @include

```css
@mixin font($size:12px){ //默认参数 默认12px 
	font-size: $size; 
} 
.footer{ 
	@include font(16px);
}


编译后
.footer{ 
	font-size: 16px; 
}
```

#### 继承    @extend         
	用法   后面写选择器名字
```css
.font{
    font-size:14px;
    height: 16px;
}
.footer{
    @extend .font;
    border-width: 2px;
}


//解析为 css 文件

.font, .footer{
    font-size:14px;
    height: 16px;
}
.footer{
    border-width: 2px;
}
```

#### 站位选择器     %  
	类似 开关宏    没调用 则不编译  调用则编译     用法 %后面写选择器
```css
%dir{ 
	font-size: 14px; 
}
%clear{ 
	overflow: hidden; 
}

div{ @extend %dir; }


dir被调用了 所以 dir被编译， clear 没调用则没编译。 就当作是 .h文件被定义却没使用
```


#### 内置函数
	以 @function 开始 @return 返回值
	用于移动端页面计算rem或者vw最佳
```css
//scss 文件 
@function per($data){
	@return $data/10 + px; 
} 
div{ 
	font-size: per(140); 
} 

//解析为 css文件 

div{ 
	font-size: 14px; 
}

```


