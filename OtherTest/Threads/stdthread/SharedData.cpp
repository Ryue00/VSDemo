#include "SharedData.h"
#include <thread>
#include <iostream>



void CSharedData::RecvMsgProcess()
{
	int data;
	for (int i = 0; i < 10000; i++)
	{
		auto result = ParseRecvMsg(data);
		if (result)
		{
			std::cout << "线程ID=" << std::this_thread::get_id() << "收到消息：" << data << std::endl;
		}
		else
		{
			std::cout << "线程ID=" << std::this_thread::get_id() << "当前队列为空" << std::endl;
		}
	}

}

bool CSharedData::ParseRecvMsg(int& data)
{
	// std::unique_lock<std::mutex> lock(m_data_mutex);
	// m_data_mutex2.lock();  // 顺序不一致，导致死锁
	// m_data_mutex.lock();
	// std::lock(m_data_mutex, m_data_mutex2);
	// std::lock_guard<std::mutex> lock1(m_data_mutex,std::adopt_lock);
	// std::lock_guard<std::mutex> lock2(m_data_mutex2, std::adopt_lock);
	// std::lock_guard 使用的是C++ RAII(资源获取即初始化)，所以在构造时会对 mutex进行加锁操作
	// 而std::adopt_lock参数，该结构体可以理解为标志为，加这个参数不会对互斥量进行加锁，但是在析构时还是会进行解锁
	std::unique_lock<std::mutex> lock(m_data_mutex);

	m_cond.wait(lock, [this]()
		{
			if (!m_testList.empty())
				return true;
			return false;
		});
	
	data = m_testList.front();
	m_testList.pop_front();
	return true;
	
}

void CSharedData::SendMsgProcess()
{
	for (int i = 0; i < 10000; i++)
	{
		std::cout << "线程ID=" << std::this_thread::get_id() << "发送消息：" << i << std::endl;
		std::unique_lock<std::mutex> lock(m_data_mutex);
		m_testList.push_back(i);
		m_cond.notify_one();
	}
}
