#define _CRT_SECURE_NO_WARNINGS 1
//#define MAX 1000

//#define NAME_MAX 20
//#define SEX_MAX 5
//#define TELE_MAX 12
//#define ADDR_MAX 30

enum Max
{
	NAME_MAX = 20,
    SEX_MAX = 5,
    TELE_MAX = 12,
    ADDR_MAX = 30,
	DEFAULT_SZ = 3//Ĭ�ϳ�ʼ����
};


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

struct ProInfo
{
	char name[NAME_MAX];
	int age;
	char sex[SEX_MAX];
	char tele[TELE_MAX];
	char addr[ADDR_MAX];
};

struct Contact
{
	struct ProInfo* date;
	int capacity;//��ǰͨѶ¼�������
	int size;//��ǰͨѶ¼���ݸ���
};


enum Opition
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT,
	SAVE
};

void InitContact(struct Contact* ps);//��ʼ��ͨѶ¼
void AddContact(struct Contact* ps);//����һ����Ϣ
void DelContact(struct Contact* ps);//ɾ��һ����Ϣ
void SearchContact(const struct Contact* ps);//����һ����ϵ��
void ModifyContact(struct Contact* ps);//�޸���ϵ��
void ShowContact(const struct Contact* ps);//��ʾͨѶ¼
void SortContact(const struct Contact* ps);//������������ϵ��
void SaveContact(const struct Contact* ps);//����ͨѶ¼
void DestoryContact(struct Contact* ps);//����ͨѶ¼