事件循环机制
```js
function fun1(){ 
	console.log(1) 
} 
function fun2(){ 
	console.log(2) 
	fun1() 
	console.log(3) 
}
fun2()
```

```js
function fun1(){ 
	console.log(1) 
} 
function fun2(){ 
	setTimeout(()=>{ 
	console.log(2) },0) 
	fun1() 
	console.log(3) 
} 
fun2()
```

```js
var p =new Promise(
	resolve =>{ console.log(4) resolve(5) }
	) 
function func1(){ 
	console.log(1) 
} 
function func2(){ 
	setTimeout(()=>{ console.log(2) },0) 
	func1() 
	console.log(3) 
	p.then(resolve=>{ console.log(resolve) }) 
} 
func2()
```

BFC
	快捷格式化上下文，它是指一个独立的块级渲染区域，只有block-level box 参与， 该区域拥有一套渲染规则来约束块级盒子的布局，且与区域外部无关

现象

	一个盒子不设置height 当内容元素都浮动时，无法撑起自身。  
	
	这个盒子没有形成BFC

如何创建BFC

1、float的值不是none 意思是 外层容器 加样式 float:left;

2、postition的值不是static 或者relative 原因以当前的父级或上级元素做定位对象

	缺点我们将一个盒子摆放在那儿，希望后面的盒子都在它后面，但是就不会老老实实的待在原来自己呆的地方了，会往上移动

3、 display的值是inline-block、flex或者 inline-flex 原因 变成行内块元素可以给外层容器设置宽度和高度

	缺点 就是想让它独占一行，这是不是也不行

4、overflow:hidden; 原因可以避免margin值，这两个元素就不再是一个BFC了，计算高度的时候，是包含浮动元素的，故可以清楚浮动。

	缺点我们就想让内部的盒子溢出外部的盒子，这样加显然就不合适了

哪个最好

	4最好

BFC的其他作用

-   BFC可以取消盒子 margin塌陷 也叫一个BFC内的元素会引起上下margin值重叠

-   BFC可以阻止元素被浮动元素覆盖 也叫 下面没浮动的会叠到 上面写浮动的元素内去


Symbol   解构 对象

apply
	改变this指向
	实现继承
	数组的传值 Array.prototype.push.apply(arr,arr1)  
	//es5 迫不得 数组合并 出的apply 减少了很多代码不然得循环写法
