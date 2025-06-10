# Electronic-ticket-system-for-tourist-attractions

#### 介绍
实现了一个基于epoll的多路转接服务器，由epoll获取TCP连接以及请求事件，并加锁推送到任务队列，由线程池获取任务并通过向MySQL连接池进行SQL查询，取得结果后再由epoll的写事件发送响应。并附带了一个简易的基于Easyx的客户端，可以实现与服务器的简易通信。

**开发环境和使用的技术知识**

C/C++、VS2022、VSCode、Xshell、单例模式、多线程、互斥锁、条件变量、线程池、MySQL


#### 部署教程

- 客户端

	在Visual Studio 2022中导入头文件与源文件 , 并将Jsoncpp库放在Visual Studio 2022项目的可执行程序下 , 再将Jsoncpp设置到Visual Studio 2022的文件目录 , 修改项目设置  , C/C++/代码生成/运行库/改为DLL  , 并将配置属性/高级/字符集 改为使用多字节字符集 , 即可编译运行. 如:

![文档](./文档.png)

- 服务器

	以centos7为例 , 确保有MySQL C connect库 与 Jsoncpp库 . 将服务端代码拉取到服务器中 , 在代码中找到Log的文件位置,并修改为位置 , 直接在项目目录终端中 make , 即可使用Makefile编译 .

```
启动服务器:
	./Server 端口号
查看Log输出:
	tail -n 100 -f 路径/log.txt
```

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request

#### 服务器流程

	// TODO