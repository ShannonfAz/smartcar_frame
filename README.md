# smartcar_frame(智能车开源gui界面框架，小工具，自己写的一些库，以及一些逐飞库addons）
## 目前该项目处在v0.1，功能较少，目前程序仅有如下功能：
- 建议将基于此框架写出来的程序丢在rc.local以达到开机自启
- 如果你这么做后，开机时会显示如下内容
  
  WIFI list
  
  1.你于/etc/wpa_supplicant.conf配置的第一个wifi
  
  2.第二个wifi
  
  etc.

  up:p16 down:p15 quit:p13
  
  press p14 to connect to:
  
  n.你当前选择的那个wifi配置

- 此时你可以通过逐飞扩展板左侧的p15，p16选择wifi，p14进行连接

  连接完成后，该wifi右侧会出现(connect）

  此时可以按p13退出了

  如果该程序已执行过一次wifi连接，那么久久派下一次开机时，会自动尝试连接你上一次连的那个wifi，保持你的wifi稳定，即可轻松开机自动连wifi
- 退出后，你会进入如下界面

  wlan0:

  你板卡的ip，和ifconfig得到的wlan0 ip一致

  press P13 key

  for 0.2s to quit

- 保证你的板卡与你的电脑（如果你要使用手机上的juicessh之类的工具连接板卡，则你的手机）连接的是同一个wifi

  即可通过各种ssh软件使用该ip连接板卡

- 按P13 0.2s以退出该页面
- 之后你会来到本gui界面的主界面
  
  内容如下：

  1.wifi_setting_tool//就是你开机进入的那个wifi连接与ip显示工具，详见我的wifi_setting_tool仓库

  2.your program//当你将你的循迹程序写进your_program.cpp后，选择并进入该菜单即可运行循迹程序

  3.pid setting//基于文件的参数保存工具，目前可设置左右电机占空比/速度（其实就是各自保存一个unsigned int，没加速度环可以把它当占空比用，加了速度环可以把它当速度用），舵机的p与d，电机的p与i（都是float）

  4.camera test//运行后于屏幕左上角显示摄像头获取的160*120彩色图像

  5.reboot//执行sync，reboot，安全重启

  6.poweroff//执行sync，poweroff，安全关机

  battery_voltage 一个电压值 V//自动识别2s/3s电池，当电压低于7.4/11.1v时，改为显示"byd go to charge the bat now!"

  up:p16,down:p15,quit:p13

  press p14 to run:

  你当前选择的功能

- 通过使用p15，p16切换选择功能，使用p14执行功能，如果需要退出此gui程序，则按p13，此时你会进入一个确认是否退出的页面，再按一次p13终止程序
# 关于wifi选择程序wifi_setting_tool的配置，请参考[ShannonfAz/wifi_setting_tool](https://github.com/ShannonfAz/wifi_setting_tool)
# 接下来讲解如何将你基于该框架搓出来的程序正确放置在板子上
1. 打开板子，连接ssh，此时你所处路径应该就是/home/root
2. mkdir pid_setting

   此目录将存放pid setting工具设置的pid之类的参数

3. 将你编译出来的可执行文件，如果你没改CmakeLists.txt那应该就叫smartcar_frame，传到/home/root
4. 先照着wifi_setting_tool仓库的讲解，至少配一个wifi（你开机总得先连至少一个网吧）
5. vi /etc/rc.local
   
   接下来直接照搬
   
```
#! /bin/bash -e

do_start()
{
#systemctl disable dhcpcd
#systemctl stop dhcpcd
insmod /usr/lib/modules/4.19.190+/aic8800_bsp.ko
insmod /usr/lib/modules/4.19.190+/aic8800_fdrv.ko
sleep 3
home/root/smartcar_frame &
}
do_stop()
{
rmmod aic8800_fdrv.ko
rmmod aic8800_bsp.ko
}
case "$1" in
   start)
     do_start
   ;;
   stop)
     do_stop
   ;;
 esac

exit 0
```

搬完后重启即直接启动程序，无需往rc.local塞udhcpc -i wlan0 &之类的乱七八糟玩意儿，本框架内置连wifi所需一切流程，开机自启此程序即可

强烈建议修复那byd 狗屎wifi驱动，不然重启会卡kernel panic

## 修复流程：

1. 于你的ubuntu上，找个文件夹，或者直接默认的用户文件夹（~）就行，执行下面的命令

   git clone https://gitee.com/seekfree/LS2K0300_Library.git

   就是逐飞的原版开源库

2. 进入【软件】交叉编译工具 上位机等，进入旧世界WiFi驱动修复重启不panic，即可找到aic8800_bsp.ko，这个是修复好的wifi驱动
3. 将该文件丢入板卡上的/usr/lib/modules/4.19.190+/，可使用scp命令，也可以mobaxterm直接拖过去，这样就把那狗屎wifi驱动替换掉了
4. 替换完之后，输入sync，回车，一定要记得同步，换vmlinuz内核也是一样的，换驱动换内核记得记得sync
5. 重启，此时仍会卡kernel panic，按一下99派上的复位键，开机，此时再重启一次，你会发现此时已经不kernel panic了，驱动修复完成
