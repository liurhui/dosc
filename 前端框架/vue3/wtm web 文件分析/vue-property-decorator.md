vue 3 又不需要这样去写 ts 了 操蛋

vue 支持ts写法， 依赖 vue-property-decorator ，这个组件完全继承 vue-class-componet 。


#### 初识 
	长这个样子
```typescript
<script lang="ts"> 
import { Component, Vue } from 'vue-property-decorator';

@Component 

export default class HelloWorld extends Vue { }

</script>

```

#### 装饰器
```typescript
@Component (完全继承于vue-class-component) 
@Emit 
@Inject 
@Provice 
@Prop 
@Watch 
@Model Mixins (在vue-class-component中定义); 
@Ref

```

##### Component  参数巨多
```
// 先了解这几个
name: 'TsDemo', 
components:{}, 
computed:{}, 
props:{}, 
watch: {}, 
filters: {},
```

##### 监听和触发
`$emit  ->   @Emit`
`$on   -> this.$on`

```javascript

addToCount(n) { 
	this.count += n;
	this.$emit('add-to-count', n)
 },

演变成
@Emit() 
addToCount(n: number) { 
	this.count += n 
 }



```

```javascript
父接收
<template> 
	<div> 
		<Emit2 @handle-emit1="handleEmit1" @test="handleTest"></Emit2>
	</div> 
</template> 

<script lang="ts"> 
import {Component, Vue} from "vue-property-decorator"; 
import Emit2 from './emit2' 

@Component({ components: { Emit2 } }) 

export default class Emit extends Vue { 
	public emit2 = 0; 
	handleEmit1(val) { 
		console.log(val) 
		this.emit2++ 
	} 
	
	handleTest(val) { 
		console.log(val)
	} 
} 
</script>

子发
mounted() { 
	console.log('mounted') 
	this.$on('handle-emit1', (val) => { console.log(  val); }) 
	this.$on('test', (val) => { console.log( val); }) 
}

@Emit() handleEmit1(n: string) { 
	console.log('触发') 
} 
@Emit('test') handleTest(n: string) { 
	console.log('触发') 
}


```

##### props  父传子
```javascript
@Prop() 
num!: number; 

@Prop({default: 'default'})
str!: string; 

@Prop()
numStr!: number | string;

```

##### computed  计算属性   
```typescript
computed: { UserName: function() { return this.firstName + this.lastName; } }

演变

@Component()

get UserName(): string { return this.firstName + this.lastName; }

```


##### watch  监听
```typescript

// 参数  ，  { 属性配置 }
@Watch('obj', {deep: true, immediate: true})    
objChange(newVal: Obj, oldVal: Obj) {    //冒号后面 类型 
	console.log(newVal, oldVal); 
	//   改变用 $set
}
```

##### mixins  混合
	相当于可以把多个 minxins.js 定义的 变量 方法  全部 一次 minxs()到某个页面去用。
```typescript

import Vue from 'vue'; 
import Component from 'vue-class-component'; 
@Component // 一定要用Component修饰 
export default class myMixins extends Vue { 
	value: string = "Hello" 
 }


使用
import Component {mixins} from 'vue-class-component'; 
import myMixins from 'mixins.ts';
@Component 
export class myComponent extends mixins(myMixins) { 
	// 直接extends myMinxins 也可以正常运行 
	created(){ 
		console.log(this.value) // => Hello
	} 
 }

```


##### ref   用于 指向 元素或子组件引用信息
	使用 调用子组件 1、方法写法： .方法（）    2、变量写法:  .变量
```typescript

<template> 
	<div class="add_form">
		<UserMessage ref='UserMessageComponent'></UserMessage> 
		<button @click="handleChildFun">访问子组件</button>
		<button @click="addFormFun" ref="refC">测试ref</button> 
	</div> 
</template> 

<script lang="ts"> 
import {Component, Vue, Ref} from "vue-property-decorator"; 
import UserMessage from 'userMessage.vue'; 
@Component({ components: { UserMessage } })
export default class Index extends Vue{
	@Ref() UserMessageComponent!: UserMessageComponent; 
	@Ref('UserMessageComponent') UserMessageComponentTow!: UserMessageComponent;
	@Ref() readonly refC!: HTMLButtonElement; 
	
	private handleChildFun(): void {
	    this.UserMessageComponent.del();  // 调用子组件的 方法
	    this.UserMessageComponent.list;  // 调用子组件的 public  变量
		this.UserMessageComponent.livePlatList; // 调用子组件的 private 变量  报错
		this.refC.innerHTML;   //  原生的一般就是拿dom 树 
	} 
} 
</script>
```
