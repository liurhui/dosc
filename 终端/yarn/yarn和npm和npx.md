### 初始化 生成package.json
	用CLI 则自带 package.json
`npm init  //手动输入值  常用`   
`npm init -y  //采用默认值`   
```js
{
  "name": "liurhui",
  "version": "1.0.0",
  "description": "",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "",
  "license": "ISC",
  "dependencies": {
    "webpack": "^5.74.0",
    "webpack-cli": "^4.10.0"
  }
}

脚手架 多一个 "private": true,   用于 拦截 npm publish 指令，防止误操作发布。

脚手架没用 "main"  ，因为默认脚手架生成的项目不是当库用 ， main是当库时候的入口。

"scripts"   属性是可以执行脚本命令  npm run xxx
	当 start\ test\  stop\restar  可以省 run

===================================  掌握
实际上写在哪里最后会按引入使用时候才被编译，但是为了规范得这么写。

开发  devDependencies
npm install webpack --save-dev     
npm install webpack -D
npm i webpack -D   常见


开发和生产  dependencies
npm install axios
npm i axios      常见

根据 package.json 依赖包  直接npm install


peerDependencies 对等依赖  
	如 element-plus -> vue3     
	如 ant design  -> react 、react-dom



=================================== 了解 小知识
npm 遵从 semver 版本规范 npm semver  "^5.74.0"
X.Y.Z
	X   API 大改动
	y   向下兼容 新功能添加
	z   修正bug
^ 开头是大概版本， 不动x 更新到最新的y.z 。
~ 开头是大概版本， 不动x.y 更新到最新的z 。

package.json 是大致版本
package-lock.json  是真实版本 锁死。
常见 把 -lock 散掉，重新安装下如 bug修复情况。


=================================== 
npm install webpack -g;   全局
npm install webpack    当前文件目录路径下有效

一般 npm install webpack -g
到具体项目内 可以做一个 npm install webpack  ，

 
```
### CLI创建
	vue cli  安装 
	vue create vue-recycle   (项目名不能大写) 
	cd .\vue-recycle\ 
	yarn serve     （等效执行 npm run serve）
	安装包是 yarn add    xx   


### 修改 默认的 npm 还是 yarn 执行下载
	如果你选择了 Use Yarn，会在 C:\Users\用户名\下 自动生成配置文件.vuerc 。
	 修改.vuerc文件
```js
{
  "useTaobaoRegistry": false,
  "packageManager": "npm" 
}

 // "packageManager": "yarn"
```
	当然，你可以将.vuerc文件删掉，然后创建的时候，又重新让你选择创建工具了。
 
### 指令比较
```js 
// npm
npm install 
npm install react --save  
npm unistall react --save
npm install react--save-dev
npm update --save
npn run serve
npm run build

缺点: 是不是实时同步，可能找出国内外版本差异。
npm config get registry
npm config set registry https://registry.npm.taobao.org


// yarn
yarn
yarn add react
yarn remove react
yarn add react --dev
yarn upgrade
yarn serve  运行
yarn build   编译 


// npx
npx  webpack




```

备忘老项目
```js
yarn add vue-router@3.2.0      vue2 用 3
yarn add less less-loader@5.0.0
yarn add vuex@3.6.2
yarn add element-ui@2.15.9
yarn add axios@0.26.1
yarn add mockjs@1.1.0
yarn add echarts@5.1.2 

"dependencies": {
    "axios": "^0.26.1",
    "core-js": "^3.8.3",
    "echarts": "^5.1.2",
    "element-ui": "^2.15.6",
    "js-cookie": "^3.0.1",
    "less": "^4.1.2",
    "less-loader": "^10.2.0",
    "mockjs": "^1.1.0",
    "vue": "^2.6.14",
    "vue-router": "^3.5.3",  //低了没router.addRoute('Main', item)
    "vuex": "^3.6.2"
  },



yarn add  webpack webpack-cli
```
 
### vue cdn链
```js
CDN:
        压缩版：
<script src="https://cdn.bootcss.com/vue/2.5.16/vue.min.js"></script>
        完整版：
<script src="https://cdn.jsdelivr.net/npm/vue@2.5.16/dist/vue.js"></script>
```

### elment ui  
安装
```
yarn add element-ui -S
```
按需引入
```
1、yarn add babel-plugin-component -D

2、配置.babel.config.js
	
 "plugins": [
    [
      "component",
      {
        "libraryName": "element-ui",
        "styleLibraryName": "theme-chalk"
      }
    ]
  ]
```