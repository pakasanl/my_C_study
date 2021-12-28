#include <stdio.h>
#include <Windows.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "dataType.h"
#include "showAndFileOperation.h"
//������������Ͳ˵���������
// 
//�Բ˵��ļ򵥲�ѯ
struct menu* searchMenu(struct menu* menuHead, int foodNum)
{
	struct menu* temp = menuHead;
	while (temp)
	{
		if (foodNum == temp->foodNum)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;//δ��ѯ���򷵻�NULL
}

//�����Ų���
int ifRepeatOrder(struct orderForm* orderFormHead, int orderNum)
{
	struct orderForm* temp;
	temp = orderFormHead;
	while (temp)
	{
		if (orderNum == temp->orderFormNum)//�������ظ�����1���򷵻�0
			return 1;
		temp = temp->next;
	}
	return 0;
}
//��ѯ����,�ú�����˵���ѯ���в�ͬ
void queryOrderForm(struct orderForm* orderFormHead,struct menu* menuHead)
{
	int orderFormNum;
	struct date formDate;
	int choice = 0;
	struct orderForm* temp;
	while (1)
	{
		temp = orderFormHead;//��¼ͷ�ڵ�
		system("cls");
		printf("\t\t\t��������-->��ѯ����\n");
		printf("1:�������Ų�ѯ/2:�����ڲ�ѯ/3:�˳���ѯ-> ");
		scanf("%d", &choice);
		getchar();//getchar()�̵�'\n',��Ȼ����bug
		if (choice == 1)
		{
			printf("\n�����붩����-> ");
			scanf("%d", &orderFormNum);
			getchar();
			while (temp)//������������  ��temp��ΪNULLʱִ��
			{
				if (temp->orderFormNum == orderFormNum)
				{
					
					showOrderForm(temp, menuHead, 1);//��ѯ������ʾ����ѯ����1��
					system("pause");
					return;//(������Ψһ,��ֱ�ӽ���)
				}
				temp = temp->next;
			}
			printf("δ��ѯ��������Ϣ��\n");//û�в�ѯ��ʱ���
			system("pause");
		}
		else if (choice == 2)//�����ڲ�ѯ ���г���Ӧ���ڵ����ж���
		{
			printf("\n���������ڣ���ʽ����/��/�գ�-> ");
			scanf("%d/%d/%d", &formDate.year, &formDate.month, &formDate.day);
			getchar();
			int flag = 1;//��¼�Ƿ��ѯ��������Ϣ
			while (temp)
			{
				if (temp->formDate.year == formDate.year
					&& temp->formDate.month == formDate.month
					&& temp->formDate.day == formDate.day)
				{
					showOrderForm(temp, menuHead, 1);
					printf("\n");//���У�����һЩ
					flag = 0;
				}
				temp = temp->next;
			}
			if (flag)//flagΪ1��δ��ѯ��
				printf("δ��ѯ��������Ϣ��\n");
			system("pause");
			return;
		}
		else if(choice == 3)
		{
			return;
		}
		else
		{
			printf("�Ƿ�������!!\n");
			system("pause");
		}
	}

}

//��Ӷ���
struct orderForm* addOrderForm(struct orderForm* orderFormHead, struct menu* menuHead)
{
	struct date orderFormDate;
	struct orderForm* newNode;
	char choice = 'y';
	int orderNum,people;
	while (choice == 'y')
	{
		system("cls");
		printf("\t\t\t��������-->��Ӷ���\n");
		printf("�����붩����-> ");
		scanf("%d", &orderNum);
		getchar();
		if (ifRepeatOrder(orderFormHead, orderNum))//�ж϶������Ƿ��ظ�
		{
			printf("��%d���Ŷ����Դ��ڣ�����������!\n",orderNum);
			system("pause");
			continue;//continue������ǰѭ�����¸�ѭ��
		}
		printf("\n�������µ�ʱ�䣨��ʽ����/��/�գ�-> ");
		scanf("%d/%d/%d", &orderFormDate.year, &orderFormDate.month, &orderFormDate.day);
		getchar();
		printf("\n������Ͳ�����-> ");
		scanf("%d", &people);
		getchar();
		system("cls");
		showMenu(menuHead, 0);//��ʾ�˵�
		char orderChoice = 'y';
		newNode = (struct orderForm*)malloc(sizeof(struct orderForm));//����ͷ�巨
		//���½��Ķ����ṹ�帳ֵ
		newNode->formDate = orderFormDate;
		newNode->orderFormNum = orderNum;//������
		newNode->menuNum = 0;//�������
		newNode->people = people;//�Ͳ�����
		while (orderChoice == 'y')
		{
			int foodNum;
			LOOP:
			printf("\n����(����˺�)-> ");
			scanf("%d", &foodNum);
			getchar();
			if (searchMenu(menuHead, foodNum) == NULL)
			{
				printf("%d�Ų˲����ڣ������µ��!\n", foodNum);
				goto LOOP;
			}
			newNode->menu[newNode->menuNum][0] = foodNum;
			printf("����������-> ");
			scanf("%d", &newNode->menu[newNode->menuNum][1]);
			getchar();
			newNode->menuNum++;
			printf("�Ƿ������ˣ�(����/y;����/n)-> ");
			scanf("%c", &orderChoice);
			getchar();
		}
		newNode->next = orderFormHead;//ͷ�巨���
		orderFormHead = newNode;
		showOrderForm(newNode, menuHead, 1);
		printf("��Ӷ����ɹ�\n");
		printf("�Ƿ������ӣ���y:����/n:������-> ");
		scanf("%c", &choice);
		getchar();

		choice = tolower(choice);//תΪСд��ĸ,����Ҳ֧��Y��N
	}
	saveOrderFormFile(orderFormHead);//���涩���ļ�
	return orderFormHead;//���ؽ�����Ӳ������ͷ�ڵ�
}

//ɾ������
struct orderForm* deleteOrderForm(struct orderForm* orderFormHead, struct menu* menuHead)
{
	system("cls");
	printf("\t\t\t��������-->ɾ������\n");
	if (orderFormHead == NULL)
	{
		printf("û�п�ɾ���Ķ�����\n");
		return NULL;
	}
	int delNum;
	struct orderForm* temp,* oldNode;
	char confirm = 'n';
	showOrderForm(orderFormHead, menuHead, 0);
	printf("��������Ҫɾ���Ķ����Ķ�����-> ");
	scanf("%d", &delNum);
	getchar();
	if (orderFormHead->orderFormNum == delNum)//���ͷ�ڵ㼴Ϊ����ɾ���ڵ�
	{
		system("cls");
		printf("ȷ��ɾ����(y:ȷ��/n:ȡ��)\n");
		showOrderForm(orderFormHead, menuHead, 1);
		scanf("%c", &confirm);
		getchar();
		if (confirm == 'n')
		{
			printf("����ȡ��ɾ������\n");
			system("pause");
			return orderFormHead;
		}
		else
		{
			temp = orderFormHead;
			orderFormHead = orderFormHead->next;
			free(temp);
			printf("ɾ���ɹ�\n");
			system("pause");
			return orderFormHead;
		}
	}
	//��ͷ�ڵ�֮��,����������
	oldNode = orderFormHead;
	temp = orderFormHead->next;
	while (temp)
	{
		if (temp->orderFormNum == delNum)
		{
			system("cls");
			printf("ȷ��ɾ����(y:ȷ��/n:ȡ��)\n");
			showOrderForm(temp, menuHead, 1);
			scanf("%c", &confirm);
			getchar();
			if (confirm == 'n')
			{
				printf("����ȡ��ɾ������\n");
				system("pause");
				return orderFormHead;
			}
			else
			{
				oldNode->next = temp->next;
				free(temp);
				printf("ɾ���ɹ�\n");
				system("pause");
				return orderFormHead;
			}
		}
		temp = temp->next;
		oldNode = oldNode->next;
	}
	printf("�޴˶�����\n");
	system("pause");
	return orderFormHead;
}

//�޸Ķ���
struct orderForm* changeOrderForm(struct orderForm* orderFormHead, struct menu* menuHead)
{
	system("cls");
	printf("\t\t\t��������-->�޸Ķ���\n");
	if (orderFormHead == NULL)//�޶�������NULL
	{
		printf("û�п��޸ĵĶ�����\n");
		return NULL;
	}
	int changeNum;//Ҫ�޸ĵĶ�����
	showOrderForm(orderFormHead, menuHead, 0);//��ʾ���ж���
	printf("��������Ҫ�޸ĵĶ����Ķ�����-> ");
	scanf("%d", &changeNum);
	getchar();
	struct orderForm* temp;
	temp = orderFormHead;
	while (temp)//������������
	{
		if (temp->orderFormNum == changeNum)
		{
			int choice;
			char orderChoice = 'y';
			printf("1.��Ӳ�Ʒ/2.ɾ����Ʒ/3.�޸Ĳ�Ʒ/0.�˳�-> ");
			scanf("%d", &choice);
			getchar();
			switch (choice)
			{
				case 1://�Ӳ�
					while (orderChoice == 'y')//�����еĲ˵�Ϊ��ά����
					{
						system("cls");
						showMenu(menuHead, 0);//��ʾ�˵�
						int foodNum;
					LOOP1:
						printf("\n����(����˺�)-> ");
						scanf("%d", &foodNum);
						getchar();
						if (searchMenu(menuHead, foodNum) == NULL)
						{
							printf("%d�Ų˲����ڣ������µ��!\n", foodNum);
							goto LOOP1;
						}
						temp->menu[temp->menuNum][0] = foodNum;
						printf("����������-> ");
						scanf("%d", &temp->menu[temp->menuNum][1]);
						getchar();
						temp->menuNum++;
						showOrderForm(temp, menuHead, 1);//��ʾ�޸ĺ�Ķ���
						printf("�Ƿ������ˣ�(����/y;����/n)-> ");
						scanf("%c", &orderChoice);
						getchar();
					}
					printf("\n�����޸ĳɹ�\n");
					saveOrderFormFile(orderFormHead);//�����޸ĺ�Ķ���
					system("pause");
					return orderFormHead;//����ͷ�ڵ�
				case 2://ɾ��
					while (orderChoice == 'y')
					{
						int foodNum;//��Ҫɾ���Ĳ˵Ĳ˺�
						system("cls");
						showOrderForm(temp, menuHead, 1);
						printf("��������Ҫɾ���Ĳ˵Ĳ˺�-> ");
						scanf("%d", &foodNum);
						getchar();
						for (int i = 0; i < temp->menuNum; i++)//ѭ�������еĲ˵�����
						{
							if (temp->menu[i][0] == foodNum)//�ҵ�Ҫɾ���Ĳ˵Ĳ˺�
							{
								for (int j = i; j < temp->menuNum; j++)
								{
									temp->menu[j][0] = temp->menu[j + 1][0];//����һ����ֵ��ǰһ��
									temp->menu[j][1] = temp->menu[j + 1][1];
								}
								temp->menuNum--;//ɾ����˵�������һ��
								break;
							}
						}
						showOrderForm(temp, menuHead, 1);//��ʾ�޸ĺ�Ķ���
						printf("�Ƿ����ɾ����(����/y;����/n)-> ");
						scanf("%c", &orderChoice);
						getchar();
					}
					printf("\n�����޸ĳɹ�\n");
					saveOrderFormFile(orderFormHead);//�����޸ĺ�Ķ���
					system("pause");
					return orderFormHead;//����ͷ�ڵ�
				case 3://�Ĳ�
					while (orderChoice == 'y')
					{
						int foodNum;//��Ҫ�޸ĵĲ˺�
						int	foodChanngeNum;//�޸ĺ�Ĳ˺�
						int	foodCount;//��Ӧ�˺��޸ĺ������
						int choice;//����ѡ��
						system("cls");
						showOrderForm(temp, menuHead, 1);
						printf("��������Ҫ�޸ĵĲ˵Ĳ˺�-> ");
						scanf("%d", &foodNum);
						getchar();
						printf("��ѡ��(1.������%s��/2.���ġ�%s��������)-> "
							, searchMenu(menuHead, foodNum)->foodName, searchMenu(menuHead, foodNum)->foodName);
						scanf("%d", &choice);
						getchar();
						if (choice == 1)
						{
							showMenu(menuHead, 0);
							printf("�����������Ĳ˵Ĳ˺�-> ");
							scanf("%d", &foodChanngeNum);
							getchar();
							for (int i = 0; i < temp->menuNum; i++)//���������еĲ˵��ҵ�Ŀ��˺��޸�
							{
								if (temp->menu[i][0] == foodNum)
								{
									temp->menu[i][0] = foodChanngeNum;//�޸Ĳ˺�,ע��ڶ���[]Ϊ0
									break;
								}
							}
						}
						else if (choice == 2)
						{
							printf("�������޸ĺ������-> ");
							scanf("%d", &foodCount);
							getchar();
							for (int i = 0; i < temp->menuNum; i++)//���������еĲ˵��ҵ�Ŀ��˺��޸�
							{
								if (temp->menu[i][0] == foodNum)
								{
									temp->menu[i][1] = foodCount;//�޸�����,ע��ڶ���[]Ϊ1
									break;
								}
							}
						}
						showOrderForm(temp, menuHead, 1);//��ʾ�޸ĺ�Ķ���
						printf("�Ƿ�����޸ģ�(����/y;����/n)-> ");
						scanf("%c", &orderChoice);
						getchar();
					}
					printf("\n�����޸ĳɹ�\n");
					saveOrderFormFile(orderFormHead);//�����޸ĺ�Ķ���
					system("pause");
					return orderFormHead;//����ͷ�ڵ�
				case 0://�˳�
					return orderFormHead;
			}
		}
		temp = temp->next;
	}
	if (!temp)//����Ķ��������������
	{
		printf("�޴˶���\n");
		system("pause");
		return orderFormHead;
	}
}
