---
创建日期:
  -  2022/8/4
---
#### TCP
![[url的http工作流程图.png]]
#### 浏览器输入url后 http请求返回的完整过程
	1、跳转
	2、查缓存
	3、解析dns
	4、创建tcp
	5、发生request请求
	6、接收response返回

#### 网络协议层

![[网络协议经典五层模型.png]]
1、物理层 -> 硬件设备
2、链路层 -> 硬件之间  创建数据链路连接
3、网络各节点之间传输创建逻辑链路
##### 传输层
	1、端对端 End to End 服务
	2、屏蔽了下层数据通信的细节，只需要会用。
##### 应用层
	1、协议构建在tcp协议之上
	2、屏蔽网络传输细节，只需要会用。
##### 发展历史
	1、HTTP/0.9
		1、只有get
		2、没有 header等描述数据包
		3、服务发送完毕，直接关闭tcp连接（一次一个发生和请求）
	2、HTTP/1.0
		1、新增POST PUT HEADER的命令
		2、新增 stratus code（请求状态） 和 header （发生和接收数据描述包）
		3、多字符集支持，多部份发送，权限，缓存等
	3、HTTP/1.1
		1、持久连接（打开后不会立即关闭）
		2、pipline（同一个连接内一次可以发送多个请求，以排队方式。但出现串行和并行问题，取决于消息处理的速度不同。）
		3、新增host 和其他一些命令（可以跑多个服务 判断来源 如：nodejs 或java ）
	4、HTTP2 还在迭代中
		1、以二进制传输（之前是以字符串传输）
		2、好处 : 同一个连接多个请求不再依赖顺序传输。
		3、头信息压缩以及推送等。以及提高效率功能（每次的信息头都是字符串，占带宽），压缩后减少带宽。推送意思是服务端具备主动发送能力。
			  1、 推送的工作流： **（并行）**
				  1、先获取html页面，获取js和css文件。以html文本连接形式，依赖浏览器解析内容。
				  2、再次根据url地址做请求对应js和css文件。
				  3、顺序问题 ，先html，解析再根据依赖去获取js和css。而有推送后则请求html，同时把js和css推送到客户端。是并行执行。效率和性能更快一些。

#### 三次握手
	目的：规避无效，主要由网络延时导致的服务器开销问题。避免丢包，服务端关闭。客服端无效的发送。以及服务端是否关闭当前的端口。
	1、syn :标志位。 
	2、seq :发送一个数字一般是1。 
	3、ack :seq的数值+1。
	1、http只有请求和响应。
		1、先进行 tcp connection (传输通道)  与 服务器 连接。
			发送给服务端 syn=1  seq=1
		2、server 接收开启tcp socket端口， 
			返回给客户端 syn=1  seq=1+1   seq=1  
		3、客户端 接收校验后，应答服务端。
			ack=1+1  seq=1 

![[三次握手时序图.png]]

#### 抓包现象查看三次握手
	URI  统一资源标识符
		URL和URN的统称
	URL  统一资源定位器
		举例： http://user:pass@host.com:80/path?query=string#hash
			hash 是定义 如果找到的文档非常大，一下返回太多，我们只需要某个片段，现在web用于相当于锚点定位的作用。
	URN  永久统一资源定位符
		在资源移动之后还能被找到 。目前还没有非常成熟的使用方案
	
![[抓包看三次握手应答图.png]]

#### 报文
![[简易报文示意图.png]]

#### 缓存
	Last-Modified 资源是否更新是否采用缓存
	Etag
		数据签名 数据有修改则 改变 利用hash
	配合If- Match 或者 If-Non-Match使用
	对比资源的签名判断是否使用缓存
	
![[缓存示意图.png]]
```javascript
	//nodejs 过期时间 经过服务器验证   
response.writeHead(200, {       
	'Content-Type': 'text/javascript',       
	'Cache-Control': 'max-age=20000, no-cache' , 
	'Last-Modified':'123', 'Etag':'777'     
	}) 
	const etag = request.headers['if-none-match'] 
	if(etag === '777'){ 
		response.writeHead(304,{ 
			'Content-Type': 'text/javascript',       
			'Cache-Control': 'max-age=20000, no-cache' , 
			'Last-Modified':'123', 'Etag':'777 
		}) 
		response.end('') 
	}else{
		 response.writeHead(304,{ 
			 'Content-Type': 'text/javascript',       
			 'Cache-Control': 'max-age=20000, no-cache' , 
			 'Last-Modified':'123', 'Etag':'777 
		}) 
		response.end() 
	} }
```

#### cookie属性
	max-age 和 expires设置过期时间
	Secure 只再https的时候发送
	HttpOnly 无法通过 document.cookie访问

![[cookie属性的多级子域.png]]
```javascript
const http = require('http') 
const fs = require('fs') 
// chrome 浏览器 的设置域名的工具 HostAdmin.App 
//二级域名共用cookie 
// domain 设置 a.test.com b.test.com 只要是.test.com 都可以共用cookie 
http.createServer(function (request, response) {   
	console.log('request come', request.url)   
	if (request.url === '/') {    
		 const html = fs.readFileSync('test.html', 'utf8') 
		if(host === 'test.com'){ 
			response.writeHead(200, {       
			'Content-Type': 'text/html',       
			'Set-Cookie': ['id=123; max-age=2', 
			'abc=456;domain=test.com']    
		})     
		response.end(html) 
	}   
} }).listen(8888)
console.log('server listening on 8888')
```
#### 长连接
	Connection:keep-alive 就是 长连接

![[浏览器看长连接步骤图1.png]]

![[浏览器看长连接步骤图2.png]]

![[浏览器看长连接步骤图3.png]]

```javascript
// 当调慢网速就会发现 端口一样。 所以 后端返回加 keep-alive就可以长连接了 
response.writeHead(200, { 
	'Content-Type': 'image/jpg', 
	'Connection': 'keep-alive' // or close
}) response.end(img)

```
#### 数据协商
	Accept
	Accept-Encoding //压缩协议
	Accept-Language //语言 q是权重值越大越优先
	User-Agent //移动还是 pc
	content-Type //返回格式
	content-Encoding   //Accept-Encoding 的 声明 
```javascript
//压缩就是 减少没用的内容 空格 换行说明的 
const http = require('http')
const fs = require('fs') 
const zlib = require('zlib') 
http.createServer(function (request, response) { 
	console.log('request come', request.url) 
	const html = fs.readFileSync('test.html') 
	response.writeHead(200, {
		 'Content-Type': 'text/html',
		 // 'X-Content-Options': 'nosniff' 
		 'Content-Encoding': 'gzip' 
	}) 
	response.end(zlib.gzipSync(html))
 }).listen(8888)
	console.log('server listening on 8888')
```

```javascript
<form action="/form" id="form" enctype="application/x-www-form-urlencoded"> 

// 相当于写在url 后面 但是http 是放到body内传输 form data multipart/form-data // http 会认为是大文件, 拆分成多个部分进行传输, 会自动生成一段boundary hash 作为分隔的标识遇到hash就是下一段。
```
	302 会再次走后端
	301 而不会再走后端直接 重跳转 省一次请求 301 是长缓存 从缓存拿跳转。不清浏览器缓存是不会 取消的 要少用或不用
	
![[form提交相当于拼接在url里示意图.png]]
 
```javascript
	if (request.url === '/') {   
	    response.writeHead(302, {  // or 301       
		    'Location': '/new'     
		})    
		response.end()   
	}   
	if (request.url === '/new') { 
		response.writeHead(200, {       
			'Content-Type': 'text/html',     
		})     
		response.end('<div>this is content</div>')   
	} 
}).listen(8888)
```
