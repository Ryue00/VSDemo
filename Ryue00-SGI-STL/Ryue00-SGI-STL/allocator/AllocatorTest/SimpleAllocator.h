#pragma once
/**
 * Copyright (c) 2020, Intretech Inc. All Rights Reserved.
 *
 * @Description: �򵥵� �ռ�������ʵ��
 * @author: RYue00
 */
#include <cstddef>
#include <iostream>
#include <vector>
 // ReSharper disable once CppInconsistentNaming
namespace RYue00
{
	// �����ڴ� ����size�� T Ԫ�صĴ�С�ڴ�ռ�
	template <class T>
	// ptrdiff_t���ͱ���ͨ��������������ָ����������Ľ��
	inline  T* _allocate(ptrdiff_t size, T*) 
	{
		// ����newʧ�ܽ���Ĭ��ִ���׳�bad_alloc�쳣
		std::set_new_handler(0);
		// std::set_new_handler([] {std::cout << "bad_alloc" << std::endl; });
		// ϵͳĬ�ϵ�ȫ��::operator new(size_t size)Ҳֻ�ǵ���malloc�����ڴ棬���ҷ���һ��void* ָ��
		// new: 1. ����operator new�����ڴ棻
		//      2. ���ù��캯�����������
		//		3. ������Ӧָ�롣
		// new��::operator new ���˲���2
		T* tmp = const_cast<T*>(::operator new(size * sizeof(T)));
		if (nullptr == tmp)
		{
			// Ϊ�� ��Ϊ����ռ�ʧ��,�˳�
			std::cerr << "out of memory" << std::endl;
			exit(-1);
		}
		return tmp;
	}

	// �ͷ��ڴ� 
	template <class T>
	inline void _deallocate(T* buffer)
	{
		// ��::operator new ����Ĭ��ȫ�֣�������
		::operator delete(buffer);
	}

	// �������
	template <class T1, class T2>
	inline void _construct(T1* p, const T2& value)
	{
		::new(p) T1(value);
	}

	// ��������
	template <class T>
	inline void _destroy(T* ptr)
	{
		ptr->~T();
	}

	// �ṩ�ⲿʹ�� allocator
	template <class T>
	class CMyAllocator
	{
	public:
		// ���������
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type; // ptrdiff_t ������ָ�����������з�����������

		template <class U>
		struct rebind
		{
			typedef CMyAllocator<U> other;
		};

		/**
		 * ����ӿ� ����ڴ���䡢�ڴ��ͷš������졢��������
		 */
		pointer allocate(size_type n, const void* hin = 0)
		{
			return _allocate((difference_type)(n), pointer(0));
		}

		void deallocate(pointer p, size_type n)
		{
			_deallocate(p);
		}

		void construct(pointer p, const T& value)
		{
			_construct(p, value);
		}

		void destroy(pointer p)
		{
			_destroy(p);
		}

		// ����ĳ�������ַ
		pointer address(reference x)
		{
			return pointer(&x);
		}

		// ����ĳ�� const ����ĵ�ַ
		const_pointer const_address(const_reference x) {
			return static_cast<const_pointer>(&x);
		}

		// ���ؿɳɹ�����������  
		size_type max_size() const {
			return (size_type)(UINT_MAX / sizeof(T)); // UINT_MAX �� unsigned long �� unsigned long long �����ֵ
		}

	};
}

