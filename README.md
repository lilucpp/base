# base library

## 说明

此库是c++基础库。

受[muduo](https://github.com/chenshuo/muduo)影响，出于学习目的，尝试移植一部分基础库到windows上，后来又”copy”了[limonp](https://github.com/yanyiwu/limonp)库的部分功能，作为平时开发基础库。

## 代码风格

google风格。修改了三处，如下，详见：.clang-format

```
BasedOnStyle: Google
DerivePointerAlignment: false
PointerAlignment: Right
ColumnLimit: 120
```

**提交代码前请使用格式化脚本格式化代码。**

```shell
python .\build_support\run_clang_format.py .\test
python .\build_support\run_clang_format.py .\src
```

格式化脚本可以设置跳过文件夹和文件。

```python
...
skippath = ['zib.h', 'zipconf.h']
for val in skippath:
  if filename.endswith(val):
    return True 
...

...
skipdir = ['baselib','lib','.git','.vscode']
for val in skipdir:
  if dir.endswith(val):
    return True 
...

```

## 编译说明

1. linux

   依赖安装
   
   ```shell
   sudo apt install libgtest-dev
   cd /usr/src/gtest
   sudo mkdir build
   cd build
   sudo cmake ..
   sudo make 
	sudo make install
	
   sudo apt install gtest zlib1g-dev libboost-dev
   ```
   
   编译
   
   ```shell
   git clone --recursive https://github.com/lilucpp/base.git
   cd base
   mkdir build
   cd build
   cmake .. -DFMT_INSTALL=1
   make 
   make install .
   ```
   
2. windows

   依赖安装，使用包管理工具vcpkg。

   ```bat
   ./vcpkg.exe install boost-utility boost-circular-buffer boost-stacktrace zlib gtest
   ```

   编译

   ```bat
   git clone --recursive https://github.com/lilucpp/base.git
   mkdir build
   cd build
   cmake .. -G "Visual Studio 14 2015"  -DCMAKE_TOOLCHAIN_FILE=P:/vcpkg/scripts/buildsystems/vcpkg.cmake -DFMT_INSTALL=1
   cmake --build . --config Release --verbose
   cmake --install .
   ```


## 主要功能

1. Atomic
2. BlockingQueue   
3. BoundedBlockingQueue
4. Colors
5. Condition
6. Config
7. Copyable
8. CountDownLatch
9. CurrentThread
10. Date
11. Exception
12. GzipFile
13. Mutex
14. Noncopyabe
15. Singleton
16. StdExtension
17. StringPiece
18. StringUtil
19. Thread
20. ThreadPool
21. Timestamp
22. Types

## todo

1. 减少boost依赖
2. ~~跨平台~~
3. 增加其他常用功能