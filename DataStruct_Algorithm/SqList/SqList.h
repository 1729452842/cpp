#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

/************************************************************************
                      ˳����ص��ܽ�                                 
1.˳�����һ��洢��ַ�����Ĵ洢��Ԫ
2.˳���Ĳ��롢ɾ��������ʱ�临�Ӷ�ΪO(n)
3.�����ڲ�����ɾ�������롢���ҵĳ���
4.˳�����������ȡ���ص�
************************************************************************/

typedef int ElemType;
typedef unsigned int UINT32;

/*���Ա�ṹ*/
typedef struct
{
    ElemType  *elem;     /*Ԫ������*/
    UINT32       nLength;  /*���Ա�ǰ��С*/
    UINT32       nCapacity;/*���Ա�ǰ�������*/
    UINT32       nIncrementSize;/*���Ա��������*/
}STRU_SQ_LIST, *PSTRU_SQ_LIST;

#define  INI_MAX_SIZE  (5)
#define  INCREMENT_SIZE (3)

/*��ʼ�����Ա�*/
int InitList_Sq(STRU_SQ_LIST* list);

/*�������Ա�*/
int CreateList_Sq(STRU_SQ_LIST* list, 
               int nMaxSize = INI_MAX_SIZE,
               int nInCrementSize = INCREMENT_SIZE);

/*����Ԫ��*/
int FindElem_Sq(STRU_SQ_LIST* list,ElemType data);

/*����Ԫ��*/
int InsertElem_Sq(STRU_SQ_LIST* list,unsigned nPos, ElemType data);

/*����Ԫ��*/
int Pushback_Sq(STRU_SQ_LIST* list, ElemType data);

/*Ԫ������*/
int Increment(STRU_SQ_LIST* list);

/*Ԫ��ɾ��*/
int DeleteElem_Sq(STRU_SQ_LIST* list,unsigned nPos, ElemType* data);

/*��ȡ����*/
int GetLenth_Sq(STRU_SQ_LIST* list);

/*��ȡĳ��λ�õ�Ԫ��*/
int GetElem(STRU_SQ_LIST* list,unsigned nPos, ElemType* data);

/*�ж��ͷ�Ϊ�ձ�*/
bool IsEmpty_Sq(STRU_SQ_LIST* list);

/*��ӡԪ��*/
int PrintList_Sq(STRU_SQ_LIST* list);

/*�������Ա�*/
int Destory_Sq(STRU_SQ_LIST* list);

/*����Ϊ��չ����*/

/*��ת���Ա�*/
int ReverseList_Sq(STRU_SQ_LIST* list);

/*�Ƚ����Ա��С*/
int CompareList_Sq(STRU_SQ_LIST* list1,STRU_SQ_LIST* list2);

/*��list2�й�����ȡԪ�ز�ͬ�����Ա�*/
int GetUniqueElem_Sq(STRU_SQ_LIST* list1,STRU_SQ_LIST* list2);


/*�������Ա�����*/

int test_sq_list();


#endif
