事件三要素  : 事件源 、事件类型、事件处理程序
事件步骤 : 获取事件源、注册(绑定)事件、添加处理函数
#### 事件   前缀加on
```javascript
click: 'tap', 单击
touchstart: 'touchstart', 手指触摸动作开始 点击不松开 
touchmove: 'touchmove', 手指触摸后移动 
touchcancel: 'touchcancel', 手指触摸被打断 如来电显示 弹窗 等导致的被中断 touchend: 'touchend',手指触摸动作停止放开 
tap: 'tap', 手机端专用 触摸 
longtap: 'longtap', 长时间触摸 //推荐使用longpress 长时间按压代替 电脑端鼠标只触发longtap 而手机端 两者都触发 
input: 'input', 输入文本 
change: 'change', 
submit: 'submit', 提交事件 

blur: 'blur', 失去焦点 
focus: 'focus', 获取焦点 

reset: 'reset', 按钮重置事件 
confirm: 'confirm',点击完成按钮触发 回车键或换行
columnchange: 'columnchange', 列表发生变化 
linechange: 'linechange', 换行 行数发生变化时触发 
error: 'error', 
scrolltoupper: 'scrolltoupper', 上滚动 左 
scrolltolower: 'scrolltolower', 下滚动 右 
scroll: 'scroll' 上下滚动


onclick 鼠标点击左键触发 
onmouseover鼠标经过触发 
onmouseout鼠标离开触发 

onfocus获得鼠标焦点触发
onblur失去鼠标焦点触发 

onmousemove鼠标移动触发 

onmouseup鼠标弹起触发 
onmousedown鼠标按下触发
```

```js
document.title 
document.children[0]   //  整个html 
document.head 
window.location  === document.location  //  url


// 创建元素  imageEl  === imageEl2  两种创建方式  本质是一样
const  imageEl =  document.createElement("img")   
const imageEl2 = new HTMLImageElment()


// 获取元素  具体到某个的直接set ,没具体到的返回集合用遍历去set。
var divEl1 = document.getElementById('box'); //<div id="box" > 
var divEl1 = document.getElementsByTagName('li'); // <li></li> 
var divEl1 = document.getElementsByName('title'); // <div name="title" > 
var divEl1 = document.getElementsByClassName('box'); // <div class="box" > 

// 根据选择器返回第一个元素对象 
var divEl1 = document.querySelector('.box'); //<div class="box" > 
var divEl1 = document.querySelector('#box'); //<div id="box" > 
var divEl1 = document.querySelectorAll('.box').[0]; //返回所有元素对象 遍历用下标


var divEl1 = document.body; // 返回body元素对象 
var divEl1 = document.documentElement; // 返回html元素对象
```
常用到的
```js
<body>
<div id="box" class="aaa" age="18">
	<span>span元素</span>
</div>
<script>
	const divEl = document.querySelector('#box');
	// 常见属性
	console.log(divEl.id);   //box
	console.log(divEl.tagName);  //DIV
	console.log(divEl.children); // span
	console.log(divEl.className); // aaa
	console.log(divEl.classList);  
	console.log(divEl.clientWidth);  // span的宽度
	console.log(divEl.clientHeight); // span的高度
	console.log(divEl.offsetLeft);
	console.log(divEl.offsetTop);
	// 常见的方法
	const value = divEl.getAttribute("age");  //<div age="18"> </div>
</script>
</body>
```

事件监听3种
1、 直接html 赋值函数        不好维护
2、xx.onclick = function(){ }       后写的会覆盖前面写的
3、 xx.addEventListener("click",()=>{})     常用
```js
const divEl = document.querySelector(".container")
divEl.addEventListener("click", ()=>{
	console.log("div元素被点击了")
})
```

#### 事件流
	触发事件后 元素节点之间按特定顺序传播 这个过程叫dom事件流
	IE公司 事件冒泡 是 内到外 默认省略为false  
	Netscape公司 事件捕获 是 外到内 true  
	两者都写 顺序  是外到内  内到外 
##### 事件 属性和方法
```js

const spanEl= document.querySelector(".span")
spanEl.addEventListener("click", (event)=>{
    console.log("span元素被点击:",event)
    console.log("事件类型:",event.type)
  
        // target 不会变化一直是 点击者  
        // currentTarget 是传递到的当前 addEventListener 的对象  会变化的 
    console.log("事件元素:",event.target)  //  点击 span 时   span
    console.log("事件元素:",event.currentTarget)  //span
})


```
阻止事件冒泡
```js
//阻止事件冒泡 
var son = document.querySelector('.son'); 
son.addEventListener('click', function(e) { 
	alert('son'); 
	e.stopPropagation(); // stop 停止 Propagation 传播 
	e.cancelBubble = true; // 非标准 cancel 取消 bubble 泡泡 
	// 兼容 ie678
	if(e && e.stopPropagation){ 
		e.stopPropagation(); 
	}else{ 
		window.event.cancelBubble = true; 
	} 
}, false);
```
事件委托
	多个li 每个都有事件 只做一次监听利于冒泡机制，做判断执行不同逻辑
```js
<ul id="ul1"> 
	<li id="add">111</li> 
	<li id="remove">222</li> 
	<li id="move">333</li> 
	<li id="select">444</li> 
</ul> 

window.onload = function(){ 　　
	var oUl = document.getElementById("ul1"); 　　
	oUl.onclick = function(ev){ 　　　　
		var ev = ev || window.event; 　　　　
		var target = ev.target || ev.srcElement; 
		//通过判断点击的是li标签 就触发 　　　　
	if(target.nodeName.toLowerCase() == 'li'){ 
	　 　　alert(123); 　　　　　　　 
	　 　　alert(target.innerHTML); 　　　　
	} //通过判断 id 来进行触发不同的内容 
	if(target.nodeName.toLocaleLowerCase() == 'li'){
		switch(target.id){ 
			case 'add' : 
				alert('添加'); 
				break;
			case 'remove' : 
				alert('删除'); 
				break; 
			case 'move' : 
				alert('移动'); 
				break; 
			case 'select' : 
				alert('选择'); 
				break; 
			} 
		} 　　
	} 
}
```