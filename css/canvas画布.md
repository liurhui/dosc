1、基本示例
```css

body{ 
	text-align: center; 
	padding-top: 80px; 
	/* margin:0 auto */ 
}

canvas{
/* box-shadow: 0 0 10px #333; */ 
/* margin: 0 auto; */ 
/* border-radius: 25px; */ 
box-shadow: 0 0 40px #333; 
border: 1px solid rgb(196,200,201); 
/* background-color: rgba(155,155,155,155); */

}

<link rel="stylesheet" href="style.css" /> 
<script src="vue.js"></script> 
</head> 
<body onload="draw()"> 
<div id="vue-app"></div> 
<canvas id="canvas" width="800" height="600"> 
	你这浏览器不支持这玩意啊 
</canvas> 
	<script src="app.js"></script>
	<script> 
		function draw() { 
		// 让vscode可以显示canvas智能提示 
		/** @type {HTMLCanvasElement} */ 
			const canvas = document.getElementById('canvas') 
			if (canvas.getContext) { 
				const ctx = canvas.getContext('2d') 
			}
		} 
	</script> 
</body>
</html>
```

常见的几种样式函数
2、填充矩形
[https://www.runoob.com/tags/canvas-fillstyle.html](https://www.runoob.com/tags/canvas-fillstyle.html)
```javascript
ctx.fillStyle="#FF0000";
ctx.fillRect(0,0,150,75); //x y 宽 高
```

3、描边矩形
[https://www.runoob.com/tags/canvas-strokestyle.html](https://www.runoob.com/tags/canvas-strokestyle.html)
```javascript
ctx.strokeStyle="#FF0000"; 
ctx.strokeRect(20,20,150,100); //x y 宽 高
```
4、清除  填充矩形内的指定矩形区域
```javascript
ctx.fillStyle="red"; 
ctx.fillRect(25,25,100,100); 
ctx.clearRect(45,45,60,60); //x y 宽 高 
ctx.clearRect(50,50,50,50);
```

采用路径 方式 画 
```javascript
// 开始绘制路径 闭合成矩形 
	ctx.beginPath(); // 起始点 x = 150 y= 150 
	ctx.moveTo(150,150); // 第一条线 x = 400 y= 150 
	ctx.lineTo(400,150); // 第二条线 x = 150 y= 400 
	ctx.lineTo(150,400); // 闭合 相当于 第二条线坐标点 直接 连到起始点
	ctx.closePath(); // 绘制 fill填充 stroke描边
	ctx.fill();


/* 绘制第二个三角形 */ 
ctx.beginPath(); 
ctx.moveTo(450,450); 
ctx.lineTo(200,450); 
ctx.lineTo(450,200); 
ctx.closePath(); 
ctx.stroke();


/*绘制圆*/
 https://jingyan.baidu.com/article/f71d603758f1445bb641d1b0.html

// 圆的组成: 圆心(x,y) 半径 开始角度 结束角度 顺时针clockwise /逆时针anticlockwise 
// true 顺时针方向， false 逆时针方向 默认 
// 半径决定圆大小

let x =400, y =300, radius =150, startAngle=0, endAngle=Math.PI, direction =false; 
ctx.arc(x, y, radius, startAngle, endAngle, direction );
ctx.arc(400, 300, 150, 0, Math.PI*1.5 ); 
ctx.arc(400, 300, 150, 0, Math.PI ); //半圈即 Math.PI = 180度 
ctx.arc(400, 300, 150, 0, Math.PI + Math.PI/2 ); // 3/4 圆
```

线性渐变、径向渐变 都是 属于样式定义， 然后 赋值给 canvas 画布的 样式属性。
```javascript
/** 
线性渐变
参数1: 起点x1 
参数2: 起点y1  
参数3: 起点x2 
参数4: 起点y2 
**/

const linearGradient = ctx.createLinearGradient(0, 0, 0, 150) 
/** 
* linearGradient.addColorStop(0,'#cc6677'); 
* 参数1: 必须是0.0~1.0之间的一个数值,数值表示颜色所在的相对位置 
* 参数2: 颜色, 
**/ 

linearGradient.addColorStop(0, '#cc6677') 
linearGradient.addColorStop(0.5, '#fff') 
linearGradient.addColorStop(0.5, '#c6c776') 

const linearGradient2 = ctx.createLinearGradient(0, 50, 0, 90) linearGradient2.addColorStop(0.5, '#000') 
linearGradient2.addColorStop(1, 'rgba(0,0,0,0)') 

ctx.fillStyle = linearGradient 
ctx.fillRect(10, 10, 150, 150) 

ctx.strokeStyle = linearGradient2 
ctx.strokeRect(60,50,50,50)
```

径向渐变
```javascript
const canvas = document.getElementById('canvas') 

if (canvas.getContext) { 
	const ctx = canvas.getContext('2d') 
	/** 
	径向渐变 radial gradient 分两个圆来看 圆心a 圆心b 
	* 参数1: x1 
	* 参数2: y1 
	* 参数3: r1 
	* 参数4: x2 
	* 参数5: y2 
	* 参数6: r2 
	* */ 
	const radialGradient = 
		 ctx.createRadialGradient(170,170,10,180,180,30); 
	radialGradient.addColorStop(0,'#a7d30c'); 
	radialGradient.addColorStop(0.9,'#019f62'); 
	radialGradient.addColorStop(1,'rgba(1,159,98,0)'); 
	const radialGradient2 = 
		ctx.createRadialGradient(280,290,10,280,280,80) 
	radialGradient2.addColorStop(0,'#ff5f98'); 
	radialGradient2.addColorStop(0.9,'#ff0188'); 
	radialGradient2.addColorStop(1,'rgba(255,1,136,0)'); 
	//画图
	 ctx.fillStyle = radialGradient; 
	 ctx.fillRect(0,0,800,800); 
	 ctx.fillStyle = radialGradient2; 
	 ctx.fillRect(0,0,325,325); }
```