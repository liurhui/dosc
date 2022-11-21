
匹配顺序查找到的第一个元素   的选择器 querySelector
 匹配全部满足的   querySelectorAll(“选择器”)  返回 数组
```javascript
 var modeSwitch = document.querySelector('.mode-switch');
 modeSwitch.addEventListener('click', function () {
    document.documentElement.classList.toggle('dark');
    modeSwitch.classList.toggle('active');
  });
```
id  对应的选择器 getElementById   返回属性节点对象。
class   对应的选择器 getElementsByClassName  返回类名的元素集合。
标签 参数不区分大小写 getElementsByTagName   返回对象数组 集合。
元素名 getElementsByName。



#### classList类名篇
1、查看类名 element.classList 返回类名的数组集合，伪数组形式存储

2、增加类名 `element.classList.add('类名')`定要加引号，可以添加一个或多个类名

3、删除类名 `element.classList.remove('类名')` 一定要加引号，可以添加一个或多个类名

4、切换类名 `element.classList.toggle()`有就删除，没有就添加

5、`element.classList.contains('类名')` 判断是否包含某个类名，返回一个布尔值

##### 范例
```js
const box = document.querySelector('.box')
 
// 1. 查看类名 element.classList  返回类名的数组集合，伪数组形式存储
console.log(box.classList) // DOMTokenList(1)  DOMTokenList ['box', value: 'box']
console.log(box.classList[0]) // box
 
// 2. 增加类名  element.classList.add('类名')  一定要加引号
box.classList.add('addDiv1')  // class="box addDiv1"
 
// 3. 删除类名  element.classList.remove('类名')  一定要加引号
box.classList.remove('addDiv1') // class="box"
 
// 4. 切换类名  element.classList.toggle()  有就删除，没有就添加
box.addEventListener('click', function () {
    box.classList.toggle('box2')
})
 
// 5. 修改并覆盖类名
box.className = 'box1' // class="box1"
 
// 6. element.classList
console.log(box.classList.contains('box')) // false
```