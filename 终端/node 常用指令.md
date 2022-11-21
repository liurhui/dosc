无webpack 下运行 express 是 `nodemon app.js`
utf8 与 utf-8 不是同一个东西。
art-template 模板 用于 express


**1、快速删除 node_modules**
https://www.jianshu.com/p/1652a152a120
```node
先安装 再用指令删除 
cnpm install rimraf -g 
rimraf node_modules
```
**2、切换源**
```node
npm install -g cnpm --registry=https://registry.npm.taobao.org


nrm ls 参看所有数据源(淘宝镜像) 
nrm test 测试所有数据源的网络连接状况 
nrm use cnpm 切换数据源(镜像)
```
**3、清除缓存**
```node
npm cache clean --force
```
**4、nvm版本管理**
n 在 win无法使用 只能去github下载 nvm进行管理 node 降级升级版本
[https://github.com/coreybutler/nvm-windows/releases](https://github.com/coreybutler/nvm-windows/releases) 下载安装 nvm-setup.zip1.1.9
https://www.jb51.net/article/202124.htm  安装教程
```node
nvm ls //查看当前已安装的 nodejs版本
nvm v //查看 nvm当前版本
nvm ls available //查看 可用的node.js版本号

nvm install 12.17.0 安装 12.17.0版本 npm install -g [npm@6.14.4](http://npm@6.14.4)
nvm use 16.8.0 nvm uninstall 16.8.0

//安装成功后切换 版本 nvm use 12.17.0 用 管理员cmd 否则报exit status 1乱码错误
```
 




#### 用过的安装包备忘
**pacjage.json**
dependencies  需要发布到生产环境(上线)的。  -S
devDependencies 只用于开发环境，bulid时候用。   -D

**.browserslistrc**
	理解：https://www.jianshu.com/p/d45a31c50711  
```node

 
"browserslist": [ 
	"> 1%", // 所支持的浏览器使用率至少要1% 
	"last 2 versions",  
	"not ie <= 8" //不支持IE低于版本8 
]
```
**dependencies**
```node
"dependencies": { 
	"babel-runtime": "^6.0.0", //es 语法转义 
	"vue": "^2.3.3", 
	"vue-router": "^2.5.3", 
	"vuex": "^2.3.1", 
	"fastclick": "^1.0.6", //移动端 点击延时 去掉点击3秒延时 
	"vue-lazyload": "1.0.3", 
	"axios": "^0.16.1", 
	"jsonp": "0.2.1", //npm install jsonp 
	"better-scroll": "^0.1.15", 
	"create-keyframe-animation": "^0.1.0", 
	"js-base64": "^2.1.9", 
	"lyric-parser": "^1.0.1", 
	"good-storage": "^1.0.1" 
},


import fastclick from 'fastclick' 
fastclick.attach(document.body) // body 的div 按钮的点击的三秒延时都取消掉
```
**devDependencies**
```node
"devDependencies": {
	"babel-polyfill": "^6.2.0", // es api 补丁 如 promise 转义
}
```

```node
npm install express -g 
npm install -g express-generator


cnpm install nodemon 
cnpm install md5-node 
cnpm install concurrently



```


**loader ->sass**
```node
npm uninstall --save-dev sass-loader
npm uninstall --save-dev node-sass

2.然后再安装合适的版本

npm i -D node-sass@4.12.0
npm i -D sass-loader@7.1.0
```








#### 错误集合
**gyp问题  -> npm i  时 sass 报错**
```node
1、 npm install -g node-gyp  //管理员运行cmd

2、cnpm i -g --production windows-build-tools
3、cnpm i -g node-gyp
4、npm config set python python2.7 
5、npm config set msvs_version 2017

node-gyp ls  //如果运行后报 node-sass错误 先卸载再安装一次 
1、npm uninstall node-sass 
2、cnpm install --save-dev node-sass 
重新编译node-sass 
1、npm rebuild node-sass 
安装sass-loader 
2、npm install sass-loader --save-dev
```
**waring  -> npm run dev      是npm版本过高**
```node
//
Warning:Accessing non-exisstent property 'cd' of module ......
...... 
```
