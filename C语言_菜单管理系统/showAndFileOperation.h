#pragma once

void showMenu(struct menu* head, int oneOrAll);//��ʾ��Ʒ

void showHomePage();//��ʾϵͳ��ҳ

void showMenuManage();//��ʾ�˵�����ҳ��

void showOrderManage();//��ʾ�����������

void showAnalyse();//��ʾͳ�Ʒ�������

struct menu* readMenuFile(struct menu* head);//��ȡ�˵��ļ�����

void saveMenuFile(struct menu* head);//����˵�����

void showOrderForm(struct orderForm* orderFormHead, struct menu* menuHead, int oneOrAll);//��ʾ����

void saveOrderFormFile(struct orderForm* orderFormHead);//���涩������

struct menu* readOrderFormFile(struct orderForm* orderFormHead);//��ȡ�����ļ�����

void showMenuSale(struct menu* head);//ͳ�Ʒ����еĲ�Ʒ��ʾ

void showFormInfo(struct orderForm* orderFormHead, struct menu* menuHead, struct date inputDate);//ͳ�Ʒ����еĶ�����ʾ