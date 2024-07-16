# 如何在该项目中使用Vcpkg
## 1. 安装Vcpkg
安装Vcpkg最推荐的方式是直接去微软官方仓库克隆下来，不推荐AUR等方式去安装，会有问题
```shell
git clone https://github.com/microsoft/vcpkg.git
```
克隆好之后，进入vcpkg目录并执行启动脚本
```shell
cd vcpkg && ./bootstrap-vcpkg.sh   #linux
cd vcpkg && ./bootstrap-vcpkg.bat  #windows
```
完成以上步骤之后Vcpkg就可以使用了
## 2. 配置Vcpkg与CMake
首先需要创建一个新的环境变量VCPKG_ROOT, 值为vcpkg的根目录，如/path/to/vcpkg

之后，在使用CMake构建项目时，要想其使用Vcpkg作为包管理工具，需传入以下参数: 
```bash
-DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake
```
使用Vscode的CMake扩展的，可以选择扩展中设置CMAKE_TOOLCHAIN_FILE

由此， CMake可以使用Vcpkg了。
## 3. 补充：Vcpkg的两种模式
Vcpkg有两种模式，经典模式（Classic Mode）和清单模式（Manifest Mode）。

- 默认情况下是经典模式，即使用全局的包管理，依赖包会被安装到vcpkg目录下。

- 目录中如果有vcpkg.json则为清单模式，该模式中的包依赖取决于vcpkg.json中的描述，运行vcpkg install会将依赖的包安装至当前目录中。该项目使用清单模式，CMake会执行vcpkg install将依赖安装至build文件夹中
  
#

更多有关通过CMake安装和使用：https://learn.microsoft.com/zh-cn/vcpkg/get_started/get-started?pivots=shell-bash

更多有关清单模式：https://learn.microsoft.com/zh-cn/vcpkg/concepts/manifest-mode
