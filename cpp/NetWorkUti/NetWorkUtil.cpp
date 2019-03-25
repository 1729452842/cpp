/***************************************************************
 * Copyright(C) 2018,Company All Rights Reserved
 * 
 * @file    : NetWorkUtil.cpp
 * 
 * @brief   : 
 * 
 * @version : 1.0
 * 
 * @author  : Jimmy
 * 
 * @date    : 2018/12/22 ������
 * 
 * Details  :
 ***************************************************************/


#include <winsock2.h>
#include <iphlpapi.h>

#include <stdio.h>
#include <stdlib.h>
#include "NetWorkUtil.h"
#include <tchar.h>
#pragma comment(lib, "IPHLPAPI.lib")   
#pragma comment(lib, "ws2_32.lib") 

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))


CNetWorkUtil::CNetWorkUtil()
{

}

CNetWorkUtil::~CNetWorkUtil()
{

}



/**************************************************************
*  @brief : CNetWorkUtil::GetLocalIPList
*     
*  @param : 
*     
*    -std::vector<std::string>& vecIP
*     
*    -int a
*     
*    -int c
*     
*  @return : bool
*     
*  @author : Jimmy
*     
*  @date : 2018/12/30 ������
*     
*  @note : 
***************************************************************/
bool CNetWorkUtil::GetLocalIPList(std::vector<std::string>& vecIP)
{
    WSADATA wsaData;
    char szIP[50] = {};
    char hostname[256] = {};
    vecIP.clear();


    int error = WSAStartup(0x0101, &wsaData);
    if (error != 0)
    {
        return false;
    }

    int ret = gethostname(hostname, sizeof(hostname));
    if (ret == SOCKET_ERROR)
    {
        WSACleanup();
        return false;
    }

    //3.��ȡ����ip
    HOSTENT* host = gethostbyname(hostname);
    if (host == NULL || host->h_addr_list[0] == NULL)
    {
        WSACleanup();
        return false;
    }

    /*       */
    in_addr addr;
    int i = 0;
    //4.ת��Ϊchar*����������
    while (host->h_addr_list[i] != NULL)
    {
        addr.s_addr = *(u_long*)host->h_addr_list[i];
        if ((int)strlen(inet_ntoa(addr)) > sizeof(szIP))
        {
            WSACleanup();
            return false;
        }
        strcpy_s(szIP, 50, inet_ntoa(addr));
        vecIP.push_back(std::string(szIP));
        i++;
    }

    WSACleanup();

    return TRUE;

}

//�������߽ṹ���Աע��
/* */

/**************************************************************
*  @brief : CNetWorkUtil::GetLocalMACList
*     
*  @param : 
*     
*    -std::vector<std::string>& vecMac
*     
*  @return : bool
*     
*  @author : Jimmy
*     
*  @date : 2018/12/22 ������
*     
*  @note : ͨ��GetAdaptersAddresses������������Windows XP�����ϰ汾��
***************************************************************/
bool CNetWorkUtil::GetLocalMACList(std::vector<std::string>& vecMac)
{
    bool ret = false;
    vecMac.clear();
    ULONG outBufLen = sizeof(IP_ADAPTER_ADDRESSES);
    PIP_ADAPTER_ADDRESSES pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
    if (pAddresses == NULL)
    {
        return false;
    }

    // Make an initial call to GetAdaptersAddresses to get the necessary size into the ulOutBufLen variable
    if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        free(pAddresses);
        pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
        if (pAddresses == NULL)
        {
            return false;
        }
    }

    if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == NO_ERROR)
    {
        // If successful, output some information from the data we received
        for (PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; pCurrAddresses != NULL; pCurrAddresses = pCurrAddresses->Next)
        {
            // ȷ��MAC��ַ�ĳ���Ϊ 00-00-00-00-00-00
            if (pCurrAddresses->PhysicalAddressLength != 6)
            {
                continue;
            }

            char acMAC[128] = { 0 };

            sprintf(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
                int(pCurrAddresses->PhysicalAddress[0]),
                int(pCurrAddresses->PhysicalAddress[1]),
                int(pCurrAddresses->PhysicalAddress[2]),
                int(pCurrAddresses->PhysicalAddress[3]),
                int(pCurrAddresses->PhysicalAddress[4]),
                int(pCurrAddresses->PhysicalAddress[5]));

            vecMac.push_back(std::string(acMAC));
            ret = true;
        }
    }

    free(pAddresses);
    return ret;
}

//********************************************
// ������:	
// ��  ��:	����Ƿ�Ϸ�����������
// ����ֵ:  
// ��  ��: 	
// ��  ע��
//********************************************
bool CNetWorkUtil::isValidSubmask(const std::string& strSubmask)
{
    //��֤�Ƿ�Ϸ�IP
    if (!isValidIP(strSubmask))
    {
        return false;
    }

    //ת��unsing long ���� ����ת�����ģʽ�ŷ����㷨Ҫ��
    unsigned long  ulSubmask =  htonl(inet_addr(strSubmask.c_str()));

    //ȡ�� & (ȡ��+1)
    //�Ϸ���11111111 11111111 11111100 00000000 11..1����
    //�Ƿ���111111111111111111111111111001111

    return ((~ulSubmask + 1) & ~ulSubmask) == 0;
}


bool CNetWorkUtil::isValidIP(const std::string& strIP)
{
    std::string::size_type     nBeginIndex = 0;
    std::string::size_type     nTargetIndex = 0;
    std::string                strSubstr = strIP;
    std::string                strElement;
    std::vector<std::string>   vecIPElement; 

    //192.168.245 
    do 
    {
        nTargetIndex =  strSubstr.find_first_of(_T('.'));
        if (nTargetIndex != std::string::npos)
        {
            strElement = strSubstr.substr(0, nTargetIndex);
            strSubstr  = strSubstr.substr(++nTargetIndex);
        }
        else
        {
            strElement = strSubstr;
        }

        if (!IsValidElementIP(strElement))
        {
            return false;
        }

        //��ֹ�쳣��������ѭ��
        if (vecIPElement.size() > 4)
        {
            return false;
        }


        vecIPElement.push_back(strElement);

    } while (nTargetIndex != std::string::npos);


    if (vecIPElement.size() != 4)
    {
        return false;
    }

    return true;
}

bool CNetWorkUtil::isValidPort(const std::string& strPort)
{
    if (strPort.empty())
    {
        return false;
    }

    size_t nLen = strPort.length();
    for (size_t i = 0; i < nLen; i++)
    {
        if (!(strPort[i] >= _T('0') && strPort[i] <= _T('9')))
        {
            return false;
        }
    }

    return true;
}


bool CNetWorkUtil::IsValidElementIP(const std::string& strElement)
{
    if (strElement.empty())
    {
        return false;
    }

    size_t nsize = strElement.length();
    for (size_t i = 0; i < nsize; i++)
    {
        if (!(strElement[i] >= _T('0') && strElement[i] <= _T('9')))
        {
            return false;
        }
    }

    if (atoi(strElement.c_str()) > 255)
    {
        return false;
    }

    return true;
}

bool CNetWorkUtil::GetLocalIP(std::string& strIP)
{
    WSADATA wsaData;
    char szIP[50] = {};
    bool bRet = FALSE;


    int error = WSAStartup(0x0101, &wsaData);
    if (error != 0)
    {
        return false;
    }

    char hostname[256] = {};
    int ret = gethostname(hostname,sizeof(hostname));
    if (ret == SOCKET_ERROR)
    {
        WSACleanup();
        return false;
    }


    //3.��ȡ����ip
    HOSTENT* host = NULL;
    struct in_addr addr;
    int i = 0;

    //gethostbyname���ܷ���null���������ԣ�ֱ�������ɹ�
    do
    {
        int nTryCount = 0;
        host = gethostbyname(hostname);
        if (host == NULL || nTryCount > 3)
        {
            Sleep(1000);
            nTryCount++;
        }
        else
        {
            break;
        }

    } while (1);

    if (NULL != host)
    {
        if (host->h_addrtype == AF_INET)
        {
            while (host->h_addr_list[i] != 0)
            {
                //char*ת��Ϊulong* ת��Ϊ long
                addr.s_addr = *(u_long *) host->h_addr_list[i++];
                strcpy_s(szIP,sizeof(szIP),inet_ntoa(addr));
                strIP.assign(szIP);
                bRet = true;
                break;
            }
        }
    }

    WSACleanup();
    return bRet;
}


/**************************************************************
*  @brief : GetDnsServerIP
*     
*  @param : 
*     
*    -std::string& strPreferredDNS ��ѡ
*     
*    -std::string& strOptionalDNS  ��ѡ
*     
*  @return : BOOL
*     
*  @author : jin
*     
*  @date : 2019/3/25
*     
*  @note : ��ȡ��ѡDNS�Լ���ѡDNS��Ϣ
***************************************************************/
bool CNetWorkUtil::GetDnsServerIP(std::string& strPreferredDNS, std::string& strOptionalDNS)
{
    FIXED_INFO *pFixedInfo = NULL;
    ULONG ulOutBufLen;
    DWORD dwRetVal;
    IP_ADDR_STRING *pIPAddr;

    pFixedInfo = (FIXED_INFO *) MALLOC(sizeof (FIXED_INFO));
    if (pFixedInfo == NULL) 
    {
        printf("Error allocating memory needed to call GetNetworkParams\n");
        return false;
    }

    ulOutBufLen = sizeof (FIXED_INFO);

    // Make an initial call to GetAdaptersInfo to get
    // the necessary size into the ulOutBufLen variable
    if (GetNetworkParams(pFixedInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
    {
        FREE(pFixedInfo);
        pFixedInfo = (FIXED_INFO *) MALLOC(ulOutBufLen);
        if (pFixedInfo == NULL) 
        {
            printf("Error allocating memory needed to call GetNetworkParams\n");
            return false;
        }
    }

    if (dwRetVal = GetNetworkParams(pFixedInfo, &ulOutBufLen) == NO_ERROR) 
    {

        printf("Host Name: %s\n", pFixedInfo->HostName);
        printf("Domain Name: %s\n", pFixedInfo->DomainName);
        printf("DNS Servers:\n\t first ip %s\n", pFixedInfo->DnsServerList.IpAddress.String);

        strPreferredDNS = std::string(pFixedInfo->DnsServerList.IpAddress.String);

        pIPAddr = pFixedInfo->DnsServerList.Next;
        while (pIPAddr) 
        {
            printf("\t second ip%s\n", pIPAddr->IpAddress.String);
            strOptionalDNS = std::string(pIPAddr->IpAddress.String);
            pIPAddr = pIPAddr->Next;
        }
    } 
    else 
    {
        printf("GetNetworkParams failed with error: %d\n", dwRetVal);
        return false;
    }

    if (pFixedInfo)
    {
        FREE(pFixedInfo);
    } 

    return true;

}


