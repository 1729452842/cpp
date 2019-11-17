
#include "DuCircularLinkedList.h"
#include "../base.h"

/* 
˫��ѭ������
ListInfo
 ____      head       node       node         head
|len |     ___        ___        ___          ___ 
|----|<---|   | <--- |   | <--- |   |  <---  |   |
|Head|--->|   | ---> |   | ---> |   |   ---> |   | 
|____|    |___|      |___|      |___|        |___|
                    
*/                         
int InitDuLinkList(DuLNodeInfo& ListInfo)
{
    ListInfo.pHead = (PDuLNode)malloc(sizeof(DuLNode));
    CHECK_PTR_RETURN_ERROR(ListInfo.pHead);

    ListInfo.pHead->data = -1;
    /*��ѭ������*/
    ListInfo.pHead->prev = ListInfo.pHead;
    ListInfo.pHead->next = ListInfo.pHead;
    /*����Ϊ0*/
    ListInfo.nLenth = 0;

    return DA_SUCCESS;
}

/*��ȡβ�����*/
PDuLNode GetTailNode(const DuLNodeInfo& ListInfo)
{
    return ListInfo.pHead != NULL ? ListInfo.pHead->prev : NULL;
}

/*��ȡ��һ�����*/
PDuLNode GetHeadNode(const DuLNodeInfo& ListInfo)
{
    return ListInfo.pHead != NULL ? ListInfo.pHead->next : NULL;
}

/*�ÿյ���������ͷ���*/
int ClearDuLinkList(DuLNodeInfo& ListInfo)
{
    PDuLNode CurNode = GetHeadNode(ListInfo);
    if (CurNode == NULL)
    {
        return DA_SUCCESS;
    }

    PDuLNode NextNode = NULL;
    while(CurNode != ListInfo.pHead)
    {
        NextNode = CurNode->next;
        free(CurNode);
        CurNode = NextNode;
    }

    /*ָ��ͷ��㱾��*/
    ListInfo.pHead->next = ListInfo.pHead;
    ListInfo.pHead->prev = ListInfo.pHead;
    ListInfo.nLenth = 0;

    return DA_SUCCESS;
}

void SafeFreeHead(DuLNodeInfo& ListInfo)
{
    if (ListInfo.pHead != NULL)
    {
        free(ListInfo.pHead);
        ListInfo.pHead = NULL;
    }

    ListInfo.nLenth = 0;
}
/*��������*/
int DestoryDuLinkList(DuLNodeInfo& ListInfo)
{
    ClearDuLinkList(ListInfo);

    SafeFreeHead(ListInfo);

    return DA_SUCCESS;
}

int GetDuListLen(DuLNodeInfo& Head)
{
    return Head.nLenth;
}

/*���һ�����*/
int _AddNode(PDuLNode newnode, PDuLNode pre, PDuLNode next)
{
    printf("add node =%d\n",newnode->data);

    newnode->next = next;
    pre->next = newnode;

    newnode->prev = pre;
    next->prev = newnode;

    return DA_SUCCESS;
}

int ListAddNode(DuLNodeInfo& ListInfo,PDuLNode newnode, PDuLNode pre, PDuLNode next)
{
   ListInfo.nLenth++;
   return _AddNode(newnode,pre,next);
}

/*����ǰ����������ɾ��*/
int _DelNode(PDuLNode delNode)
{
    printf("delete node =%d\n",delNode->data);

    PDuLNode pre = delNode->prev;
    PDuLNode next = delNode->next;

    pre->next = next;
    next->prev = pre;

    return DA_SUCCESS;
}

int ListDelNode(DuLNodeInfo& ListInfo,PDuLNode delNode)
{
    ListInfo.nLenth--;
    return _DelNode(delNode);
}

/*׷�ӽ��*/
int InsertAfterLinkList(DuLNodeInfo& ListInfo, NodeType data)
{
    PDuLNode NewNode = (PDuLNode)malloc(sizeof(DuLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;

    return ListAddNode(ListInfo,NewNode,ListInfo.pHead->prev, ListInfo.pHead);
}

/*��ͷ�������*/
int InsertBeforeLinkList(DuLNodeInfo& ListInfo, NodeType data)
{
    PDuLNode NewNode = (PDuLNode)malloc(sizeof(DuLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;
    return ListAddNode(ListInfo,NewNode, ListInfo.pHead, ListInfo.pHead->next);
}


/*ɾ����㲢�ͷ���Դ*/
int DelDuLinkListNode(DuLNodeInfo& ListInfo,PDuLNode& delnode)
{
    ListDelNode(ListInfo,delnode);
    free(delnode);
    delnode = NULL;
    return DA_SUCCESS;
}

/*�������*/
PDuLNode FindDuLinkListNode(DuLNodeInfo& ListInfo,NodeType DataValue)
{
    PDuLNode curNode = GetHeadNode(ListInfo);
    PDuLNode FindNode = NULL;

    while (curNode != ListInfo.pHead && curNode != NULL)
    {
        if (curNode->data == DataValue)
        {
            FindNode = curNode;
            break;
        }
        curNode = curNode->next;
    }

    return FindNode;
}
int UnionDuLinkList(DuLNodeInfo& ListInfo1, DuLNodeInfo& ListInfo2)
{

    if (ListInfo1.nLenth == 0)
    {
        DuLNodeInfo ListInfo = ListInfo1;
        ListInfo1 = ListInfo2;
        ListInfo1 = ListInfo;
    }
    else
    {
        PDuLNode curNode = GetHeadNode(ListInfo2);
        PDuLNode FindNode = NULL;
        PDuLNode NextNode = NULL;
        /*����list2��� O(M)*/
        while (curNode != ListInfo2.pHead)
        {
            NextNode = curNode->next;
            //�����ڵ������list1�������list2��ɾ��
            //���ҵ�ʱ�临�Ӷ�ΪO(n)
            if (NULL != FindDuLinkListNode(ListInfo1,curNode->data))
            {
                DelDuLinkListNode(ListInfo2, curNode);
            }
            else
            {
                ListDelNode(ListInfo2,curNode);

                ListAddNode(ListInfo1,curNode,ListInfo1.pHead->prev,ListInfo1.pHead);
            }
            curNode = NextNode;
        }
    }

    return DA_SUCCESS;
}


/*�����ӡ*/
int PrintDuLinkList(DuLNodeInfo& ListInfo, bool bReverse/* = false*/)
{
    PDuLNode CurNode = NULL;

    if (bReverse)
    {
        CurNode = GetTailNode(ListInfo);
        printf("from tail print:");
    } 
    else
    {
        CurNode = GetHeadNode(ListInfo);
        printf("from head print:");
    }

    //��������Ϊ�Ƿ����ͷ���
    while(CurNode != ListInfo.pHead && CurNode != NULL)
    {
        printf("%d->",CurNode->data);
        CurNode = (bReverse ? CurNode->prev : CurNode->next);
    }

    printf("NULL,len = %d\n",GetDuListLen(ListInfo));
    return DA_SUCCESS;
}


void TestDuLinkList()
{
    DuLNodeInfo List1;
    DuLNodeInfo List2;
    InitDuLinkList(List1);
    InitDuLinkList(List2);

    InsertBeforeLinkList(List1,4);
    InsertAfterLinkList(List1,1);
    InsertAfterLinkList(List1,2);
    InsertAfterLinkList(List1,3);

    PrintDuLinkList(List1);

    /*
    PDuLNode FindNode = NULL;
    if (FindDuLinkListNode(List1,FindNode,1) == DA_SUCCESS)
    {
        DelDuLinkListNode(List1,FindNode);
    }
    PrintDuLinkList(List1, true);
    */


    InsertBeforeLinkList(List2,1);
    InsertBeforeLinkList(List2,2);
    InsertBeforeLinkList(List2,32);
    PrintDuLinkList(List2);

    UnionDuLinkList(List1, List2);
    printf("union link list:");
    PrintDuLinkList(List1);

    InsertBeforeLinkList(List2,11);
    InsertBeforeLinkList(List2,2);
    InsertBeforeLinkList(List2,32);
    PrintDuLinkList(List2);


    DestoryDuLinkList(List1);
    DestoryDuLinkList(List2);
}