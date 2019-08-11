#include "MonitorUserCfg.h"
#include <fstream>
#include "ReportMac.h"

CMonitorUserCfg::CMonitorUserCfg()
{

}

CMonitorUserCfg::~CMonitorUserCfg()
{

}

unsigned CMonitorUserCfg::Process()
{
    //�������ڽ��նಥ��Ϣ
    STRU_DATAGRAM_OPTION  opt;
    opt.broadcast =false;
    opt.reusesock = true;
    opt.multi_cast = true;

    DatagramSocket ListenConfig(6000,"239.1.10.1", opt);

    char szRecvMsg[128] = {};

    while (1)
    {
        memset(szRecvMsg, 0, sizeof(szRecvMsg));
        ListenConfig.receive(szRecvMsg,sizeof(szRecvMsg));

        if (strlen(szRecvMsg) >= 0)
        {
            if (szRecvMsg[0] == 0x10)
            {
                //���ü�����ַ
                SaveListenAddr(szRecvMsg + 1);
            }
            //�ϱ�Mac
            else if (szRecvMsg[0] == 0x11)
            {
                printf("i will report mac info...\n");
                CReportMac reportMac;
                reportMac.ReportMac(szRecvMsg + 1);
            }

        }
    }
}

void CMonitorUserCfg::SaveListenAddr(const char* szMsg)
{
    char szAppDir[128] = {};
    CAppPathUtil::GetAppDir(szAppDir, sizeof(szAppDir));
    
    std::string strFilePath(szAppDir);
    strFilePath.append("mail_addr");

    std::ofstream writer;
    writer.open(strFilePath.c_str(),std::ios::out | std::ios::trunc);
    writer << szMsg;
    writer.close();
}