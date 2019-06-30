/******************************************************************************* 
*  @file      TTThread.cpp
*  @author    jimmy
*  @brief   windows�̴߳���İ�װ
******************************************************************************/

#include "stdafx.h"
#include "TTThread.h"


TTThread::TTThread()
:m_hThread(0)
{

}


TTThread::~TTThread()
{
    if (m_hThread)
    {
        ::CloseHandle(m_hThread);
    }

    m_hThread = 0;
}

/**************************************************************
*  @brief : TTThread::create
*     
*  @param : -none
*     
*  @return : BOOL
*     
*  @author : Jimmy
*     
*  @date : 2019/2/13 ������
*     
*  @note : �����̺߳���
***************************************************************/
BOOL TTThread::Create()
{

    m_hThread = (HANDLE)_beginthreadex(0,0, _threadProc, this, 0, (unsigned*)&m_dwThreadID);
    if (0 == m_hThread)
    {
        m_dwThreadID = 0;
    }

    return m_hThread >(HANDLE)1;
}

void TTThread::Destory()
{
    if (m_hThread)
    {
        //TerminateThread���첽��ʽִ��,�������ز������߳̽���,
        //�̺߳���ִֹͣ�У�λ�����������󲻻ᱻ���������ڴ�й©
        ::TerminateThread(m_hThread, 0);

        //�ȴ��߳̽���
        ::WaitForSingleObject(m_hThread, 500);

        ::CloseHandle(m_hThread);
        m_hThread = 0;
        m_dwThreadID = 0;
    }
}

BOOL TTThread::Wait(DWORD dwWaitTime)
{
    if (m_hThread == 0)
        return TRUE;
    return (::WaitForSingleObject(m_hThread, dwWaitTime) != WAIT_TIMEOUT);
}

/**************************************************************
*  @brief : TTThread::Process
*     
*  @param : -none
*     
*  @return : unsigned
*     
*  @author : Jimmy
*     
*  @date : 2019/2/16 ������
*     
*  @note :  ����̳У�����ʵ��ÿ���̶߳���ҵ���߼�
***************************************************************/
unsigned TTThread::Process()
{
    return 0;
}

unsigned __stdcall TTThread::_threadProc(void *lpParam)
{
    TTThread* pThread = (TTThread*)lpParam;
    assert(pThread);
    if (pThread != 0)
    {
        pThread->Process();
    }
    return 0;
}


/******************************************************************************/