#ifndef  __LINK_LIST_H__
#define  __LINK_LIST_H__

typedef int DataType;

/*����������Ա�ṹ*/
typedef struct LNode 
{
    DataType  data;     /*Ԫ������*/
    struct LNode* pNext;
}LinkLNode, *PLinkLNode;

/*��ͷ���ĵ������б�*/

/*��ʼ��������*/
int Init_LinkList(PLinkLNode *pLinkHead);

/*�ÿյ���������ͷ���*/
int Clear_LinkList(PLinkLNode LinkHead);

/*���ٵ�������ͬͷ���Ҳ����*/
int Destory_LinkList(PLinkLNode* pLinkHead);

/*�ж������Ƿ�Ϊ��*/
bool IsEmpty_LinkList(PLinkLNode LinkHead);

/*��������Ԫ�صĸ���*/
int Length_LinkList(PLinkLNode LinkHead);

/*���ص�i������Ԫ��*/
int GetElem_LinkList(PLinkLNode LinkHead, int i, DataType *e);

/*����Ԫ��*/
//int FindElem_LinkList(PLinkLNode LinkHead, DataType data, PLinkLNode node);

/*�ڵ�����L��i��λ��֮ǰ����e*/
int InsertNode_LinkList(PLinkLNode LinkHead, int i, DataType data);

/*ɾ��������L��i��λ�õ�ֵ������e����*/
int DeleteNode_LinkList(PLinkLNode LinkHead, int pos, DataType *pData);

/*ͷ�巨����������L(��������)*/
int InsertNodeByHead(PLinkLNode LinkHead, DataType data);

/*β�巨����������L(˳������)*/
int InsertNodeByTail(PLinkLNode LinkHead, DataType data);

/*��ȡǰ��Ԫ��*/
int GetPriorNode(PLinkLNode LinkHead, PLinkLNode PosNode,PLinkLNode* PriorNode);

/*��ӡԪ��*/
int PrintLinkList(PLinkLNode LinkHead);

/*��ת����*/
int ReverseLinkList(PLinkLNode* LinkHead);


void Test_LinkList();

#endif
