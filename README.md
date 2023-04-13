此项目的源文件最早来自于shcalc中，为使其他项目能够方便地引用libformula的源代码，故将其从shcalc中单独提取出来作为一个新的项目，在此之后，shcalc的工程结构也将进行一次大修，其他引用了libformula的项目也将进行一些调整。  
libformula中包含有一些常用的功能函数和一些数学公式，能够在开发中提供一定程度的帮助。  
## 如何编译libformula  
### 1.使用CMake：
```
    mkdir build
    cd build
    cmake ..    # 如果要自己手动指定编译器可使用-G选项
    make        # 配置成功后即可执行make进行编译
```
### 2.直接使用make命令
```
    make
```
**注意，如果是在Windows下需要指定Windows平台的make文件，例如 `make -f win32.make` 。**  
***
libformula与shcalc一样使用MIT许可证。[单击此处查看](./LICENSE)  
### libformula当前的最新版本为V1.2.1