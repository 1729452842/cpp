// TCPServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <WinSock2.h>
#include "ConnectThread.h"
#pragma  comment(lib, "ws2_32.lib")




int _tmain(int argc, _TCHAR* argv[])
{
    //�����׽��ֿ�
    WORD wVersionRequested;
    WSADATA wsaData = {0};
    wVersionRequested = MAKEWORD(1,1);

    if (WSAStartup(wVersionRequested, &wsaData) != 0 ) 
    {
        return 1;
    }

    if (LOBYTE(wsaData.wVersion) != 1 ||
        HIBYTE(wsaData.wVersion) != 1) 
    {
        WSACleanup( );
        return 1; 
    }

    //The WinSock DLL is acceptable.

    //�������ڼ������׽��֣�ӵ�е�ַ�� ����û�����֣���ַ��+��ַ+�˿ں�
    SOCKET socketSrv = socket(AF_INET, SOCK_STREAM,0);

    //����socket��Ϣ
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;//��ַ��

    addrSrv.sin_port = htons(6100);//�˿ں�

    //�����������е�������ַ�������������ݴ��ĸ���������
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);


    //�����ֺ��׽��ְ���һ��
    bind(socketSrv,(SOCKADDR*)&addrSrv, sizeof(SOCKADDR_IN));

    //���׽�����Ϊ����ģʽ��׼�����տͻ�����
    listen(socketSrv,SOMAXCONN);

    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);
    const int MAX_THREAD = 5;

    //ģ���̳߳أ����5��
    CConnectThread vecThread[MAX_THREAD];

    while (1)
    {
        //accpet��������ֱ��client�˵���connect
        SOCKET sockConn = accept(socketSrv,(SOCKADDR*)&addrClient,&len);
        int index = 0;
        vecThread[index].InitSocket(sockConn);
        vecThread[index].Create();
        index++;

        if (index >= MAX_THREAD)
        {
            break;
        }
    }

    //�رռ����׽���
    closesocket(socketSrv); 

    //�����׽��ֿ��ʹ��
    WSACleanup();

    system("pause");
    return 0;
}

