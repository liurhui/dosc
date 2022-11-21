行  有4根线，4行分别是  顶线 中线  基线  底线
两行 之间  
基线到基线 是 line-height 行高 ，  
底线到顶线叫 行距， 那么一半是叫半行距
顶线到底线 叫 font-size  。
所以   上半行距  顶线 中线  基线  底线 下半行距  也叫 line-height。
即  font-size  和 line-height  实际上 是同轴。
font-size  一定是小于 line-height 才会在容器内。

行距 = line-height - font-size = 0  即 <0 就重叠

div的高度取 line-height的值
1、font-size  >  line-height       文本会溢出 
2、font-size < line-height    文本会在 div内但不一定居中
3、div  height == line-height  看起来是在中间 
4、div height  > line-height  看起来  靠上
5、div height  < line-height   看起来  偏下

line-height 默认是 120% 即 1.2倍 的 font-size的大小
`normal 默认   number 数值  length 固定行间距   % 字体百分比     inherit继承`
```css


body{
	line-height: 1.5;
}
h1, h2, h3, h4, h5, h6{
	line-height: 1.2;
}


```