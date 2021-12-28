#include <stdio.h>
#include <Windows.h>
#include "dataType.h"
#include "orderManage.h"
#include "showAndFileOperation.h"

//����������
void sortBySales(struct menu* menuHead)
{
	struct menu temp;
	struct menu* pointTemp_1, *pointTemp_2;
	pointTemp_1 = menuHead;
	while (pointTemp_1)//��������,ѡ������
	{
		pointTemp_2 = pointTemp_1->next;
		while (pointTemp_2)
		{
			if (pointTemp_1->dailySales < pointTemp_2->dailySales)//��һ��С���򽻻�
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
//������������
void sortByIncome(struct menu* menuHead)
{
	struct menu temp;
	struct menu* pointTemp_1, * pointTemp_2;
	pointTemp_1 = menuHead;
	while (pointTemp_1)//��������,ѡ������
	{
		pointTemp_2 = pointTemp_1->next;
		while (pointTemp_2)
		{
			if (pointTemp_1->dailyIncome < pointTemp_2->dailyIncome)//��һ��С���򽻻�
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
//����Ʒ�е����������վ�������0
void clearSalesAndIncome(struct menu* menuHead)
{
	struct menu* temp = menuHead;
	while (temp)
	{
		temp->dailySales = 0;//����������ʼ��Ϊ0
		temp->dailyIncome = 0;//���վ������ʼ��Ϊ0
		temp = temp->next;
	}
}
//��Ʒ����ͳ��
void menuSaleAnalyse(struct orderForm* orderFormHead, struct menu* menuHead)
{
	struct date inputDate;
	int choice = 1;
	struct orderForm* temp;
	temp = orderFormHead;
	clearSalesAndIncome(menuHead);////����Ʒ�е����������վ�������0
	system("cls");
	printf("�����붩������(��ʽ:��/��/��)-> ");
	scanf("%d/%d/%d", &inputDate.year, &inputDate.month, &inputDate.day);
	getchar();
	system("cls");
	while (temp)
	{
		if (temp->formDate.year == inputDate.year
			&& temp->formDate.month == inputDate.month
			&& temp->formDate.day == inputDate.day)//��������������
		{
			for (int i = 0; i < temp->menuNum; i++)//ѭ�������еĲ˵�����
			{
				struct menu* target;
				//�������orderForm.h�е� searchMenu()����(�䷵��ֵΪstruct menu*) �����Ҷ�Ӧ�Ĳ�Ʒ
				target = searchMenu(menuHead, temp->menu[i][0]);//menu[][]��ά�����һ��Ϊ�˺ţ��ڶ���Ϊ��Ӧ�˺Ų˵�����
				target->dailySales += temp->menu[i][1];//��Ӧ��Ʒ����������
				target->dailyIncome = (target->price - target->cost) * target->dailySales;//�����վ�����
			}
		}
		temp = temp->next;
	}
	//��ʾ����ͳ�Ʒ�����Ĳ˵�
	printf("%d��%02d��%02d�յ��������\n", inputDate.year, inputDate.month, inputDate.day);
	showMenuSale(menuHead);
	printf("��ѡ��(1.������������/2.���վ���������/0.�˳�)-> ");
	scanf("%d", &choice);
	getchar();
	system("cls");
	while (1)
	{
		system("cls");
		if (choice == 1)
		{
			sortBySales(menuHead);
		}
		else if (choice == 2) {
			sortByIncome(menuHead);
		}
		else if (choice == 0) {
			return;
		}
		printf("%d��%02d��%02d�յ��������\n", inputDate.year, inputDate.month, inputDate.day);
		showMenuSale(menuHead);//��ʾ
		printf("��ѡ��(1.������������/2.���վ���������/0.�˳�)-> ");
		scanf("%d", &choice);
		getchar();
	}
}

//�����ж����е�sumPrice��0
void clearSumPrice(struct orderForm* orderFormHead)
{
	struct orderForm* temp = orderFormHead;
	while (temp)
	{
		temp->sumPrice = 0;
		temp = temp->next;
	}
}

//�������ж������ܼ�
void calculatePrice(struct orderForm* orderFormHead, struct menu* menuHead)//�������ж������ܼ�
{
	struct orderForm* temp = orderFormHead;
	struct menu* target;//���ҵ���Ŀ���Ʒ
	while (temp)
	{
		for (int i = 0; i < temp->menuNum; i++)
		{
			target = searchMenu(menuHead, temp->menu[i][0]);//���Ҷ�Ӧ�˺ŵĲ�
			if(target != NULL)
				temp->sumPrice += target->price * temp->menu[i][1];//����۸�
		}
		temp = temp->next;
	}
}

//�������ܼ�����
void sortBySumPrice(struct orderForm* orderFormHead)//����ֱ��copy�����sortByIncome()���� (>_<)
{
	struct orderForm temp;
	struct orderForm* pointTemp_1, * pointTemp_2;
	pointTemp_1 = orderFormHead;
	while (pointTemp_1)//��������,ѡ������
	{
		pointTemp_2 = pointTemp_1->next;
		while (pointTemp_2)
		{
			if (pointTemp_1->sumPrice < pointTemp_2->sumPrice)//��һ��С���򽻻�
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

//�������Ͳ���������
void sortByPeople(struct orderForm* orderFormHead)//copy�����
{
	struct orderForm temp;
	struct orderForm* pointTemp_1, * pointTemp_2;
	pointTemp_1 = orderFormHead;
	while (pointTemp_1)//��������,ѡ������
	{
		pointTemp_2 = pointTemp_1->next;
		while (pointTemp_2)
		{
			if (pointTemp_1->people < pointTemp_2->people)//��һ��С���򽻻�
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

//����ͳ��
void orderFormAnalyse(struct orderForm* orderFormHead, struct menu* menuHead)
{
	struct date inputDate;
	int choice = 1;
	struct orderForm* temp;
	temp = orderFormHead;
	system("cls");
	printf("�����붩������(��ʽ:��/��/��)-> ");
	scanf("%d/%d/%d", &inputDate.year, &inputDate.month, &inputDate.day);
	getchar();
	system("cls");
	clearSumPrice(orderFormHead);//�����ж������ܼ���0
	calculatePrice(orderFormHead, menuHead);//�������ж����ܼ�
	//��ʾ����ͳ�Ʒ�����Ĳ˵�
	printf("%d��%02d��%02d�յ��������\n", inputDate.year, inputDate.month, inputDate.day);
	showFormInfo(orderFormHead, menuHead, inputDate);//��ʾ��Ӧ�Ķ�����Ϣ
	system("pause");
	printf("��ѡ��(1.�������ܼ�����/2.���Ͳ���������/0.�˳�)-> ");
	scanf("%d", &choice);
	getchar();
	system("cls");
	while (1)
	{
		system("cls");
		if (choice == 1)
		{
			sortBySumPrice(orderFormHead);
		}
		else if (choice == 2) {
			sortByPeople(orderFormHead);
		}
		else if (choice == 0) {
			return;
		}
		printf("%d��%02d��%02d�յ��������\n", inputDate.year, inputDate.month, inputDate.day);
		showFormInfo(orderFormHead, menuHead, inputDate);//��ʾ
		printf("��ѡ��(1.�������ܼ�����/2.���Ͳ���������/0.�˳�)-> ");
		scanf("%d", &choice);
		getchar();
	}
}