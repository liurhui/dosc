---
创建日期:
  -  2022/8/5
---
	打印时间需要转行成JSON不能直接输出。
`console.log(JSON.stringify(new Date()))`

	1、原本是   "2022-01-06 12:26:47"
	转换为 iso
`var a =new Date(r.Data[0].StartTime.replace(/-/g, '/')); `
	输出为 "2022-01-06T04:26:47.000Z"	

	2、把 - 改为 /
`var a = r.Data[0].StartTime.replace(/-/g, '/');`
	输出为 "2022/01/06 12:26:47"

	3、只改第一个 - 改为 /
`var a = r.Data[0].StartTime.replace("-","/");`
	输出为 “2022/01-06 12:26:47”

```javascript
var nowtime = time.gettime.timeConvert(new Date(), 3); 
var StartTime = r.Data[0].StartTime.replace(/-/g, '/'); //-改为 / 
var date3 = new Date(nowtime).getTime()- new Date(StartTime).getTime(); 
//时间差的毫秒数 
console.log( JSON.stringify( new Date(date3)) ) 
// 相差时间 + 1970 01 ... 的和 时间
```


	4、返回的是当前时间
`time.gettime.timeConvert(new Date(), 4);`
	输出为 “2022-01-06 12:26”

	5、流水号 日期
`new Date().toLocaleDateString().match(/\d+/g).join("")`
	输出为  2022119

	6、流水号随机数
`console.log( (Math.round(Math.random() * 23 + 100)).toString() );`
	输出为 112

	7、流水号32位
```javascript
randomString(len) { 　　 
	var len = len || 32; 
	var $chars=
	'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'; 
	var maxPos = $chars.length; 
	var pwd = ''; 
	for (var i = 0; i < len; i++) { //0~32的整数 　　
		pwd += $chars.charAt(Math.floor(Math.random() * (maxPos+1))); 
	} 　
	return pwd; 
} 
	this.randomString(32);
```
输出 co7vdCUkt0Wmgi6Gsi9Owoxbeu2DBXAt



```js
<script>
 var date1=new Date()
 var year=date1.getFullYear()
 var month=date1.getMonth()
 var date=date1.getDate()
 var day=date1.getDay()
 var xq=new Array('星期日','星期一','星期二','星期三','星期四','星期五','星期六')

 document.write('当前日期为：'+"</br>")
 document.write("年："+year+"</br>")
 document.write("月："+(month+1)+"</br>")
 document.write("日："+date+"</br>")
 document.write("星期："+xq[day]+"<hr>")
</script>
```