# base library

## 说明

此库是c++基础库，受[muduo](https://github.com/chenshuo/muduo)影响。出于学习目的，尝试移植一部分基础库到windows上，后来“copy”了[limonp](https://github.com/yanyiwu/limonp)库的部分功能。

## 编译

1. windows

   ```bat
   python .\build_support\run_clang_format.py .\test
   python .\build_support\run_clang_format.py .\src
   mkdir build
   cd build
   cmake .. -G "Visual Studio 14 2015"  -DCMAKE_TOOLCHAIN_FILE=P:/vcpkg/scripts/buildsystems/vcpkg.cmake
   cmake --build . --config Release
   ```

   

主要功能

1. Atomic
2. BlockingQueue   
3. BoundedBlockingQueue
4. Colors
5. Condition
6. Config
7. copyable
8. CountDownLatch
9. CurrentThread
10. Date
11. Exception
12. GzipFile
13. Mutex
14. noncopyabe
15. Singleton
16. StdExtension
17. StringPiece
18. StringUtil
19. Thread
20. ThreadPool
21. Timestamp
22. Types
