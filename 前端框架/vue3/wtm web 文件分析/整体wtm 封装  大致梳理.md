vue-property-decorator   
的 get  是计算属性函数    mixin 混合 也是类似 追加函数到本文件的意思。
可以用于  html 的  事件的函数  或者 是子组件的prop的 参数函数

src
	vue-custom
		component
			1、index.ts     //整体 封装更名 wtm 组件

	setting.ts   // 独立定义了/store/modules/settings  的mixin 里用的每个变量的默认值 以及类型。
	
vue-custom/component/index


//layout布局

		{ key: "Card", value: Card },    //   内容布局
		
 //page	 页面
	
	  { key: "WtmDialogBox", value: DialogBox },    //   弹出框
	  { key: "WtmSearchBox", value: SearchBox }, //  查询
	  { key: "WtmTableBox", value: TableBox }, //   列表
	  { key: "WtmButBox", value: ButBox }, //   操作按钮
	  { key: "WtmFormItem", value: FormItem }, //   表单项
	  { key: "WtmFlexBox", value: FlexBox }, //   felx 控制
	  { key: "WtmCreateForm", value: CreateForm }, //   创建表单 js
	  { key: "WtmRenderView", value: RenderView }, //   string  转函数式组件
	  { key: "WtmIcon", value: Icon } //   icon

Card
	1、if 路由名    显示路由名称 
	2、一个插槽
	3、if 插槽底部
			内容 插槽

##### 1、DialogBox
	1、一个弹窗框 el-dialog   		
			头：里面 一个 el-link (超链接)      文本
			内容是  插槽
			底：两个按钮    关闭 和 提交
	2、el-drawer  抽屉 类似 拉宽窄的一个可拖拉的边框按钮
			内容是  插槽
			底：两个按钮   关闭和提交

##### 2、SearchBox
	1、一个内容布局 el-dialog   		
			WtmCreateForm
				WtmFormItem
					el-buttn-group
						两个el-button    查询    ， 折叠查询面板   （点击触发 是否执行）
					el-button    重置按钮
							


##### 3、TableBox
	1、v-loading   
			容器
				el-table
					el-table-column
						模板 遍历
							el-table-column
								模板 插槽
									插槽
							el-table-column
								模板 插槽
									el-button   详情
									el-button   修改
									el-button   删除		
							el-table-column
				 容器   table右侧
					ek-checkbox-group
						el-checkbox
					容器 折叠展开功能
						i     展开?     展开图标 :  折叠图标
				el-popover 弹出框
					el-checkbox-group
						el-checkbox
					容器 折叠展开功能
						i     展开?     展开图标 :  折叠图标


##### 4、ButBox
	就是 增删改查的button 集合页面

##### 5、FormItem
	1、el-col
				el-fotm-item
					if 是否修改   插槽 
					模板
						if  是否图片
						else 插槽   修改文本

##### 6、FlexBox 全部是 样式  用 & 组合的样式 且还引入了 mixin样式
	
	容器
		插槽
##### 7、CreateForm  是纯js
	又分成了 2个js    
	一个 interface 接口定义类型主要是elui 对应表单的参数    
	一个 utils  定义表单每行用到的组件 input  button  checkbox 等。把每个组件用到的参数都封装成一个private函数，等于 外部new了这个Utils类  ， 运行后通过render 去遍历 keys，每个key 就是组件名找到后 。
	

##### 8、RenderView


##### 9、Icon  引入 静态的font图标资源  再这里面 进行遍历然后 return 出去
