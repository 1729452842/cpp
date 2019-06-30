// TCPClient.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include "stdafx.h"
#include <WinSock2.h>
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
    SOCKET socketClient = socket(AF_INET, SOCK_STREAM,0);

    //����socket��Ϣ
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;//��ַ��

    addrSrv.sin_port = htons(6100);//�˿ں�

    //��������ַ,�����ַʹ�� inet_addr("192.168.xxx.xxx"),���ص�ַʹ��  htonl(INADDR_LOOPBACK)
    addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.0.108");
    int nLength = sizeof(SOCKADDR_IN);

    connect(socketClient,(SOCKADDR*)&addrSrv,nLength);

    //��������
    char szSendMsg[100] = {};
    //��������
    char szRecvBuf[100] = {0};

    while (1)
    {
        //��������
        printf("pls input msg...:\n");

        memset(szSendMsg,0, sizeof(szSendMsg));

        gets_s(szSendMsg, sizeof(szSendMsg));

        int nSendSize = sendto(socketClient,szSendMsg,strlen(szSendMsg),0,(SOCKADDR*)&addrSrv,nLength);
        if (nSendSize > 0)
        {
            printf("client->server:%s\n",szSendMsg);
        }
        else
        {
            printf("send data error...\n");
        }

        //��������
        memset(szRecvBuf,0, sizeof(szRecvBuf));
        int nRecvSize = recvfrom(socketClient,szRecvBuf,100,0,(SOCKADDR*)&addrSrv,&nLength);
        if (nRecvSize > 0)
        {
            printf("server->client:%s\n",szRecvBuf);

            if (strlen(szRecvBuf) == 1 && szRecvBuf[0] == 'q')
            {
                printf("quit chat...\n");

                break;
            }
        }

    }

    //�رռ����׽���
    closesocket(socketClient); 

    //�����׽��ֿ��ʹ��
    WSACleanup();

    system("pause");
    return 0;
}

