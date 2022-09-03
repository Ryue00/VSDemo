# 并发与多线程

## 并发基本概念及实现，进程、线程基本概念
### 并发
两个或者更多的任务同时发生：一个程序同时之性能多个独立的任务

### 可执行程序
磁盘上的一个文件，如，windows下的 .exe文件

### 进程
系统进行资源分配和调度的基本单位，是操作系统结构的基础。

### 线程
操作系统能够进行运算调度的最小单位。它被包含在进程之中，是进程中的实际运作单位。
一条线程指的是进程中一个单一顺序的控制流，一个进程中可以并发多个线程，每条线程并行执行不同的任务。

## C++标准线程使用

### thread 类的简单介绍

| 函数名 | 功能 |
|--|--|
| thread() | 构造一个线程对象，没有关联任何线程函数，即没有启动任何线程 |
| thread(fn, args1, args2, …) | 构造一个线程对象，并关联线程函数fn，args1，args2，…为线程函数的参数
| get_id() | 获取线程id
| jionable() | 线程是否还在执行，joinable代表的是一个正在执行中的线程。
| jion() | 该函数调用后会阻塞住线程，当该线程结束后，主线程继续执行
| detach() |在创建线程对象后马上调用，用于把被创建线程与线程对象分离开，分离的线程变为后台线程，创建的线程的"死活"就与主线程无关

## 线程传参详解,成员函数做线程函数
### 线程函数

* 函数指针
* lambda表达式
* 函数对象
``` cpp

void Fun1()
{
    std::cout << "函数指针作线程函数" << std::endl;
    return;
}

class Fun3
{
public:
    void operator()()
    {
        std::cout << "类对象作线程函数" << std::endl;
    }
};

class Fun4
{
public:
    void ThreadWork(int num)
    {
        std::cout << "类成员函数作线程函数 " << num << std::endl;
    }
};

int main()
{
    // 函数指针作线程函数
    std::thread t1(Fun1);
    t1.join();

	// lambda 表达式作线程函数
    std::thread t2([]() {std::cout << "lambda 表达式作线程函数" << std::endl; });
    t2.join();

	// 类对象作线程函数
    Fun3 f3;
    std::thread t3(f3);
    t3.join();

	// 类成员函数作线程函数
    Fun4 f4;
    std::thread t4(&Fun4::ThreadWork,f4,100);  
    t4.join();
	
    return 0;
}

```
### thread类是防拷贝的，不允许拷贝构造以及赋值，但是可以移动构造和移动赋值，即将一个线程对象关联线程的状态转移给其他线程对象，转移期间不影响线程的执行。
### 可以通过jionable()函数判断线程是否是有效的，如果是以下任意情况，则线程无效
* 采用无参构造函数构造的线程对象
* 线程对象的状态已经转移给其他线程对象
* 线程已经调用jion或者detach结束

### 并发与并行的区别？
* 并行是指两个或者多个事件在同一时刻发生；而并发是指两个或多个事件在同一时间间隔发生。
* 并行是在不同实体上的多个事件，并发是在同一实体上的多个事件。
* 在一台处理器上“同时”（这个同时实际上市交替“”）处理多个任务，在多台处理器上同时处理多个任务

### 线程函数传参
线程函数参数是以值拷贝的方式传入线程的栈空间，所以即使传入的是引用类型，在线程修改也无法对外部实参改变，并且一些编译器会被报错.

```cpp
void Fun1(int& num)
{
    num += 10;
    std::cout << "void Fun1(int& num) " << num <<  std::endl;
}

void Fun2(int* num)
{
    (*num) += 10;
    std::cout << "void Fun2(int* num) " << *num << std::endl;
}

void Fun3(std::unique_ptr<int> num)
{
    *num += 10;
    std::cout << "void Fun3(int* num) " << *num << std::endl;
}

void Fun4(std::shared_ptr<int> num)
{
    *num += 10;
    std::cout << "void Fun4(int* num) " << *num << std::endl;
    std::cout << "numSharedPtr.use_count()=" << num.use_count() << std::endl;
}

int main()
{
    int num = 10;

    // std::thread t0(Fun1, num); // 编译错误
    // t0.join();
    // std::cout << "int main() " << num << std::endl;

    // 引用传递的正确用法，需要借助std::ref() 函数
    std::thread t1(Fun1, std::ref(num)); // 正确， 同样的使用还有 std::bind() 的引用传参
    t1.join();
    std::cout << "int main() " << num << std::endl;

    // 地址传递
    std::thread t2(Fun2,&num);
    t2.join();
    std::cout << "int main() " << num << std::endl;

    // 传递独占式智能指针，借助std::move()函数完成语义转换，否则编译失败
    std::unique_ptr<int> numUniquePtr = std::make_unique<int>(100);
    std::thread t3(Fun3, std::move(numUniquePtr));
    t3.join();
    std::cout << "int main() " << numUniquePtr << std::endl;

    // 传递共享智能指针
    std::shared_ptr<int> numSharedPtr = std::make_shared<int>(100);
    std::cout << "numSharedPtr.use_count()=" << numSharedPtr.use_count() << std::endl;
    std::thread t4(Fun4, numSharedPtr);
    t4.join();
    std::cout << "numSharedPtr.use_count()=" << numSharedPtr.use_count() << std::endl;
    std::cout << "int main() " << numSharedPtr << std::endl;

    return 0;
}
```

## 创建多个线程、数据共享问题分析
### 创建多个线程
使用容器管控线程
```cpp

std::vector<std::thread> threads;

void OnPrint(int i)
{
    std::cout << std::this_thread::get_id() << "--> i = " << i << std::endl;
}

constexpr int THREAD_COUNT_MAX = 10;
int main()
{
    for (int i= 0; i< THREAD_COUNT_MAX; i++ )
    {
        threads.push_back(std::thread(OnPrint, i));
    }
    std::vector<std::thread>::iterator ite = threads.begin();
	for (;ite != threads.end(); ++ite)
	{
        ite->join();
	}
    return 0;
}
```

### 数据共享问题分析

* only read data：安全稳定,不需要特殊处理
* read and write data：恶性条件竞争
C++标准提供保护共享数据的最基本方式就是互斥量mutex，加锁

## 互斥量概念、用法、死锁问题
### 概念、用法
std::mutex 互斥是C++最基本的保护共享数据的措施，需要妥善组织和编排代码
```cpp

std::list<int> m_testList;
std::mutex m_data_mutex;  // 互斥量，一把锁
void CSharedData::RecvMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
		// std::unique_lock<std::mutex> lock(m_data_mutex); 
		m_data_mutex.lock();
		if (!m_testList.empty())
		{
			int data = m_testList.front();
			std::cout << "线程ID=" << std::this_thread::get_id() << "收到消息：" << data << std::endl;
			m_testList.pop_front();
		}
		m_data_mutex.unlock();
		// lock.unlock();
	}
	
}

void CSharedData::SendMsgProcess()
{
	for (int i =0; i < 10000; i++)
	{
		// std::unique_lock<std::mutex> lock(m_data_mutex);
		m_data_mutex.lock();
		std::cout << "线程ID=" << std::this_thread::get_id() << "发送消息：" << i << std::endl;
		m_testList.push_back(i);
		// lock.unlock();
		m_data_mutex.unlock();
	}
}

```

### 死锁

当至少两个线程，都需同时锁住两个互斥量，才能进行某项操作，但两个线程都分别只锁住了一个互斥，都在等待另一个互斥加锁。
此为死锁。

```cpp
std::list<int> m_testList;
std::mutex m_data_mutex1;  // 互斥量，一把锁
std::mutex m_data_mutex2;  // 互斥量，一把锁
void CSharedData::RecvMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
         // std::lock_guard<std::mutex> lock(m_data_mutex1);
         // std::lock_guard<std::mutex> lock(m_data_mutex2);
		// std::unique_lock<std::mutex> lock(m_data_mutex1);
		m_data_mutex2.lock();  // 顺序不一致，导致死锁
		m_data_mutex1.lock();
		if (!m_testList.empty())
		{
			int data = m_testList.front();
			std::cout << "线程ID=" << std::this_thread::get_id() << "收到消息：" << data << std::endl;
			m_testList.pop_front();
		}
		m_data_mutex1.unlock();
		m_data_mutex2.unlock();
		// lock.unlock();
	}
	
}

void CSharedData::SendMsgProcess()
{
	for (int i =0; i < 10000; i++)
	{
		// std::unique_lock<std::mutex> lock(m_data_mutex1);
		m_data_mutex1.lock();  // 顺序不一致，导致死锁
		m_data_mutex2.lock();
		std::cout << "线程ID=" << std::this_thread::get_id() << "发送消息：" << i << std::endl;
		m_testList.push_back(i);
		// lock.unlock();
		m_data_mutex2.unlock();
		m_data_mutex1.unlock();
	}
}

造成示例代码这种死锁，一般的解决方法可以使用 std::lock() 模板函数如下：
```cpp
std::list<int> m_testList;
std::mutex m_data_mutex1;  // 互斥量，一把锁
std::mutex m_data_mutex2;  // 互斥量，一把锁
void CSharedData::RecvMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
		// std::unique_lock<std::mutex> lock(m_data_mutex1);
		// m_data_mutex2.lock();  // 顺序不一致，导致死锁
		// m_data_mutex1.lock();
		
		std::lock(m_data_mutex1, m_data_mutex2);
		std::lock_guard<std::mutex> lock1(m_data_mutex1,std::adopt_lock);
		std::lock_guard<std::mutex> lock2(m_data_mutex2, std::adopt_lock); // 
		// 
		if (!m_testList.empty())
		{
			int data = m_testList.front();
			std::cout << "线程ID=" << std::this_thread::get_id() << "收到消息：" << data << std::endl;
			m_testList.pop_front();
		}
		// m_data_mutex1.unlock();
		// m_data_mutex2.unlock();
	}

}

void CSharedData::SendMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
		// m_data_mutex1.lock();  // 顺序不一致，导致死锁
		// m_data_mutex2.lock();
		std::lock(m_data_mutex2, m_data_mutex1);
		std::lock_guard<std::mutex> lock1(m_data_mutex1, std::adopt_lock);
		std::lock_guard<std::mutex> lock2(m_data_mutex2, std::adopt_lock);
		std::cout << "线程ID=" << std::this_thread::get_id() << "发送消息：" << i << std::endl;
		m_testList.push_back(i);
		// m_data_mutex2.unlock();
		// m_data_mutex1.unlock();
	}
}

```
std::lock 可以同时对多个互斥量进行加锁操作，std::lock_guard 使用的是C++ RAII(资源获取即初始化)风格，所以在构造时会对 mutex进行加锁操作
而std::adopt_lock参数，该结构体可以理解为标志为，加这个参数不会对互斥量进行加锁，但是在析构时还是会进行解锁。

## unique_lock详解

### 概述

* std::unique_lock 可以用来代替 std::lock_guard 也是使用 RAII 方式管理,加锁在资源初始化阶段，解锁在资源析构阶段
* std::unique_lock 更加灵活，但这种灵活的代价就是内存以及开销增加，更加灵活体现在第二参数以及成员参数

### 第二参数

* std::adpot_lock 与 lock_guard 相似

```cpp
std::list<int> m_testList;
std::mutex m_data_mutex1;  // 互斥量，一把锁
std::mutex m_data_mutex2;  // 互斥量，一把锁
void CSharedData::RecvMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
		// std::unique_lock<std::mutex> lock(m_data_mutex1);
		// m_data_mutex2.lock();  // 顺序不一致，导致死锁
		// m_data_mutex1.lock();
		// std::lock(m_data_mutex1, m_data_mutex2);
		// std::lock_guard<std::mutex> lock1(m_data_mutex1,std::adopt_lock);
		// std::lock_guard<std::mutex> lock2(m_data_mutex2, std::adopt_lock);
		// std::lock_guard 使用的是C++ RAII(资源获取即初始化)，所以在构造时会对 mutex进行加锁操作
		// 而std::adopt_lock参数，该结构体可以理解为标志为，加这个参数不会对互斥量进行加锁，但是在析构时还是会进行解锁

		m_data_mutex1.lock();
		std::unique_lock<std::mutex> lock(m_data_mutex1,std::adopt_lock);

		if (lock.owns_lock())
		{
			if (!m_testList.empty())
			{
				int data = m_testList.front();
				std::cout << "线程ID=" << std::this_thread::get_id() << "收到消息：" << data << std::endl;
				m_testList.pop_front();
			}
		}
		else
		{
			std::cout << "线程ID=" << std::this_thread::get_id() << "。。。。。没有拿到锁" << i << std::endl;
		}
		
		// m_data_mutex1.unlock();
		// m_data_mutex2.unlock();
	}

}

void CSharedData::SendMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{

		m_data_mutex1.lock();
		std::unique_lock<std::mutex> lock1(m_data_mutex1,std::adopt_lock);
		
		std::cout << "线程ID=" << std::this_thread::get_id() << "发送消息：" << i << std::endl;
		m_testList.push_back(i);
	}
}

```
std::unique_lock<std::mutex> lock(m_data_mutex1,std::adopt_lock)，如上述代码 std::adopt_lock 告诉变量lock，我已经加锁了，不需要在构造加锁
否则会出现问题

* std::try_to_lock
```cpp

void CSharedData::RecvMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
		// std::unique_lock<std::mutex> lock(m_data_mutex1);
		// m_data_mutex2.lock();  // 顺序不一致，导致死锁
		// m_data_mutex1.lock();
		// std::lock(m_data_mutex1, m_data_mutex2);
		// std::lock_guard<std::mutex> lock1(m_data_mutex1,std::adopt_lock);
		// std::lock_guard<std::mutex> lock2(m_data_mutex2, std::adopt_lock);
		// std::lock_guard 使用的是C++ RAII(资源获取即初始化)，所以在构造时会对 mutex进行加锁操作
		// 而std::adopt_lock参数，该结构体可以理解为标志为，加这个参数不会对互斥量进行加锁，但是在析构时还是会进行解锁

		m_data_mutex1.lock();
		std::unique_lock<std::mutex> lock(m_data_mutex1,std::try_to_lock);

		if (lock.owns_lock())
		{
			if (!m_testList.empty())
			{
				int data = m_testList.front();
				std::cout << "线程ID=" << std::this_thread::get_id() << "收到消息：" << data << std::endl;
				m_testList.pop_front();
			}
		}
		else
		{
			std::cout << "线程ID=" << std::this_thread::get_id() << "。。。。。没有拿到锁" << i << std::endl;
		}
		
		// m_data_mutex1.unlock();
		// m_data_mutex2.unlock();
	}

}

void CSharedData::SendMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{

		std::unique_lock<std::mutex> lock1(m_data_mutex1);

		std::chrono::milliseconds deDuration(20);
		std::this_thread::sleep_for(deDuration);
		
		std::cout << "线程ID=" << std::this_thread::get_id() << "发送消息：" << i << std::endl;
		m_testList.push_back(i);
	}
}

```	
由以上代码可以看出 std::unique_lock<std::mutex> lock(m_data_mutex1,std::try_to_lock)，生产者线程 SendMsgProcess 等待休眠20毫秒时候，此时已经获取到m_data_mutex1的所有权， 消费者线程便无法取得所有权，所以使用 std::try_to_lock 语义为尝试加锁，可以不阻塞等待，用owns_lock函数判断是否已经获取锁。

* std::defer_lock

std::defer_lock 与 std::adpot_lock 有相反的效果，std::defer_lock 滞后需要手动lock，代码不再赘述

### 成员函数

* lock()、 unlock()
与 std::mutex 自身的lock、unlock效果一致，查看模板类函数实现可以知道，当对象对互斥量获取所有权，其lock()只是对该互斥量本身函数的封装

* release()
该函数实现把对互斥量的所有权解绑，并且返回该互斥量的对象指针，意味着当使用 release() 函数时，该对象析构无法对曾经拥有的互斥量进行析构，所以用户需要对互斥量手动unlock

### 所有权转移

对于对象std::unique_lock<std::mutex> 不允许被拷贝，这个跟 std::unique_ptr 智能指针、std::thread() 一样不允许被拷贝，但是可以使用std::move()函数来语义转移，将旧对象所有权转移给新的对象。

## 单例设计模式共享数据

### call_once用法 

```cpp
static std::once_flag resource_flag;
// CSharedData* CSharedData::s_pInstance = nullptr;
class CSharedData
	
{
	public:
		static CSharedData* GetInstance()
		{
			// 双重检验锁定 可能引起 data race，恶性条件竞争
			// if (nullptr == s_pInstance)
			// {
			// 	std::lock_guard<std::mutex> lk(resource_mutex);
			// 	if (nullptr == s_pInstance)x`
			// 	{
			// 		s_pInstance = new CTest2MsgHandler();
			// 	}
			// }
			// return s_pInstance;
	
			// C++ 11 初始化保护共享数据
			std::call_once(resource_flag, []() {s_pInstance = new CSharedData(); });
			return s_pInstance;
		}
	protected:
		CSharedData(){}
	public:
		virtual ~CSharedData(){}

		void RecvMsgProcess();
		void SendMsgProcess();
	protected:
		static CSharedData* s_pInstance;

private:
	std::list<int> m_testList;
	std::mutex m_data_mutex1;
	std::mutex m_data_mutex2;
};

#define g_pSharedData CSharedData::GetInstance()
```
std::call_once 需要传入 std::once_flag 变量， 以及一个函数指针，实现只需要加载一次的代码，这互斥量的开销会小并且更安全一些。
cu
### 使用模板写法
```cpp
#pragma once
#include <list>
#include <mutex>
#include <memory>
#include<condition_variable>
// 初始化资源锁
// static std::mutex resource_mutex;
template <typename T>
class Singleton
{
public:
	static T& GetInstance()
	{
		// 初始化资源专用
		static std::once_flag resource_flag;
		std::call_once(resource_flag, [&]() {s_pInstance.reset(new T); });
		return *s_pInstance;
	}
protected:
	Singleton() {}
	~Singleton() {}
protected:
	static std::unique_ptr<T> s_pInstance;
};

template <typename T>
std::unique_ptr<T> Singleton<T>::s_pInstance = nullptr;

class CSharedData
	
{
public:
	void RecvMsgProcess();
	bool ParseRecvMsg(int& data);
	void SendMsgProcess();
		
private:
	std::list<int> m_testList;
	std::mutex m_data_mutex;
	std::mutex m_data_mutex2;
	std::condition_variable m_cond;
};

#define g_pSharedData Singleton<CSharedData>::GetInstance()

```

## RAII
上面的几个类（lock_guard，unique_lock，call_once）都使用了一个叫做RAII的编程技巧。

RAII全称是Resource Acquisition Is Initialization，直译过来就是：资源获取即初始化。

RAII是一种C++编程技术，它将必须在使用前请求的资源（例如：分配的堆内存、执行线程、打开的套接字、打开的文件、锁定的互斥体、磁盘空间、数据库连接等——任何存在受限供给中的事物）的生命周期与一个对象的生存周期相绑定。 RAII保证资源可用于任何会访问该对象的函数。它亦保证所有资源在其控制对象的生存期结束时，以获取顺序的逆序释放。类似地，若资源获取失败（构造函数以异常退出），则为已构造完成的对象和基类子对象所获取的所有资源，会以初始化顺序的逆序释放。这有效地利用了语言特性以消除内存泄漏并保证异常安全。

RAII 可总结如下:

* 将每个资源封装入一个类，其中：
+ 造函数请求资源，并建立所有类不变式，或在它无法完成时抛出异常，
+ 析构函数释放资源并决不抛出异常；
* 始终经由 RAII 类的实例使用满足要求的资源，该资源
+ 自身拥有自动存储期或临时生存期，或
+ 具有与自动或临时对象的生存期绑定的生存期

## condition_variable、wait、notify_one、notify_all

## async、future、packaged_task、promise
## future其他成员函数、shared_future、atomic
## std::atomic续谈、std::async深入谈
## windows临界区、其他各种mutex互斥量
## 线程池浅谈、数量谈