---
创建日期:
  -  2022/8/10 
---

相当与 每次 先执行一次 efferct  当 reactive 后 会再次 efferct，
有个细节  就是 交互  e1  执行 出现 e2   e2切换回e1  又出现e3 则e1切到e3
每次  reactive  都把 key 收集了 给efferct用

	举例
```javascript
	effect(() =>{   //parent =null , activeEffect =e1
		state.name    //name  ->e1
		effect(()=>{ //parent =e1 , activeEffect =e2
			state.age //age  ->e2
		})
		state.address   //address  ->e1
		effect(()=>{ //parent =e1 , activeEffect =e3
			state.age   //age  ->e3
		})
	})
```

```javascript

export let activeEffect = undefined;

class ReactiveEffect{
	public parent =null;
	public active = true;  //默认激活 为true
	 
	constructor(public fn){
		//用户传递的错那湖是也会当this上 this.fn = fn
	}
	run(){
			if(!this.active){  //非激活
				this.fn();
			}
			//执行函数，不需要进行依赖收集
	
			//手机  就是当前effect 和骚后渲染的属性关联在一起
		try{
			this.parent= activeEffect   //记录下
			activeEffect = this;
			reutrn this.fn() // 当稍后调用取值操作的时候 就可以获取到这个全局的activeEffect
		 
		}finally{
			activeEffect = this.parent;  //还原
			
		}
			  
	}
	
}



export function effect(fn){
	//这里fn可以根据状态变化  重新执行 ，effect可以嵌套写

	const  _effect = new ReactiveEffect(fn);
	_effect.run(); //默认先执行一次
}


```



	
```javascript
const {effect, reactive} = VueReactivity;  //封装了很多api使用
const state = reactive({name:'zf', age:13，address:{num:11}});
 
effect(()=>{
// 此effect函数默认先执行一次，对响应式数据取值的过程中数据会依赖于当前的effecgt
	app.innerHTML = state.name + '今年' + state.age +'岁'
})
 
```

```javascript

// src/index.ts
export {activeEffect} from './effect'; 
  
// src/reactive.ts
 
const enum ReactiveFlags{  //解决伪装数据再次代理（reactive）拦截
	IS_REACTIVE = '__v_isReactive'
}

exprot function reactive(object){// 只能做对象的代理
	 
 
	//中间函数 proxy 效果
	const proxy = new  Proxy(target,{
		get(target,key,receiver){
			if(key === ReactiveFlags.IS_REACTIVE){
				return true;
			}
			activeEffect
			track(target,'get',key)
			return Reflect.get(target,key,receiver);
		},
		set(target,key,value,receiver){
			return Reflect.set(target,key,value,receiver);
		}
	}); 
	return proxy;
}
 
```
