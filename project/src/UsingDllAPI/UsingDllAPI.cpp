// TestDllAPI.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "../DLLCoding/DllAPI.h"
#pragma comment(lib,"../../lib/DLLCoding.lib")

int _tmain(int argc, _TCHAR* argv[])
{
    //case1 vs2008 ��crt��һ����MT����ģ���ͷźͷ�������
    //����vs 2013������������⣬�п���vs����˸�����
    const int MAX_MALLOC_NUM = 5;
    unsigned int usSize = sizeof(int)* MAX_MALLOC_NUM;
    int* pnArray = NULL;

    bool bCrossModule = false;
    bool bUsingSTLCrossModule = true;

    if (!XDll_Malloc_Memory(usSize, (void**)&pnArray))
    {
        printf("malloc memory error...\n");
        return 0;
    }

    for (int i = 0; i < MAX_MALLOC_NUM; i++)
    {
        pnArray[i] = i + 1;
        printf("array[%d] = %d\n", i, pnArray[i]);
    }

    if (!bCrossModule)
    {
        if (!XDll_Free_Memory((void**)&pnArray))
        {
            printf("free memory error...\n");
        }
    }
    else
    {
        if (NULL != pnArray)
        {
            free(pnArray);
            pnArray = NULL;
        }
    }

    //case2  vs2008��2013������� ����crt��MT/MD
    if (bUsingSTLCrossModule)
    {
        //����ڴ����·���
        std::string strInfo;
        XDll_Assign_String(strInfo);
    }
    return 0;
}

