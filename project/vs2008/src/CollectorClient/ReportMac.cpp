#include "ReportMac.h"
#include <string>

CReportMac::~CReportMac()
{

}

CReportMac::CReportMac()
{

}

unsigned CReportMac::Process()
{
//     //��������̨��������
//     DatagramSocket ListenActionType(6001,"255.255.255.255",false,true);
//     char szCtrlMsg[128] = {};
//     while (1)
//     {
//         memset(szCtrlMsg, 0, sizeof(szCtrlMsg))
//         ListenActionType.receive(szCtrlMsg, sizeof(szCtrlMsg));
//         
//         if (strlen(szCtrlMsg) > 0)
//         {
//             if (szCtrlMsg[1] == 0x11)
//             {
//                 ReportMac(szCtrlMsg + 1);
//             }
//         }
// 
//     }

    return 0;
}


//ָ�������ϱ�
void CReportMac::ReportMac(const char* szConsoleIP)
{
    //��ȡmac��ַ
    char szMacInfo[128] = {};
    CIPUtil::GetLocalMAC(szMacInfo,sizeof(szMacInfo));

    //�����̨������Ϣ
    //
    STRU_DATAGRAM_OPTION  opt;
    opt.broadcast =false;
    opt.reusesock = true;
    opt.multi_cast = false;

    DatagramSocket reportMac(6002,szConsoleIP,opt);
    reportMac.send(szMacInfo,sizeof(szMacInfo));
}