#include "Entry.h"
// #include <thread>
// #include <chrono>
// #include <condition_variable>
// #include <future>
// #include <iostream>
// #include <mutex>
// #include <queue>


#include "MsgHandler.h"
#include "ThreadManager.h"
// 注意某些调用可能会抛出std::system_error， 为了简单（偷懒），我没有去捕获
// std::mutex mutex;
// std::condition_variable condvar;
//
// std::queue<int> msgQueue;
//
// void producer(int start, int end)
// {
//     for (int x = start; x < end; x++) {
//         std::this_thread::sleep_for(std::chrono::milliseconds(200));
//         {
//             std::lock_guard<std::mutex> guard(mutex);
//             msgQueue.push(x);
//         }
//         printf("Produce message %d\n", x);
//         condvar.notify_all();
//     }
// }
//
// void consumer(int demand)
// {
//     while (true) {
//         std::unique_lock<std::mutex> ulock(mutex);
//         condvar.wait(ulock, [] { return msgQueue.size() > 0; });
//         // wait的第二个参数使得显式的double check不再必要
//         printf("Consume message %d\n", msgQueue.front());
//         msgQueue.pop();
//         --demand;
//         if (!demand) break;
//     }
// }
// void Fun1()
// {
//     std::cout << "函数指针作线程函数" << std::endl;
//     return;
// }
//
// class Fun3
// {
// public:
//     void operator()()
//     {
//         std::cout << "类对象作线程函数" << std::endl;
//     }
// };
//
// class Fun4
// {
// public:
//     void ThreadWork(int num)
//     {
//         std::cout << "类成员函数作线程函数 " << num << std::endl;
//     }
// };
//
// int main()
// {
//     // 函数指针作线程函数
//     std::thread t1(Fun1);
//     t1.join();
//
//     // lambda 表达式作线程函数
//     std::thread t2([]() {std::cout << "lambda 表达式作线程函数" << std::endl; });
//     t2.join();
//
//     // 类对象作线程函数
//     Fun3 f3;
//     std::thread t3(f3);
//     t3.join();
//
//     // 类成员函数作线程函数
//     Fun4 f4;
//     std::thread t4(&Fun4::ThreadWork, f4, 100);
//     t4.join();
//
//     return 0;
// }
// std::thread producer1(producer, 0, 10);
// std::thread producer2(producer, 10, 20);
// std::thread producer3(producer, 20, 30);
// std::thread consumer1(consumer, 20);
// std::thread consumer2(consumer, 10);
// producer1.join();
// producer2.join();
// producer3.join();
// consumer1.join();
// consumer2.join();

// void Fun1(int& num)
// {
//     num += 10;
//     std::cout << "void Fun1(int& num) " << num <<  std::endl;
// }
//
// void Fun2(int* num)
// {
//     (*num) += 10;
//     std::cout << "void Fun2(int* num) " << *num << std::endl;
// }
//
// void Fun3(std::unique_ptr<int> num)
// {
//     *num += 10;
//     std::cout << "void Fun3(int* num) " << *num << std::endl;
// }
//
// void Fun4(std::shared_ptr<int> num)
// {
//     *num += 10;
//     std::cout << "void Fun4(int* num) " << *num << std::endl;
//     std::cout << "numSharedPtr.use_count()=" << num.use_count() << std::endl;
// }
//
// int main()
// {
//     int num = 10;
//
//     // std::thread t0(Fun1, num); // 编译错误
//     // t0.join();
//     // std::cout << "int main() " << num << std::endl;
//
// 	// 引用传递的正确用法，需要借助std::ref() 函数
//     std::thread t1(Fun1, std::ref(num)); // 正确， 同样的使用还有 std::bind() 的引用传参
//     t1.join();
//     std::cout << "int main() " << num << std::endl;
//
// 	// 地址传递
// 	std::thread t2(Fun2,&num);
//     t2.join();
//     std::cout << "int main() " << num << std::endl;
//
// 	// 传递独占式智能指针，借助std::move()函数完成语义转换，否则编译失败
//     std::unique_ptr<int> numUniquePtr = std::make_unique<int>(100);
//     std::thread t3(Fun3, std::move(numUniquePtr));
//     t3.join();
//     std::cout << "int main() " << numUniquePtr << std::endl;
//
//     // 传递共享智能指针，否则编译失败
//     std::shared_ptr<int> numSharedPtr = std::make_shared<int>(100);
//     std::cout << "numSharedPtr.use_count()=" << numSharedPtr.use_count() << std::endl;
//     std::thread t4(Fun4, numSharedPtr);
//     t4.join();
//     std::cout << "numSharedPtr.use_count()=" << numSharedPtr.use_count() << std::endl;
//     std::cout << "int main() " << numSharedPtr << std::endl;
//
//     std::weak_ptr<int> d;
//     return 0;
// }

int main()
{
    
    CThreadManager test;
    test.Init();

    return 0;
}
