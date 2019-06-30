// UDPClient.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#pragma  comment(lib, "ws2_32.lib")


int _tmain(int argc, _TCHAR* argv[])
{
    WORD        wVersionRequested;
    WSADATA     wsaData;

    /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) 
    {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

    /* Confirm that the WinSock DLL supports 2.2.*/
    /* Note that if the DLL supports versions greater    */
    /* than 2.2 in addition to 2.2, it will still return */
    /* 2.2 in wVersion since that is the version we      */
    /* requested.                                        */

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
        return 1;
    }

    //-----------------------------------------------
    SOCKET socketClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketClient == INVALID_SOCKET) 
    {
        printf("socket failed with error %d\n", WSAGetLastError());
        return 1;
    }

    //Ĭ�ϵ��׽���������sock�ǲ�֧�ֹ㲥�����������׽�����������֧�ֹ㲥
    int so_broadcast = 1;
    setsockopt(socketClient, SOL_SOCKET, SO_BROADCAST, (const char*)&so_broadcast,sizeof(so_broadcast));

    //��������socket��Ϣ
    SOCKADDR_IN addrServer;
    addrServer.sin_family   = AF_INET;

    //��������Ӧ�ó���˿�
    addrServer.sin_port     = htons(6000);

    //��������IP��ַ,INADDR_BROADCAST����255.255.255.255 �ǹ㲥
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
    

    int nLength = sizeof(addrServer);
    char szSendMsg[100]= {0};
    char szRecvBuf[100] = {0};

    
    while (1)
    {
        //��������
        printf("pls input msg...:\n");

        memset(szSendMsg,0, sizeof(szSendMsg));

        gets_s(szSendMsg, sizeof(szSendMsg));

        int nSendSize = sendto(socketClient,szSendMsg,strlen(szSendMsg),0,(SOCKADDR*)&addrServer,nLength);
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
        int nRecvSize = recvfrom(socketClient,szRecvBuf,100,0,(SOCKADDR*)&addrServer,&nLength);
        if (nRecvSize > 0)
        {
            printf("server->client:%s\n",szRecvBuf);
        }
    }

    closesocket(socketClient);

    WSACleanup();

    return 0;
}

