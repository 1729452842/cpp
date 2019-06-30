#include "ConnectThread.h"
#include <stdio.h>


CConnectThread::CConnectThread():m_socket(SOCKET_ERROR)
{

}

CConnectThread::~CConnectThread()
{
    if (SOCKET_ERROR != m_socket)
    {
      //�ر��׽���
      closesocket(m_socket); 
    }
}



unsigned CConnectThread::Process()
{
    char recvBuf[100] = {0};
    char sendBuf[100] = {0};


    while (1)
    {
        //��������
        memset(recvBuf,0,sizeof(recvBuf));

        recv(m_socket,recvBuf,sizeof(char)*100,0/*һ������Ϊ0*/);

        //��ӡ��������
        printf("recv data:%s\n",recvBuf);

        if ('q' == recvBuf[0] && 1 == strlen(recvBuf))
        {
            printf("quit one chat thread:%d\n",GetThreadID());
            send(m_socket,"q", strlen("q"),0);
            break;
        }

        sprintf_s(sendBuf, sizeof(sendBuf),"%s","recv data ok.");

        //��������
        send(m_socket,sendBuf, strlen(sendBuf),0);
    }

   return 0;
}


void CConnectThread::InitSocket(SOCKET fd)
{
    m_socket = fd;
}