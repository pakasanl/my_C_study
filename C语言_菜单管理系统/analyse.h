#pragma once
//����������
void sortBySales(struct menu* menuHead);

//������������
void sortByIncome(struct menu* menuHead);

//��Ʒ����ͳ��
void menuSaleAnalyse(struct orderForm* orderFormHead, struct menu* menuHead);

//����Ʒ�е����������վ�������0
void clearSalesAndIncome(struct menu* menuHead);

//�������ж������ܼ�
void calculatePrice(struct orderForm* orderFormHead, struct menu* menuHead);

//�����ж����е�sumPrice��0
void clearSumPrice(struct orderForm* orderFormHead);

//�������ܼ�����
void sortBySumPrice(struct orderForm* orderFormHead);

//�������Ͳ���������
void sortByPeople(struct orderForm* orderFormHead);

//����ͳ��
void orderFormAnalyse(struct orderForm* orderFormHead, struct menu* menuHead);
