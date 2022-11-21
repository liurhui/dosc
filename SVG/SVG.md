---
创建日期:
  -  2022/7/4
---

1、 小写相对 大写绝对
	相对：基于上一个点的位置为起始
	正负： 是看上一个点为准 左边是－ 右边是＋（忽略不写）
2、path 
l   x,y    **基于上个点 x左（-）右（+） ，y上（-）下（+）**  

	加粗常用
**M** = 移动起点  //   m 50 20   =》  以（50,20）位置为起始点  
**L** = 直线   // m 50 20 l 20 50 =》从（50,20）到（20,50）作直线  
**H** = 水平线  //  m 50 20 h 50  =》 从（50,20）到（50,50）绘制一条平行线  
**V** =  垂直线  //  m 50 20 v 50  =》 从（50,20）到（100,20）绘制一条垂直线  
C = 三次贝赛曲线   //
S = smooth curveto  
Q = 二次贝赛曲线  //
T = 映射  //
**A** = 弧形  //
**Z** =   结束路径，回到原点 //






##### 圆和直线 画 搜索框放大镜图标
```
<!-- 绘制搜索框的放大镜图标 -->
<svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="none" stroke="currentColor" stroke-linecap="round" stroke-linejoin="round" stroke-width="2" class="feather feather-search" viewBox="0 0 24 24">

	<defs></defs>
	<!-- 圆-->
	<!-- cx cy是 圆心坐标 r是半径 stroke-width是边框，没写的就是没有  -->
	<circle cx="11" cy="11" r="8"></circle>
	
	<!-- 杆 -->
	<!-- 起始（21，21）连接点是相对坐标（-4.35，-4.35） 
 即M点的 左边上方点连接方式直线 -->
	<path d="M21 21l-4.35-4.35"></path>

</svg>
```

#####  多弧度画月亮 白/黑夜模式按钮
	注意有的参数值连着写没空格也不报错。 如 1 1 1  写成 111
```
   <svg class="moon" fill="none" stroke="currentColor" stroke-linecap="round" stroke-linejoin="round" stroke-width="2" width="24" height="24" viewBox="0 0 24 24">

   <defs></defs>

   <!-- M起点(21 ,12.79) , 最后两个参数 :  终点(21,12.79) -->
   <!-- 弧形中心点 (9,9)    -->
   <!--  角度(x轴旋转的角度  有值就是有倾斜,  以圆出现 的底边是x轴 )  -->
   <!-- 倒数第四个参数: 绘制大的还是小的部分（一个圆弧有缺口 可以看作有两个弧套娃，因为给了起点和终点 ）   0小   1大 -->
   <!-- 倒数第三个参数: 起点到终点0逆时针   1顺时针 -->
   <!-- A 9 9 0 1 1  11.21 3   -->
   <!-- 这里把 11.21 3 作为 第二段圆弧的起点 -->
   <!--   7 7 0 0 0   21   12.79 z -->
   <path d="M21 12.79A9 9 0 1 1 11.21 3    7 7 0 0 0 21 12.79z"></path>
  </svg>
```


##### 画十字 添加图标
```
<svg class="btn-icon" xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="3" stroke-linecap="round"  stroke-linejoin="round" class="feather feather-plus">
	 <line x1="12" y1="5" x2="12" y2="19" />
	 <line x1="5" y1="12" x2="19" y2="12" />
</svg>
```