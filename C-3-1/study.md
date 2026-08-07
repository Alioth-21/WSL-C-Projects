

# 1. 整体流程

```txt
用户输入 → 解析IP和端口范围 → 对每个端口发起TCP连接 → 判断结果 → 输出
```

# 2. 核心知识点

## 1. Socket 编程基础

Socket（套接字）是网络通信的"管道"。**TCP三次握手**是核心思想：

```txt
客户端 → 发送SYN → 服务器
客户端 ← 收到SYN+ACK ← 服务器
客户端 → 发送ACK → 服务器  （连接建立）
```

在C语言中，客户端连接服务器的流程：

```c
// 1. 创建socket
int sockfd = socket(AF_INET, SOCK_STREAM, 0);

// 2. 填写服务器地址结构
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(port);           // 端口（注意字节序）
inet_pton(AF_INET, ip, &server_addr.sin_addr); // IP地址

// 3. 发起连接
int ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
// ret == 0 → 端口开放；ret < 0 → 端口关闭或不可达
```

## 2. 串行 vs 并发

**串行**（慢）：一个端口一个端口地扫描，假设每个端口超时2秒，80个端口就要160秒。

**多线程并发**（快）：同时发起多个连接，80个端口可能只要2-3秒。

```txt
串行: [端口20]→[端口21]→[端口22]→... （一个做完才做下一个）
并发: [端口20]→
      [端口21]→   （同时进行）
      [端口22]→
      ...
```

## 3. 阻塞 vs 非阻塞 & 超时设置

**阻塞**：`connect()` 调用后，程序会一直等着，直到连接成功或失败。如果目标主机不可达，可能等很久（默认约75秒）。

**超时设置**：让 `connect()` 最多只等1-2秒就返回，解决"卡死"问题。

```c
// 方法1：设置socket为非阻塞，用select/poll等待
int flags = fcntl(sockfd, F_GETFL, 0);
fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);   // 设为非阻塞

int ret = connect(sockfd, ...);
if (ret < 0 && errno == EINPROGRESS) {
    // 连接正在进行中，用select等待结果
    fd_set wfds;
    FD_ZERO(&wfds);
    FD_SET(sockfd, &wfds);
    struct timeval tv = {2, 0};  // 2秒超时
    ret = select(sockfd + 1, NULL, &wfds, NULL, &tv);
    // ret > 0 表示可写 → 连接成功
}
```

## 4. 线程（pthread）与互斥锁（Mutex）

**为什么需要线程**：每个端口用一个线程去扫描，大家同时干活。

```c
#include <pthread.h>

// 线程函数（每个端口一个线程）
void* scan_thread(void* arg) {
    int port = *(int*)arg;
    // 尝试连接该端口...
    return NULL;
}

// 创建线程
pthread_t tid;
int port = 80;
pthread_create(&tid, NULL, scan_thread, &port);
pthread_join(tid, NULL);  // 等待线程结束
```

**为什么要互斥锁**：多个线程同时往一个全局数组/变量里写数据，会互相覆盖（数据竞争）。需要加锁保证"同一时刻只有一个线程在写"。

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int open_ports[100];  // 共享数据

// 在写共享数据前加锁
pthread_mutex_lock(&mutex);
open_ports[count++] = port;
pthread_mutex_unlock(&mutex);  // 写完解锁
```

**锁的作用**：就像厕所门上的锁，一个人进去后锁门，其他人只能等。

## 5. 线程参数传递的坑

不能直接传局部变量的地址：

```c
// 错误写法（所有线程拿到同一个变量地址！）
int port;
for (int i = 0; i < 80; i++) {
    port = start + i;
    pthread_create(&tid[i], NULL, scan_thread, &port);  // ❌
}

// 正确写法（每个线程分配独立内存）
int* ports = malloc(count * sizeof(int));
for (int i = 0; i < count; i++) {
    ports[i] = start + i;
    pthread_create(&tid[i], NULL, scan_thread, &ports[i]);  // ✅
}
```

## 6. 端口与服务映射

简单做法：硬编码常见端口表

```c
struct service_map {
    int port;
    const char* name;
} services[] = {
    {20, "FTP-Data"}, {21, "FTP"}, {22, "SSH"}, {23, "Telnet"},
    {25, "SMTP"}, {53, "DNS"}, {80, "HTTP"}, {110, "POP3"},
    {143, "IMAP"}, {443, "HTTPS"}, {3306, "MySQL"}, {8080, "HTTP-Alt"}
};
// 扫描到80端口 → 查表 → 输出"HTTP"
```

## 7. 命令行参数解析

```c
int main(int argc, char* argv[]) {
    // 用法: ./scanner 192.168.1.1 20-100
    char* ip = argv[1];           // "192.168.1.1"
    char* range = argv[2];        // "20-100"
    
    // 解析 "20-100" 得到 start=20, end=100
    int start, end;
    sscanf(range, "%d-%d", &start, &end);
}
```

---

## 8. 程序结构框架

```txt
main()
 ├─ 解析命令行参数（IP、端口范围）
 ├─ 建立端口→服务名映射表
 ├─ 创建 N 个线程（每个线程扫描若干端口）
 ├─ 等待所有线程结束 (pthread_join)
 └─ 输出结果（按端口号排序）

每个线程的 scan_thread()
 ├─ 创建 socket
 ├─ 设置非阻塞 + select 超时
 ├─ connect 尝试连接目标端口
 ├─ 判断结果：
 │   ├─ 成功 → 加锁 → 记录开放端口 → 解锁
 │   └─ 失败/超时 → 忽略
 └─ 关闭 socket
```

---

## 9. 编译命令

```bash
gcc scanner.c -o scanner -lpthread
# 链接线程库，必须！
```

---

现在你对整个框架有概念了吗？接下来你可以告诉我你想从哪里开始，我可以一步步带你写代码。比如：
1. 先写**命令行解析**部分
2. 或者先写**单个端口的扫描逻辑**
3. 或者先写**多线程框架**
