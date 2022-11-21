
epoll模型
	回调 和无限制



下载 http://nginx.org/en/download.html
Mainline version   -  开发版本
Stable version - 稳定版本
Legacy version - 历史版本

官方安装教程 http://nginx.org/en/linux_packages.html

  RHEL/CentOS  是用同一套   比较简便
  ubuntu  是用一套   比较麻烦


sudo yum install yum-utils
vim /etc/yum.repos.d/nginx.repo
```yum


[nginx-stable]
name=nginx stable repo
baseurl=http://nginx.org/packages/centos/centos版本号/$basearch/
gpgcheck=1
enabled=1
gpgkey=https://nginx.org/keys/nginx_signing.key
module_hotfixes=true

[nginx-mainline]
name=nginx mainline repo
baseurl=http://nginx.org/packages/mainline/centos/$releasever/$basearch/
gpgcheck=1
enabled=0
gpgkey=https://nginx.org/keys/nginx_signing.key
module_hotfixes=true
```
sudo yum-config-manager --enable nginx-mainline
yum list |grep nginx

yum install nginx
y

nginx -v    版本号
nginx -V    更详细的依赖  一堆 --width-xxx 连接符的东西


/etc/logrotate.d/nginx    日志轮转   定时切割日志

主要配置文件
/etc/nginx
/etc/nginx/nginx.conf     启动访问
/etc/nginx/conf.d      
/etc/nginx/conf,d/default.conf    默认 server加载

缓存目录
/var/cache/nginx

日志目录
/var/log/nginx 

模块目录
/usr/lib64/nginx.modules
/etc/nginx/modules

调试终端
/usr/sbin/nginx    
/usr/sbin/nginx-debug

帮助文档
/use/share/man/man8/nginx.8.gz



/etc/nginx/fastcgi_params      
/etc/nginx/uwsgi_params
/etc/nginx/scgi_params

编码转换    少用到
/etc/nginx/koi-utf
/etc/nginx/koi-win
/etc/nginx/win-utf

http协议匹配 content-type 对应  扩展更多的类型
/etc/nginx/mime.types    


守护进程 管理器模式 配置
/usr/lib/systemd/system/nginx-debug.service
/usr/lib/systemd/system/nginx.service  
/etc/sysconfig/ngnix
/etc/sysconfig/nginx-debug