
#include "stdafx.h"
#include "CSqlManager.h"
#include <iostream>
#include <tchar.h>

CADOManager::CADOManager()
{

}

CADOManager::~CADOManager()
{

}


CADOManager& CADOManager::GetInstance()
{
    static CADOManager s_ADOManager;

    return s_ADOManager;
}


//********************************************
// ������:	InitADOConn
// ��  ��:	�û��༭
// ����ֵ:  �����������ݿ��Ƿ�ɹ�
// ��  ��: 	
// ��  ע��ÿ���������ݿⶼ��Ҫ���²���
// ��  ��:  2018/12/20
//********************************************
BOOL CADOManager::InitADOConn(const STRU_CONN_SQL_INFO& stSqlInfo, unsigned int timeout)
{
    BOOL bRet = FALSE;

    m_strErrDesc.clear();

    try
   {
       //����һ      
       CoInitialize(NULL); //��ʼ���ز����� 
      
       std::wstring strConn;
       strConn = _T("Provider=SQLOLEDB;");

       strConn += _T("Password=");
       strConn += stSqlInfo.strPassword;

       strConn += _T(";User ID=");
       strConn += stSqlInfo.strUserName;

       strConn += _T(";Data Source=");
       strConn += stSqlInfo.strHost;
       strConn += _T(",");
       strConn += stSqlInfo.strPort;
       strConn += _T(";");

       strConn += _T("Initial Catalog=");
       strConn += stSqlInfo.strDBName;
       strConn += _T(";");

        //�����
       _ConnectionPtr pCon;  //ADO���Ӷ���
       HRESULT hr = pCon.CreateInstance(__uuidof(Connection));
       if(FAILED(hr))
       {
           //std::cout<<"create _ConnectionPtr object failed ������"<< std::endl;
           m_strErrDesc = _T("create ptr object failed...");
           return FALSE;
       }
        
       //������
       if (pCon != NULL)
       {
           pCon->ConnectionString = (_bstr_t)strConn.c_str();
           pCon->ConnectionTimeout = timeout;
           HRESULT hr =  pCon->Open("","","",NULL);

           if(!FAILED(hr))
           {
               bRet = TRUE;
               //��δ�����ӳɹ����ر��������ݿ�����쳣 
               pCon->Close();
           }
       }

   }
   catch(_com_error &ex)
   {
       //��ʾ��¼�쳣���
       std::wstring strError = ex.Description();
       int i = strError.find(_T("SQL Server"));
       if (strError.find(_T("SQL Server")) != std::string::npos)
       {
            m_strErrDesc = _T("SQL Server �����ڻ��߾ܾ�����");
       }
       else
       {
            m_strErrDesc = strError;
       }
   }
   catch (...)
   {

   }
    
   //������
   CoUninitialize();


   return bRet;
}


std::wstring CADOManager::GetErrorDesc()
{
    if (m_strErrDesc.empty())
    {
        m_strErrDesc = _T("���ݿ�����ʧ��");
    }

    return m_strErrDesc;
}
