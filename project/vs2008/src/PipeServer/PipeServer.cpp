#include "stdafx.h"
#include "stdio.h"
#include "utilityAPI.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SECURITY_ATTRIBUTES sa;
    sa.bInheritHandle = TRUE; //���þ�����Լ̳�
    sa.lpSecurityDescriptor = NULL;
    sa.nLength = sizeof(sa);

    HANDLE hIN_Read = NULL;
    HANDLE hIN_Write = NULL;

    HANDLE hOUT_Read = NULL;
    HANDLE hOUT_Write = NULL;

    //��ȡ�����ܵ���д���
    if (!CreatePipe(&hIN_Read, &hIN_Write, &sa,0))
    {
        printf("create pipe error...\n");
        return 1;
    }
    
    if (!CreatePipe(&hOUT_Read, &hOUT_Write, &sa,0))
    {
        printf("create pipe error...\n");
        return 1;
    }
    
    //���β���Ҫ�̳еľ��
    SetHandleInformation(hIN_Write, HANDLE_FLAG_INHERIT, 0);
    SetHandleInformation(hOUT_Read, HANDLE_FLAG_INHERIT, 0);

    char szSendMsg[128] = {0};
    char szReadMsg[128] = {0};
    DWORD dwWrite = 0;
    DWORD dwRead = 0;

    //����������Ϣ�����ܵ�A������͹ܵ�B��д������ݸ��ӽ���
    STARTUPINFOA startInfo;
    memset(&startInfo,0,sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);
    startInfo.dwFlags = STARTF_USESTDHANDLES;
    startInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    startInfo.hStdInput = hIN_Read;
    startInfo.hStdOutput= hOUT_Write;

    //�����ӽ����Լ����ü̳�����
    CWorkProcess cmdChild("PipeClient.exe",NULL);
    cmdChild.SetStartupInfo(startInfo);
    cmdChild.SetInheritanceOpt(); /*���ü̳�����*/
    cmdChild.LaunchProcess(); /*��������*/

    //˫��ͨ���û���������ʾ
    printf("pls input msg...:\n");
    while (1)
    {
        //�ӿ���̨��ȡ�û�����
        memset(szSendMsg,0, sizeof(szSendMsg));
        gets_s(szSendMsg, sizeof(szSendMsg));

        //��Ļ��ʾ
        printf("server: write data to pipe : %s\n",szSendMsg);

        //��ܵ���д�����ݣ�
        if (!WriteFile(hIN_Write,szSendMsg, strlen(szSendMsg),&dwWrite,NULL))
        {
            printf("server: write file error...");
        }

        if (strcmp(szSendMsg,"quit") == 0)
        {
            break;
        }

        memset(szReadMsg,0, sizeof(szReadMsg));

        //�ӹܵ��ж�ȡ����
        if (!ReadFile(hOUT_Read,szReadMsg,sizeof(szReadMsg),&dwRead,NULL))
        {
            printf("server: read file error...");
        }
        else
        {
            printf("server: read data from client (%s)\n",szReadMsg);
        }
    }

    cmdChild.WaitForEnded(INFINITE);

    //���ڲ��������ȷ����Դ��ȷ���ͷ�
    CloseHandle(hIN_Read);
    CloseHandle(hIN_Write);
    CloseHandle(hOUT_Read);
    CloseHandle(hOUT_Write);

    return 0;
}

