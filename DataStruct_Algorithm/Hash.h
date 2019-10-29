#include "base.h"

#ifndef  __HASH_H__
#define  __HASH_H__

typedef enum
{
    EN_STATUS_EMPTY,
    EN_STATUS_DELETE,
    EN_STATUS_EXIST,
}ENUM_DATA_STATUS;

typedef int DATA_TYPE;

typedef struct
{
    DATA_TYPE   key;
    ENUM_DATA_STATUS status;
}STRU_HASH_NODE;

typedef struct
{
    STRU_HASH_NODE* hashNode;
    int size;
    int capacity;
}HASH_TABLE;

int InitHash(HASH_TABLE* table, int capacity);

/*������ϣ��*/
int CreateHash(HASH_TABLE* table, int capacity);

/*��ϣ��ؼ�������*/
bool SearchHash(HASH_TABLE* table, DATA_TYPE data);

/*��ϣ�����ؼ���*/
int InsertHash(HASH_TABLE *table, DATA_TYPE data);

/*ɾ��ָ���Ĺؼ���*/
bool RemoveHash(HASH_TABLE* table, DATA_TYPE data);

/*����Ƿ���Ҫ����*/
bool CheckCapacity(HASH_TABLE* table);

/*��ϣ�������㷨*/
int GetCapacity(HASH_TABLE* table);

/*��ϣ������*/
int RecreateHashTable(HASH_TABLE *table);

/*��ϣ����*/
int HashFun(HASH_TABLE* table, DATA_TYPE data);

/*����ͻ�����ŵ�ַ��->����̽�ⷨ*/
int Collision(HASH_TABLE *table, int *p);

/*ɾ����ϣ��*/
void DestoryHash(HASH_TABLE* table);

/*��ӡ��ϣ��*/
void PrintHash(HASH_TABLE* table);

/*���Թ�ϣ����*/
void test_hash();




#endif
