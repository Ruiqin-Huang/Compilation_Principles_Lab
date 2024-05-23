### 测试环境

华为云ECS服务器，Ubuntu 22.04，gcc-11 

### 测试方法



在Linux 终端中执行 
  gcc -m32 -no-pie <输入汇编文件> -o <输出可执行文件> 

```cmd
gcc -m32 -no-pie eXX.s -o eXX
```

  ./<输出可执行文件> 

```cmd
./eXX
```

即可观察到输出结果。

注：在一些机器上，你可能需要添加i386 架构的包才能正确执行以上操
作，参考命令如下 
```cmd
sudo dpkg --add-architecture i386 
sudo apt-get update 
sudo apt-get install libc6:i386 libstdc++6:i386 gcc-multilib 
```