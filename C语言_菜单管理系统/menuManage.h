#pragma once
struct menu* queryMenu(struct menu* head, struct menu** oldNode);//��ѯ��Ʒ

struct menu* addMenu(struct menu* head);//���

struct menu* deleteMenu(struct menu* head);//ɾ����Ʒ

struct menu* changeMenu(struct menu* head);//�޸Ĳ�Ʒ

int ifRepeatMenu(struct menu* head, int foodNum, char* foodName, int select);//�ж��Ƿ�˺Ż�����ظ�

void sortByNum(struct menu* menuHead);//����Ʒ���ղ˺��ź�������
