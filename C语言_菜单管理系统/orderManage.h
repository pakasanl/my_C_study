#pragma once
//��ѯ����
void queryOrderForm(struct orderForm* orderFormHead,struct menu* menuHead);

//��Ӷ���
struct orderForm* addOrderForm(struct orderForm* orderFormHead, struct menu* menuHead);

//ɾ������
struct orderForm* deleteOrderForm(struct orderForm* orderFormHead, struct menu* menuHead);

//�޸Ķ���
struct orderForm* changeOrderForm(struct orderForm* orderFormHead, struct menu* menuHead);

//�Բ˵��ļ򵥲�ѯ
struct menu* searchMenu(struct menu* menuHead, int foodNum);

//�����Ų���
int ifRepeatOrder(struct orderForm* orderFormHead, int orderNum);