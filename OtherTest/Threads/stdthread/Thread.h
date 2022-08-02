#pragma once
#include <thread>
#include <vector>

/**
* Copyright (c) 2022, RYue All rights reserved.
*
* @Description: 标准库线程
* @author: RYue
* @date: 2022-07-01 11:43:57
*/


class IRunable;

class CThread
{
public:
	CThread(IRunable* run = nullptr);
    ~CThread();

    void Start();

    void Run();

    void Wait();

private:
    static void* ThreadProc(void* arg);
    std::thread m_thread;
    std::thread::id m_threadId;
    IRunable* m_run;
};

