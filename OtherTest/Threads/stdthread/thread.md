# ��������߳�

## �����������ʵ�֣����̡��̻߳�������
### ����
�������߸��������ͬʱ������һ������ͬʱ֮���ܶ������������

### ��ִ�г���
�����ϵ�һ���ļ����磬windows�µ� .exe�ļ�

### ����
ϵͳ������Դ����͵��ȵĻ�����λ���ǲ���ϵͳ�ṹ�Ļ�����

### �߳�
����ϵͳ�ܹ�����������ȵ���С��λ�����������ڽ���֮�У��ǽ����е�ʵ��������λ��
һ���߳�ָ���ǽ�����һ����һ˳��Ŀ�������һ�������п��Բ�������̣߳�ÿ���̲߳���ִ�в�ͬ������

## C++��׼�߳�ʹ��

### thread ��ļ򵥽���

| ������ | ���� |
|--|--|
| thread() | ����һ���̶߳���û�й����κ��̺߳�������û�������κ��߳� |
| thread(fn, args1, args2, ��) | ����һ���̶߳��󣬲������̺߳���fn��args1��args2����Ϊ�̺߳����Ĳ���
| get_id() | ��ȡ�߳�id
| jionable() | �߳��Ƿ���ִ�У�joinable�������һ������ִ���е��̡߳�
| jion() | �ú������ú������ס�̣߳������߳̽��������̼߳���ִ��
| detach() |�ڴ����̶߳�������ϵ��ã����ڰѱ������߳����̶߳�����뿪��������̱߳�Ϊ��̨�̣߳��������̵߳�"����"�������߳��޹�

## �̴߳������,��Ա�������̺߳���
### �̺߳���

* ����ָ��
* lambda���ʽ
* ��������
``` cpp

void Fun1()
{
    std::cout << "����ָ�����̺߳���" << std::endl;
    return;
}

class Fun3
{
public:
    void operator()()
    {
        std::cout << "��������̺߳���" << std::endl;
    }
};

class Fun4
{
public:
    void ThreadWork(int num)
    {
        std::cout << "���Ա�������̺߳��� " << num << std::endl;
    }
};

int main()
{
    // ����ָ�����̺߳���
    std::thread t1(Fun1);
    t1.join();

	// lambda ���ʽ���̺߳���
    std::thread t2([]() {std::cout << "lambda ���ʽ���̺߳���" << std::endl; });
    t2.join();

	// ��������̺߳���
    Fun3 f3;
    std::thread t3(f3);
    t3.join();

	// ���Ա�������̺߳���
    Fun4 f4;
    std::thread t4(&Fun4::ThreadWork,f4,100);  
    t4.join();
	
    return 0;
}

```
### thread���Ƿ������ģ��������������Լ���ֵ�����ǿ����ƶ�������ƶ���ֵ������һ���̶߳�������̵߳�״̬ת�Ƹ������̶߳���ת���ڼ䲻Ӱ���̵߳�ִ�С�
### ����ͨ��jionable()�����ж��߳��Ƿ�����Ч�ģ����������������������߳���Ч
* �����޲ι��캯��������̶߳���
* �̶߳����״̬�Ѿ�ת�Ƹ������̶߳���
* �߳��Ѿ�����jion����detach����

### �����벢�е�����
* ������ָ�������߶���¼���ͬһʱ�̷�������������ָ���������¼���ͬһʱ����������
* �������ڲ�ͬʵ���ϵĶ���¼�����������ͬһʵ���ϵĶ���¼���
* ��һ̨�������ϡ�ͬʱ�������ͬʱʵ�����н��桰���������������ڶ�̨��������ͬʱ����������

### �̺߳�������
�̺߳�����������ֵ�����ķ�ʽ�����̵߳�ջ�ռ䣬���Լ�ʹ��������������ͣ����߳��޸�Ҳ�޷����ⲿʵ�θı䣬����һЩ�������ᱻ����.

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

    // std::thread t0(Fun1, num); // �������
    // t0.join();
    // std::cout << "int main() " << num << std::endl;

    // ���ô��ݵ���ȷ�÷�����Ҫ����std::ref() ����
    std::thread t1(Fun1, std::ref(num)); // ��ȷ�� ͬ����ʹ�û��� std::bind() �����ô���
    t1.join();
    std::cout << "int main() " << num << std::endl;

    // ��ַ����
    std::thread t2(Fun2,&num);
    t2.join();
    std::cout << "int main() " << num << std::endl;

    // ���ݶ�ռʽ����ָ�룬����std::move()�����������ת�����������ʧ��
    std::unique_ptr<int> numUniquePtr = std::make_unique<int>(100);
    std::thread t3(Fun3, std::move(numUniquePtr));
    t3.join();
    std::cout << "int main() " << numUniquePtr << std::endl;

    // ���ݹ�������ָ��
    std::shared_ptr<int> numSharedPtr = std::make_shared<int>(100);
    std::cout << "numSharedPtr.use_count()=" << numSharedPtr.use_count() << std::endl;
    std::thread t4(Fun4, numSharedPtr);
    t4.join();
    std::cout << "numSharedPtr.use_count()=" << numSharedPtr.use_count() << std::endl;
    std::cout << "int main() " << numSharedPtr << std::endl;

    return 0;
}
```

## ��������̡߳����ݹ����������
### ��������߳�
ʹ�������ܿ��߳�
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

### ���ݹ����������

* only read data����ȫ�ȶ�,����Ҫ���⴦��
* read and write data��������������
C++��׼�ṩ�����������ݵ��������ʽ���ǻ�����mutex������

## ����������÷�����������
### ����÷�
std::mutex ������C++������ı����������ݵĴ�ʩ����Ҫ������֯�ͱ��Ŵ���
```cpp

std::list<int> m_testList;
std::mutex m_data_mutex;  // ��������һ����
void CSharedData::RecvMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
		// std::unique_lock<std::mutex> lock(m_data_mutex); 
		m_data_mutex.lock();
		if (!m_testList.empty())
		{
			int data = m_testList.front();
			std::cout << "�߳�ID=" << std::this_thread::get_id() << "�յ���Ϣ��" << data << std::endl;
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
		std::cout << "�߳�ID=" << std::this_thread::get_id() << "������Ϣ��" << i << std::endl;
		m_testList.push_back(i);
		// lock.unlock();
		m_data_mutex.unlock();
	}
}

```

### ����

�����������̣߳�����ͬʱ��ס���������������ܽ���ĳ��������������̶߳��ֱ�ֻ��ס��һ�����⣬���ڵȴ���һ�����������
��Ϊ������

```cpp
std::list<int> m_testList;
std::mutex m_data_mutex1;  // ��������һ����
std::mutex m_data_mutex2;  // ��������һ����
void CSharedData::RecvMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
         // std::lock_guard<std::mutex> lock(m_data_mutex1);
         // std::lock_guard<std::mutex> lock(m_data_mutex2);
		// std::unique_lock<std::mutex> lock(m_data_mutex1);
		m_data_mutex2.lock();  // ˳��һ�£���������
		m_data_mutex1.lock();
		if (!m_testList.empty())
		{
			int data = m_testList.front();
			std::cout << "�߳�ID=" << std::this_thread::get_id() << "�յ���Ϣ��" << data << std::endl;
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
		m_data_mutex1.lock();  // ˳��һ�£���������
		m_data_mutex2.lock();
		std::cout << "�߳�ID=" << std::this_thread::get_id() << "������Ϣ��" << i << std::endl;
		m_testList.push_back(i);
		// lock.unlock();
		m_data_mutex2.unlock();
		m_data_mutex1.unlock();
	}
}

���ʾ����������������һ��Ľ����������ʹ�� std::lock() ģ�庯�����£�
```cpp
std::list<int> m_testList;
std::mutex m_data_mutex1;  // ��������һ����
std::mutex m_data_mutex2;  // ��������һ����
void CSharedData::RecvMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
		// std::unique_lock<std::mutex> lock(m_data_mutex1);
		// m_data_mutex2.lock();  // ˳��һ�£���������
		// m_data_mutex1.lock();
		
		std::lock(m_data_mutex1, m_data_mutex2);
		std::lock_guard<std::mutex> lock1(m_data_mutex1,std::adopt_lock);
		std::lock_guard<std::mutex> lock2(m_data_mutex2, std::adopt_lock); // 
		// 
		if (!m_testList.empty())
		{
			int data = m_testList.front();
			std::cout << "�߳�ID=" << std::this_thread::get_id() << "�յ���Ϣ��" << data << std::endl;
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
		// m_data_mutex1.lock();  // ˳��һ�£���������
		// m_data_mutex2.lock();
		std::lock(m_data_mutex2, m_data_mutex1);
		std::lock_guard<std::mutex> lock1(m_data_mutex1, std::adopt_lock);
		std::lock_guard<std::mutex> lock2(m_data_mutex2, std::adopt_lock);
		std::cout << "�߳�ID=" << std::this_thread::get_id() << "������Ϣ��" << i << std::endl;
		m_testList.push_back(i);
		// m_data_mutex2.unlock();
		// m_data_mutex1.unlock();
	}
}

```
std::lock ����ͬʱ�Զ�����������м���������std::lock_guard ʹ�õ���C++ RAII(��Դ��ȡ����ʼ��)��������ڹ���ʱ��� mutex���м�������
��std::adopt_lock�������ýṹ��������Ϊ��־Ϊ���������������Ի��������м���������������ʱ���ǻ���н�����

## unique_lock���

### ����

* std::unique_lock ������������ std::lock_guard Ҳ��ʹ�� RAII ��ʽ����,��������Դ��ʼ���׶Σ���������Դ�����׶�
* std::unique_lock ���������������Ĵ��۾����ڴ��Լ��������ӣ�������������ڵڶ������Լ���Ա����

### �ڶ�����

* std::adpot_lock �� lock_guard ����

```cpp
std::list<int> m_testList;
std::mutex m_data_mutex1;  // ��������һ����
std::mutex m_data_mutex2;  // ��������һ����
void CSharedData::RecvMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
		// std::unique_lock<std::mutex> lock(m_data_mutex1);
		// m_data_mutex2.lock();  // ˳��һ�£���������
		// m_data_mutex1.lock();
		// std::lock(m_data_mutex1, m_data_mutex2);
		// std::lock_guard<std::mutex> lock1(m_data_mutex1,std::adopt_lock);
		// std::lock_guard<std::mutex> lock2(m_data_mutex2, std::adopt_lock);
		// std::lock_guard ʹ�õ���C++ RAII(��Դ��ȡ����ʼ��)�������ڹ���ʱ��� mutex���м�������
		// ��std::adopt_lock�������ýṹ��������Ϊ��־Ϊ���������������Ի��������м���������������ʱ���ǻ���н���

		m_data_mutex1.lock();
		std::unique_lock<std::mutex> lock(m_data_mutex1,std::adopt_lock);

		if (lock.owns_lock())
		{
			if (!m_testList.empty())
			{
				int data = m_testList.front();
				std::cout << "�߳�ID=" << std::this_thread::get_id() << "�յ���Ϣ��" << data << std::endl;
				m_testList.pop_front();
			}
		}
		else
		{
			std::cout << "�߳�ID=" << std::this_thread::get_id() << "����������û���õ���" << i << std::endl;
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
		
		std::cout << "�߳�ID=" << std::this_thread::get_id() << "������Ϣ��" << i << std::endl;
		m_testList.push_back(i);
	}
}

```
std::unique_lock<std::mutex> lock(m_data_mutex1,std::adopt_lock)������������ std::adopt_lock ���߱���lock�����Ѿ������ˣ�����Ҫ�ڹ������
������������

* std::try_to_lock
```cpp

void CSharedData::RecvMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
		// std::unique_lock<std::mutex> lock(m_data_mutex1);
		// m_data_mutex2.lock();  // ˳��һ�£���������
		// m_data_mutex1.lock();
		// std::lock(m_data_mutex1, m_data_mutex2);
		// std::lock_guard<std::mutex> lock1(m_data_mutex1,std::adopt_lock);
		// std::lock_guard<std::mutex> lock2(m_data_mutex2, std::adopt_lock);
		// std::lock_guard ʹ�õ���C++ RAII(��Դ��ȡ����ʼ��)�������ڹ���ʱ��� mutex���м�������
		// ��std::adopt_lock�������ýṹ��������Ϊ��־Ϊ���������������Ի��������м���������������ʱ���ǻ���н���

		m_data_mutex1.lock();
		std::unique_lock<std::mutex> lock(m_data_mutex1,std::try_to_lock);

		if (lock.owns_lock())
		{
			if (!m_testList.empty())
			{
				int data = m_testList.front();
				std::cout << "�߳�ID=" << std::this_thread::get_id() << "�յ���Ϣ��" << data << std::endl;
				m_testList.pop_front();
			}
		}
		else
		{
			std::cout << "�߳�ID=" << std::this_thread::get_id() << "����������û���õ���" << i << std::endl;
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
		
		std::cout << "�߳�ID=" << std::this_thread::get_id() << "������Ϣ��" << i << std::endl;
		m_testList.push_back(i);
	}
}

```	
�����ϴ�����Կ��� std::unique_lock<std::mutex> lock(m_data_mutex1,std::try_to_lock)���������߳� SendMsgProcess �ȴ�����20����ʱ�򣬴�ʱ�Ѿ���ȡ��m_data_mutex1������Ȩ�� �������̱߳��޷�ȡ������Ȩ������ʹ�� std::try_to_lock ����Ϊ���Լ��������Բ������ȴ�����owns_lock�����ж��Ƿ��Ѿ���ȡ����

* std::defer_lock

std::defer_lock �� std::adpot_lock ���෴��Ч����std::defer_lock �ͺ���Ҫ�ֶ�lock�����벻��׸��

### ��Ա����

* lock()�� unlock()
�� std::mutex �����lock��unlockЧ��һ�£��鿴ģ���ຯ��ʵ�ֿ���֪����������Ի�������ȡ����Ȩ����lock()ֻ�ǶԸû������������ķ�װ

* release()
�ú���ʵ�ְѶԻ�����������Ȩ��󣬲��ҷ��ظû������Ķ���ָ�룬��ζ�ŵ�ʹ�� release() ����ʱ���ö��������޷�������ӵ�еĻ��������������������û���Ҫ�Ի������ֶ�unlock

### ����Ȩת��

���ڶ���std::unique_lock<std::mutex> ����������������� std::unique_ptr ����ָ�롢std::thread() һ�����������������ǿ���ʹ��std::move()����������ת�ƣ����ɶ�������Ȩת�Ƹ��µĶ���

## �������ģʽ��������

### call_once�÷� 

```cpp
static std::once_flag resource_flag;
// CSharedData* CSharedData::s_pInstance = nullptr;
class CSharedData
	
{
	public:
		static CSharedData* GetInstance()
		{
			// ˫�ؼ������� �������� data race��������������
			// if (nullptr == s_pInstance)
			// {
			// 	std::lock_guard<std::mutex> lk(resource_mutex);
			// 	if (nullptr == s_pInstance)x`
			// 	{
			// 		s_pInstance = new CTest2MsgHandler();
			// 	}
			// }
			// return s_pInstance;
	
			// C++ 11 ��ʼ��������������
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
std::call_once ��Ҫ���� std::once_flag ������ �Լ�һ������ָ�룬ʵ��ֻ��Ҫ����һ�εĴ��룬�⻥�����Ŀ�����С���Ҹ���ȫһЩ��
cu
### ʹ��ģ��д��
```cpp
#pragma once
#include <list>
#include <mutex>
#include <memory>
#include<condition_variable>
// ��ʼ����Դ��
// static std::mutex resource_mutex;
template <typename T>
class Singleton
{
public:
	static T& GetInstance()
	{
		// ��ʼ����Դר��
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
����ļ����ࣨlock_guard��unique_lock��call_once����ʹ����һ������RAII�ı�̼��ɡ�

RAIIȫ����Resource Acquisition Is Initialization��ֱ��������ǣ���Դ��ȡ����ʼ����

RAII��һ��C++��̼���������������ʹ��ǰ�������Դ�����磺����Ķ��ڴ桢ִ���̡߳��򿪵��׽��֡��򿪵��ļ��������Ļ����塢���̿ռ䡢���ݿ����ӵȡ����κδ������޹����е����������������һ�����������������󶨡� RAII��֤��Դ�������κλ���ʸö���ĺ��������ౣ֤������Դ������ƶ���������ڽ���ʱ���Ի�ȡ˳��������ͷš����Ƶأ�����Դ��ȡʧ�ܣ����캯�����쳣�˳�������Ϊ�ѹ�����ɵĶ���ͻ����Ӷ�������ȡ��������Դ�����Գ�ʼ��˳��������ͷš�����Ч�����������������������ڴ�й©����֤�쳣��ȫ��

RAII ���ܽ�����:

* ��ÿ����Դ��װ��һ���࣬���У�
+ �캯��������Դ�������������಻��ʽ���������޷����ʱ�׳��쳣��
+ ���������ͷ���Դ�������׳��쳣��
* ʼ�վ��� RAII ���ʵ��ʹ������Ҫ�����Դ������Դ
+ ����ӵ���Զ��洢�ڻ���ʱ�����ڣ���
+ �������Զ�����ʱ����������ڰ󶨵�������

## condition_variable��wait��notify_one��notify_all

## async��future��packaged_task��promise
## future������Ա������shared_future��atomic
## std::atomic��̸��std::async����̸
## windows�ٽ�������������mutex������
## �̳߳�ǳ̸������̸