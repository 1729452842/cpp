#include "stdafx.h"
#include "WRConfigFile.h"
#include "json/json.h"


CWRConfigFile::CWRConfigFile(const char * szFileName) :
m_strFile(szFileName)
{

}

CWRConfigFile::~CWRConfigFile()
{

}

CWRConfigFile&CWRConfigFile::GetInstance()
{
    static  CWRConfigFile  wrConfFile("deployment.conf");

    return   wrConfFile;
}

bool CWRConfigFile::ReadFile()
{
    bool bRet = false;

    //ate �򿪺�����Ѱλ������β
    // in Ϊ����
    m_strContent.clear();
    m_FileStream.open(m_strFile, std::ios::in | std::ios::ate | std::ios::binary);
    if (!m_FileStream.is_open())
    {
        printf("open file error...\n");
    }



    std::streamoff  position = m_FileStream.tellg();
    if (position != -1)
    {
        // ���� string Ϊ����С
        std::string strJSON(position, '\0');
        //��λ������ʼλ��
        m_FileStream.seekg(0);
        //��ȡָ����С��strJSON
        if (m_FileStream.read(&strJSON[0], position))
        {
            m_strContent = strJSON;
            bRet = true;
        }
        else
        {
            printf("read error..\n");
        }
    }
    m_FileStream.close();
    m_FileStream.clear();
    return bRet;
}


bool CWRConfigFile::WriteFile()
{
    // out Ϊд��
    m_FileStream.open(m_strFile, std::ios::out);
    m_FileStream << m_strContent;
    m_FileStream.close();
    m_FileStream.clear();

    return true;
}


void CWRConfigFile::UpdateFile(const char* szRoot, const char* szKey, const char* szValue)
{

    ReadFile();

    Json::Reader reader;
    Json::StyledWriter writer;
    Json::Value  root;

    if (reader.parse(m_strContent, root))
    {
        root[szRoot][szKey] = szValue;
    }

    m_strContent = writer.write(root);

    WriteFile();
}