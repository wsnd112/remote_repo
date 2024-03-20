#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"
//实现函数;

//声明函数
void CheckCapacity(struct Contact* ps);

void Loadcontact(struct Contact* ps)
{
	struct ProInfo tmp = { 0 };
	FILE* pf = fopen("contact.dat", "rb");
	if (pf == NULL)
	{
		printf("Loadcontact::%s\n", strerror(errno));
		return;
	}
	//读取文件信息放到通讯录中
	while (fread(&tmp, sizeof(struct ProInfo), 1, pf))//如果fread返回值为0，则读取完毕
	{
		CheckCapacity(ps);
		ps->date[ps->size] = tmp;
		ps->size++;
	}
	fclose(pf);
	ps = NULL;
	
}

void InitContact(struct Contact* ps)
{
	
	ps->date = (struct ProInfo*)malloc(DEFAULT_SZ * sizeof(struct ProInfo));
	if (ps->date == NULL)
	{
		return;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;
	//把文件中保存的信息初始化到通讯录中
	Loadcontact(ps);
}

static int FindByName(const struct Contact* ps, char* name)
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (0 == strcmp(ps->date[i].name, name))
		{
			return i;
		}
	}
	return -1;//找不到姓名
}

void CheckCapacity(struct Contact* ps)
{
	if (ps->size == ps->capacity)
	{
		//增容
		struct ProInfo* ptr = realloc(ps->date, (ps->capacity + 2) * sizeof(struct ProInfo));
		if (ptr)
		{
			ps->date = ptr;
			ps->capacity += 2;
		}
	}
}
void AddContact(struct Contact* ps)
{
	CheckCapacity(ps);//检测当前容量
	//如果满了，增加容量
	//如果没满，啥都不干
	//增加数据
	printf("请输入姓名：");
	scanf("%s", ps->date[ps->size].name);
	printf("请输入年龄：");
	scanf("%d", &(ps->date[ps->size].age));
	printf("请输入性别：");
	scanf("%s", ps->date[ps->size].sex);
	printf("请输入电话：");
	scanf("%s", ps->date[ps->size].tele);
	printf("请输入住址：");
	scanf("%s", ps->date[ps->size].addr);
	ps->size++;
	printf("添加成功。\n");
}


void DelContact(struct Contact* ps)
{
	char name[NAME_MAX];
	printf("请输入要删除联系人的姓名：");
	scanf("%s", name);
	//查找
	//查到了返回下标
	//查不到返回-1
	int ret = FindByName(ps, name);
	if (ret == -1)
	{
		printf("找不到联系人！\n");
	}
	else//删除联系人
	{
		int j = 0;
		for (j = ret; j < ps->size - 1; j++)
		{
			ps->date[j] = ps->date[j + 1];
		}
		ps->size--;
		printf("删除成功。\n");
	}
}


void SearchContact(const struct Contact* ps)
{
	char name[NAME_MAX];
	printf("请输入联系人姓名：");
	scanf("%s", name);
	int ret = FindByName(ps, name);
	if (-1 == ret)
	{
		printf("查不到联系人！\n");
	}
	else
	{
		printf("%-12s\t%-12s\t%-12s\t%-12s\t%-12s\n", "姓名", "年龄", "性别", "电话", "住址");
		printf("%-12s\t%-12d\t%-12s\t%-12s\t%-12s\n",
			ps->date[ret].name,
			ps->date[ret].age,
			ps->date[ret].sex,
			ps->date[ret].tele,
			ps->date[ret].addr);
	}
}


void ModifyContact(struct Contact* ps)
{
	char name[NAME_MAX];
	printf("请输入要修改联系人的姓名：");
	scanf("%s", name);
	int ret = FindByName(ps, name);
	if (ret == -1)
	{
		printf("找不到联系人！\n");
	}
	else
	{
		printf("请输入姓名：");
		scanf("%s", ps->date[ret].name);
		printf("请输入年龄：");
		scanf("%d", &(ps->date[ret].age));		printf("请输入性别：");
		scanf("%s", ps->date[ret].sex);
		printf("请输入电话：");
		scanf("%s", ps->date[ret].tele);
		printf("请输入住址：");
		scanf("%s", ps->date[ret].addr);
		printf("修改成功。\n");
	}
}

void ShowContact(const struct Contact* ps)
{
	printf("%-12s\t%-12s\t%-12s\t%-12s\t%-12s\n", "姓名", "年龄", "性别", "电话", "住址");
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		printf("%-12s\t%-12d\t%-12s\t%-12s\t%-12s\n",
			ps->date[i].name,
			ps->date[i].age,
			ps->date[i].sex,
			ps->date[i].tele,
			ps->date[i].addr);
	}
}
int compar_age(const void* p1, const void* p2)
{
	return (((struct Contact*)p1)->date->age - ((struct Contact*)p2)->date->age);
}
int compar_name(const void* p1, const void* p2)
{
	return strcmp(((struct Contact*)p1)->date->name, ((struct Contact*)p2)->date->name);
}

void SortContact(const struct Contact* ps)
{
	qsort(ps->date, ps->size, sizeof(ps->date[0]), compar_age);
	ShowContact(ps);
}

void SaveContact(const struct Contact* ps)
{
	FILE* pfwrite = fopen("contact.dat", "wb");
	if (pfwrite == NULL)
	{
		printf("SaveContact::%s\n", strerror(errno));
		return;
	}
	//将通讯录内容写入contact.dat文件中;
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->date[i]),sizeof(struct ProInfo),1,pfwrite);
	}
	fclose(pfwrite);
	pfwrite = NULL;
	printf("保存成功。\n");
}

void DestoryContact(struct Contact* ps)
{
	free(ps->date);
	ps->date = NULL;
}
