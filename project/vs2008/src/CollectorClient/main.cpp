// CollectorClient.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MonitorUserCfg.h"

//0x10 ������ʼ����Ϣ
//0x11 ����mac�ϱ���Ϣ

int _tmain(int argc, _TCHAR* argv[])
{
	//�����㲥��Ϣ
    //����mac��ַ����


    while (1)
    {
        CMonitorUserCfg Monitor;
        Monitor.Create();
        Monitor.Wait(INFINITE);
    }
    return 0;
}

