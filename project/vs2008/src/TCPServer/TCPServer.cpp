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

    int nResult = 0;            // used to return function results

    //The WinSock DLL is acceptable.

    //�������ڼ������׽���
    SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM,0);
    if (INVALID_SOCKET == ListenSocket)
    {
        printf("create socket error (%d)\n",::WSAGetLastError());
        WSACleanup();
        return 1;
    }

    //����socket��Ϣ
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;//��ַ��

    addrSrv.sin_port = htons(6100);//�˿ں�

    //�����������е�������ַ�������������ݴ��ĸ���������
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    //�����ֺ��׽��ְ���һ��
    nResult = bind(ListenSocket,(SOCKADDR*)&addrSrv, sizeof(SOCKADDR_IN));
    if (nResult == SOCKET_ERROR)
    {
        printf("bind socket error code = %d\n",::WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    

    //���׽�����Ϊ����ģʽ��׼�����տͻ�����
    nResult = listen(ListenSocket,SOMAXCONN);
    if (SOCKET_ERROR == nResult)
    {
        printf("listen socket error(%d)\n",::WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    fd_set allSocket;
    FD_ZERO(&allSocket);

    FD_SET(ListenSocket,&allSocket);

    printf("�������������...\n");

    while (TRUE)
    {
        fd_set read_set;
        FD_ZERO(&read_set);

        read_set = allSocket;

        nResult = select(0,&read_set,NULL,NULL,NULL);
        if (SOCKET_ERROR == nResult)
        {
            printf("select error(%d)...\n",::WSAGetLastError());
            break;
        }
        else
        {
            //printf("readable or writable socket number %d\n",nResult);
        }

        if (FD_ISSET(ListenSocket,&read_set))
        {
            SOCKADDR_IN ClientAddr;
            int nLen = sizeof(ClientAddr);
            SOCKET socketClient = accept(ListenSocket,(sockaddr*)&ClientAddr, &nLen);
            if (INVALID_SOCKET == socketClient)
            {
                printf("accept socket is invalid...\n");
                continue;
            }

            FD_SET(socketClient, &allSocket);

            char* pszClientIP = inet_ntoa(ClientAddr.sin_addr);
            if(NULL != pszClientIP)
            {
                printf("���¿ͻ���[%s:%d]����������\n",pszClientIP,ntohs(ClientAddr.sin_port));
                printf("Ŀǰ�ͻ��˵�����Ϊ: %d\n",allSocket.fd_count - 1);
            }

            continue;
        }

        for (unsigned i = 0; i < allSocket.fd_count; i++)
        {
            SOCKET socket = allSocket.fd_array[i];

            SOCKADDR_IN addrClient;
            int nLen = sizeof(addrClient);
            getpeername(socket,(sockaddr*)&addrClient, &nLen);
            char* pszClientIp = inet_ntoa(addrClient.sin_addr);
            unsigned short usClientPort = ntohs(addrClient.sin_port);

            if (FD_ISSET(socket,&read_set))
            {
                char szMsg[128] = {};
                int nResult = recv(socket,szMsg,sizeof(szMsg),0);
                if (nResult > 0)
                {
                    printf("--------�ͻ���[%s:%d]--------\n",pszClientIp,usClientPort);
                    printf("��Ϣ����%d�ֽ�\n",nResult);
                    printf("��Ϣ����: %s\n",szMsg);
                }
                else if (0 == nResult)
                {
                    //�Է��ر�����
                    printf("�ͻ���[%s:%d]�����ر�����...\n",pszClientIp,usClientPort);
                    closesocket(socket);
                    FD_CLR(socket,&allSocket);
                    printf("Ŀǰ�ͻ��˵�����Ϊ: %d\n",allSocket.fd_count - 1);
                    continue;
                }
                else
                {
                    DWORD err = WSAGetLastError();
                    // �ͻ��˵�socketû�б������ر�,��û�е���closesocket
                    if (err == WSAECONNRESET)
                    {
                        printf("�ͻ���[%s:%d]��ǿ�йر�",pszClientIp,usClientPort);
                    }
                    else
                    {
                        printf("recv data error code(%d)...\n",::WSAGetLastError());
                    }

                    closesocket(socket);
                    FD_CLR(socket, &allSocket);

                    //����socket����ͻ��˶�
                    printf("Ŀǰ�ͻ��˵�����Ϊ: %d\n",allSocket.fd_count - 1);

                    continue;

                }

            }//read end
        }


    }



    //�رռ����׽���
    closesocket(ListenSocket); 

    //�����׽��ֿ��ʹ��
    WSACleanup();
    system("pause");
    return 0;
}

