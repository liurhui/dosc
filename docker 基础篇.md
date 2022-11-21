---
创建日期:
  -  2022/6/6 
---

# 来源记录

#### 教学教程
[https://www.bilibili.com/video/BV12Z4y1t7uu/?spm_id_from=pageDriver](https://www.bilibili.com/video/BV12Z4y1t7uu/?spm_id_from=pageDriver)


#### 安装笔记教程
[https://q.shanyue.tech/deploy/simple-docker.html#%E5%9C%A8%E6%9C%AC%E5%9C%B0%E5%90%AF%E5%8A%A8%E5%B9%B6%E8%BF%90%E8%A1%8C%E9%A1%B9%E7%9B%AE](https://q.shanyue.tech/deploy/simple-docker.html#%E5%9C%A8%E6%9C%AC%E5%9C%B0%E5%90%AF%E5%8A%A8%E5%B9%B6%E8%BF%90%E8%A1%8C%E9%A1%B9%E7%9B%AE)
 

#### 容器安装包
**docker安装包下载**

[https://www.docker.com/get-started/](https://www.docker.com/get-started/)

**wsl2 容器 补丁**
**文章**
[https://blog.csdn.net/qq_39611230/article/details/108625840](https://blog.csdn.net/qq_39611230/article/details/108625840) 
**补丁安装包**
[https://link.csdn.net/?target=https%3A%2F%2Fwslstorestorage.blob.core.windows.net%2Fwslblob%2Fwsl_update_x64.msi](https://link.csdn.net/?target=https%3A%2F%2Fwslstorestorage.blob.core.windows.net%2Fwslblob%2Fwsl_update_x64.msi) 
 

### 基础使用
1、直接 npm  i  安装
2、node server.js  （3000被占用换8080）
3、cmd 直接 执行  curl -vvv localhost:8080 成功显示
```
* Trying 127.0.0.1:8080... 
* Connected to localhost (127.0.0.1) port 8080 (#0) 
* > GET / HTTP/1.1 
* > Host: localhost:8080 
* > User-Agent: curl/7.79.1 
* > Accept: */* 
* > * Mark bundle as not supporting multiuse 
* < HTTP/1.1 200 OK < Date: Mon, 06 Jun 2022 08:22:13 GMT 
* < Connection: keep-alive 
* < Keep-Alive: timeout=5 
* < Content-Length: 132 
* < <!DOCTYPE html> 
* <html lang="en"> 
* <head> 
* <meta charset="UTF-8"> 
* <title></title>
*  </head> 
* <body> hello, shanyue. </body> 
* </html>
  Connection #0 to host localhost left intact
```

### docker容器 node.Dockerfile
#### 步骤
>node 版本很多 所以采用容器方式管理。

**1、 docker 需要先安装且运行。**

**2、可以借助 [https://hub.docker.com/_/node?tab=description](https://hub.docker.com/_/node?tab=description)  查看已存在的node镜像版本。(node:14-alpine 学习以体积比较小的来先学习这个基础。)**

**3、配置 node.Dockerfile 文件** 
``` 
# 选择一个体积小的镜像 (~5MB)
FROM node:14-alpine 

# 设置为工作目录，以下 RUN/CMD 命令都是在工作目录中进行执行
WORKDIR /code 

# 把代码置于镜像
ADD . /code
 
# 装包
RUN yarn


EXPOSE 8080


# 启动 Node Server
CMD npm start

```

**4、在执行终端  docker 指令**  

	4.1、生成镜像文件  docker build -f node.Dockerfile -t simple-node-app .
``` 
1、当项目内只有一个dockrfile文件时 
	  docker build -t simple-app . 
2、多个Dockfile文件 需要指定下 
	  docker build -f node.Dockerfile -t simple-node-app .
```
	4.2、用镜像文件启动容器  docker run -d --rm -p 3000:3000 simple-node-app


#### 容器指令 和 注释说明
```
docker run --rm -p 30000:30000 simple-app 

1、 --rm: 当容器停止运行时，自动删除容器 
2、 -p: 3000:3000，将容器中的 3000 端口映射到宿主机的 3000 端口，左侧端口为宿主机端口，右侧为容器端口 


1、 d 是 dockerfile缩写 由于文件内只有一个 配置文件所以可以不写
2、 -t 构建镜像的名称
3、 . 代表当前路径


如果修改了 package.json 得重新 生成镜像。 
否则无法变更  "scripts": {     "start": "serve . -p 30000",   }, server.listen(30000, () => {   console.log('Listening 3000') }) 

https://www.csdn.net/tags/NtzaMg1sMjYzMC1ibG9n.html 

#查看 镜像 对应的版本号  docker build -t simple-app:$(git rev-parse --short HEAD)  
#查看镜像 类似ls    docker images 
#查看镜像 文件过多筛选 前面的几条来看 docker images | head -5 
#删除所有镜像，不删除容器 docker rmi $(docker images -q) 
#查看镜像 docker images 
#查看运行中的容器 docker ps 
#查看所有容器 docker ps -a

```

#### 问题两者端口不是同一个（太久没用有点混淆了）

> 1、node server.js 是运行server.js文件 与 npm的 package.json 的serve端口无关 。
   2、npm start 运行的是 index.html文件 端口与 server.js的 server.listen 无关
   3、node.Dockerfile的 EXPOSE 端口号是预留的默认。有配置 docker run --rm -p 30000:30000 simple-app 则不会用默认。

```
1、docker -p 配置 30011：30000 
2、server 配置30000 结果： 打开提示http://localhost:30000/ 但是得访问 http://localhost:30011/才能 访问成功index.html。 

"scripts": {     "start": "serve . -p 30000",   }, 


 -p <hostPort>:<containerPort> 将容器端口<containerPort> 映射到指定的主机端口<hostPort>

多种写法 
https://www.csdn.net/tags/MtTaIg0sOTExMzA1LWJsb2cO0O0O.html
```

 
### docker容器 nginx.Dockerfile

>node体积太大不利于前端所以用 nginx 常用

```
1、 生成镜像文件
	docker build -f nginx.Dockerfile -t simple-nginx-app .
2、 把进行运行到容器（也就是启动容器）
	docker run -d --rm -p 3000:80 simple-nginx-app 
3、
	nginx.conf  


server {
    listen       80;
    server_name  localhost; 
    
    root   /usr/share/nginx/html;
    index  index.html index.htm;

    location / {
        expires -1;

        # 此时通过 docker-compose 打开地址，可发现添加了一个新的 X-Hello 响应头
        add_header X-Hello shanyue;
    }
}

4、
	nginx.Dockerfile 配置

FROM nginx:alpine 

ADD index.html /usr/share/nginx/html/
```


#### 注释说明
```
server {     
	listen       80;    # 服务端口     
	server_name  localhost;  # 服务ip 
	
	# 这个是访问root（也就是根目录） 是到 /usr/share/nginx/html目录 里面有 50x.html 和 index.html文件     
	root   /usr/share/nginx/html;     
	index  index.html index.htm;     
	
	location / { 
		# 可以在 F12的network 的headers的 response headers 新增头信息 
	  expires -1;         
	    # 此时通过 docker-compose 打开地址，可发现添加了一个新的 X-Hello 响应头         
	  add_header X-Hello shanyue;    
	 } 
}
```