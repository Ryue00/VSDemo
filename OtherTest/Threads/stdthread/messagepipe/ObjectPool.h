#pragma once

/**
 * �ڴ�أ�ʹ�ÿռ�������std::allocator��std::construct�Ƚ��ռ�ͳ�ʼ���ֿ��������ڴ���Ƭ
 */

#include <memory>
#include <iostream>
#include <mutex>

template<typename T>
class CObjectPool
{
public:
	CObjectPool(const char* pName);
	~CObjectPool();

public:
	// ��ʼ��������objPoolSize��ʾ����ش�С�������������Ԥ�ȷ�����ڴ�
	bool Init(int objPoolSize);
	T* CreateObject();
	void RecycleObject(T* pObj);

private:
	// ����
	char m_name[64];
	int m_objPoolSize;
	T* m_pFirstObj;
	std::allocator<T> m_setObj;
	// CCriticalSection m_critSec;
};


template<typename T>
CObjectPool<T>::CObjectPool(const char* pName)
	: m_objPoolSize(0)
	, m_pFirstObj(NULL)
{
	// MYASSERT(pName);
	if (pName != NULL)
	{
		// strncpy(m_name, pName, sizeof(m_name) - 1);
	}
}

template<typename T>
CObjectPool<T>::~CObjectPool()
{
	//std::unique_lock<std::mutex> lock(ttttttttt);
	if (m_pFirstObj)
	{
		for (int i = 0; i < m_objPoolSize; ++i)
		{
			m_setObj.destroy(m_pFirstObj + i);
		}

		m_setObj.deallocate(m_pFirstObj, m_objPoolSize);
	}
}

template<typename T>
bool CObjectPool<T>::Init(int objPoolSize)
{
	if(objPoolSize != 0)
	{
		std::cout << "" << std::endl;
	}

	if (m_objPoolSize > 0)
	{
		// LOG_SYS_INFO("%s has allocated %u objects already", m_name, m_objPoolSize);
		return true;
	}

	m_objPoolSize = objPoolSize;
	m_pFirstObj = m_setObj.allocate(m_objPoolSize);

	T* pObj = m_pFirstObj;
	for (auto i = 0; i < m_objPoolSize; ++i)
	{
		pObj = m_pFirstObj + i;
		m_setObj.construct(pObj);
		pObj->SetAllocatedId(i + 1);
	}

	// LOG_SYS_INFO("%s: allocate %u objects", m_name, m_objPoolSize);

	return (m_pFirstObj != NULL);
}

template<typename T>
T* CObjectPool<T>::CreateObject()
{
	T* pCanUseObj = NULL;
	if (m_pFirstObj)
	{
		//std::unique_lock<std::mutex> lock(ttttttttt);
		for (int i = 0; i < m_objPoolSize; ++i)
		{
			T* pObj = m_pFirstObj + i;
			if (pObj->CanUse())
			{
				//LOG_SYS_DEBUG("allocate %d \"Object\"", pObj->allocatedNum);
				pCanUseObj = pObj;
				pObj->SetCanUse(false);
				break;
			}
		}
	}

	if (pCanUseObj)
	{
		return pCanUseObj;
	}

	// �Ҳ������õĶ�������new
	// LOG_SYS_DEBUG("no allocated \"Object\" can use, new \"Object\"");
	return new T();
}

template<typename T>
void CObjectPool<T>::RecycleObject(T* pObj)
{
	CHECK(pObj);

	//std::unique_lock<std::mutex> lock(ttttttttt);
	if (pObj->IsAllocatedObj())
	{
		//LOG_SYS_DEBUG("recycle %d \"Object\"", pObj->allocatedNum);
		pObj->SetCanUse(true);
	}
	else
	{
		SAFE_DELETE(pObj);
	}
}
