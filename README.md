# FTP
2017-02-17

先把之前写好的线程池传输文件的丢进来了。

客户端：

把输入指令拆成两部分，命令cmd和文件名filename，把命令转换成数字就能很方便的用switch了。把switch当成中心以后再加什么功能也能很方便，之后只要增加把命令换成数字的函数(command)和switch的分支就足够了。利用command的返回值来做非法命令的过滤，goto做这种非法输入和返回重新输入的时候真的很好用啊。

服务器：

因为之前写好了线程池的流程了，直接从线程入口函数下手，修改了队列的成员，把cmd和filename增加到节点里面了，本来是希望让客户端直接传命令数字减少压力，可是果然还是有点问题的，最后还是传了字符串了，之后的处理跟客户端一样，换成数字之后用switch进行下一步的功能操作。

问题&解决：

1.客户端在读标准输入的时候读入了'\n'，导致command函数返回出错，学艺不精，不记得read是不忽略'\n'的，因为最后肯定是敲回车输入的，就不判断'\0'为输入的字符串结尾而将'\n'作为判断依据；

2.服务器的recv太快，客户端还没有send就recv结束了，导致所有命令都没接收到，最后用epoll解决的，之后应该还会再扩展epoll比如子线程完成任务然后返回接着再向客户端发消息，不过等到用到的时候再细想吧；

3.epoll_wait，在所有能加错误判断的地方都加上了，可是没有任何一个返回出现错误，但是客户端的网络套接字可读时仍然没有反应，直接退出服务器。做接收命令的测试的时候把epoll部分全部注释掉，再删除注释之后自然就好了。写代码果然是一个玄学问题；

4.send_recv_n,懒得写两个函数了，客户端没有发出正确的len，或者服务器端的接收长度有误，总之肯定是传参传错了，明天要再仔细想想了，现在真的已经有点体力透支了，还是回去好好睡一觉，睡醒起来清醒一点再想。

计划：

1.把send_recv_n的问题处理掉；

2.6个功能其实有三个都实现过了，只要命令能正确传输，就封装之前写的直接拷进去，不过已经拷进去了一部分不是；

3.因为线程的文件目录是共享的，要创建空目录，这个就丢到最后一整天去想吧。

2017-02-18

![image](https://github.com/AkiraMo/FTP/blob/dev/bugimg/server%E9%97%AE%E9%A2%98%E9%83%A8%E5%88%86%E6%BA%90%E7%A0%81.png)

![image](https://github.com/AkiraMo/FTP/blob/dev/bugimg/client%E9%97%AE%E9%A2%98%E9%83%A8%E5%88%86%E6%BA%90%E7%A0%81.png)

send_recv_n出问题部分的代码截图

使用normal.h中定义的transferdata的数据结构，首先将结构体中的buf的长度赋给len，之后传输len 4个字节及len所记录的buf的长度。

之后recv_n先接收4个字节知道之后要接收的数据长度，再进行命令及文件名的接收。

预期效果是服务器端先接收cmd的长度，之后再接收cmd并存入节点，但实际运行效果却是接收长度为0，同时曾经测试，将接收cmd时的长度固定，从客户端发送固定长度的命令，但是仍然无法接收cmd

运行结果
![image](https://github.com/AkiraMo/FTP/blob/dev/bugimg/server%E7%BB%93%E6%9E%9C.png)

![image](https://github.com/AkiraMo/FTP/blob/dev/bugimg/client%E7%BB%93%E6%9E%9C.png)

今天一天毫无进展，还卡在send和recv，不过确认了不是传参的问题，昨天想茬了。然后唯一的好消息是客户端已经确定是对的了，send没有问题了，接着就是专心解决服务器端的recv。上网拷了一份epoll的模型，虽然之前有自己写过，可是自信心被打击了一整天，已经陷入人生迷茫期对自己一点信任感都没有了呢。

现在主要怀疑是不是epoll写了一半没写全或者是时间差的问题，所以recv才接收不到数据。send成功返回并不代表成功发送数据，只是成功将数据发送到了网络，今天唯一一点收获了。

幸好之后的功能大多都写过一开始就相当快了，现在只要解决了recv的问题，让服务器成功接收，大概一天半就能做完了。当然前提是能成功接收，距离出现问题已经超过24小时了还没解决，自信这种东西都扔海里去吧（╯‵□′）╯ノ┻━┻

2017-02-19

终于找到错误的地方了，第一次出现recv自己乱跑没堵塞的时候为啥没反应过来还去加epoll，脑子得进了多少水。问题的根源就是复制错文件了，send_recv_n这个函数的实现文件，复制错了，把没改正的那个复制进来了，白白耗了我一天多。

然后今天搞定了非法输入的过滤和循环输入，乱七八糟折腾了好久，还是用goto吧，这个真的无比的好用啊，为什么学校老师都说不要用这个呢，加个判断条件，反正非法了就让它直接滚回去重新输入重新接收，因为之前就把cmd单独提取出来变成数字了，只要设一个错误码，反正只要等于错误码直接回去，什么都不用废话了。

算算时间估计是赶不上了，只能一点点爬了，总会做完的。

计划：

1.解决一下为什么第二次连接服务器端，服务器会出现端错误；

2.所有线程共用文件目录，字符串拼接好像很麻烦的样子，又要各种算长度确认符号了，以前总是迷之出现毫无规律的/君，大概是又要见面了；

3.完成文件名的非法检查，又是各种搞字符串了，反正最后非法就设个错误码goto滚回去重新收；

4.完成实际功能，虽然好像工程量很大的样子，可是感觉应该能最快完成。
