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
// ע��ĳЩ���ÿ��ܻ��׳�std::system_error�� Ϊ�˼򵥣�͵��������û��ȥ����
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
//         // wait�ĵڶ�������ʹ����ʽ��double check���ٱ�Ҫ
//         printf("Consume message %d\n", msgQueue.front());
//         msgQueue.pop();
//         --demand;
//         if (!demand) break;
//     }
// }
// void Fun1()
// {
//     std::cout << "����ָ�����̺߳���" << std::endl;
//     return;
// }
//
// class Fun3
// {
// public:
//     void operator()()
//     {
//         std::cout << "��������̺߳���" << std::endl;
//     }
// };
//
// class Fun4
// {
// public:
//     void ThreadWork(int num)
//     {
//         std::cout << "���Ա�������̺߳��� " << num << std::endl;
//     }
// };
//
// int main()
// {
//     // ����ָ�����̺߳���
//     std::thread t1(Fun1);
//     t1.join();
//
//     // lambda ���ʽ���̺߳���
//     std::thread t2([]() {std::cout << "lambda ���ʽ���̺߳���" << std::endl; });
//     t2.join();
//
//     // ��������̺߳���
//     Fun3 f3;
//     std::thread t3(f3);
//     t3.join();
//
//     // ���Ա�������̺߳���
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
//     // std::thread t0(Fun1, num); // �������
//     // t0.join();
//     // std::cout << "int main() " << num << std::endl;
//
// 	// ���ô��ݵ���ȷ�÷�����Ҫ����std::ref() ����
//     std::thread t1(Fun1, std::ref(num)); // ��ȷ�� ͬ����ʹ�û��� std::bind() �����ô���
//     t1.join();
//     std::cout << "int main() " << num << std::endl;
//
// 	// ��ַ����
// 	std::thread t2(Fun2,&num);
//     t2.join();
//     std::cout << "int main() " << num << std::endl;
//
// 	// ���ݶ�ռʽ����ָ�룬����std::move()�����������ת�����������ʧ��
//     std::unique_ptr<int> numUniquePtr = std::make_unique<int>(100);
//     std::thread t3(Fun3, std::move(numUniquePtr));
//     t3.join();
//     std::cout << "int main() " << numUniquePtr << std::endl;
//
//     // ���ݹ�������ָ�룬�������ʧ��
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
