# device_TI8127

###TI8127使用说明：

####【1】配置摄像机ip

1.摄像机默认的ip：192.168.1.238；

2.用网线和电脑直连，设置电脑ip网段和摄像机是同一网段；

3.在IE浏览器（只能用IE）打开摄像机ip地址，弹出的登陆界面中输入

	用户名：admin，密码：123456；端口：12560；

4.登陆成功会进入到摄像机的界面，在配置项下面，选择网络参数，修改摄像机的ip地址，确认设置。

####【2】代码目录结构
1.example目录结构：

- -----main.cpp是TI上跑羚羊云平台例子代码
- -----Makefile，编译脚本，编译后生成LYsdk_main的可执行程序
- -----include，用到的相关头文件
- -----libs用到的相关链接库

####【3】TI平台编译羚羊云平台例子

1.在代码目录下执行make，编译生成可执行文件

2.使用ssh登录到摄像机：用户名：root；密码：ipnc367*

3.TI摄像机文件系统是只读，需要设置成可写，使用下面命令设置opt目录可写：

    echo 1 >/sys/devices/virtual/mtd/mtd7/writable
    mount -oremount,rw /opt
   
4.使用mount挂载到虚拟机上：

	如：mount -o nolock 192.168.88.43:/srv/nfs /mnt/   
   
5.在/opt/ipnc/app/下创建一个羚羊应用目录，如：LYSdk

6.在羚羊应用目录下创建一个存放链接库的目录libs（这个目录名字和Makefile脚本里的链接路径要一致）

7.将编译好的可执行文件放到羚羊应用目录LYSdk下，将所有的动态链接库拷贝带libs目录下，拷贝时使用-rdf保持库的软链接关系

8.将配置文件拷贝到camera_config.ini羚羊应用目录LYSdk下，该配置文件记录了设备的SN和Cid，可以通过配置文件更换修改

####【4】简单更换程序

1.使用TI摄像机本地ip进行ssh登录

	用户：root； 密码：ipnc367*

2.设置摄像机文件系统/opt目录可写状态

    echo 1 >/sys/devices/virtual/mtd/mtd7/writable
    mount -oremount,rw /opt

3.使用mount挂载到虚拟机上：

	如：mount -o nolock 192.168.88.43:/srv/nfs /mnt/   

4.进入程序存放目录，将新的程序拷贝覆盖掉旧程序

	cd /opt/ipnc/app/LYSdk/
	cp /mnt/Ti8127/LYsdk_main .

5.重启系统

	reboot