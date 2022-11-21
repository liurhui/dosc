---
创建日期:
  -  2022/8/10 
---

script   编译 的入口文件
		dev.js      
		 require('minimist')   用来解析命令行参数
	‘iife’  是立即执行函数的意思    
	'cjs'  是node中的模块   
	‘esm’是浏览器中esModule模块



#### 理解reactivity.global.js 的工作原理
//script 引入reactivity.global.js  是用 VueReactivity ， 用框架是 Vue。
`const {effect,reactive}= VueReactivity;`
effect   代表副作用函数，如果 数据发生了变化。会做什么
reactive  讲数据变成响应式  proxy
shallowReactive  , readonly, shallowReadonly 

##### 原因：
vue2 是用 defineProperty 只能劫持已经存在的，对删除和新增不太方便。
vue3则使用Proxy 实现 可以监听对象 和原本不存在的数据。
##### 用法：
	
```javascript
const {effect, reactive} = VueReactivity;  //封装了很多api使用
const state = reactive({name:'zf', age:13，address:{num:11}});
console.log(state)


//同数据，多次reactive 则 不相等,当用了new WeakMap(); 后就为true
const state1 =reactive(data)
const state2 =reactive(data)
console.log(state1 === state2)

//伪装下，把上一次的结果 给下一次
const state1 =reactive(data)
const state2 =reactive(state1)
console.log(state1 === state2)


 
effect(()=>{
// 此effect函数默认先执行一次，对响应式数据取值的过程中数据会依赖于当前的effecgt
	app.innerHTML = state.name + '今年' + state.age +'岁'
})

//  稍后name和age变化会重新执行effect函数
setTimeout(()=>{
	state.age = 14;
},1000)
```


##### 数组 
数组不做劫持 单独处理  其他数据可以通过proxy代理进行响应式劫持数据。


##### 响应式数据 代理的大概流程模拟
https://www.bilibili.com/video/BV1Q3411w7SQ?p=4&spm_id_from=pageDriver&vd_source=8c250cc458d476b5cdce2e6ed0343a02
25分钟 -29分钟
```javascript

// src/index.ts
export {effect} from './effect';
export {reactive} from './reactive';

exprot const isObject = (value) =>{
	return typeof value === 'object' && value !== null;
}

// src/reactive.ts

//拦截目的是对代理过的数据 不再代理
const reactiveMap =  new WeakMap(); //解决同数据 多次代理 回收拦截
const enum ReactiveFlags{  //解决伪装数据再次代理（reactive）拦截
	IS_REACTIVE = '__v_isReactive'
}

exprot function reactive(object){// 只能做对象的代理
	
	if(!isObject(target)){
	 //不是对象
		return
	}
	
	if(target[ReactiveFlags.IS_REACTIVE]){
		//解决伪装的数据 已经被代理过一次 则不再次代理
		return target
	}

	let exisitingProxy = reactiveMap.get(target);
	if(exisitingProxy){
	 // 判断同一组数据不进行多次代理
		return exisitingProxy
	}





	//中间函数 proxy 效果
	const proxy = new  Proxy(target,{
		get(target,key,receiver){
			if(key === ReactiveFlags.IS_REACTIVE){
				return true;
			}
			return Reflect.get(target,key,receiver);
		},
		set(target,key,value,receiver){
			return Reflect.set(target,key,value,receiver);
		}
	}); 
	return proxy;
}


举例：
let target ={
	name:'zf',
	get  alias(){
		return this.name   //指这个this
	}
}
const proxy = new  Proxy(target,{
		get(target,key,receiver){
			//return target[key];  // 这样this不正确 应该把this变成receiver
			return Reflect.get(target,key,receiver);
			
		},
		set(target,key,value,receiver){
			//target[key] = value;
			//return  true;
			return Reflect.set(target,key,value,receiver);
		}
	}); 
proxy.alias;

```
