#include "Hash.h"
#include <stdio.h>
#include <memory>

int InitHash(HASH_TABLE* table, int capacity)
{
    if(NULL == table)
    {
        return DA_ERROR;
    }
    table->size = 0;
    table->capacity = capacity;
    table->capacity = GetCapacity(table);

    table->hashNode = (STRU_HASH_NODE*)malloc(sizeof(STRU_HASH_NODE) * table->capacity);

    for (int i = 0; i < table->capacity; i++)
    {
        table->hashNode[i].status = EN_STATUS_EMPTY;
    }

    return DA_SUCCESS;
}

/*��������ʱ����ϣ���С*/
int GetCapacity(HASH_TABLE* table)
{
    //��ϣ������������һ�����ʵ��������У����ٳ�ͻ�Ŀ���
    const int nPrimeSize = 13;
    const int HashSize[] = 
    {
        7,13,17,101,
        211,307,401,503,
        601,701,809,907,
        997
    };

    for (int i = 0; i < nPrimeSize; i++)
    {
        if (table->capacity < HashSize[i])
        {
            return HashSize[i];
        }
    }

    return HashSize[nPrimeSize - 1];
}

bool CheckCapacity(HASH_TABLE* table)
{
    //��鸺�����Ӵ�С
    int check_capacity = (table->size * 10) / table->capacity;
    if (check_capacity >= 7)
    {
        return true;
    }

    return false;
}

/*��ϣ������*/
int RecreateHashTable(HASH_TABLE *table)
{
    HASH_TABLE NewTable;

    //�����µĹ�ϣ��
    InitHash(&NewTable,table->capacity);

    for (int i = 0; i < table->capacity; i++)
    {
        if (EN_STATUS_EXIST == table->hashNode[i].status)
        {
            InsertHash(&NewTable,table->hashNode[i].key);
        }
    }

   if (table->hashNode != NULL)
   {
       free(table->hashNode);
       table->hashNode = NULL;
   }

   table->capacity = NewTable.capacity;
   table->size = NewTable.size;
   table->hashNode = NewTable.hashNode;

   return DA_SUCCESS;
}

/*����������*/
int HashFun(HASH_TABLE* table, DATA_TYPE data)
{
    return data % table->capacity;
}

/*��ͻʱ������̽�ⷵ���µĵ�ַ*/
int Collision(HASH_TABLE *table, int hash_addr)
{
    return (hash_addr + 1) % (table->capacity);
}

/*��ϣ�����ؼ���*/
/*
step1:������Ӧ�Ĺ�ϣ��ַ
step2:�жϵ�ǰ��ϣ��ַ�Ƿ��г�ͻ
step3:�г�ͻ����ó�ͻ���ԣ����򽫸�Ԫ�ط��ڸ�λ��
*/
int InsertHash(HASH_TABLE *table, DATA_TYPE data)
{
    if (CheckCapacity(table))
    {
        printf("hash table need to recreate\n");
        RecreateHashTable(table);
    }

    int hash_addr = HashFun(table, data);

    int index = hash_addr;
    
    //��ͻ����Լ���ͻ�������:����̽�ⷨ
    while (table->hashNode[index].status == EN_STATUS_EXIST)
    {
        if (table->hashNode[index].key == data)
        {
            return DA_ALREADY_EXIST;
        }

        index = Collision(table,index);
    }

    printf("key = %d hash addr=%d target= %d\n",data, hash_addr,index);

    table->hashNode[index].key = data;
    table->hashNode[index].status = EN_STATUS_EXIST;
    table->size += 1;

    return DA_SUCCESS;
}

/*��ϣ��ؼ�������*/
bool SearchHash(HASH_TABLE* table, DATA_TYPE data)
{
    int hash_addr = HashFun(table, data);

    int index = hash_addr;
    //����̽�ⷨ������
    while (table->hashNode[index].status == EN_STATUS_EXIST)
    {
        //��������
        if (table->hashNode[index].key == data)
        {
            return true;
        }

        //����̽����һ��Ԫ��
        index = Collision(table,index);
    }
    
    return false;
}

/*ɾ����ϣ�ؼ���*/
/*
��������̽�ⷨ����ɢ��ʱ�ĳ�ͻ,
���ӹ�ϣ��ɾ��һ����¼ʱ,��Ӧ�������¼������λ���ÿ�,
����Ӱ��������¼�Ĳ���
*/
bool RemoveHash(HASH_TABLE* table, DATA_TYPE data)
{
    int hash_addr = HashFun(table, data);

    int index = hash_addr;
    //����̽�ⷨ������
    while (table->hashNode[index].status == EN_STATUS_EXIST)
    {
        //��������
        if (table->hashNode[index].key == data)
        {
            table->hashNode[index].status = EN_STATUS_DELETE;
            table->size--;
            return true;
        }
        //����̽����һ��Ԫ��
        index = Collision(table,index);
    }

    return false;
}

void DestoryHash(HASH_TABLE* table)
{
    table->capacity = 0;
    table->size = 0;
    free(table->hashNode);
    table->hashNode = NULL;
}

void PrintHash(HASH_TABLE* table)
{
   printf("��ϣ������Ϊ%d, Ԫ�ظ���Ϊ%d\n",table->capacity,table->size);

   for (int i = 0; i < table->capacity; i++)
   {
       if (table->hashNode[i].status == EN_STATUS_EXIST)
       {
           printf("key=%d\t",table->hashNode[i].key);
       }
   }

   printf("\n");

   for (int i = 0; i < table->capacity; i++)
   {
       if (table->hashNode[i].status == EN_STATUS_DELETE)
       {
           printf("delete key=%d\t",table->hashNode[i].key);
       }
   }

   printf("\n");
}

void test_hash()
{
    HASH_TABLE  ht;
    InitHash(&ht, 0);//��ϣ���ʼ��

    printf("begin insert data....\n");

    InsertHash(&ht, 37);//��������
    InsertHash(&ht, 25);//��������
    InsertHash(&ht, 11);//��������
    InsertHash(&ht, 36);//��������
    InsertHash(&ht, 41);//��������
    InsertHash(&ht, 42);//��������

    PrintHash(&ht);//��ӡ��ϣ��;

    printf("begin search data....\n");

    if (SearchHash(&ht,11))
    {
        printf("find  data success...\n");
    }
    else
    {
        printf("find data fail...\n");
    }

    printf("begin remove data....\n");

    RemoveHash(&ht, 11);//��������

    PrintHash(&ht);//��ӡ��ϣ��;

    DestoryHash(&ht);
}
