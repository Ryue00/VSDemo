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
			std::cout << "�߳�ID=" << std::this_thread::get_id() << "�յ���Ϣ��" << data << std::endl;
		}
		else
		{
			std::cout << "�߳�ID=" << std::this_thread::get_id() << "��ǰ����Ϊ��" << std::endl;
		}
	}

}

bool CSharedData::ParseRecvMsg(int& data)
{
	// std::unique_lock<std::mutex> lock(m_data_mutex);
	// m_data_mutex2.lock();  // ˳��һ�£���������
	// m_data_mutex.lock();
	// std::lock(m_data_mutex, m_data_mutex2);
	// std::lock_guard<std::mutex> lock1(m_data_mutex,std::adopt_lock);
	// std::lock_guard<std::mutex> lock2(m_data_mutex2, std::adopt_lock);
	// std::lock_guard ʹ�õ���C++ RAII(��Դ��ȡ����ʼ��)�������ڹ���ʱ��� mutex���м�������
	// ��std::adopt_lock�������ýṹ��������Ϊ��־Ϊ���������������Ի��������м���������������ʱ���ǻ���н���
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
		std::cout << "�߳�ID=" << std::this_thread::get_id() << "������Ϣ��" << i << std::endl;
		std::unique_lock<std::mutex> lock(m_data_mutex);
		m_testList.push_back(i);
		m_cond.notify_one();
	}
}
