# `Linux` 系统基础知识点整理
1. ## `C`和`C++`文件编译全流程:
    ### 编译四阶段详解 **:**
    * **预处理** **:** `头文件展开` , `宏替换` ,  `条件编译` , `去注释`
    * **编译** **:** 把 `C` 或 `C++` 语言变成汇编语言
    * **汇编** **:** 把 `汇编语言` 变成 `二进制` 目标文件 `->` ( 该 `目标文件` 不是 `可执行` )
    * **链接** **:** 将 `目标文件` 和 `库文件` 链接成可执行文件

    ### 分段编译命令示例（以 GCC 为例） **:**
    ```shell
    # 完整流程示例（生成main可执行文件）
    gcc -E main.c -o main.i       # 预处理
    gcc -S main.i -o main.s       # 编译为汇编
    gcc -c main.s -o main.o       # 汇编为目标文件
    gcc main.o -o main            # 链接为可执行文件

    # 一键编译（等价于上述四步）
    gcc main.c -o main

    # 静态库编译（生成静态链接的可执行文件）
    gcc main.c -o main -static
    ```
    > 命令 `[ ESc ]` 对应 `[ iso ]` 文件后缀名
2. ## `Linux` 系统基础操作
    ### 用户权限管理
    #### 为普通用户添加 `sudo` 权限步骤
    * 以 `root` 身份登录或使用 `sudo su -`
    * 编辑 `sudoers` 文件：`vim /etc/sudoers`
    * 在 `root ALL=(ALL) ALL` 行下方添加：`your_username ALL=(ALL) ALL`
    * 保存退出后，普通用户可通过 `sudo command` 执行提权命令
    #### `Linux` 缺少 `C` 静态库文件 的解决方法
    *  **`centos` 系列安装** **:** 

        ```shell
        sudo yum install glibc-static 
        ``` 
    *  **`ubuntu` 系列安装** **:** 

        ```shell
        sudo apt-get install libc6-dev
        ```
    > **注意** **:** 在 `centos` 系列中包管理工具是 `yum` , 在 `ubuntu` 系列中包管理工具是 `apt`
    ### **`make` 命令与 `Makefile`**
    #### **`make` 命令功能** **:** `make` 命令会根据 `Makefile` 文件中的命令来编译程序, `Makefile` 文件中定义了编译程序所需要的命令和规则, `make` 命令在 `Windows` 中也适用
    #### `Makefile` 核心语法示例 **:**
    ```makefile
    # 简单Makefile示例
    main: main.o func.o
        gcc main.o func.o -o main
    main.o: main.c func.h
        gcc -c main.c
    func.o: func.c func.h
        gcc -c func.c
    clean:
        rm -f *.o main
    ```
3. ## `Vim` 编辑器常用命令 **:** 
    > `vim` 进入`命令`模式后，按 `i` 键进入`插入`模式，按 `Esc` 键退出插入模式，`Shift + :`进入`末行`模式 按 `wq` 保存并退出，按 `:q!` 不保存并退出，按 `:q` 退出。
    * 光标移动 **:** 
        * `h` 左移光标
        * `j` 下移光标
        * `k` 上移光标
        * `l` 右移光标
        * `w` 跳转到下一个单词
        * `b` 跳转到上一个单词
        * `Shift + 6` 跳转到行首的第一个非空字符
        * `Shift + 4` 跳转到行尾
        * `Shift + g` 跳转到文件末尾
        * `gg` 跳转到文件开头
        * `n + Shift + g` 跳转到文件第 `n` 行
        * `Ctrl + f` 向下翻页
    *  文本编辑 **:**
        * `dd` 删除光标所在行
        * `ndd` 删除光标所在行及其下n行
        * `u` 撤销
        * `Ctrl + r` 恢复撤销
        * `yy` 复制光标所在行
        * `nyy` 复制光标所在行及其下n行
        * `p` 粘贴
        * `np` 粘贴n次
        * `x` 删除光标所在字符
        * `nx` 删除光标所在字符及其后n个字符
    *  `vim` 文件操作 **:**
        * `:w` 保存
        * `:q` 退出
        * `:wq` 保存并退出
        * `:q!` 不保存并退出
        * `:wq!` 强制保存并退出
4. ## `Git` 版本控制基础命令 **:**
    ``` shell
    # 初始化仓库
    git init

    # 克隆远程仓库
    git clone https://github.com/user/repo.git

    # 本地操作
    git add .                # 添加所有文件到暂存区
    git commit -m "提交说明"  # 提交更改到本地仓库
    git status               # 查看当前状态

    # 远程协作
    git push origin main     # 推送本地分支到远程
    git pull origin main     # 拉取远程更新到本地
    git log                  # 查看提交历史
    ```
5. ## 进程理解 **:**
    * #### 进程状态 **:**
        * **运行** **:** `R(running)` 进程正在运行，在进程队列上;
        * **睡眠** **:** `S(sleeping)` 可中断睡眠状态，进程因等待某个事件（比如 `I/O` 完成、信号触发）而暂停，可被信号唤醒;
        * **等待** **:** `D(disk sleep)` 不可中断睡眠状态，多因等待磁盘 `I/O` 等关键操作，无法被信号打断;
        * **暂停** **:** `T(stopped)` 进程被停止运行，等待信号;
        * **暂停** **:** `t(tracing stop)` 因调试（如 `ptrace` 跟踪）暂停的状态，和普通 `T` 类似，但由调试器触发,表示这个进程正在被追踪;
        * **僵尸** **:** `Z(zombie)` 进程已经结束，但是其父进程还没有回收其资源;
        * **死亡** **:** `X(dead)` 进程被杀掉或结束;
    * #### 查看进程信息命令 **:** 
        * `ps ajx` 查看所有进程信息
        * `top` 查看当前进程信息
        * `htop` 查看当前进程信息
        * `pstree` 查看进程树
        * `ps -ef` 查看所有进程信息
        * `ps -aux` 查看所有进程信息
        * `ps -ef | grep [ 进程名 ]` 查看指定进程信息
    > 如果显示的是如 `R+` `S+` 说明这是前台进程，，不带加则是后台进程
    * #### 进程信号
        * **`SIGINT`  2**  **:** 中断进程;
        * **`SIGQUIT` 3**  **:** 退出进程;
        * **`SIGKILL` 9**  **:** 杀死进程;
        * **`SIGTERM` 15** **:** 终止进程;
        * **`SIGCONT` 18** **:** 继续进程;
        * **`SIGSTOP` 19** **:** 停止进程;
        * **`SIGTSTP` 20** **:** 暂停进程;

    * #### `kill` 命令 **:**
        * `kill  -信号 [ 进程ID ]` 对进程做更改
6. ### 环境变量 **:**
   #### 查看环境变量命令 **:**
    * `env` **:** 查看所有环境变量；
    * `echo` **:** 查看某一环境变量
    * `export` **:** 设置一个新的环境变量
    * `set` **:** 显示本地定义的环境变量和`shell`变量
    * `unser` **:** 清除环境变量
    ```shell
    env     #显示当前所有环境变量
    echo $NAME      #显示NAME环境变量
    MY_USER=wang      #定义一个本地变量
    export MY_NAME="泥嚎"     #设置一个MY_NAME的环境变量
    set     #显示本地定义的shell和环境变量
    unset MY_NAME     #删除定义的MY_NAME变量
    ```
        > 本地变量不能被子进程继承,对于 `echo` 这是一个子进程，再`export`定义一个新的本地变量，为么能访问本地变量？
   #### 系统调用 **:**
    * `char* env[]`
    * `getenv()`
    * `extern char** environ`
7. ### 进程地址空间 **:**
* #### 为什么要有进程地址空间？
    * 因为如果没有内存地址空间进程就会直接访问物理地址，这会对其他的进程非常的不安全，比如非法越界访问或修改，导致信息泄漏
    * 地址空间的存在,可以更方便的进行进程和进程数据代码的解耦，保证了进程的独立性
  <!-- <img src=./gallery/process_address_space.png#80% width = 80%> -->
* #### 看下面 `C++` 代码和输出结果,为什么值的地址会相同？为什么子进程修改了值,父进程的值却没变?
    ```c++
    #include <iostream>
    #include <unistd.h>
    int output_counters = 10;
    int main()
    {
        pid_t create_value = fork();
        if(create_value == 0)
        {
            std::cout << "子进程 "  << std::endl;
            int child = 0;
            while(output_counters)
            {
                std::cout << "我是子进程 : "<< " 子进程ID " << getpid() << " 父进程ID " << getppid() << " output_counters值 " << output_counters << " 地址 " << &output_counters <<  std::endl;
                if( child == 10 )
                {
                    std::cout << "子进程改变了output_counters" << std::endl;
                    output_counters = 800;
                }
                sleep(1);
                child++;
            }
        }
        else if(create_value > 0)
        {
            std::cout << "父进程 "  << std::endl;
            while(output_counters)
            {
                std::cout  << "我是父进程 : " << " 子进程ID " << getpid() << " 父进程ID " << getppid() << " output_counters值 " << output_counters << " 地址 " << &output_counters <<  std::endl;
                sleep(2);
            }
        }
        else
        {
            std::cout << "创建失败 !" << std::endl;
            return 0;
        }
    }
    ```
    ``` C++
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 10 地址 0x615f3a810010
    我是父进程 :  子进程ID 7544 父进程ID 6928 output_counters值 10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 10 地址 0x615f3a810010
    我是父进程 :  子进程ID 7544 父进程ID 6928 output_counters值 10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 10 地址 0x615f3a810010
    我是父进程 :  子进程ID 7544 父进程ID 6928 output_counters值 10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 10 地址 0x615f3a810010
    我是父进程 :  子进程ID 7544 父进程ID 6928 output_counters值 10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 10 地址 0x615f3a810010
    我是父进程 :  子进程ID 7544 父进程ID 6928 output_counters值 10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 10 地址 0x615f3a810010
    子进程改变了output_counters
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 800 地址 0x615f3a810010
    我是父进程 :  子进程ID 7544 父进程ID 6928 output_counters值  10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 800 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 800 地址 0x615f3a810010
    我是父进程 :  子进程ID 7544 父进程ID 6928 output_counters值  10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 800 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 800 地址 0x615f3a810010
    我是父进程 :  子进程ID 7544 父进程ID 6928 output_counters值  10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 800 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 800 地址 0x615f3a810010
    我是父进程 :  子进程ID 7544 父进程ID 6928 output_counters值  10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 800 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 800 地址 0x615f3a810010
    我是父进程 :  子进程ID 7544 父进程ID 6928 output_counters值  10 地址 0x615f3a810010
    我是子进程 :  子进程ID 7545 父进程ID 7544 output_counters值 800 地址 0x615f3a810010
    ```
    **解答** **:** 为进程具有独立性，创建子进程的时候是先把父进程的PCB拷贝一份来创建自己的PCB,包括虚拟地址
    前面10秒打印的时候父子进程访问同一全局变量的虚拟地址，都是一个物理地址(创建进程时父进程的虚拟地址拷贝走了)，但是在子进程改变了值时会触发操作系统的写时拷贝，会把子进程的 `output_counters` 值在内存中创建一个新的物理地址来存储改变的 `output_counters` 值，并将子进程的 `output_counters` 值的映射在刚刚创建的物理地址上，以此来保证进程之间的独立性
8. ### 进程和进程地址空间源码理解
    ``` cpp
    struct mm_struct
    {   //进程地址空间模块
        unsigned long start_code, end_code, start_data, end_data; //代码区的起始和结束地址，数据段区的起始和结束地址
		unsigned long start_brk, brk, start_stack; //堆区的起始地址，堆区当前地址，栈区起始地址
		unsigned long arg_start, arg_end, env_start, env_end;//命令行起始和结束地址，环境变量的起始和结束地址

    };
    struct task_struct  
    {   //进程控制模块
        int on_rq; //是否在就序队列中
        int prio; //动态优先级
        int static_prio; //静态优先级
        int normal_prio; //正常优先级
        unsigned int rt_priority; //实时优先级
        struct sched_rt_entity rt; //个调度实体
        struct sched_dl_entity dl; //一个实时调度实体
        struct sched_dl_entity *dl_server; //一个dl调度实体
        struct mm_struct *mm; //进程的内存管理
	    struct mm_struct *active_mm; //活动内存的管理
        struct task_struct __rcu *real_parent; //指向父进程
	    struct address_space *faults_disabled_mapping; //错误映射
	    int exit_state; //进程的退出状态
	    int exit_code; //进程的退出代码
	    int exit_signal; //进程的退出信号
        //....
    };
    ```
    在 `sched` 文件中会定义一个task_struct结构体(PCB)里面包含了进程的信息和进程地址空间，在进程地址空间结构体定义了堆栈代码和数据段区的范围
9. ### 虚拟地址 物理地址 逻辑地址
    * 逻辑地址 **:** 可执行文件内部使用的地址;
    * 虚拟地址 **:** 进程地址空间内的地址，由操作系统分配和管理;
    * 物理地址 **:** 实际内存条上的物理存储位置
    #### 可执行文件加载到内存中的地址转换 **:** 可执行文件加载到内存时，其内部的逻辑地址（编译生成的相对地址）会先由操作系统映射到进程的虚拟地址空间（通过基址偏移实现，若启用 ASLR 则基址随机化），程序运行时再经 CPU 的内存管理单元（MMU）通过页表将虚拟地址转换为物理地址，这一过程借助 TLB 缓存加速，同时动态链接库通过地址无关代码（PIC）技术实现共享，最终形成 “逻辑地址→虚拟地址→物理地址” 的完整转换链条，确保进程独立运行与内存高效管理