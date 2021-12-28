#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dataType.h"
#include "showAndFileOperation.h"
//��.c�ļ�Ϊ�����йز˵��������غ�������

//��ѯ��Ʒ
struct menu* queryMenu(struct menu* head, struct menu** oldNode)
	//����ָ��oldNode���ڼ�¼Ŀ����ϸ��ڵ㣬����ɾ��������ʹ�ã���ʹ��ʱ��ֵΪNULL����
{
	int foodNum;
	char foodName[30] = { 0 };
	int choice = 0;
	struct menu* temp;
	temp = head;//��¼ͷ�ڵ�
	if (oldNode != NULL)//������oldNode ��ֵ˵��ʹ����ɾ������oldNode�������ó�
	{
		*oldNode = head;//����ָ�븳ֵ
	}
	while (1)
	{
		system("cls");
		printf("1:���˺Ų�ѯ/2:��������ѯ-> ");
		scanf("%d", &choice);
		getchar();//getchar()�̵�'\n',��Ȼ����bug
		if (choice == 1)//���˺Ų�ѯ
		{
			printf("\n������˺�-> ");
			scanf("%d", &foodNum);
			getchar();
			while (temp)//�����˵�����  temp��temp��ΪNULL��ִ��
			{
				if (temp->foodNum == foodNum)
				{
					return temp;//��ѯ���򷵻ز�ѯ���Ľṹ���ַ
				}
				if (oldNode != NULL)//�����Ҫ��oldNode
				{
					*oldNode = temp;
				}
				temp = temp->next;
			}
			return NULL;//û�в�ѯ��ʱ����NULL
		}
		else if (choice == 2)//��������ѯ  ��Ӧ����ͬ��
		{
			printf("\n���������-> ");
			scanf("%s", foodName);
			getchar();
			while (temp)//������Ʒ����
			{
				if (!strcmp(temp->foodName, foodName))//������ͬ
				{
					return temp;
				}
				if (oldNode != NULL)
				{
					*oldNode = temp;
				}
				temp = temp->next;
			}
			return NULL;//����NULL��δ��ѯ�������Ϣ
		}
		else
		{
			printf("�Ƿ�������!!\n");
			system("pause");
		}
	}
	
}

//��Ӳ�Ʒ
struct menu* addMenu(struct menu* menuHead)//�����Ʒ�ķ������������ͷ�巨
{
	struct menu* newNode;
	char choice = 'y';
	int foodNum;
	char foodName[30] = { 0 };
	int price;
	int cost;
	system("cls");
	printf("\t\t\t�˵�����-->��Ӳ�Ʒ\n");
	while (choice == 'y')
	{
		printf("������˺�-> ");
		scanf("%d", &foodNum);
		getchar();
		if (ifRepeatMenu(menuHead, foodNum, NULL, 1) == 1)//���ĸ�����Ϊ1Ϊ�жϲ˺ţ�Ϊ0Ϊ�жϲ���
		{
			printf("��%02d���Ų��Դ��ڣ���������ӣ�\n",foodNum); //����1��ʾ�ò˺��Դ���,����2��ʾ�ò����Դ���
			system("pause");
			return menuHead;
		}
		printf("\n���������-> ");
		scanf("%s", foodName);
		getchar();
		if (ifRepeatMenu(menuHead, 0, foodName, 0) == 2)
		{
			printf("��%s���Ѵ��ڣ���������ӣ�\n",foodName);
			system("pause");
			return menuHead;
		}
		printf("\n������˼�-> ");
		scanf("%d", &price);
		getchar();
		printf("\n������ɱ�-> ");
		scanf("%d", &cost);
		getchar();
		newNode = (struct menu*)malloc(sizeof(struct menu));//�����µĽڵ�
		newNode->next = NULL;//�����˸�β�͸�ֵΪNULL
		//���½��Ĳ�Ʒ�ṹ�帳ֵ
		newNode->foodNum = foodNum;
		strcpy(newNode->foodName, foodName);
		newNode->price = price;
		newNode->cost = cost;

		newNode->next = menuHead;//ͷ�巨
		menuHead = newNode;
		showMenu(newNode, 1);//��ʾ����ӵĲ�Ʒ
		printf("��ӳɹ�\n");
		printf("�Ƿ������ӣ���y:����/n:������-> ");
		scanf("%c", &choice);
		getchar();
		
		choice = tolower(choice);//תΪСд��ĸ,����Ҳ֧��Y��N
	}
	saveMenuFile(menuHead);
	return menuHead;//���ؽ�����Ӳ������ͷ�ڵ�
}

//ɾ����Ʒ
struct menu* deleteMenu(struct menu* head)//�˺���һ��ֻɾ��һ���ڵ�
{
	struct menu* target;
	struct menu* oldNode;
	char confirm = 'n';
	//���ò�ѯ����queryMenu()�Ƚ��в�ѯ����
	target = queryMenu(head, &oldNode);
	if (target)//�����ѯ���˲�Ʒ�������ɾ������
	{
		showMenu(target, 1);//��ʾ��ѯ���Ĳ�Ʒ
		printf("ȷ��Ҫɾ����%s����(y:ȷ��/n:ȡ��)-> ", target->foodName);
		scanf("%c", &confirm);
		getchar();
		confirm = tolower(confirm);
		if (confirm == 'y')
		{
			if (target == head)//���ͷ�ڵ㼴Ϊ����ɾ���Ľڵ�
			{
				head = head->next;
				free(target);
			}
			else//��ͷ�ڵ�  
			{
				oldNode->next = target->next;//ɾ��target�ڵ�
				free(target);
			}
			printf("\nɾ���ɹ�!");
		}
		else
		{
			printf("\n����ȡ������");
		}
	}
	else
	{
		printf("\nδ��ѯ�������Ϣ!");
	}
	system("pause");
	saveMenuFile(head);
	return head;//����ɾ���������ͷ�ڵ�
}

//�޸Ĳ�Ʒ
struct menu* changeMenu(struct menu* head)
{
	struct menu* target;
	int foodNum;
	char foodName[30] = { 0 };
	int price;//��Ʒ�۸�
	int cost;
	char select = 'y';
	target = queryMenu(head, NULL);//�޸Ĺ����ȵ��ò�ѯ����
	if (target)//����ҵ����޸�
	{
		while (select == 'y')//����y������n����(�������·�)
		{
			system("cls");
			showMenu(target, 1);//��ʾ��ѯ���Ľ��
			LOOP1:
			printf("��ѡ������Ҫ�Ĺ���:\n�޸Ĳ˺�(1)/�޸Ĳ���(2)/�޸ļ۸�(3)/�޸ĳɱ�(4)/ȡ���޸�(n)\n");
			scanf("%c", &select);
			getchar();//���س��̵�����Ȼ��bug
			switch (select)
			{
				case '1':
					printf("�޸Ĳ˺�\n��Ҫ���ò˺��޸�Ϊ-> ");
					scanf("%d", &foodNum);
					getchar();
					target->foodNum = foodNum;
					break;
				case '2':
					printf("�޸Ĳ���\n��Ҫ�������޸�Ϊ-> ");
					scanf("%s", foodName);
					getchar();
					strcpy(target->foodName, foodName);
					break;
				case '3':
					printf("�޸ļ۸�\n��Ҫ���۸��޸�Ϊ-> ");
					scanf("%d", &price);
					getchar();
					target->price = price;
					break;
				case '4':
					printf("�޸ĳɱ�\n��Ҫ���ɱ��޸�Ϊ-> ");
					scanf("%d", &cost);
					getchar();
					target->cost = cost;
					break;
				case 'n':
					return head;
				default:
					printf("�Ƿ�������!\n");
					system("pause");
					goto LOOP1;
			}
			printf("�޸ĳɹ�!\n");
			showMenu(target, 1);
			system("pause");
			LOOP2:
			printf("�Ƿ�����޸�?/����(y)/����(n)-> ");
			scanf("%c", &select);
			getchar();
			
			if (select != 'y' && select != 'n')
			{
				printf("�Ƿ�������!\n");
				//system("pause");
				goto LOOP2;
			}
		}
	}
	else
	{
		printf("δ��ѯ�������Ϣ!\n");
	}

	saveMenuFile(head);
	system("pause");
	return head;
}

//����Ϊ������ӵ�ϸ��,������Ӳ�Ʒʱ����
int ifRepeatMenu(struct menu* head,int foodNum,char *foodName,int select)//�ж��Ƿ�˺Ż�����ظ�
{//select����Ϊ1Ϊ�жϲ˺ţ�Ϊ0Ϊ�жϲ���
	struct menu* temp;
	temp = head;
	if (select)//���˺�
	{
		while (temp)//��������
		{
			if (foodNum == temp->foodNum)
			{
				return 1;//����1��ʾ�ò˺��Դ���
			}
			temp = temp->next;
		}
	}
	else 
	{//������ͬ��
		while (temp)
		{
			if (!strcmp(temp->foodName, foodName))//strcmp()�������ַ�����ȷ���0
			{
				return 2;//����2��ʾ�ò����Դ���
			}
			temp = temp->next;
		}
	}
}

//����Ʒ���ղ˺��ź�������
void sortByNum(struct menu* menuHead)//ѡ������
{
	struct menu temp;
	struct menu* pointTemp_1, * pointTemp_2;
	pointTemp_1 = menuHead;
	while (pointTemp_1)//��������,ѡ������
	{
		pointTemp_2 = pointTemp_1->next;
		while (pointTemp_2)
		{
			if (pointTemp_1->foodNum > pointTemp_2->foodNum)//��һ�������򽻻�
			{
				temp = *pointTemp_1;
				*pointTemp_1 = *pointTemp_2;
				*pointTemp_2 = temp;
				pointTemp_2->next = pointTemp_1->next;//�������ڵ�next��ָ�򱣳ֲ���
				pointTemp_1->next = temp.next;
			}
			pointTemp_2 = pointTemp_2->next;//ǰ����һ���ڵ�
		}
		pointTemp_1 = pointTemp_1->next;//ǰ����һ���ڵ�
	}
}