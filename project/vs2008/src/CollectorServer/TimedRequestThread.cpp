#include "TimedRequestThread.h"
#include <Windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

CTimedRequest::CTimedRequest():
m_uTimerID(0)
{

}

CTimedRequest::~CTimedRequest()
{
    //�����������ٶ�ʱ��
    KillTimer(NULL, m_uTimerID);

}


//��ʱ��ʹ�÷�ʽ��
//�����:��ʱ���������
void CALLBACK Timerproc (
                         HWND hwnd,        // handle to window for timer messages 
                         UINT message,     // WM_TIMER message 
                         UINT idTimer,     // timer identifier 
                         DWORD dwTime     // current system time 
                         )
{
    
    WSAData wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    STRU_DATAGRAM_OPTION  opt;
    opt.broadcast =true;
    opt.reusesock = true;
    opt.multi_cast = false;

    DatagramSocket RequestData(6000, "239.1.10.1",opt);

    char szServerIP[128] = {};
    CIPUtil::GetLocalIP(szServerIP,sizeof(szServerIP));

    //֪ͨ�ն� ִ������
    char szSendMsg[128] = {};
    szSendMsg[0] = 0x11;
    strcat_s(szSendMsg,sizeof(szSendMsg) - 1,szServerIP);


    int ret = RequestData.send(szSendMsg,strlen(szSendMsg));
    printf("send ret %d.. errcode %d\n",ret,RequestData.getErrorcode());
}




//ÿ5�뿪ʼִ��
unsigned CTimedRequest::Process()
{
    BOOL bRet = FALSE;
    MSG msg = { 0 };
    //����һ:������ʱ��

    //���hWndΪNULL������ֵΪ�½�����timer��ID
    m_uTimerID = SetTimer(NULL, 0, 5000, (TIMERPROC)Timerproc);

    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if (bRet == -1)
        {
            // handle the error and possibly exit 
        }
        else
        {
            //����ʱ����Ϣ���ݸ�so��Ϣ����,�������ܴ���Timerprocִ��
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}

