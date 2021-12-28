#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"
#include "orderManage.h"

void showHomePage()//��ʾϵͳ��ҳ
{
	printf("\n\n\n");
	printf("\t\t\t��ӭʹ�ò˵�����ϵͳ1.0\n\n");
	printf("\t\t\t-----1.�˵�����---------\n\n");
	printf("\t\t\t-----2.��������---------\n\n");
	printf("\t\t\t-----3.ͳ�Ʒ���---------\n\n");
	printf("\t\t\t-----0.�˳�ϵͳ---------\n\n");
}

void showMenuManage()//��ʾ�˵�����ҳ��
{
	printf("\n\n\n");
	printf("\t\t\t########�˵�����##########\n\n");
	printf("\t\t\t------1.��Ӳ�Ʒ----------\n\n");
	printf("\t\t\t------2.ɾ����Ʒ----------\n\n");
	printf("\t\t\t------3.�޸Ĳ�Ʒ----------\n\n");
	printf("\t\t\t------4.��ѯ��Ʒ----------\n\n");
	printf("\t\t\t------5.��ʾ���в�Ʒ-------\n\n");
	printf("\t\t\t------0.�˳��˵�����-------\n\n");
}

void showOrderManage()//�����������
{
	printf("\n\n\n");
	printf("\t\t\t########��������##########\n\n");
	printf("\t\t\t------1.��Ӷ���----------\n\n");
	printf("\t\t\t------2.ɾ������----------\n\n");
	printf("\t\t\t------3.�޸Ķ���----------\n\n");
	printf("\t\t\t------4.��ѯ����----------\n\n");
	printf("\t\t\t------5.��ʾ���ж���-------\n\n");
	printf("\t\t\t------0.�˳���������-------\n\n");
}

void showAnalyse()//ͳ�Ʒ�������
{
	printf("\n\n\n");
	printf("\t\t\t########ͳ�Ʒ���##########\n\n");
	printf("\t\t\t------1.��Ʒ����ͳ��--------\n\n");
	printf("\t\t\t------2.����ͳ��----------\n\n");
	printf("\t\t\t------0.�˳���������-------\n\n");
}

//ͳ�Ʒ����еĲ�Ʒ��ʾ
void showMenuSale(struct menu* head)
{
	struct menu* temp;
	temp = head;
	printf("\t\t�˺�%10s����\t\t������\t\t�վ�����\n", " ");
	while (temp)
	{
		printf("\t\t%02d\t%10s\t\t%d\t\t%d\n",
			temp->foodNum, temp->foodName, temp->dailySales, temp->dailyIncome);
		temp = temp->next;
	}
}

//ͳ�Ʒ����еĶ�����ʾ
void showFormInfo(struct orderForm* orderFormHead, struct menu* menuHead, struct date inputDate)
{
	struct orderForm* temp;
	struct menu* searchTemp;
	int sum = 0, num = 0;
	temp = orderFormHead;
	while (temp)//������������
	{
		if (temp->formDate.year == inputDate.year
			&& temp->formDate.month == inputDate.month
			&& temp->formDate.day == inputDate.day)//�ҵ���Ӧ���ڵĶ����������
		{
			num++;//ͳ�����������Ķ�������
			sum += temp->sumPrice;//ͳ�ƶ�Ӧ���ڵĶ������ܼ�
			printf("�����š�%02d��\t�µ�ʱ�䡾%d/%02d/%02d��\t��%d��\t�ö����ܼ�Ϊ��%d����\n",
				temp->orderFormNum, temp->formDate.year, temp->formDate.month, temp->formDate.day, temp->people, temp->sumPrice);
			for (int i = 0; i < temp->menuNum; i++)
			{
				searchTemp = searchMenu(menuHead, temp->menu[i][0]);
				if (searchTemp)
					printf("[%02d]�Ųˡ�%s��x %d\t\t", temp->menu[i][0], searchTemp->foodName, temp->menu[i][1]);
				if ((i + 1) % 3 == 0)
					printf("\n");
			}
			printf("\n\n");
		}
		temp = temp->next;
	}
	printf("%d��%02d��%02d�յ����ж����ܼ�Ϊ %dԪ\t������Ϊ %.2fԪ\n",
		inputDate.year, inputDate.month, inputDate.day, sum, 1.0 * sum / num);
}

//�˵����������ʾ�Ͳ˵��ļ���ȡ

//�˵���ʾ
void showMenu(struct menu* head, int oneOrAll)//oneOrAll����Ϊ��ʾ����1Ϊ��ʾһ��������Ϊ��ʾ����
{
	if (oneOrAll == 1)
	{
		printf("\t\t�˺�%10s����\t\t�۸�\t\t�ɱ�\n"," ");
		printf("\t\t%02d\t%10s\t\t%d\t\t%d\n", head->foodNum, head->foodName, head->price, head->cost);
	}
	else
	{
		struct menu* temp;
		temp = head;
		printf("\t\t�˺�%10s����\t\t�۸�\t\t�ɱ�\n"," ");
		while (temp)
		{
			printf("\t\t%02d\t%10s\t\t%d\t\t%d\n", 
				temp->foodNum, temp->foodName, temp->price, temp->cost);
			temp = temp->next;
		}
	}
}


struct menu* readMenuFile(struct menu* head)//��ȡ�˵��ļ�����
{
	FILE* menuFile;
	menuFile = fopen("menu.txt", "r");//�ļ���ȡ
	if (!menuFile)//û��menu.txt�ļ�����NUL
		return NULL;
	//menu.txt�ļ�,ִ������Ķ�ȡ������ȡ
	char fill[256] = { 0 };
	struct menu* temp, *newNode;
	struct menu tempMenu;
	fgets(fill, 256, menuFile);//����ȡ�ļ���һ�еı�����
	while (fscanf(menuFile, "\t\t%d\t%s\t\t%d\t\t%d\n",
		&tempMenu.foodNum, tempMenu.foodName, &tempMenu.price, &tempMenu.cost) != EOF)//��������Ϊֹ
	{//�����β�巨
		if (!head)//���û��ͷ�ڵ�
		{
			newNode = (struct menu*)malloc(sizeof(struct menu));
			*newNode = tempMenu;
			head = newNode;
			temp = head;
			temp->next = NULL;
		}
		else //��ͷ�ڵ�
		{
			newNode = (struct menu*)malloc(sizeof(struct menu));
			*newNode = tempMenu;
			temp->next = newNode;
			temp = temp->next;
			temp->next = NULL;
		}

	}
	fclose(menuFile);//�ر��ļ�������
	return head;
}

void saveMenuFile(struct menu* head)//����˵�����
{
	FILE* menuFile;
	struct menu* temp;
	temp = head;
	menuFile = fopen("menu.txt", "w");//���������menu.txt�ļ�
	fprintf(menuFile,"\t\t�˺�\t%16s����\t\t�۸�\t\t�ɱ�\n", " ");//����%16s�Ŀո�Ϊ�˸�ʽ�������
	while (temp)
	{
		fprintf(menuFile,"\t\t%02d\t%16s\t\t%d\t\t%d\n",//����%16s�Ŀո�Ϊ�˸�ʽ�������
			temp->foodNum, temp->foodName, temp->price, temp->cost);
		temp = temp->next;
	}
	fclose(menuFile);
}
//�������������ʾ�Ͷ����ļ��Ķ�ȡ
void showOrderForm(struct orderForm* orderForm, struct menu* menuHead,int oneOrAll)
//oneOrAll����Ϊ��ʾ����1Ϊ��ʾһ��������Ϊ��ʾ����
{
	if (orderForm == NULL)//û�ж���
	{
		printf("���޶���\n");
		return;
	}
	if (oneOrAll)//���һ������
	{
		printf("�����š�%02d��\t�µ�ʱ�䡾%d/%02d/%02d��\t��%d��\n",
			orderForm->orderFormNum,orderForm->formDate.year,
			orderForm->formDate.month,orderForm->formDate.day, orderForm->people);
		for (int i = 0; i < orderForm->menuNum; i++)
		{
			printf("[%02d]�Ųˡ�%s��x %d\t\t", orderForm->menu[i][0], searchMenu(menuHead, orderForm->menu[i][0])->foodName, orderForm->menu[i][1]);
			if ((i + 1) % 3 == 0)
				printf("\n");
		}
		printf("\n");
	}
	else//������ж���
	{
		struct orderForm* temp;
		struct menu* searchTemp;
		temp = orderForm;
		while (temp)//������������
		{
			printf("�����š�%02d��\t�µ�ʱ�䡾%d/%02d/%02d��\t��%d��\n",
				temp->orderFormNum, temp->formDate.year, temp->formDate.month, temp->formDate.day, temp->people);
			for (int i = 0; i < temp->menuNum; i++)
			{
				searchTemp = searchMenu(menuHead, temp->menu[i][0]);
				if (searchTemp)
					printf("[%02d]�Ųˡ�%s��x %d\t\t", temp->menu[i][0],searchTemp->foodName, temp->menu[i][1]);
				if ((i + 1) % 3 == 0)
					printf("\n");
			}
			printf("\n\n");
			temp = temp->next;
		}
	}
}

struct menu* readOrderFormFile(struct orderForm* orderFormHead)//��ȡ�����ļ�����
{
	FILE* orderFormFile;
	orderFormFile = fopen("orderForm.txt", "r");
	if (!orderFormFile)//�����ȡʧ�ܷ���NULL
		return NULL;
	struct orderForm* orderFormTemp, * newNode;
	struct orderForm temp;//�м����
	//ʹ��β�巨���붩������
	while (!feof(orderFormFile))
	{
		fscanf(orderFormFile, "%d�ֲ�\t%d��\t�����š�%2d��\t�µ�ʱ�䡾%d/%02d/%02d��\n",
			&temp.menuNum, &temp.people,&temp.orderFormNum, &temp.formDate.year, &temp.formDate.month, &temp.formDate.day);
		for (int i = 0; i < temp.menuNum; i++)
		{
			fscanf(orderFormFile, "��%d���Ų� x %d\t", &temp.menu[i][0], &temp.menu[i][1]);
			if ((i + 1) % 2 == 0)
				fscanf(orderFormFile, "\n");
		}
		fscanf(orderFormFile, "\n\n");
		newNode = (struct orderForm*)malloc(sizeof(struct orderForm));
		temp.next = NULL;
		*newNode = temp;
		if (!orderFormHead)//û��ͷ�ڵ�
		{
			orderFormHead = newNode;
			orderFormTemp = orderFormHead;
		}
		else
		{
			orderFormTemp->next = newNode;
			orderFormTemp = orderFormTemp->next;
		}
	}
	return orderFormHead;
	fclose(orderFormFile);
}

void saveOrderFormFile(struct orderForm* orderFormHead)//���涩������
{
	FILE* orderFormFile;
	struct orderForm* temp = orderFormHead;
	orderFormFile = fopen("orderForm.txt", "w");
	while (temp)
	{
		fprintf(orderFormFile, "%d�ֲ�\t%d��\t�����š�%02d��\t�µ�ʱ�䡾%d/%02d/%02d��\n",
			temp->menuNum,temp->people,temp->orderFormNum, temp->formDate.year, temp->formDate.month, temp->formDate.day);
		for (int i = 0; i < temp->menuNum; i++)
		{
			fprintf(orderFormFile, "��%d���Ų� x %d\t", temp->menu[i][0], temp->menu[i][1]);
			if ((i + 1) % 2 == 0)
				fprintf(orderFormFile, "\n");
		}
		fprintf(orderFormFile, "\n\n");
		temp = temp->next;
	}
	fclose(orderFormFile);
}