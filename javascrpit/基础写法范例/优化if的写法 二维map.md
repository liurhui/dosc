---
创建日期:
  -  2022/8/5
---
	多种条件情景根据type和count 得到pic图片
	1、麻烦这样写浪费时间  不推荐
```javascript
const getImg = (res) => {
	if(res.type === 0){
		return 'pic1';
	}
	if(res.type === 1 && res.count === 6.6){
		return 'pic2';
	}
	if(res.type === 1 && res.count === 8.8){
		return 'pic3';
	}
	....
	if(res.type === 3 ){
		return 'pic9';
	}
}
```
	2、采用数组编码，再采用filter过滤，但如果只找到一条就结束可以改用find() 。找到直接结束。
```javascript
const refactorGetImg = (res) =>{
	const arr =[
		[0,false,'pic1'],
		[1,6.6,'pic2'],
		[1,8.8,'pic3'],
		[2,1,'pic4'],
		[2,3,'pic5'],
		[2,5,'pic6'],
		[2,31,'pic7'],
		[2,365,'pic8'],
		[3,false,'pic9'], 
	];
	return arr.filter(item =>{
		return res.type === item[0] && (res.count === item[1] || !!res.count === !!item[1]);
	})[0][2];
}

console.log(refactorGetImg({ type:0 })); //pic1
console.log(refactorGetImg({ type:1, count:6.6 })); //pic2
console.log(refactorGetImg({ type:9 })); //pic9



```
	3、采用map，一维map 更生代码 把两个参数 组合为一个参数，如果有传递count参数 就组合type
```javascript
const map = new Map([
	[0,"pic1"], 
	[1_6.6,"pic2"],
	[1_8.8,"pic3"],
	[2_1,"pic4"],
	[2_3, "pic5"],
	[2_5,"pic6"],
	[2_31,"pic7"],
	[2_365,"pic8"],
	[3,"pic9"], 
])
fucntion mapPic(type,count){
	return map.get(count? type + "_" + count:type)
}


或者优化为二维
fucntion mapPic(type,count){
const map = new Map([
	0:pic1, 
	1:{
	 6.6:pic2,
	 8.8:pic3,
	},
	2:{
	 1:pic4,
	 3:pic5,
	 5:pic6,
	 31:pic7, 
	 365:pic8,
	},
	3:pic9, 
])
	return count?map [type][count]:map[type]
}
```