# 1. 要求

1. 项目1：学生成绩管理系统

2. 核心主题：
    - 结构体

    - 数组

    - 文件IO（文本模式）

3. 功能定义：
    - 用结构体数组存储最多100名学生（姓名、学号、语数外三科成绩）。

    - 实现增、删、改、查，以及按总分排序并输出排名。

    - 关键动作：程序启动时从students.txt读取数据，修改后按Ctrl+C或正常退出时自动保存回文件。

    - 攻克目标：彻底搞懂fscanf和fprintf的格式化读写，以及feof的正确用法（新手极易在此踩坑）。

# 2. 版本

## version 1

1. 结构体数组存储学生信息
2. 增、删、改、查功能
3. 按总分排序并输出排名
4. 文件IO：启动时读取数据，退出时保存数据

## version 2
- 用

# 3. 关键内容

## 2.1 fscanf

1. 函数原型
    ```c
    int fscanf(FILE *stream, const char *format, ...);
    ```
    - **`stream`**：文件指针（如 `fp`）
    - **`format`**：格式控制字符串
    - **返回值**：成功匹配并赋值的**参数个数**；到达文件末尾返回 `EOF`（-1）

2.  基本用法：从文件读取格式化数据

    ```c
    // student.txt 内容格式：1001 张三 90 88 92
    FILE *fp = fopen("students.txt", "r");
    int id;
    char name[20];
    float ch, ma, en;

    // 读取一行，返回 5 表示 5 个变量都成功赋值
    int result = fscanf(fp, "%d %19s %f %f %f",
                        &id, name, &ch, &ma, &en);
    ```

3. 与 `scanf` 的区别

| 特性 | `scanf` | `fscanf` |
|------|---------|----------|
| 数据来源 | 键盘标准输入 `stdin` | 指定文件流 |
| 等价关系 | `scanf(...)` = `fscanf(stdin, ...)` | 可指定任意文件 |
| 应用场景 | 交互式输入 | 文件批量读取 |

---

4. 常见注意点（踩坑指南）

#### ⚠️ 注意点 1：**不要用 `feof` 控制读取循环**

```c
// ❌ 错误写法：feof 会在最后一次读取后才变为真，导致多读一次
while (!feof(fp)) {
    fscanf(fp, "%d", &id);
    // 处理数据...
}

// ✅ 正确写法：检查 fscanf 的返回值
while (fscanf(fp, "%d %19s %f %f %f",
              &id, name, &ch, &ma, &en) == 5) {
    // 处理数据...
}
```

**原因**：`feof` 只有在尝试读取**越过文件末尾**后才返回 true，所以循环体会多执行一次。

---

#### ⚠️ 注意点 2：**返回值必须检查**

```c
// ❌ 不检查返回值，可能读到垃圾数据
fscanf(fp, "%d %s", &id, name);

// ✅ 检查返回值，确保都成功
if (fscanf(fp, "%d %s", &id, name) != 2) {
    printf("读取失败或文件格式错误\n");
}
```

---

#### ⚠️ 注意点 3：**字符串缓冲区溢出**

```c
// ❌ 危险：name 只有 20 字节，可能溢出
fscanf(fp, "%s", name);

// ✅ 安全：限制最大读取 19 个字符（留 1 字节给 '\0'）
fscanf(fp, "%19s", name);
```

---

#### ⚠️ 注意点 4：**`%s` 无法读取含空格的名字**

```c
// 文件内容：1001 张 三   ← 注意名字中有空格
// fscanf 会把它读成两个字符串！
fscanf(fp, "%d %s", &id, name);  // name = "张"

// 解决办法：使用固定格式、或用 fgets + sscanf
```

---

#### ⚠️ 注意点 5：**文件格式必须严格匹配**

```c
// 文件内容：1001,张三,90,88,92   （逗号分隔）
// ❌ 错误：格式不匹配，读取失败
fscanf(fp, "%d %s %f %f %f", &id, name, &ch, &ma, &en);

// ✅ 正确：格式串要匹配逗号
fscanf(fp, "%d,%s,%f,%f,%f", &id, name, &ch, &ma, &en);
```

---

### 5. 在你的项目中的实际应用

你的 `read()` 函数使用了 `fgets + sscanf` 组合，这也是一种很好的方式：

```c
// 方式一：fscanf 直接读取（要求文件格式严格）
void read(Stu *Students, int *num) {
    FILE *fp = fopen(FILE_NAME, "r");
    int n = 0;
    while (n < MAX && 
           fscanf(fp, "%d %19s %f %f %f",
                  &Students[n].id, Students[n].name,
                  &Students[n].CH, &Students[n].MA, 
                  &Students[n].EN) == 5) {
        Students[n].score = Students[n].CH + 
                            Students[n].MA + 
                            Students[n].EN;
        n++;
    }
    *num = n;
    fclose(fp);
}

// 方式二：fgets + sscanf（更灵活，能处理空行和注释）
void read(Stu *Students, int *num) {
    FILE *fp = fopen(FILE_NAME, "r");
    char line[100];
    int n = 0;
    while (n < MAX && fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d %19s %f %f %f",
                   &Students[n].id, Students[n].name,
                   &Students[n].CH, &Students[n].MA,
                   &Students[n].EN) == 5) {
            Students[n].score = Students[n].CH + 
                                Students[n].MA + 
                                Students[n].EN;
            n++;
        }
    }
    *num = n;
    fclose(fp);
}
```

