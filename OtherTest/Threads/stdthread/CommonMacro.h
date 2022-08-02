#pragma once

//////////////////////////////////////////////////////////////////////////
// 工厂函数
#define	NEW_RELEASE(T)	\
public:	\
	static T* CreateNew() { return new T; } \
	void Release() { delete this; }

//////////////////////////////////////////////////////////////////////////
// 单例模式
#define	INSTANCE_DECLARATION(T)	\
	public:	\
		static T* GetInstance() \
	{ \
		if (s_pInstance == NULL) \
	{ \
		s_pInstance = new T(); \
	} \
		if(nullptr == s_pInstance) \
		{\
			return nullptr; \
		}\
		return s_pInstance; \
	} \
	protected: \
		T(); \
	public: \
		virtual ~T(); \
	protected: \
		static T* s_pInstance;

#define	INSTANCE_IMPLEMENTATION(T) \
	T* T::s_pInstance = NULL;

#define	INSTANCE_IMPLEMENTATION_DEFAULT(T) \
	T* T::s_pInstance = NULL; \
	T::T(){} \
	T::~T(){}

#define	PROTECTED_DECLARATION(T) \
protected:	\
	T(){} \
	virtual ~T(){}

#define	INTERFACE_DECLARATION(T) \
protected:	\
	T(){} \
public: \
	virtual ~T(){}