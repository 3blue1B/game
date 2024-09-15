#include "contact.h"
void menu()
{
	printf("********1.add**********\n");
	printf("********2.del*********\n");
	printf("********3.search********\n");
	printf("********4.modify*****\n");
	printf("********5.show*****\n");
	printf("********6.sort*******\n");
	printf("********0.eixt*******\n");
}
enum options
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT,
};
int main()
{
	int input = 0;
	
	Contact con;
	InitContact(&con);

	do {
		menu();
		printf("please choose:>");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			AddContact(&con);
			break;
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;		
		case SHOW:
			ShowContact(&con);

			break;
		case SORT:
			SortContact(&con);
			ShowContact(&con);
			break;
		case EXIT:
			SaveContact(&con);
			DestroyContact(&con);
			printf("eixt\n");
			break;
		default:
			printf("please input a vaild number\n");
		}

	} while(input);

	return 0;
}
