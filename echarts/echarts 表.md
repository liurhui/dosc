---
创建日期:
  -  2022/6/10 
---
#### 官网
	https://echarts.apache.org/handbook/zh/get-started/
	折线line 、 柱状bar  、  扇形pie
### 指令
```

yarn add echarts@5.1.2


"dependencies": { 
    "echarts": "^5.1.2", 
  },

哪个文件用在哪个文件引入
import * as echarts from "echarts";
```
### 数据包格式模板
```
   返回一组数据Object
   data:{
	   code:20000,
	   data:{
	    //折线图数据包
			orderData:[
			
			   //  标题      keyArray 就是每个key
			   //  折线数据有几个对象就有几条折线   series
			 data:[
			 {苹果: 4827, vivo: 1530, oppo: 2393, 魅族: 170, 三星: 4160,小米: 7545},
			 {苹果: 778, vivo: 1385, oppo: 4052, 魅族: 5295, 三星: 1642,小米: 4310},
			 {苹果: 331, vivo: 5484, oppo: 1037, 魅族: 4467, 三星: 2811,小米: 2436},
			 {苹果: 6784, vivo: 362, oppo: 5292, 魅族: 3929, 三星: 5381,小米: 7907},
			 {苹果: 5666, vivo: 6347, oppo: 1006, 魅族: 6542, 三星: 7435,小米: 917},
			 {苹果: 5705, vivo: 691, oppo: 676, 魅族: 7501, 三星: 538,小米: 2264}
			   ]
			   // 日期  x轴文本  xAxis
			date:['20191001', '20191002', '20191003', '20191004', '20191005', '20191006',"20191007"]  
		   ],


		//饼图数据包
			// name 和 value  是名称和值   series
			videoData:[
				 {name: '小米', value: 2999}
				 {name: '苹果', value: 5999}
				 {name: 'vivo', value: 1500}
				 {name: 'oppo', value: 1999}
				 {name: '魅族', value: 2200}
				 {name: '三星', value: 4500}
			]


		//柱状图  
			// date是x轴文本 xAxis       
			// new和active  是柱状数据有几个就有几个柱状 series
			userDat:[
			 {date: '周一', new: 5, active: 200}
			 {date: '周二', new: 10, active: 500}
			 {date: '周三', new: 12, active: 550}
			 {date: '周四', new: 60, active: 800}
			 {date: '周五', new: 65, active: 550}
			 {date: '周六', new: 53, active: 770}
			 {date: '周日', new: 33, active: 170}
			],
		   
	   }
   
   }
   
```

#### 折线图
![[Pasted image 20220610164059.png]]
```
  mounted() {
    getData().then((res) => {
      console.log(res);
      const { code, data } = res.data;
      if (code === 20000) { 
        const order = data.orderData;
        const xData = order.date;
        const keyArray = Object.keys(order.data[0]);
        const series = [];
        keyArray.forEach((key) => {
          series.push({
            name: key,  //点击key 会隐藏这条key的折线
            data: order.data.map((item) => item[key]),  //折线数据 数据来源
            type: "line",  // 类型是实心线
          });
        });

        // 货物 折线图
        const option = {
          xAxis: {
            data: xData,  // x轴的文本
          },
          yAxis: {},
          legend: {
            data: keyArray,  //标题是 带折线颜色的key
          },
          series, // 折线数据
        };
		//初始化且生成表
        const E = echarts.init(this.$refs.echarts);  
        E.setOption(option);
```
 
 
#### 柱状图
![[Pasted image 20220610164251.png]]
```
 // 用户图  柱状图
        const userOption = {
          legend: {  //标题文本颜色
            textStyle: {
              color: "#333",  
            },
          },
          grid: {
            left: "20%",   
          },
          tooltip: {  //鼠标放上去  弹窗显示队友信息数据
            trigger: "axis",  // 模式 放在轴上面 触发出现效果
          },
          xAxis: {  //x轴文本
            type: "category",  //种类
            data: data.userData.map((item) => item.date), //数据来源
            axisLine: {  //x轴 横线
              lineStyle: {
                color: "#17b3a3",
              },
            },
            axisLabel: {  //x轴文本
              interval: 0,
              color: "#333",
            },
          },

          yAxis: [  //y轴文本
            {
              type: "value",  //数值
              axisLine: {  //y轴 横线 
                lineStyle: {
                  coloer: "#17b3a3",
                },
              },
            },
          ],
          color: ["#2ec7c9", "#b6a2de"], //两组数据的颜色
          series: [
            {
              name: "新增用户",  //数据第一组
              data: data.userData.map((item) => item.new), //数据来源
              type: "bar",
            },
            {
              name: "活跃用户",  //数据第二组
              data: data.userData.map((item) => item.active), //数据来源
              type: "bar",
            },
          ],
        };
        
        const U = echarts.init(this.$refs.userEcharts);
        U.setOption(userOption);
```


#### 扇形图
![[Pasted image 20220610164234.png]]
```
 // 饼图
        const videoOption = {
          tooltip: {   //鼠标放上去 弹窗提示
            trigger: "item",  //放在每个块上触发出现效果
          },
          color: [  //每个数据块的颜色
            "#0f78f4",
            "#dd536b",
            "#9462e5",
            "#a6a6a6",
            "#e1bb22",
            "#39c362",
            "#3ed1cf",
          ],

          series: [  //扇形图数据
            {
              data: data.videoData, //数据来源
              type: 'pie'  //模式是圆形
            }
          ],
        }

        const V = echarts.init(this.$refs.videoEcharts)
        V.setOption(videoOption)
```
### 封装
如果 封装的只有一个div 那说明 只需要一个div就可以呈现内容
```
<template>
  <div ref="echart"></div>
</template>

<script>
import * as echarts from 'echarts'
export default {
  props: {

    isAxisChart: {
      type: Boolean,
      default: true
    },

    chartData: {
      type: Object,
      default() {
        return {
          xData: [],
          series: []
        }
      }

    }
  },

  watch: {

    chartData: {
      handler: function () {
        this.initChart()
      },
      deep: true  
    }

  },

  methods: {

    initChart() {
      this.initChartData()
      if (this.echart) {
        this.echart.setOption(this.options)
      } else {
        this.echart = echarts.init(this.$refs.echart)
        this.echart.setOption(this.options)
      }
    },

    initChartData() {
      // 折线图
      if (this.isAxisChart) {
        this.axisOption.xAxis.data = this.chartData.xData
        this.axisOption.series = this.chartData.series
      } else {
        this.normalOption.series = this.chartData.series
      }
    }
    
  },

  data() {
    return {
      axisOption: {
        legend: {
          // 图例文字颜色
          textStyle: {
            color: "#333",
          },
        },

        grid: {
          left: "20%",
        },

        // 提示框
        tooltip: {
          trigger: "axis",
        },

        xAxis: {
          type: "category", // 类目轴
          data: [],
          axisLine: {
            lineStyle: {
              color: "#17b3a3",
            },
          },
          axisLabel: {
            interval: 0,
            color: "#333",
          },
        },

        yAxis: [
          {
            type: "value",
            axisLine: {
              lineStyle: {
                color: "#17b3a3",
              },
            },
          },
        ],
        color: ["#2ec7c9", "#b6a2de"],
        series: [],
      },

      normalOption: {
        tooltip: {
          trigger: "item",
        },
        color: [
          "#0f78f4",
          "#dd536b",
          "#9462e5",
          "#a6a6a6",
          "#e1bb22",
          "#39c362",
          "#3ed1cf",
        ],
        series: [],
      },

      // 用于表示图表是否已经渲染
      echart: null,

    }

  },

  computed: {
    options() {
      // 柱状图或 折线图 ：  否则没有
      return this.isAxisChart ? this.axisOption : this.normalOption
    }
    
  }
  
}

</script>
```
### 使用
```
      <el-card style="height: 280px">
        <!--<div style="height: 280px" ref="echarts"></div>-->
	    <echarts :chart-data="echartData.order" style="height: 280px" 
        </echarts>
      </el-card>

      <div class="graph">
        <el-card style="height: 260px">
          <!--<div style="height: 240px" ref="userEcharts"></div>-->
          <echarts :chart-data="echartData.user" style="height: 240px" > 
          </echarts>
        </el-card>

        <el-card style="height: 260px">
          <!--<div style="height: 240px" ref="videoEcharts"></div>-->
          <echarts :chart-data="echartData.video" :is-axis-chart="false"
 style="height: 240px" ></echarts>
		</el-card> 
      </div>


import Echarts from "../../src/components/ECharts";


  components: {
    Echarts,
  },

// 要一个 高度就好
```