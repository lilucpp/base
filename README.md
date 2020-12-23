# base library

## 说明

此库是c++基础库。

受[muduo](https://github.com/chenshuo/muduo)影响，出于学习目的，尝试移植一部分基础库到windows上，后来又”copy”了[limonp](https://github.com/yanyiwu/limonp)库的部分功能，作为平时开发基础库。

## 编译

1. windows

   安装包管理工具vcpkg，使用vcpkg安装依赖库：
   
   - boost
     - boost-utility
     - boost-circular-buffer
     - boost-stacktrace
   - zlib
   - gtest。
   
	```bat
	python .\build_support\run_clang_format.py .\test
   python .\build_support\run_clang_format.py .\src
   mkdir build
   cd build
   cmake .. -G "Visual Studio 14 2015"  -DCMAKE_TOOLCHAIN_FILE=P:/vcpkg/scripts/buildsystems/vcpkg.cmake
   cmake --build . --config Release
   cmake --install .
   ```
   
   最终目录如下：
   ```bat
   ~base/build/PeanutBase$ tree
   .
   ├── bin
   │   ├── blockingqueue_bench.exe
   │   ├── blockingqueue_test.exe
   │   ├── boundedblockingqueue_test.exe
   │   ├── gtest_main.exe
   │   ├── gzipfile_test.exe
   │   ├── singleton_test.exe
   │   ├── testdata
   │   │   ├── 1.conf
   │   │   ├── dict.gbk
   │   │   └── dict.utf8
   │   └── threadpool_test.exe
   ├── include
   │   ├── Atomic.h
   │   ├── BlockingQueue.h
   │   ├── BoundedBlockingQueue.h
   │   ├── Colors.h
   │   ├── Condition.h
   │   ├── Config.h
   │   ├── Copyable.h
   │   ├── CountDownLatch.h
   │   ├── CurrentThread.h
   │   ├── Date.h
   │   ├── Exception.h
   │   ├── GzipFile.h
   │   ├── Mutex.h
   │   ├── Noncopyable.h
   │   ├── Singleton.h
   │   ├── StdExtension.h
   │   ├── StringPiece.h
   │   ├── StringUtil.h
   │   ├── Thread.h
   │   ├── ThreadPool.h
   │   ├── Timestamp.h
   │   ├── Types.h
   │   └── portable_endian.h
   └── lib
       └── PeanutBase.lib
   ```
   
   

主要功能

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
2. 跨平台
3. 增加其他常用功能