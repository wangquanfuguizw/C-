#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define OK 1
#define ERROR 0

int SUM = 0;
typedef struct
{
    char Cus_Name[10];  //����
    char Cus_Sex[4];    //�Ա�
    int Cus_Age;        //����
    char Cus_ID[19];    //���֤
    char leaveTime[10]; //�뿪ʱ��
}Customer;
typedef struct
{
    int Room_type;     //���� (1���˴� 2˫�˴� 3���˴� 4������ 5������)
    Customer people[5];    //ס��
    int flag;           //�ж��Ƿ����� 0�� 1��
    int number;         //��ס����
}Room;
typedef struct
{
    Room data;           //����������
    struct LNode *next;  //����ָ����
    int Room_num;          //����
}LNode, *LinkList;


int index();                              //��ҳ�溯��
void choose(LinkList L, int i);           //ѡ����
int InitList(LinkList *L);                //��ʼ������
int ListInsert(LinkList L,int i,int num); //������
void creatHotel(LinkList L);              //������������
void printLink(LinkList L);               //���������Ϣ
int checkRoom(LinkList p,int num, int i); //�ȽϷ����
void enterMessage(LinkList p, int j);     //¼����Ϣ��ס����Ϣ��
void Inmessage(LinkList L);               //¼����Ϣ�����ţ�
void printFile();                         //����ļ�
void printMess(LinkList p, int j);        //�����Ϣ��ס����Ϣ��
void printMessage(LinkList p);            //�����Ϣ�����ͣ�
void searchName(LinkList L);              //��������
void searchNum(LinkList L);               //��������
void searchID(LinkList L);                //���֤������
void typeRoom(LinkList L);                //���͸�ֵ
void leaveRoom(LinkList L);               //�˷�


int InitList(LinkList *L)
{
    *L = (LinkList*)malloc(sizeof(LNode));
    (*L)->next = NULL;
    return OK;
}
int ListInsert(LinkList L,int i,int num)
{
    LinkList p=L,s;
    int j=0;
    while(p&&(j<i-1))
    {
        p=(LinkList)p->next;
        ++j;
    }
    if(!p||j>i-1)
    {
        return ERROR;
    }
    else
    {
        s=(LinkList)malloc((sizeof(LNode)));
        s->Room_num = num;
        s->next=p->next;
        p->next=s;
    }
    return OK;
}
void creatHotel(LinkList L)
{
    int i, j, sum, room_sum = 1,temp;

    for(i = 100; i <= 500; i += 100)
    {
        for(j = 0; j < 10; j++)
        {
            sum = i + j;
            ListInsert(L, room_sum, sum);
            room_sum++;
        }
    }
}
void printLink(LinkList L)
{
    system("cls");
    LNode *p = L->next;
    int j = 1;
    printf("\t");
    while(1)
    {
        printf("|%d| ",p->Room_num);
        switch(p->data.Room_type){
     case 1:
         printf("\t���˷�");
        break;
     case 2:
         printf("\t˫�˷�");
        break;
     case 3:
         printf("\t���˷�");
        break;
     case 4:
         printf("\t������");
        break;
     case 5:
         printf("\t������");
        break;
        }
        if(p->data.flag == 1)
        {
            printf("\t��ס");
        }
        else {
            printf("\t�շ�");
        }
        if(j % 4 == 0) printf("\n\t");
        else printf("\t");
        if(p->Room_num == 509) break;
        p = p->next;
        j++;
    }
    printf("\n\t");
}
int checkRoom(LinkList p,int num, int i)
{
    if(p->Room_num == num) return OK;
    else {
        if(i > 49) return ERROR;
        else {
                p = p->next;
                i++;
                checkRoom(p, num, i);
        }
    }
}
void enterMessage(LinkList p, int j)
{
    int i, temp;
    time_t t;
    SUM += j * 60;
    struct tm * lt;
    time (&t);
    lt = localtime(&t);
    FILE * fp;
    fp = fopen("customers.txt", "a+");
    for(i = 1; i <= j; i++)
    {
        printf("\t������ס����Ϣ��\n");
        printf("\t������");
        scanf("%s", p->data.people[i].Cus_Name);
        printf("\t�Ա�: ");
        scanf("%s", p->data.people[i].Cus_Sex);
        printf("\t���䣺");
        scanf("%d", &p->data.people[i].Cus_Age);
        printf("\t���֤��");
        scanf("%s", p->data.people[i].Cus_ID);
        p->data.number = i;
        if(fp == NULL) printf("\t��ʧ�ܣ�����\n");
        else{
            fprintf(fp,"%d\t%s\t%s\t%d\t%s\t%d/%d/%d %d:%d\n", p->Room_num, p->data.people[i].Cus_Name, p->data.people[i].Cus_Sex, p->data.people[i].Cus_Age, p->data.people[i].Cus_ID,lt->tm_year+1900,lt->tm_mon+1,lt->tm_mday,lt->tm_hour,lt->tm_min);

        }
        if(i < j)
        {
            printf("\t�Ƿ����������һλס����Ϣ��(1->�� || 0->��)\n\t");
            scanf("%d", &temp);
            if(temp == 0) break;
        }
    }
    fclose(fp);
}
void Inmessage(LinkList L)
{
    system("cls");
    int num, n, a, b, i;
    LinkList p = L;
    printf("\t������ס����Ϣ��\n");
    printf("\t���ţ�");
    scanf("%d",&num);
    n = checkRoom(p, num, 0);
    if(n == 0)
    {
        printf("\t�÷���Ų����ڣ����������룡����\n\t");
        system("pause");
    }
    else {
        a = num / 100 - 1;
        b = num % 10;
        num = 10 * a + b;
        for(i = 0; i <= num; i++)
        {
            p = p->next;
        }
        if(p->data.flag == 1)
        {
            printf("\t�÷�������ס�ͣ��������������룡����\n\t");
            system("pause");
        }
        else
        {
            switch(p->data.Room_type) {
        case 1:
            printf("\t�÷�Ϊ���˷����ɹ�һ��ס�;�ס������\n");
            enterMessage(p,1);
            p->data.flag = 1;
            break;
        case 2:
            printf("\t�÷�Ϊ˫�˷����ɹ�����ס�;�ס������\n");
            enterMessage(p,2);
            p->data.flag = 1;
            break;
        case 3:
            printf("\t�÷�Ϊ���˷����ɹ�����ס�;�ס������\n");
            enterMessage(p,3);
            p->data.flag = 1;
            break;
        case 4:
            printf("\t�÷�Ϊ���������ɹ�����ס�;�ס������\n");
            enterMessage(p,4);
            p->data.flag = 1;
            break;
        case 5:
            printf("\t�÷�Ϊ���������ɹ�����ס�;�ס������\n");
            enterMessage(p,5);
            p->data.flag = 1;
            break;
            }
        }
    }
}
void printFile()
{
    FILE * fp;
    char s[80];
    fp = fopen("customers.txt","r");
    if(fp == NULL) printf("��ʧ�ܣ�����\n");
    else{
        while(!feof(fp))
        {
            memset(s, 0, sizeof(s));
            fgets(s, sizeof(s), fp);
            printf("\t%s\n", s);
        }
    }
    fclose(fp);
}
void printMess(LinkList p, int j)
{
    int i;
    printf("\t���ţ�%d", p->Room_num);
    for(i = 1; i <= j; i++)
    {
        if(i >= 2)
        {
            printf("\t\t\t\t������%s", p->data.people[i].Cus_Name);
            printf("\t�Ա�: %s", p->data.people[i].Cus_Sex);
            printf("\t���䣺%d", p->data.people[i].Cus_Age);
            printf("\t���֤��%s\n", p->data.people[i].Cus_ID);
        }
        else
        {
            printf("\t������%s", p->data.people[i].Cus_Name);
            printf("\t�Ա�: %s", p->data.people[i].Cus_Sex);
            printf("\t���䣺%d", p->data.people[i].Cus_Age);
            printf("\t���֤��%s\n", p->data.people[i].Cus_ID);
        }
    }
}
void printMessage(LinkList p)
{
    switch(p->data.Room_type){
     case 1:
         printf("\t���˷�");
         printMess(p, p->data.number);
        break;
     case 2:
         printf("\t˫�˷�");
         printMess(p, p->data.number);
        break;
     case 3:
         printf("\t���˷�");
         printMess(p, p->data.number);
        break;
     case 4:
         printf("\t������");
         printMess(p, p->data.number);
        break;
     case 5:
         printf("\t������");
         printMess(p, p->data.number);
        break;
    }
}
void searchName(LinkList L)
{
    LinkList p = L;
    char name[10];
    printf("\t������������");
    scanf("%s", &name);
    int i, j = 0, m = 1;
    while(1)
    {
        if(p->data.flag == 1)
        {
            for(i = 1; i <= p->data.number; i++)
            {
                if(strcmp(p->data.people[i].Cus_Name, name) == 0)
                {
                    if(m == 1) printf("\t���ҳɹ�������\n");
                    printf("\t%s", p->data.people[i].Cus_Name);
                    printf("\t%s", p->data.people[i].Cus_Sex);
                    printf("\t%d", p->data.people[i].Cus_Age);
                    printf("\t%s", p->data.people[i].Cus_ID);
                    printf("\t%d\n", p->Room_num);
                    m++;
                }
            }
        }
        if(j > 49) break;
        j++;
        p = p->next;
    }
    if(m == 1)
    {
        printf("\t����ʧ�ܣ�����\n\t");
        system("pause");
    }
    else{
        printf("\t");
        system("pause");
    }
}
void searchNum(LinkList L)
{
    LinkList p = L;
    int num, i, m = 1;
    printf("\t�����뷿�ţ�");
    scanf("%d", &num);
    while(1)
    {
        if(p->Room_num == num && p->data.flag == 1)
        {
            printf("\t���ҳɹ�������\n");
            for(i = 1; i <= p->data.number; i++)
            {
                printf("\t%s", p->data.people[i].Cus_Name);
                printf("\t%s", p->data.people[i].Cus_Sex);
                printf("\t%d", p->data.people[i].Cus_Age);
                printf("\t%s", p->data.people[i].Cus_ID);
                printf("\t%d\n", p->Room_num);
            }
            m++;
            printf("\t");
            system("pause");
            break;
        }
        else{
            if(p->Room_num == 509) break;
            p = p->next;
        }
    }
    if(m == 1)
    {
        printf("\t�÷�����ס�ͣ�����ʧ�ܣ�����\n\t");
        system("pause");
    }
}
void searchID(LinkList L)
{
    LinkList p = L;
    char ID[19];
    printf("\t���������֤�ţ�");
    scanf("%s", &ID);
    int i, j = 0, m = 1;
    while(1)
    {
        if(p->data.flag == 1)
        {
            for(i = 1; i <= p->data.number; i++)
            {
                if(strcmp(p->data.people[i].Cus_ID, ID) == 0)
                {
                    if(m = 1) printf("\t���ҳɹ�������\n");
                    printf("\t%s", p->data.people[i].Cus_Name);
                    printf("\t%s", p->data.people[i].Cus_Sex);
                    printf("\t%d", p->data.people[i].Cus_Age);
                    printf("\t%s", p->data.people[i].Cus_ID);
                    printf("\t%d\n", p->Room_num);
                    m++;
                }
            }
        }
        if(j > 49) break;
        j++;
        p = p->next;
    }
    if(m == 1)
    {
        printf("\t����ʧ�ܣ�����\n\t");
        system("pause");
    }
    else{
        printf("\t");
        system("pause");
    }
}
void typeRoom(LinkList L)
{
    int i, a;
    LinkList p = L;
    for(i = 0; i <= 50; i++)
    {
        a = p->Room_num / 100;
        p->data.Room_type = a;
        p = p->next;
    }
}
void leaveRoom(LinkList L)
{
    int num, n, a, b, i;
    LinkList p = L;
    printf("\t�����뷿���:");
    scanf("%d", &num);
    n = checkRoom(p, num, 0);
    if(n == 0)
    {
        printf("\t�÷���Ų����ڣ����������룡����\n\t");
        system("pause");
    }
    else{
        a = num / 100 - 1;
        b = num % 10;
        num = 10 * a + b;
        for(i = 0; i <= num; i++)
        {
            p = p->next;
        }
        if(p->data.flag == 0)
        {
            printf("\t��ǰ���䲢û��ס�ͣ�����\n\t");
            system("pause");
        }
        else{
            p->data.flag = 0;
            printf("\t�˷��ɹ�������\n\t");
            system("pause");
        }
    }
}
int index()
{
    int i,temp;
    system("cls");
    system("color F0");
    printf("\t*******************************************************************************************************\n");
    printf("\t***************************************                     *******************************************\n");
    printf("\t***************************************   ���׿ͷ�����ϵͳ  ************************************* �� **\n");
    printf("\t***************************************                     ************************************* �� **\n");
    printf("\t*************************************************************************************************  ��**\n");
    printf("\t********************                                                                ************* �� **\n");
    printf("\t********************         ��ϵͳ�ܼ�ʵ�ֶԿ�ջ��ס��������й���               ************* �� **\n");
    printf("\t********************                                                                *******************\n");
    printf("\t*******************************************************************************************************\n");
    printf("\t*******************************************************************************************************\n\n");
    printf("\t��ʵ�ֹ��ܣ�\n");
    printf("\t1.ס����Ϣ¼��\n");
    printf("\t2.ס����Ϣ����\n");
    printf("\t3..�ͷ���Ϣ�鿴\n");
    printf("\t4.ס���˷�\n");
    printf("\t5.ͳ��\n");
    printf("\t6.�˳�\n");
    printf("\t����������Ҫʵ�ֵĹ��ܶ�Ӧ����ţ�");
    scanf("%d", &i);
    return i;
}
void choose(LinkList L, int i)
{
    int temp;
    if(i != 1 && i != 2 && i != 3 && i != 4 && i != 5 && i != 6)
    {
        printf("\t����ֵ��Ч���������������룡����\n\t");
        system("pause");
    }
    else{
    switch(i)
    {
    case 1:
        Inmessage(L);
        break;
    case 2:
        system("cls");
        printf("\t��ѡ����ҷ�ʽ��\n");
        printf("\t1.��������\n\t2.�����š�\n\t3.�����֤��\n\t");
        printf("��������ţ�");
        scanf("%d",&temp);
        if(temp == 1)
        {
            searchName(L);
        }
        else if(temp == 2)
        {
            searchNum(L);
        }
        else if(temp == 3)
        {
            searchID(L);
        }
        else
        {
           printf("\t����ֵ��Ч������");
           system("pause");
        }
        break;
    case 3:
        printLink(L);
        printf("�Ƿ���Ҫ�鿴��ϸ��Ϣ��(1->��||0->��)");
        scanf("%d", &temp);
        if(temp == 1)
        {
            while(L)
            {
                if(L->data.flag == 1)
                {
                    printMessage(L);
                    temp++;
                }
                L = L->next;
            }
            if(temp == 1)
                printf("\t����ס��Ϣ������\n\t");
        }
        printf("\t");
        system("pause");
        break;
    case 4:
        leaveRoom(L);
        break;
    case 5:
        printf("\t1.�鿴��ʷ��¼\n");
        printf("\t2.�鿴��ǰ�������\n");
        printf("\t��������ţ�");
        scanf("%d", &temp);
        if(temp == 1) printFile();
        else if(temp == 2) printf("\t��ǰ����Ϊ��%dԪ", SUM);
        else printf("\t������Ŵ��󣡣���");
        printf("\n\t");
        system("pause");
        break;
    case 6:
        printf("\n");
        printf("\t**************************\n");
        printf("\t*******��ӭ�´�ʹ��*******\n");
        printf("\t**************************\n");
        exit(0);
        break;
    }
   }
}

int main()
{
    int i;
    LinkList L;
    InitList(&L);
    creatHotel(&L);
    typeRoom(&L);
    while(1)
    {
        i = index();
        choose(&L, i);
    }
    return 0;
}
