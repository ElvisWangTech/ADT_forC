# ADT for C

- hash_table 哈希表
- linked_list 链表
- stack 栈
- queue 队列
- tree 树
- graph 图
- heap 堆
- string 字符串
- vector 动态数组

## 静态库使用指南

本工程采用CMake构建系统，支持Windows和Linux平台，为每个数据结构模块构建独立的静态库。

### 构建静态库

#### 1. 构建所有模块

**Windows (Visual Studio)**
```bash
# 创建构建目录
mkdir build && cd build
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
```

**Linux (GCC/Clang)**
```bash
# 创建构建目录
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

#### 2. 构建特定模块

**Windows**
```bash
cmake --build . --target linked_list --config Release
```

**Linux**
```bash
make linked_list
```

### 静态库文件位置

构建完成后，静态库文件位于：
- **Windows**: `build/lib/Release/*.lib`
- **Linux**: `build/lib/*.a`

### 使用静态库

#### 1. 在项目中使用

**Windows (Visual Studio)**

**方法1：使用CMake**
```cmake
# 在你的CMakeLists.txt中
find_package(ADT_forC REQUIRED PATHS ${ADT_FOR_C_PATH})

add_executable(my_app main.c)
target_link_libraries(my_app 
    linked_list
    queue
    stack
    # 其他需要的模块
)
```

**方法2：手动配置**
1. 将头文件目录添加到包含目录：`项目属性 -> C/C++ -> 常规 -> 附加包含目录`
2. 将库文件目录添加到库目录：`项目属性 -> 链接器 -> 常规 -> 附加库目录`
3. 添加库依赖：`项目属性 -> 链接器 -> 输入 -> 附加依赖项`

```c
// main.c
#include <stdio.h>
#include "linked_list/single_list.h"

int main() {
    // 使用链表功能
    sl_list_t *list = sl_create();
    // ... 使用链表
    sl_destroy(list);
    return 0;
}
```

**Linux (GCC/Clang)**

**方法1：使用CMake**
```cmake
# 在你的CMakeLists.txt中
find_package(PkgConfig REQUIRED)
pkg_check_modules(ADT_forC REQUIRED adt-for-c)

add_executable(my_app main.c)
target_link_libraries(my_app ${ADT_forC_LIBRARIES})
```

**方法2：命令行编译**
```bash
gcc -o my_app main.c \
    -I/path/to/ADT_forC \
    -L/path/to/ADT_forC/build/lib \
    -llinked_list -lqueue -lstack
```

**方法3：Makefile**
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
INCLUDES = -I/path/to/ADT_forC
LIBS = -L/path/to/ADT_forC/build/lib -llinked_list -lqueue -lstack

my_app: main.c
    $(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

clean:
    rm -f my_app
```

#### 2. 头文件使用

每个模块的头文件位于对应目录下，使用时直接包含：

```c
// 使用单链表
#include "linked_list/single_list.h"

// 使用双链表
#include "linked_list/double_list.h"

// 使用循环队列
#include "queue/circle_queue.h"

// 使用优先队列
#include "queue/priority_queue.h"

// 其他模块类似...
```

#### 3. 链接注意事项

**Windows**
- 确保库文件路径正确，使用`.lib`后缀
- 32位和64位库文件需要匹配项目架构
- 可以在Visual Studio中配置不同的构建配置(Debug/Release)

**Linux**
- 库文件使用`.a`后缀
- 使用`-l`参数时省略lib前缀和.a后缀
- 可以通过设置`LD_LIBRARY_PATH`环境变量来指定库文件搜索路径
