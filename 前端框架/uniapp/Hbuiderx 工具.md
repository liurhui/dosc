#### 连接夜神模拟器
	plus. 的h5+方法只可能在模拟器或真机运行 ，小程序和 内置浏览器都运行不了，因此记录下用模拟器运行的方法。如果模拟器重启启动那么需要 重新执行 cmd命令一次。否则运行code会提示已失去连接。
1、进入nox的安装目录bin下，打开当前目录的cmd窗口执行以下两个命令：
2、先运行模拟器exe 
`nox_adb connect 127.0.0.1:62001`
`nox_adb devices`

![[Hbuiderx 工具1.png]]
进入Hbuilderx的安装目录下，
`\HBuilderX\plugins\launcher\tools\adbs,执行cmd下述两个命令`：
`adb connect 127.0.0.1:62001`
`adb devices`
![[Hbuiderx 工具2.png]]
![[Hbuiderx 工具3.png]]


