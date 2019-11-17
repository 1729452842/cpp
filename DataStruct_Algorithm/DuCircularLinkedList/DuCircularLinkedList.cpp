
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
    return ListInfo.pHead->prev;
}

/*��ȡ��һ�����*/
PDuLNode GetHeadNode(const DuLNodeInfo& ListInfo)
{
    return ListInfo.pHead->next;
}

/*�ÿյ���������ͷ���*/
int ClearDuLinkList(DuLNodeInfo& ListInfo)
{
    PDuLNode CurNode = GetHeadNode(ListInfo);
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

/*��������*/
int DestoryDuLinkList(DuLNodeInfo& ListInfo)
{
    ClearDuLinkList(ListInfo);

    free(ListInfo.pHead);
    ListInfo.pHead = NULL;

    return DA_SUCCESS;
}

int GetDuListLen(DuLNodeInfo& Head)
{
    return Head.nLenth;
}

/*���һ�����*/
int AddNode(PDuLNode newnode, PDuLNode pre, PDuLNode next)
{
    printf("add node =%d\n",newnode->data);

    newnode->next = next;
    pre->next = newnode;

    newnode->prev = pre;
    next->prev = newnode;

    return DA_SUCCESS;
}

/*����ǰ����������ɾ��*/
int DelNode(PDuLNode delNode)
{
    printf("delete node =%d\n",delNode->data);

    PDuLNode pre = delNode->prev;
    PDuLNode next = delNode->next;

    pre->next = next;
    next->prev = pre;

    return DA_SUCCESS;
}

/*׷�ӽ��*/
int InsertAfterLinkList(DuLNodeInfo& ListInfo, NodeType data)
{
    PDuLNode NewNode = (PDuLNode)malloc(sizeof(DuLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;
    ListInfo.nLenth++;

    return AddNode(NewNode,ListInfo.pHead->prev, ListInfo.pHead);
}

/*��ͷ�������*/
int InsertBeforeLinkList(DuLNodeInfo& ListInfo, NodeType data)
{
    PDuLNode NewNode = (PDuLNode)malloc(sizeof(DuLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;
    ListInfo.nLenth++;
    return AddNode(NewNode, ListInfo.pHead, ListInfo.pHead->next);
}


/*ɾ����㲢�ͷ���Դ*/
int DelDuLinkListNode(DuLNodeInfo& ListInfo,PDuLNode& delnode)
{
    DelNode(delnode);
    free(delnode);
    delnode = NULL;

    ListInfo.nLenth--;
    return DA_SUCCESS;
}

/*�������*/
int FindDuLinkListNode(DuLNodeInfo& ListInfo, PDuLNode& FindNode,NodeType DataValue)
{
    PDuLNode curNode = GetHeadNode(ListInfo);
    int bRet = DA_ERROR;

    while (curNode != ListInfo.pHead && curNode != NULL)
    {
        if (curNode->data == DataValue)
        {
            FindNode = curNode;
            bRet = DA_SUCCESS;
            break;
        }
        curNode = curNode->next;
    }

    return bRet;
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
    while(CurNode != ListInfo.pHead)
    {
        printf("%d->",CurNode->data);
        CurNode = (bReverse ? CurNode->prev : CurNode->next);
    }

    printf("NULL,len = %d\n",GetDuListLen(ListInfo));
    return DA_SUCCESS;
}


void TestDuLinkList()
{
    DuLNodeInfo head;
    InitDuLinkList(head);
    PrintDuLinkList(head);
    InsertBeforeLinkList(head,4);
    InsertAfterLinkList(head,1);
    InsertAfterLinkList(head,2);
    InsertBeforeLinkList(head,3);

    PrintDuLinkList(head);

    PDuLNode FindNode = NULL;
    if (FindDuLinkListNode(head,FindNode,1) == DA_SUCCESS)
    {
        DelDuLinkListNode(head,FindNode);
    }
    PrintDuLinkList(head, true);

    ClearDuLinkList(head);

    PrintDuLinkList(head);

    InsertBeforeLinkList(head,1);
    InsertBeforeLinkList(head,2);
    InsertBeforeLinkList(head,3);

    PrintDuLinkList(head);

    DestoryDuLinkList(head);
}