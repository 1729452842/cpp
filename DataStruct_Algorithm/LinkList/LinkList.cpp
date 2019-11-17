
#include "LinkList.h"
#include <memory>
#include "../base.h"

int Init_LinkList(PLinkLNode *LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    *LinkHead = (PLinkLNode)malloc(sizeof(LinkLNode));
    (*LinkHead)->pNext = NULL;

    return DA_SUCCESS;
}

int Clear_LinkList(PLinkLNode LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    //�ӵ�һ����㿪ʼ����
    PLinkLNode CurNode = LinkHead->pNext;
    PLinkLNode NextNode = NULL; 

    while (CurNode)
    {
        //��һ��Ԫ��
        NextNode = CurNode->pNext;
        
        free(CurNode);

        CurNode = NextNode;
    }

    LinkHead->pNext = NULL;

    return DA_SUCCESS;
}

int Destory_LinkList(PLinkLNode* pLinkHead)
{
    CHECK_PTR_RETURN_ERROR(pLinkHead);
    
    Clear_LinkList(*pLinkHead);

    //�ͷ�ͷ���
    free(*pLinkHead);
    *pLinkHead = NULL;
    
    return DA_SUCCESS;
}

bool IsEmpty_LinkList(PLinkLNode LinkHead)
{
    CHECK_PTR_RETURN_FALSE(LinkHead);
    
    return LinkHead->pNext == NULL ? true : false; 
}

int Length_LinkList(PLinkLNode LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);
    //����Ԫ�ؿ�ʼ����
    PLinkLNode curNode = LinkHead->pNext;
    int len = 0;

    while (curNode)
    {
        curNode = curNode->pNext;
        len++;
    }

    return len;
}

int GetElem_LinkList(PLinkLNode LinkHead, int pos, DataType *data)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    if (pos >= Length_LinkList(LinkHead))
    {
        return DA_ERROR;
    }

    PLinkLNode curNode = LinkHead->pNext;
    int cur_len = 0;

    while (curNode)
    {
        if (cur_len == pos)
        {
            *data = curNode->data;
            break;
        }

        curNode = curNode->pNext;
        cur_len++;
    }

    return cur_len == pos ? DA_SUCCESS : DA_ERROR;
}

int InsertNode_LinkList(PLinkLNode LinkHead, int pos, DataType data)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);
    if (pos >= Length_LinkList(LinkHead))
    {
        return DA_ERROR;
    }

    //��һ�����
    PLinkLNode curNode = LinkHead->pNext;
    PLinkLNode PriorNode = NULL;

    int nCurPos = 0;

    while (curNode)
    {
        if (nCurPos == pos)
        {
            GetPriorNode(LinkHead,curNode,&PriorNode);
            break;
        }
        curNode = curNode->pNext;
        nCurPos++;
    }

    if (NULL != PriorNode)
    {
        //�½��
        PLinkLNode NewNode = (PLinkLNode)malloc(sizeof(LinkLNode));
        CHECK_PTR_RETURN_ERROR(NewNode);
        NewNode->data = data;

        //curNode->pNext��Ϊ�½��ĺ�� 
        NewNode->pNext = curNode;
        //PriorNode�ĺ��Ϊ�½��NewNode
        PriorNode->pNext = NewNode;
    }
    else
    {
        printf("prior node is null\n");
    }



    return DA_SUCCESS;
}

int GetPriorNode(PLinkLNode LinkHead, PLinkLNode PosNode,PLinkLNode* PriorNode)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);
    CHECK_PTR_RETURN_ERROR(PosNode);
    CHECK_PTR_RETURN_ERROR(PriorNode);

    //��ͷ��㿪ʼ
    PLinkLNode curNode = LinkHead;
    while (curNode)
    {
        //�Ƚ��Ƿ���ǰ�����
        if (curNode->pNext == PosNode)
        {
            *PriorNode = curNode;
            break;
        }
        curNode = curNode->pNext;
    }

    return DA_SUCCESS;
}
int DeleteNode_LinkList(PLinkLNode LinkHead, int pos, DataType *pData)
{   
    CHECK_PTR_RETURN_ERROR(LinkHead);
    CHECK_PTR_RETURN_ERROR(pData);

    if (pos >= Length_LinkList(LinkHead))
    {
        return DA_ERROR;
    }

    //��һ�����
    PLinkLNode curNode = LinkHead->pNext;
    PLinkLNode PriorNode = NULL;
    int nCurPos = 0;

    while (curNode)
    {
        if (nCurPos == pos)
        {
            GetPriorNode(LinkHead,curNode,&PriorNode);
            break;
        }
        curNode = curNode->pNext;
        nCurPos++;
    }

    //�ı���
    PriorNode->pNext = curNode->pNext;

    //���ر�ɾ����ֵ
    *pData = curNode->data;
    free(curNode);
    curNode = NULL;

    return DA_SUCCESS;
}

int InsertNodeByTail(PLinkLNode LinkHead, DataType data)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);
    printf("insert data %d\n",data);

    //ͷ���
    PLinkLNode curNode = LinkHead;

    //�ж��Ƿ񵽴�β���
    while (curNode->pNext)
    {
        curNode = curNode->pNext;
    }

    //�½��
    PLinkLNode NewNode = (PLinkLNode)malloc(sizeof(LinkLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;
    NewNode->pNext = NULL;
    
    //�ı��̽��
    curNode->pNext = NewNode;


    return DA_SUCCESS;
}

int InsertNodeByHead(PLinkLNode LinkHead, DataType data)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);
    printf("insert data %d\n",data);

    //�½��
    PLinkLNode NewNode = (PLinkLNode)malloc(sizeof(LinkLNode));
    CHECK_PTR_RETURN_ERROR(NewNode);
    NewNode->data = data;
    NewNode->pNext = LinkHead->pNext;

    LinkHead->pNext = NewNode;
    
    return DA_SUCCESS;
}

int PrintLinkList(PLinkLNode LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    //��һ�����
    PLinkLNode curNode = LinkHead->pNext;
    while (curNode)
    {
        printf("%d->",curNode->data);
        curNode = curNode->pNext;
    }
    printf("NULL\n");

    return DA_SUCCESS;
}

/*��ת����*/
int ReverseLinkList(PLinkLNode *LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    //ָ���һ�����
    PLinkLNode IndcateNode = (*LinkHead)->pNext;

    //�������õı���Ϊ�ձ�
    PLinkLNode L = *LinkHead;
    L->pNext = NULL;

    PLinkLNode InsertNode = NULL;

    while(IndcateNode)
    {
        //���汻"ɾ��"�Ľ����Ϣ
        InsertNode = IndcateNode;
        //ָ����һ�����
        IndcateNode = IndcateNode->pNext;

        //ͷ�����½��
        InsertNode->pNext = L->pNext;//�ı䱻"ɾ��"�ĺ��
        L->pNext = InsertNode;//�ı�ͷ���ĺ��
    }

    *LinkHead = L;

    return DA_SUCCESS;
}

/*��ת����*/
int ReverseLinkList2(PLinkLNode *LinkHead)
{
    CHECK_PTR_RETURN_ERROR(LinkHead);

    //ָ���һ�����
    PLinkLNode p = (*LinkHead)->pNext;
    if (p == NULL)
    {
        return DA_SUCCESS;
    }

    //p�ĺ�̽��
    PLinkLNode q = p->pNext;

    //��һ������ָ����
    p->pNext = NULL;

    //��ʱ���
    PLinkLNode pre = NULL;

    while(q)
    {
        //������
        pre = p;

        //�ƶ����
        p = q;
        q = q->pNext;

        //�ı�����ָ��
        p->pNext = pre;
    }

    (*LinkHead)->pNext = p;

    return DA_SUCCESS;
}


void Test_LinkList()
{
    PLinkLNode Head = NULL;
    
    Init_LinkList(&Head);

    if (IsEmpty_LinkList(Head))
    {
        printf("link list is empty\n");
    }

    InsertNodeByHead(Head,1);
    InsertNodeByHead(Head,2);
    InsertNodeByHead(Head,3);
    InsertNodeByHead(Head,4);

    PrintLinkList(Head);

    Clear_LinkList(Head);
    printf("clear list\n");
    InsertNodeByTail(Head,10);
    InsertNodeByTail(Head,20);

    PrintLinkList(Head);

    DataType DataValue = 0;
    
    if (DA_SUCCESS != DeleteNode_LinkList(Head, 1,&DataValue))
    {
        printf("delete node error ...\n");
    } 
    else
    {
        printf("delete data %d\n",DataValue);
        PrintLinkList(Head);
    }

    InsertNode_LinkList(Head,0,110);
    InsertNode_LinkList(Head,1,1100);

    PrintLinkList(Head);
    
    ReverseLinkList(&Head);

    PrintLinkList(Head);

    ReverseLinkList2(&Head);

    PrintLinkList(Head);

    Destory_LinkList(&Head);
}
