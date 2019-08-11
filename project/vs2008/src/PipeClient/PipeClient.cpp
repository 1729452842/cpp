// PipeClient.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include <fstream>


int _tmain(int argc, _TCHAR* argv[])
{
    //�õ������̵Ķ�д��������ܵ��Ķ��˺�д��
    HANDLE hRead = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hWrite = GetStdHandle(STD_OUTPUT_HANDLE);
    std::ofstream of("child_pipe_data.txt",std::ios::trunc | std::ios::out);

     char  szReadBuf[128] = {};
     char  szRespondData[128] = {};
     DWORD dwRead = 0;
     DWORD dwWrite = 0;

     for (;;)
     {
         memset(szReadBuf,0,sizeof(szReadBuf));

         //�ӹܵ��л�ȡ����
         if (!ReadFile(hRead,szReadBuf, sizeof(szReadBuf),&dwRead,NULL))
         {
             printf("client: read data from pip error ...\n");
             break;
         }

         if (strcmp("quit",szReadBuf) == 0)
         {
             break;
         }
         else
         {
             //printf("client: read data from pipe : %s\n",szReadBuf);
             of << "client: read data from pipe : " << szReadBuf << "\n";
             of.flush();
         }
         //��ܵ���д�����ݣ�֪ͨ�����̶�ȡ
         sprintf_s(szRespondData,sizeof(szRespondData),"I receive data \'%s\'",szReadBuf);
         if (!WriteFile(hWrite,szRespondData, strlen(szRespondData),&dwWrite,NULL))
         {
             of << "client: write data error...\n" << "\n";
         }
         else
         {
            of << "client: write data to pipe : " << szRespondData << "\n";
            of.flush();
         }
     }

     of.close();

    return 0;
}

