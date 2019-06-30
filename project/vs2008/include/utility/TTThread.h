/*******************************************************************************
*  @file      TTThread.h 2014\7\1 16:04:05 $
*  @author    jimmy
*  @brief   windows�̴߳���İ�װ
******************************************************************************/

#ifndef TTTHREAD_27D478B1_0BAD_4015_A6E5_8AF2DA7739BF_H__
#define TTTHREAD_27D478B1_0BAD_4015_A6E5_8AF2DA7739BF_H__
#include <assert.h>
#include <process.h>
#include <Windows.h>

#include "utilityDll.h"
/**
* The class <code>TTThread</code> 
*
*/
class UTILITY_CLASS TTThread
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
    * Constructor 
    */
    TTThread();
    /**
    *virtual Destructor
    */
    virtual ~TTThread();
    //@}

public:

    BOOL Create();

    void Destory();

    BOOL Wait(DWORD dwWaitTime =INFINITE);

    inline DWORD GetThreadID() { return m_dwThreadID; }

protected:

    virtual unsigned Process() = 0;

private:
    //�߳���ڵ�ַ
    static unsigned  __stdcall _threadProc(void *lpParam);

private:
    HANDLE		m_hThread;
    DWORD		m_dwThreadID;
};


/******************************************************************************/
#endif// TTTHREAD_27D478B1_0BAD_4015_A6E5_8AF2DA7739BF_H__
