#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define OK 1
#define ERROR 0

int SUM = 0;
typedef struct
{
    char Cus_Name[10];  //姓名
    char Cus_Sex[4];    //性别
    int Cus_Age;        //年龄
    char Cus_ID[19];    //身份证
    char leaveTime[10]; //离开时间
}Customer;
typedef struct
{
    int Room_type;     //房型 (1单人床 2双人床 3三人床 4海景房 5豪华房)
    Customer people[5];    //住客
    int flag;           //判定是否有人 0无 1有
    int number;         //居住人数
}Room;
typedef struct
{
    Room data;           //结点的数据域
    struct LNode *next;  //结点的指针域
    int Room_num;          //房号
}LNode, *LinkList;


int index();                              //主页面函数
void choose(LinkList L, int i);           //选择函数
int InitList(LinkList *L);                //初始化链表
int ListInsert(LinkList L,int i,int num); //插入结点
void creatHotel(LinkList L);              //创建房间链表
void printLink(LinkList L);               //输出房间信息
int checkRoom(LinkList p,int num, int i); //比较房间号
void enterMessage(LinkList p, int j);     //录入信息（住客信息）
void Inmessage(LinkList L);               //录入信息（房号）
void printFile();                         //输出文件
void printMess(LinkList p, int j);        //输出信息（住客信息）
void printMessage(LinkList p);            //输出信息（房型）
void searchName(LinkList L);              //姓名搜索
void searchNum(LinkList L);               //房号搜索
void searchID(LinkList L);                //身份证号搜索
void typeRoom(LinkList L);                //房型赋值
void leaveRoom(LinkList L);               //退房


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
         printf("\t单人房");
        break;
     case 2:
         printf("\t双人房");
        break;
     case 3:
         printf("\t三人房");
        break;
     case 4:
         printf("\t海景房");
        break;
     case 5:
         printf("\t豪华房");
        break;
        }
        if(p->data.flag == 1)
        {
            printf("\t已住");
        }
        else {
            printf("\t空房");
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
        printf("\t请输入住客信息：\n");
        printf("\t姓名：");
        scanf("%s", p->data.people[i].Cus_Name);
        printf("\t性别: ");
        scanf("%s", p->data.people[i].Cus_Sex);
        printf("\t年龄：");
        scanf("%d", &p->data.people[i].Cus_Age);
        printf("\t身份证：");
        scanf("%s", p->data.people[i].Cus_ID);
        p->data.number = i;
        if(fp == NULL) printf("\t打开失败！！！\n");
        else{
            fprintf(fp,"%d\t%s\t%s\t%d\t%s\t%d/%d/%d %d:%d\n", p->Room_num, p->data.people[i].Cus_Name, p->data.people[i].Cus_Sex, p->data.people[i].Cus_Age, p->data.people[i].Cus_ID,lt->tm_year+1900,lt->tm_mon+1,lt->tm_mday,lt->tm_hour,lt->tm_min);

        }
        if(i < j)
        {
            printf("\t是否继续输入下一位住客信息？(1->是 || 0->否)\n\t");
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
    printf("\t请输入住客信息：\n");
    printf("\t房号：");
    scanf("%d",&num);
    n = checkRoom(p, num, 0);
    if(n == 0)
    {
        printf("\t该房间号不存在！请重新输入！！！\n\t");
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
            printf("\t该房间已有住客！！！请重新输入！！！\n\t");
            system("pause");
        }
        else
        {
            switch(p->data.Room_type) {
        case 1:
            printf("\t该房为单人房，可供一名住客居住！！！\n");
            enterMessage(p,1);
            p->data.flag = 1;
            break;
        case 2:
            printf("\t该房为双人房，可供两名住客居住！！！\n");
            enterMessage(p,2);
            p->data.flag = 1;
            break;
        case 3:
            printf("\t该房为三人房，可供三名住客居住！！！\n");
            enterMessage(p,3);
            p->data.flag = 1;
            break;
        case 4:
            printf("\t该房为海景房，可供四名住客居住！！！\n");
            enterMessage(p,4);
            p->data.flag = 1;
            break;
        case 5:
            printf("\t该房为豪华房，可供五名住客居住！！！\n");
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
    if(fp == NULL) printf("打开失败！！！\n");
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
    printf("\t房号：%d", p->Room_num);
    for(i = 1; i <= j; i++)
    {
        if(i >= 2)
        {
            printf("\t\t\t\t姓名：%s", p->data.people[i].Cus_Name);
            printf("\t性别: %s", p->data.people[i].Cus_Sex);
            printf("\t年龄：%d", p->data.people[i].Cus_Age);
            printf("\t身份证：%s\n", p->data.people[i].Cus_ID);
        }
        else
        {
            printf("\t姓名：%s", p->data.people[i].Cus_Name);
            printf("\t性别: %s", p->data.people[i].Cus_Sex);
            printf("\t年龄：%d", p->data.people[i].Cus_Age);
            printf("\t身份证：%s\n", p->data.people[i].Cus_ID);
        }
    }
}
void printMessage(LinkList p)
{
    switch(p->data.Room_type){
     case 1:
         printf("\t单人房");
         printMess(p, p->data.number);
        break;
     case 2:
         printf("\t双人房");
         printMess(p, p->data.number);
        break;
     case 3:
         printf("\t三人房");
         printMess(p, p->data.number);
        break;
     case 4:
         printf("\t海景房");
         printMess(p, p->data.number);
        break;
     case 5:
         printf("\t豪华房");
         printMess(p, p->data.number);
        break;
    }
}
void searchName(LinkList L)
{
    LinkList p = L;
    char name[10];
    printf("\t请输入姓名：");
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
                    if(m == 1) printf("\t查找成功！！！\n");
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
        printf("\t查找失败！！！\n\t");
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
    printf("\t请输入房号：");
    scanf("%d", &num);
    while(1)
    {
        if(p->Room_num == num && p->data.flag == 1)
        {
            printf("\t查找成功！！！\n");
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
        printf("\t该房间无住客，查找失败！！！\n\t");
        system("pause");
    }
}
void searchID(LinkList L)
{
    LinkList p = L;
    char ID[19];
    printf("\t请输入身份证号：");
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
                    if(m = 1) printf("\t查找成功！！！\n");
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
        printf("\t查找失败！！！\n\t");
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
    printf("\t请输入房间号:");
    scanf("%d", &num);
    n = checkRoom(p, num, 0);
    if(n == 0)
    {
        printf("\t该房间号不存在！请重新输入！！！\n\t");
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
            printf("\t当前房间并没有住客！！！\n\t");
            system("pause");
        }
        else{
            p->data.flag = 0;
            printf("\t退房成功！！！\n\t");
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
    printf("\t***************************************   简易客房管理系统  ************************************* 作 **\n");
    printf("\t***************************************                     ************************************* 者 **\n");
    printf("\t*************************************************************************************************  ：**\n");
    printf("\t********************                                                                ************* 章 **\n");
    printf("\t********************         该系统能简单实现对客栈的住宿情况进行管理               ************* 旺 **\n");
    printf("\t********************                                                                *******************\n");
    printf("\t*******************************************************************************************************\n");
    printf("\t*******************************************************************************************************\n\n");
    printf("\t可实现功能：\n");
    printf("\t1.住客信息录入\n");
    printf("\t2.住客信息查找\n");
    printf("\t3..客房信息查看\n");
    printf("\t4.住客退房\n");
    printf("\t5.统计\n");
    printf("\t6.退出\n");
    printf("\t请输入您想要实现的功能对应的序号：");
    scanf("%d", &i);
    return i;
}
void choose(LinkList L, int i)
{
    int temp;
    if(i != 1 && i != 2 && i != 3 && i != 4 && i != 5 && i != 6)
    {
        printf("\t输入值无效！！！请重新输入！！！\n\t");
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
        printf("\t请选择查找方式：\n");
        printf("\t1.【姓名】\n\t2.【房号】\n\t3.【身份证】\n\t");
        printf("请输入序号：");
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
           printf("\t输入值无效！！！");
           system("pause");
        }
        break;
    case 3:
        printLink(L);
        printf("是否需要查看详细信息？(1->是||0->否)");
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
                printf("\t无入住信息！！！\n\t");
        }
        printf("\t");
        system("pause");
        break;
    case 4:
        leaveRoom(L);
        break;
    case 5:
        printf("\t1.查看历史记录\n");
        printf("\t2.查看当前收益情况\n");
        printf("\t请输入序号：");
        scanf("%d", &temp);
        if(temp == 1) printFile();
        else if(temp == 2) printf("\t当前收益为：%d元", SUM);
        else printf("\t输入序号错误！！！");
        printf("\n\t");
        system("pause");
        break;
    case 6:
        printf("\n");
        printf("\t**************************\n");
        printf("\t*******欢迎下次使用*******\n");
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
