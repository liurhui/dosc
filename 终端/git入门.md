
当git add 后撤删操作
```c
// 先看一下 git add. 后是有多少文件
git status
// 撤删add的所有文件
git reset HEAD
//  撤删add的某文件
git reset HEAD src/mode/hello.java
```

当git add 后报错warning: LF will be replaced by CRLF in   ******
其实可以忽略没什么后遗症
```c
//(仅对当前git仓库有效）  
git config core.autocrlf false 
//(全局有效，不推荐设置全局）   用这个比较快
git config --global core.autocrlf false 

```

直接删除git仓库的 某个文件
```c
git commit -m"test1.txt"
```
恢复被删除的git仓库的 某个文件
```c
git checkout -- test1.txt
```


初次从本地提交数据到git仓库
```c
//设置用户名 及 邮箱账户  类似联系人和邮箱
git config --global user.name "lxxxi"
git config --global user.email "xxxxx@xx.com"

git init
//改为自己的仓库
git remote add origin https://git.com/ouzzy/xxxxxxx.git
//同步仓库到本地
git pull origin master
// 本地非空文件 放到缓存区
git add .
//"" 内写当前提交的描述  从缓冲区推到git仓库
git commit -m "first commit"
// 推送到仓库
git push origin master
```

迭代本地仓库 到git仓库
```c
// 包含工作区、暂存区与版本库之间的文件变化
git status
//查看比较 迭代文件差异
git diff file

// 本地非空文件 放到缓存区
git add .
git status
//"" 内写当前提交的描述  从缓冲区推到git仓库
git commit -m "first commit"
// 推送到仓库
git push origin master
```

回滚
```c
//查看已存在的历史版本 
git log
//根据版本号回滚  版本号输入前面的7位即可
git reset --hard 0a73015
```

滚回原本(回滚后想回到最新的)
```c
git reflog
git reset --hard 5896314
```