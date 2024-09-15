#include "contact.h"
void InitContact(Contact* pc)
{
	assert(pc);
	pc->count = 0;
	pc->data = (PeoInfo*)calloc(3, sizeof(PeoInfo));
	if (pc->data == NULL)
	{
		printf("InitContact%s\n", strerror(errno));
		return;
	}
	pc->capacity = Default;
	LoadContact(pc);
}



void CheckCapacity(Contact* pc)
{
	if (pc->capacity == pc->count)
	{
		PeoInfo* ptr = realloc(pc->data, (pc->capacity + Increase) * sizeof(PeoInfo));
		if (ptr == NULL)
		{
			printf("AddContact%s\n", strerror(errno));
			return;
		}
		else
		{
			pc->data = ptr;
			pc->capacity += Increase;
		}
		printf("succeed in increasing\n");
	}
}
void LoadContact(Contact* pc)
{
	FILE* pf = fopen("Contact.txt", "rb");
	if (pf == NULL)
	{
		perror(fopen);
		return;
	}
	PeoInfo tmp;
	while (fread(&tmp, sizeof(PeoInfo), 1, pf) == 1)
	{
		CheckCapacity(pc);
		pc->data[pc->count] = tmp;

		pc->count++;
	}
}
void AddContact(Contact* pc)
{
	CheckCapacity(pc);
	if (pc->capacity != 0)
	{
		assert(pc);
		printf("please enter name:>");
		scanf("%s", &pc->data[pc->count].name);
		printf("please enter age:>");
		scanf("%d", &pc->data[pc->count].age);
		printf("please enter sex:>");
		scanf("%s", &pc->data[pc->count].sex);
		printf("please enter tele:>");
		scanf("%s", &pc->data[pc->count].tele);
		printf("please enter addr:>");
		scanf("%s", &pc->data[pc->count].addr); 
		(pc->count)++;
		printf("\nsucceed in adding one\n");

	}
	else
		printf("fully occupied already\n");

	return;

}
void ShowContact(const Contact* pc)
{
	assert(pc);
	int i = 0;
	printf("%3s\t%20s\t%3s\t%5s\t%12s\t%30s\n",
		"num", "name", "age", "sex", "tele", "addr");
	for (i = 0; i < pc->count; i++)
	{
		printf("%3d\t%20s\t%3d\t%5s\t%12s\t%30s\n",
			i + 1, 
			pc->data[i].name,
			pc->data[i].age,
			pc->data[i].sex, 
			pc->data[i].tele,
			pc->data[i].addr);
	}

}
static int FindByName(char name[max_name], Contact* pc)
{
	assert(pc);
	int i = 0;
	for (i = 0; i < pc->count; i++)
	{
		int ret = strcmp(pc->data[i].name, name);
		if (ret == 0)
		{
			return i;
		}
	}
	return -1;
}
void DelContact(Contact* pc)
{
	char name[max_name] = { 0 };
	assert(pc);
	printf("please enter the name:>");
	scanf("%s", name);
	if (pc->count == 0)
	{
		printf("empty Contact directory\n");
	}
	else
	{
		int ret = FindByName(name, pc);
		if (ret == -1)
		{
			printf("no the name you typed just now\n");
		}
		else
		{
			for (int i = ret; i < (pc->count)-1; i++)
			{
				pc->data[i] = pc->data[i + 1];
			}
			(pc->count)--;
			printf("succeed in deleting one member\n");
		}
	}
}
void SearchContact(Contact* pc)
{
	char name[max_name] = { 0 };
	assert(pc);
	printf("please enter the name:>");
	scanf("%s", name);
	if (pc->count == 0)
	{
		printf("empty Contact directory\n");
	}
	else
	{
		int ret = FindByName(name, pc);
		if (ret == -1)
		{
			printf("no the name you typed just now\n");
		}
		else
		{
			printf("%3s\t%20s\t%3s\t%5s\t%12s\t%30s\n",
				"num", "name", "age", "sex", "tele", "addr");
			printf("%3d\t%20s\t%3d\t%5s\t%12s\t%30s\n",
				ret + 1,
				pc->data[ret].name,
				pc->data[ret].age,
				pc->data[ret].sex,
				pc->data[ret].tele,
				pc->data[ret].addr);
			printf("succeed in searching one member\n");
		}
	}
}
void ModifyContact(Contact* pc)
{
	char name[max_name] = { 0 };
	assert(pc);
	printf("please enter the name:>");
	scanf("%s", name);
	if (pc->count == 0)
	{
		printf("empty Contact directory\n");
	}
	else
	{
		int ret = FindByName(name, pc);
		if (ret == -1)
		{
			printf("no the name you typed just now\n");
		}
		else
		{
			printf("please modify name:>");
			scanf("%s", &pc->data[pc->count].name);
			printf("please modify age:>");
			scanf("%d", &pc->data[pc->count].age);
			printf("please modify sex:>");
			scanf("%s", &pc->data[pc->count].sex);
			printf("please modify tele:>");
			scanf("%s", &pc->data[pc->count].tele);
			printf("please modify addr:>");
			scanf("%s", &pc->data[pc->count].addr);
			(pc->count)++;
			printf("\nsucceed in modifying one\n");

		}
	}
}

int CompareAge(const void* e1, const void* e2)
{
	//return (*(int*)e1) - (*(int*)e2);
	return (((PeoInfo*)e1)->age) - (((PeoInfo*)e2)->age);
}
void SortContact(Contact* pc)
{
	assert(pc);
	if (pc->count == 0)
	{
		printf("empty Contact directory\n");
	}
	else
	{
		qsort(pc->data, pc->count, sizeof(PeoInfo), &CompareAge);
		printf("quick sort successfully\n");
	}
}
void DestroyContact(Contact* pc)
{
	assert(pc);
	free(pc->data);
	pc->data = NULL;
}
void SaveContact(const Contact* pc)
{
	assert(pc);
	FILE* pfWrite = fopen("Contact.txt", "wb");
	if (pfWrite == NULL)
	{
		perror(fopen);
		return;
	}
	for (int i = 0; i < pc->count; i++)
	{
		fwrite(pc->data+i, sizeof(PeoInfo), 1, pfWrite);
	}

	fclose(pfWrite);
	pfWrite = NULL;
}





