https://juejin.cn/post/7005140118960865317/    比较全的笔记把离线的md 放到掘金了

git 获取的示例[[vue3快速上手]]
https://github.com/Panyue-genkiyo/vue3-learning

https://www.yuque.com/cessstudy/kak11d/wi9lp4   vue2 带目录的笔记

https://www.bilibili.com/video/BV1Zy4y1K7SH?p=152&spm_id_from=pageDriver&vd_source=8c250cc458d476b5cdce2e6ed0343a02
F:\尚硅谷 vue3应用视频资料


#### 1、入口文件 变化了  
#### 2、setup  更像是原生js  写法 可以直接定义变量 和 函数
	1、函数 以 function 开头  ，  变量调用可以不用写this
	2、setup 不能写 await  setup   ,不是异步函数
	3、js变成响应式 ref    和    .value     。html不用写.value
	4、基本类型用ref    ,  对象类型用 reactive  可以不用 .value 了
	5、可以把所有都当作键值对 封装成对象 给reactive 免去 .value
	6、setup  执行时机在 beforeCreate 前面。所以没有this
总结：
	变量尽量用  封装成 person 这种对象形式 ， 用reactive去统一的响应式。
```javascript

<template>
  <!--vue3的组件模版结构可以没有根标签-->
  <h1>我是app组件</h1>
  <h1>我叫{{ name }}, {{ age }}岁</h1>
  <h3>职位:{{ person.type }}</h3> 
  <h3>爱好:{{ person.hobbies }}</h3>
  <h4>测试的数据c:{{ person.a.b.c }}</h4>
  <button @click="changeInfo">修改人的信息</button>
</template>

import {ref,reactive}  from 'vue'
 setup(){ 

    //准备数据 data 
    let name = ref('py'); 
    let age = ref(21);  
    
      let person = reactive({
      name: 'py',  
      age: 21,
      type: 'frontend developer',
      salary: '30',
      hobbies: ['抽烟', '喝酒', '烫头'],
      a:{
        b:{
          c: 666
        }
      }
    });
     
    function changeInfo(){
      name.value = '李四';
      age.value = 42;
      person.type = 'UI developer';  
      person.a.b.c = 100;
      person.hobbies[0] = 'play tennis';
    }
    //方法 methods 
    function sayHello(){ 
      alert(`My name is ${name.value}, ${age.value} ${age.value === 1  ? 'year' : 'years'} old`);


 //返回一个对象

    return { 
      name, 
      age,  
      person,
      changeInfo
      sayHello   
 }
}```
 
html 里 这样写才能更改 视图
```javascript
this.$set(this.person,'sex','女')；  // 给data加 属性：sex 值：女
this.$delete(this.person,'name');  // 删除 属性： name

this.$set(this.person.hobby,0,'逛街') //修改
this.person.hobby.splice(0,1,'逛街')//修改
```


#### 3、父子组件
vue2
父传了 子 没有 props 接收，则会被$attrs接收
父写了 html   子没slot 接收  则会被 $vnode 接收   ，有slot 则被 $slots接收。
	插槽有名称 则 得父写  ` <template>`
	
vue3
父传子   子 不写props  则会报错， 没传但接收不警告。 有传必有收，有收不一定传。
子 的 setup 参数  
	1、props可以接收父传的  子的 props未定义的参数。
	2、context 是个对象 ，含有 attrs   emit    slots  
```javascript
<script>

import { reactive } from 'vue';
export default {
  name: 'Demo',
  beforeCreate() {
    console.log('----@bc');
  },
  props: [],  //props 不接收但是也得 定义
  emits:['hello'],
  setup(props, context){  
	//1、context.attrs 同参数一的props一样 不接收的这里会拿到，都接收这里就没有数据

	//2、context.emit  是给父的方法  额外要定义emits:['hello'],
    return {
      person,
      test(){
        context.emit('hello', 666); //传给父事件函数 hello  参数是666
      }
    }
    
	//3、context.slots   是插槽就是父写的  <template v-slot:qqq>
	console.log(context.slots); 就拿到 qqq
}

</script>
``` 
补充：
	如果子传给父 emit 如果 同名 js内置函数， 父用 .native 接收
	如 举例vue2   `  子 this.$emit(click, xx)       父  @click.native`
 

####  4、computed   计算属性
不推荐
	this.  访问 setup 的reactive响应数据
```javascript
//vue2的写法  举例
// computed:{
//   fullName(){
//     //vue2看得到vue3 注意
//     return this.person.firstName + '-' + this.person.lastName;
//   }
// },
// setup(){ 
//   }
```
推荐 写成统一化形式返回
	解释：
		写在 setup(){}  内， 且应当 谁被计算则返回谁。不要用函数名作为返回，封装进去作为person的函数 来简化 返回。
```javascript
  setup(){
    let person = reactive({
      firstName: 'pan',
      lastName: 'yue',
      age: 21,
    });
 
 //计算属性(完整写法，既考虑了读也考虑了改)  
    person.fullName = computed({
      get(){
        return person.firstName + '-' + person.lastName
      },
      set(name){
        let [ fn, ln ] = name.split('-');
        //响应式
        person.firstName = fn;
        person.lastName = ln;
      }
    })

    //返回一个对象
    return {
      person,
    }
}
```

#### 5、watch  监听
多种情况使用常规5 种写法，主要分 ref 和  reactive。
1、immediate: true  立即 ：一运行没变化时也 watch触发一次。
2、deep: true  深度   vue3  无法直接用，写法有变化。
3、reactive  定义的变量 多层嵌套的 对象 不需要 deep:true 也可以 直接监听，因为reactive根本没有 deep。
4、 ref  
	基本类型 不加  .value  
	对象类型分两种情况：
	1、不加.value 是会成功 但是不会被捕获，因为地址没变化，但是内容变了，但不会捕获到，想捕获 得加  `{deep:true}`。
	2、加 .value 会成功，也会被捕获 ，是因为直接检测值而不是地址。
	
监听 
	分为ref 和  reactive 两种响应式
	ref   newValue 和 oldValue  不会出问题。
	reactive   newValue 和 oldValue  会直接出问题。
问题：
	reactive 无法直接 监听 reactive的 oldValue的值。
解决办法：
	单独把 需要监听用到 oldValue值 的 reactive 独立出来 用ref 定义。

问题：
	reactive  默认强制开启deep  且无法关闭(估计以后会修bug)，造成无效的监听开销大。
解决办法：
	watch 时候 直接  xx.xx 到具体的 对象（不用xx 全部对象），且写成函数形式语法。 
```javascript
setup(){ 
    let sum = ref(0); 
    let msg = ref('你好'); 
    let person = reactive({ 
      name: '张三',
      age: 18,
      job:{
        j1:{
          salary: 20
        }
      }
    });
   //5、单独 reactive  具体对象写法
	watch([() => person.age, () => person.name], (nv, ov) => {
	      //此时nv和ov都是数组
	        console.log('person的age或name发生改变了',nv, ov);
	});
	
	//返回一个对象 
    return {
      sum,
      msg,
      person
    }
}
```
	 示例代码
	 newValue,oldValue  简写  nv,ov
```jvavascript
//1、单个ref
	watch(sum, (nv, ov) => { 
       console.log('sum的值发生变化了');
       console.log(`newValue:${nv}, oldValue:${ov}`);
     }, { 
		immediate: true //一上来就更新
    });

//2、多个ref 同时监听
	watch([sum, msg], (nv, ov) => {
		//此时nv和ov都是被监视属性值的数组
		console.log(Array.isArray(ov)); //true
		console.log('sum的值或者msg的值发生变化了');
		console.log(`newValue:${nv}, oldValue:${ov}`);
	},{
		immediate: true
	});

//3、reactive 每个都监听   
	 watch(person, (nv, ov) => {
	     console.log('person变化了'); 
	     console.log(nv, ov); 
	  }, { 
	     deep: false //此处的deep配置是无效的 
     });

//4、 reactive 某个对象非全部对象 也不是某个具体属性
// 这个属性的值它依然是一个对象 ，所以deep配置有效
	watch(() => person.job, (nv, ov) => {
       //这里依然无法拿到正确的ov，因为依然监视的是对象
	  console.log('person的job信息发生改变了',nv, ov);
    }, {
     //这里必须要加deep:true注意
      deep: true  
   })
```

#### 5.1、wacthEffect    监视作用
	不传递参数 
	默认带有immediate: true 效果
	在wacthEffect函数内用了哪个变量，变量就被监视
	与 computed 有点类似， computed是必须写返回值。而 wacthEffect 注重过程，不需要返回值。

#### 6、生命周期变化
	销毁的概念变化了， 变成卸载的说法。
	v3 变化不大 大体上一致。只是说一些说法变化了。
	on 比 没on的执行快一步。
	放到 setup 内叫组合式api写法。
	
`beforeCreate`===>`setup()`
`created`=======>`setup()`
`beforeMount` ===>`onBeforeMount`
`mounted`=======>`onMounted`
`beforeUpdate`===>`onBeforeUpdate`
`updated` =======>`onUpdated`
`beforeUnmount` ==>`onBeforeUnmount`
`unmounted` =====>`onUnmounted`
```javascript
import { ref, onBeforeMount, onMounted, onBeforeUpdate, onUpdated, onBeforeUnmount, onUnmounted } from 'vue';

setup(){
    let sum = ref(0);
    //通过组合式api的形式去使用生命周期钩子
    ///setup()相当于beforeCreate()和created()
    onBeforeMount(() => {  console.log('----beforeMount----'); });
    onMounted(() => {  console.log('-----mounted-----'); });
    onBeforeUpdate(() => {  console.log('-----beforeUpdate-----') });
    onUpdated(() => { console.log('-----updated-----'); });
    onBeforeUnmount(() => { console.log('-----beforeUnmount----'); });
    onUnmounted(() => { console.log('-----unmounted----'); })
    console.log('-----setup----')
    //返回一个对象
    return {
      sum,
    }
  },
```
#### 7、自定义hook函数
都封装到外部文件   以usexxx.js 开头文件名
就是复用 把js代码独立出去 引入使用。
```javascript

```
#### 8、toRef  跟toRefs  是一组
只能返回一层 { }  嵌套的得 链式 点操作拿属性。
就是用于批量 return 用 否则每个都写出来很麻烦
```javascript
<template>
    <h4>{{person}}</h4>
    <h2>姓名：{{name}}</h2>
    <h2>年龄：{{age}}</h2>
    <h2>薪资：{{job.j1.salary}}K</h2>
    <button @click="name+='~'">修改姓名</button>
    <button @click="age++">增长年龄</button>
    <button @click="job.j1.salary++">涨薪</button>
</template>

import {ref,reactive,toRef,toRefs} from 'vue'
    export default {
        name: 'Demo',
        setup(){
            //数据
            let person = reactive({
                name:'张三',
                age:18,
                job:{
                    j1:{
                        salary:20
                    }
                }
            })
            // const name1 = person.name
            // console.log('%%%',name1)
            // const name2 = toRef(person,'name')
            // console.log('####',name2)
            const x = toRefs(person)
            console.log('******',x)
  
            //返回一个对象（常用）
            return {
                person,
                //直接 ... 是解构的意思 把  里面的name  age  job 解构出来
                ...toRefs(person)
            }
        }
```

#### 9、shallowRef  和 shallowReactive
shallowReactive 只外层 一层进行响应式
shallowRef  只基本数据类型 不对 对象处理。
ref 定义对象 实际上还会去调用reactive ，而shallowRef  定义对象是不会去调用reactive 。
```javascript 
<script>
    import {ref,reactive,toRef,toRefs,shallowReactive,shallowRef} from 'vue'
    export default {
        name: 'Demo',
        setup(){
            //数据
            // let person = shallowReactive({ //只考虑第一层数据的响应式
            let person = reactive({
                name:'张三',
                age:18,
                job:{
                    j1:{
                        salary:20
                    }
                }
            })

            let x = shallowRef({
                y:0
            })

            console.log('******',x)
            //返回一个对象（常用）
            return {
                x,
                person,
                ...toRefs(person)
            }
        }
    }

```


#### 10、readonly  和shallowReadonly
-   `readonly`: 让一个响应式数据变为只读的（深只读）。
-   `shallowReadonly`：让一个响应式数据变为只读的（浅只读）。
#### 11、toRaw  和markRaw
toRaw   响应式对象转为普通对象
markRaw 标记一个对象， 不会成为响应式对象。