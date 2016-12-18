#C++11 Thread
###`Thread`类
用于建立Thead

```cpp
#include <thread>

void fun();

std::thread thr1(fun);
std::thread thr2;

thr2 = std::thread(foo);

/* wait thrs to terminate */
thr1.join();
thr2.join();
```

### `Mutex`类
互斥量
- `lock_guard` scope-based mutex ownership wrapper
**初始化即加锁**
函数中利用`static`防输出混乱
```cpp
void foo() {
	/* static io_mutex guarantee thread-safe */
	static std::mutex io_mutex;
    {
		/* lock io_mutex */
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << std::thread::get_id() << " printing" << endl;    
    } /* unlock io_mutex when leaving {} */
}
```
- `unique_lock` movable mutex ownership wrapper  
可控制加锁时机，可同时为几个锁上锁，避免死锁
```cpp
std::mutex m1, m2;
void foo() {
	std::unique_lock<std::mutex> lk1(m1, std::defer_lock);
	std::unique_lock<std::mutex> lk2(m2, std::defer_lock);
	std::lock(lk1, lk2); /* avoid deadlock */
}
```

### `condition_variable`类
`Mutex` 状态变化的通知机制
```cpp 
std::condition_variable condvar;

consumer:
        std::unique_lock<std::mutex> ulock(mutex);
        condvar.wait(ulock, []{ return msgQueue.size() > 0;});

producer:
        condvar.notify_all();
```
  