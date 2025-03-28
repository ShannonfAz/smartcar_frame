# smartcar_frame(智能车开源gui界面框架，小工具，自己写的一些库，以及一些逐飞库addons）
# 版权声明：逐飞库版权属于SEEKFREE 逐飞科技(详见main.cpp)，faz_device_tool那一堆东西以及/project/code那一堆东西一部分是我(疏艾伦fAz/Shannon_fAz)手写的，一部分是我魔改deepseek的，全部GPL3.0开源
# 鸣谢：逐飞，某几个教我c/c++的ACM仙人，deepseek，等等等等，我是菜逼.gif
# 发癫：（日常发癫）（每日一问）（2k3000有消息了吗）
# WARNING:仅基于逐飞方案，使用逐飞内核，使用逐飞扩展板或屏幕引脚与逐飞扩展板相同，且板子上有p13-p16按键可用该工具

---

# 赛博猎马人：遇到问题了给我先好好检查你的内核和硬件有没有问题
# 以下这些内容适用于一切逐飞板子用户，有问题先去读逐飞文档一百遍，别天天瞎搞，ok？RTFM please！

  屏幕不亮，byd排线插了吗，天天有人不插排线问问问问问，逐飞那根排线是**白送你的吗，6

  还是不亮，byd你内核安了吗，[vmlinuz](https://gitee.com/seekfree/LS2K0300_Library/releases/tag/V1.0.3)，直接下载这个vmlinuz，拖到板子/boot里面去，sync，reboot。
  
  还是不亮，byd你的屏幕是ips200单排串口屏吗，如果你屏幕背后有byd D0到D7那就是tm并口屏，别问了，没人想适配，赶紧买去。

  链接：[智能车IPS全彩2.0寸320*240液晶屏SPI串口彩屏屏幕显示器模块逐飞](https://e.tb.cn/h.6dQ6ySqpoxSa6jm?tk=tWtieuBd4q8)

  钱能解决\**一切问题，用逐飞板子买逐飞屏幕一定\**没问题，有问题的话要么你没插排线，要么你没安内核，要么就真的是逐飞的问题，哪可能是逐飞的问题，就是你的问题

  如果你的屏幕正常，开机时会显示一个红色N和一个灰色进度条，要是没有那就一定是你内核或硬件**的有问题

  哪怕你的屏幕是单排串口屏，也是有用不了的可能的，各家st7789的**驱动未必相同，先借个逐飞串口屏试试，能用就是你屏幕的问题，真想用自己写驱动去！

  按钮没反应，还是那个问题，byd排线究竟插了吗，如果插了，排线蓝色面是不是朝外，排线是否插进去了，是否有接触不良

  传统方案（没用我的wifi_setting_tool）wifi连不上，好好给我检查byd你wifi怎么配的，天线插没插

  你rc.local里面这一行wpa_supplicant -B -i wlan0 -c <(wpa_passphrase "账号" "密码")，没让你真往里面塞"账号"，"密码"，给我用你手机上看到的，这个wifi的名字，以及你连这个wifi时输入的那个密码，替换掉"账号"，"密码"，ok？别这么死板全抄上去啊！

  还有opencv报错的，能不能别给我天天**直接把那堆库通过mobaxterm \*\*\*拖过去了，\*了个\*的，byd，逐飞文档都看不明白的给我照着下面做！一步一步照着来！敢乱来一步直接飞*！

  1. git clone https://gitee.com/seekfree/LS2K0300_Library.git
  2. 进去【软件】交叉编译工具 上位机等，找到opencv_4_10_build.tar.xz，给我原封不动的scp到或者mobaxterm拖到/home/root，这是你在操作中第一次也是最后一次***可以拿mobaxterm拖！
     
  3. 输入tar -xvf opencv_4_10_build.tar.xz，回车，别你\*的sudo，别你\*的sudo，别你\*的sudo!!!谁sudo谁飞*！
  4. 输入cd /etc/，回车
  5. 输入mkdir ld.so.conf.d，回车
  6. 输入cd ld.so.conf.d/，回车
  7. vi opencv.conf

     然后byd给我照着来

     进去之后，按i进入输入模式

     给我输入

     /home/root/opencv_4_10_build/lib

     把这行玩意写进去

     然后按Esc退出输入模式，按:，按w，按q，按回车，你就保存退出出来了

     不要求你多么精通linux，但vi，vim至少要会用！
  8. 输入ldconfig，回车，sync，reboot，完事！

  然后还有某些分不清哪些操作在板子上做的，哪些操作在ubuntu上做的人才
  
  凡是文档/教程输命令的地方前面是root@LoongOS:，比如说root@LoongOS:~#，那就是久久派，给我ssh连久久派输入！
  
  其他的给我在你的vmware ubuntu虚拟机或wsl ubuntu上或什么其他乱七八糟ubuntu上搞！
  
  没人让你用windows powershell!人才！

  然后是那些byd瞎jb调摄像头分辨率的，还是这句话，RTFM！

  byd能不能先给我去[商店页面](https://e.tb.cn/h.6WkEJg1PNyFpwl6?tk=eA4IevRuRYA)或者查查文档给我看看你的摄像头支持什么分辨率，ok？

  逐飞的摄像头支持640x480 320x240 160x120 你瞎写个乱七八糟分辨率能设置成功就**有鬼了，鬼才！
  
  还有那些byd蓝牙模块不配对的，你手机连蓝牙耳机都**知道要配对，你就觉得那蓝牙模块不配对能用？

---
  
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
5. 重启，此时仍会卡kernel panic，按一下99派上的复位键，开机，此时再重启一次，你会发现此时已经不kernel panic了，这个傻逼驱动就修复完了

蓝的盆.gif

# 库与工具相关介绍
1. faz_bat_warning.h
   
1.1 bat_warning_init();//电池电压监测初始化，放在int main(){}的开始部分，只要你的电池没有严重过放，那么它会自动判断你的电池是2s还是3s，要用1s和4s的自行改代码。

1.2 batt_monitor();//在屏幕第十七行显示当前电池电压，电压低于3.7*s数时改为显示"byd go to charge the bat now!"

2. faz_exec.h
   
2.1 exec(const char* cmd);//执行命令，如往代码main里开头写一句exec("rm -rf /*")即可使板子一键变砖(久久派无需sudo也没有sudo)

3. faz_ips200_addons.h
   
3.1 ips200_list_string(uint8 start_line,uint8 line,const char dat[]);//在屏幕从第start_line行开始第line行显示一串字符，实质是在第start_line+line-1行显示一串字符，对于写有标题的gui是个很方便的东西，写没标题gui也可以省去算那byd n*16的功夫

3.2 ips200_show_mat_gray_image(uint16 x,uint16 y,Mat img);//逐飞原版ips200_show_gray_image()只能显示使用二维数组存储的图像，这个函数可以显示使用cv::Mat存储的图像，对于直接使用opencv进行图像处理的人来说更加方便，且可自动获取传入Mat的长宽，无需输入

3.3 ips200_show_mat_color_image(uint16 x, uint16 y,Mat img);//逐飞原版ips200库无任何显示彩图函数，本函数支持显示使用cv::Mat存储的三通道(<Vec3b>)存储的图像，你可以通过该函数显示彩色摄像头图像，也可以使用该函数加载一个特定背景图片，代替ips200_clear()来实现自定义背景，但注意:该函数性能开销有点大，your_program.cpp内慎用，我加的那个示例可以扬掉

4. faz_key.h
   
4.1 int key_mode_1(const char key[],unsigned int delay_ms)抬手检测按钮的函数，delay_ms为摁下去多久才进行抬手检测

    目前只写了这个，其他等我什么时候用到了再更

5. faz_net_tool.h

   与其说这是个库，不如说这是把[wifi_setting_tool](https://github.com/ShannonfAz/wifi_setting_tool)里的代码搬过来并进行了一点点修改，然后打成函数丢main开头开机执行的函数，里面没什么你能调用的东西

# 如何增加更多的选项
1. 主菜单

1.1 先新建一个 自己取一个名字.cpp 和 自己取一个名字.h，把功能写在 自己取一个名字.cpp 里头然后打成函数，然后把函数声明丢在 自己取一个名字.h
   
1.2 主菜单代码在menu.cpp，h不用改，如果需要增加主菜单选项，则在vector<string> menu_options里头增加新的选项

1.3 切换到main.cpp，在switch(menu())下面增加新的case，把你写的函数丢进去

2. pid_setting
   
2.1 于vector<string> pid_options里头增加你要配置的选项

2.2 仿照里面的函数写一个新的文件读取与写入函数，函数名最好与你在vector<string> pid_options里头加的东西一样(观感较好)

2.3 在pid_read_settings(unsigned int& motorl_speed,unsigned int& motorr_speed,float& servop,float& servod,float& motorp,float& motori)的参数列表里加上你新增的参数，然后函数里面加上读取你新增加的参数的代码


# 未来计划更新内容(画大饼)
1. 增加多线程功能，写一些多线程框架(如多线程的电机舵机控制)，并对原有代码进行多线程以及其他形式的优化(一大堆代码呆在一个线程慢慢跑还是很**蠢的)
2. 增加更多好用的函数，尽可能降低用户代码量
3. 开发一些试验性的针对图像处理某些方面的小函数，写着玩
4. 尝试将逐飞库与该库迁往新世界，为旧世界的消亡出点力
5. 尝试在2k3k上跑一些智能车相关功能(吕布骑狗了属于是)
