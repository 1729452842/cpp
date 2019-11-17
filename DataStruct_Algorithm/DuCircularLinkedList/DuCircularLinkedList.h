#ifndef __DU_CIRCULAR_LINKEDLIST__
#define __DU_CIRCULAR_LINKEDLIST__

typedef  int NodeType;

/*���������Ϣ*/
typedef struct _DuLNode
{
    NodeType data;
    struct _DuLNode *prev;
    struct _DuLNode *next;
}DuLNode,*PDuLNode;

/*������Ϣ*/
/*�����ͨ�ṹ,���ַ�ʽ���Կ��ٻ�ȡ������,����ı�������*/
typedef struct
{
    int     nLenth; /*������*/
    PDuLNode Head;  /*����ͷ���*/
}DuLNodeInfo;

/*��ʼ��˫��ѭ������*/
int InitDuLinkList(DuLNodeInfo& ListInfo);

/*�ÿյ���������ͷ���*/
int ClearDuLinkList(DuLNodeInfo& ListInfo);

/*��������*/
int DestoryDuLinkList(DuLNodeInfo& ListInfo);

/*���һ�����*/
int AddNode(PDuLNode newnode, PDuLNode pre, PDuLNode next);

/*����ǰ����������ɾ��*/
int DelNode(PDuLNode delNode);

/*��ȡ������*/
int GetDuListLen(DuLNodeInfo& ListInfo);

/*����ָ�����ǰ*/
int InsertBeforeLinkList(DuLNodeInfo& ListInfo, NodeType data);

/*����ָ������*/
int InsertAfterLinkList(DuLNodeInfo& ListInfo, NodeType data);

/*��ȡͷ���*/
PDuLNode GetTailNode(const DuLNodeInfo& ListInfo);

/*��ȡβ���*/
PDuLNode GetHeadNode(const DuLNodeInfo& ListInfo);

/*ɾ�����*/
int DelDuLinkListNode(DuLNodeInfo& ListInfo,PDuLNode& delnode);

/*�������*/
int FindDuLinkListNode(DuLNodeInfo& ListInfo, PDuLNode& FindNode,NodeType DataValue);

/*�����ӡ*/
int PrintDuLinkList(DuLNodeInfo& ListInfo, bool bReverse = false);

void TestDuLinkList();



#endif
