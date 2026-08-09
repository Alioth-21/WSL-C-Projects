# AGENTS.md — WSL-C-Projects

C 语言学习工作区（WSL/Linux，`/usr/bin/gcc`）。本文件帮助 AI 编码助手在该代码库中高效工作。

## 项目结构

- `C-1-1/`：学生成绩管理系统（结构体数组 + 文件 IO）
- `C-2-1/` / `C-2-2/`：日程计划（链表；C-2-2 增加链式栈实现的撤销功能）
- `C-3-1/`：简易端口扫描器（Socket/多线程，当前仅文档）
- `DataStructure/`：数据结构代码，按 `1-LinearList/{1-1 SuqList, 1-2 LinkList, 1-3 Stack, 1-4 Queue, 1-5 String}`、`2-Tree/` 分层
- `Test/`：临时冒烟测试（如 `HW.c`）
- 每个项目/数据结构子目录含 `Compiled-Files/`（编译产物）及可选 `readme.md`

各项目需求详见各目录 `readme.md`（勿重复内嵌，按需链接）。

## 构建与运行

编译单个活动文件（`.vscode/tasks.json`）：

```bash
/usr/bin/gcc -g -O0 -std=c23 "${file}" -o "${fileDirname}/CompiledFiles/${fileBasenameNoExtension}"
```

- **首选 `build-c` 任务**（输出到 `CompiledFiles/`），并配套 `launch.json`（`preLaunchTask: build-c`）调试。
- 运行：`./Compiled-Files/<name>`（注意磁盘目录名带连字符 `Compiled-Files`，而 tasks.json 输出路径是 `CompiledFiles`，两者不一致为已知坑）。
- IntelliSense 配置为 **c17**（`c_cpp_properties.json`），构建用 **c23**，二者不同属预期。
- 编译产物（ELF/`students.txt`）**被 git 跟踪**（无 `.gitignore`）：勿意外修改/提交它们。

## 编码约定（务必遵守）

- **函数命名**：PascalCase 动词+名词，如 `InitList`、`IsEmpty`、`InsertHead`、`GetElem`、`ClearList`、`DestoryList`。
- **拼写注意**：全库一致使用 `DestoryList`（非 `Destroy`）、`chioce`（非 `choice`）——保持既有拼写，勿“修正”。
- **匈牙利指针前缀**：`Ptr`（Item）、`PtrL`（List）、`PtrS`（Stack）、`Sptr`（SeqList）。
- **抽象元素类型**：`typedef int ElemType;` 用于泛化数据结构；结构体 `struct Xxx{...};` 后跟 `typedef struct Xxx* XxxPtr;`。
- **宏/常量**：全大写下划线，如 `MAX_SIZE`、`MAX_ITEMS`、`NotFound`。
- **头文件**：用 `#pragma once` 守卫；本地头用双引号 `#include"xxxhead.h"`；主 `main.c` 顶部集中声明结构体 + 宏 + 函数原型，正文按 `//Basic Operations` / `//Operations` 分区。
- **注释**：分类注释用英文（`//Basic Operations`），关键算法用中文（如 `//查找前驱节点`）。
- **入口**：`main()` 使用 `while(chioce)` + `scanf` + `switch` 的 CLI 菜单循环。

## 未完成/已知待办（改动前留意）

- `C-2-2/main.c` include 了 `c-2-1head.h`，但引用了该头中尚无定义的 `PtrS`/`StackList` 类型——`C-2-2` 处于未完成状态。
- `C-2-2` 缺 `readme.md`；`C-3-1` 尚无代码；顶层 `main.c` 为空占位。
- 修改 `DataStructure/1-LinearList/1-1 SuqList` 下的两个顺序表实现时，保留现有 `Insert` 扩容、`GetCapacity` 等接口命名。

## 提交约定

- 按**每完成一个版本/项目一次提交**推进，`readme.md` 以 `version 1 / 2-1 / 2-2` 记录演进。
- 提交信息可用中文，与 README 文档语言一致。
