#pragma once
struct menu {//�����Ʒ�ṹ��
	int foodNum;
	char foodName[30];
	int price;//�۸�
	int cost;//�ɱ�
	int dailySales;//������
	int dailyIncome;//�վ�����
	struct menu* next;
};

struct date {//��������
	int year;
	int month;
	int day;
};

struct orderForm {//���嶩���ṹ��
	int orderFormNum;
	int people;//����
	struct date formDate;//����
	int menu[50][2];//ÿ�ݶ�������ѡ�Ĳ�,һ����ά����menu[i][0]��˺�,menu[i][1]���Ӧ�˵�������
	int menuNum;//�˵�����
	int sumPrice;//�����ܼ�
	struct orderForm* next;
};