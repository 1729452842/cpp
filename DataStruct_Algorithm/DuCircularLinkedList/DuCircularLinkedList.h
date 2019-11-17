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
    PDuLNode pHead;  /*����ͷ���*/
}DuLNodeInfo;

/*��ʼ��˫��ѭ������*/
int InitDuLinkList(DuLNodeInfo& ListInfo);

/*�ÿյ���������ͷ���*/
int ClearDuLinkList(DuLNodeInfo& ListInfo);

/*��������*/
int DestoryDuLinkList(DuLNodeInfo& ListInfo);

/*���һ�����,��㱾���Ѵ���*/
int ListAddNode(DuLNodeInfo& ListInfo,PDuLNode newnode, PDuLNode pre, PDuLNode next);

/*ɾ��һ����㣬��㱾���Դ���*/
int ListDelNode(DuLNodeInfo& ListInfo,PDuLNode delNode);

/*��ȡ������*/
int GetDuListLen(DuLNodeInfo& ListInfo);

/*��ͷ������룬�����ɵĽ��*/
int InsertBeforeLinkList(DuLNodeInfo& ListInfo, NodeType data);

/*׷�ӽ�㣬�����ɵĽ��*/
int InsertAfterLinkList(DuLNodeInfo& ListInfo, NodeType data);

/*��ȡͷ���*/
PDuLNode GetTailNode(const DuLNodeInfo& ListInfo);

/*��ȡβ���*/
PDuLNode GetHeadNode(const DuLNodeInfo& ListInfo);

/*ɾ����㲢�ͷ���Դ*/
int DelDuLinkListNode(DuLNodeInfo& ListInfo,PDuLNode& delnode);

/*�������*/
PDuLNode FindDuLinkListNode(DuLNodeInfo& ListInfo,NodeType DataValue);

/*�����ӡ*/
int UnionDuLinkList(DuLNodeInfo& ListInfo1, DuLNodeInfo& ListInfo2);

/*�����ӡ*/
int PrintDuLinkList(DuLNodeInfo& ListInfo, bool bReverse = false);

void TestDuLinkList();



#endif
