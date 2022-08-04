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
