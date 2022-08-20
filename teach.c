#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <unistd.h>

#define NAMEMAX 12                      //名字长度
#define SEXMAX 6                        //性别长度
#define PATH_2247_stu "2247/stu_message.txt" // 2247班学生信息文件的路径

FILE *stu_fp; //学生信息文件描述符


typedef struct student
{
  float Eng;
  float Math;
  float Chin;
  float Clang;
  float Sum;
  float Avg;
  char name[NAMEMAX];
  char sex[SEXMAX];
  int Id;
  struct student *next;
} student;

const int stu_size = sizeof(student); //结构体大小

//初始化节点
student *initNode()
{
  student *head = malloc(sizeof(student));
  if (head == NULL)
  {
    printf("erro：init malloc fail\n");
    return NULL;
  }

  head->next = NULL;
  head->Avg = 0;
  head->Chin = 0;
  head->Clang = 0;
  head->Eng = 0;
  head->Id = 0;
  head->Math = 0;
  strcpy(head->name, "\0");
  strcpy(head->sex, "\0");
  head->Sum = 0;

  return head;
}

//判断链表是否为空
bool isEmpty(student *head)
{
  return head->next == NULL;
}

//随机生成学生的数据
void createData(student *stu)
{
  if (stu == NULL)
    return;

  int sex = rand() % 2;
  if (sex == 0)
    strcpy(stu->sex, "female");
  else
    strcpy(stu->sex, "male");

  stu->Id = rand() % 100 + 20221000;

  stu->Chin = (float)(rand() % 51 + 50);
  stu->Math = (float)(rand() % 51 + 50);
  stu->Eng = (float)(rand() % 51 + 50);
  stu->Clang = (float)(rand() % 51 + 50);
  stu->Sum = stu->Chin + stu->Eng + stu->Math;
  stu->Avg = stu->Sum / 3;
}

//增加节点  只输入姓名
void insert_rand(student *head, char *name)
{
  student *p = head;
  student *new = malloc(sizeof(student));
  if (new == NULL)
  {
    printf("erro: insert fail\n");
    return;
  }

  strcpy(new->name, name);
  createData(new);

  while (p->next)
  {
    p = p->next;
  }
  p->next = new;
  new->next = NULL;
}

//增加节点  输入全部数据 尾插法
void insert_tail(student *head, char *name, int Id, char *sex, float Eng, float Math, float Chin, float Clang)
{
  student *new = malloc(sizeof(student));
  if (new == NULL)
  {
    printf("erro: insert fail\n");
    return;
  }

  new->Chin = Chin;
  new->Clang = Clang;
  new->Eng = Eng;
  //printf("Id: %d\n", Id);
  new->Id = Id;
  new->Math = Math;
  strcpy(new->name, name);
  strcpy(new->sex, sex);
  new->Sum = Chin + Eng + Math;
  new->Avg = new->Sum / 3;

  while (head->next)
  {
    head = head->next;
  }
  head->next = new;
  new->next = NULL;
}

//显示全链表
void display(student *head)
{
  if (head == NULL || isEmpty(head))
    return;

  student *p = head;
  p = p->next;

  printf("姓名   学号     性别     语文  数学  英语 c语言  总分  平均分\n");

  for (int i = 1; p != NULL; p = p->next, i++)
  {
    printf("%-6s%-8d  %-6s    %-3g   %-3g   %-3g  %-3g   %-3g   %-3g\n", p->name, p->Id, p->sex, p->Chin, p->Math, p->Eng, p->Clang, p->Sum, p->Avg);
  }
}

//显示节点
void displayNode(student *head)
{
  if (head == NULL)
    return;

  student *p = head;

  printf("姓名    学号    性别     语文  数学  英语 c语言  总分  平均分\n");
  printf("%-6s%-8d  %-3s    %-3g   %-3g   %-3g   %-3g   %-3g   %-3g\n", p->name, p->Id, p->sex, p->Chin, p->Math, p->Eng, p->Clang, p->Sum, p->Avg);
}

//查找节点 根据学号查找 返回所查找节点的上一个节点
student *search_prev(student *head, int id)
{
  if (head == NULL || isEmpty(head))
    return NULL;

  student *p = head;
  student *prev = p;
  p = p->next;

  while (p != NULL)
  {
    if (p->Id == id)
    {
      break;
    }
    p = p->next;
    prev = prev->next;
  }
  if (p == NULL)
    return NULL;

  return prev;
}

//删除节点 根据学号删除
student *Remove(student *head, int id)
{
  if (head == NULL || isEmpty(head))
    return NULL;

  student *tmp = NULL;
  student *prev = search_prev(head, id);
  if (prev == NULL)
    return NULL;

  tmp = prev->next;
  prev->next = prev->next->next;
  tmp->next = NULL;

  return tmp;
}

//将链表的数据写入文件 stu_message.txt 中
void write_file(student *head)
{
  if (isEmpty(head) || head == NULL)
    return;
  int ret = 0;
  student *p = head;

  //文件在main函数打开
  //将光标移到最后
  fseek(stu_fp, 0, SEEK_END);
  p = p->next;
  while (p)
  {
    // stu_size 即结构体大小
    ret = fwrite(p, stu_size,1,stu_fp);
    if (ret != 1)
    {
      printf("erro: stu_message.txt write fail\n");
      return;
    }

    p = p->next;
  }

  return;
}

//将文件的数据读到链表
void read_file(student *head)
{
  if (head == NULL)
    return;

  student *p = head;
  student *tmp = NULL;
  int ret = 1;

  //将光标移到开头
  fseek(stu_fp, 0, SEEK_SET);
  while (1)
  {
    tmp = initNode();
    ret = fread(tmp, stu_size,1,stu_fp);
    if(ret < 1)
    {
      break;
    }
    p->next = tmp;
    p = p->next;
  }
  free(tmp);

  return;
}

//释放链表
void destroy(student *head)
{
  if (isEmpty(head) || head == NULL)
    return;

  student *p = head->next;
  student *tmp;
  while (p)
  {
    tmp = p;
    p = p->next;
    tmp->next = NULL;
    free(tmp);
  }
  head->next = NULL;

  return;
}

void teach_insert_function(student *head)
{
  student *tmp;
  char name[NAMEMAX] = {0};
  int id = 0;
  char sex[SEXMAX] = {0};
  float Eng, Math, Chin, Clang;
  char ch;
  while (1)
  {
    printf("1-随机插入  2-手写插入  3-查看插入记录   4-删除插入  5-保存插入  0-退出\n");
    while (getchar() != '\n');
    ch = getchar();
    switch (ch)
    {
    case '1':
      printf("请输入所添加的学生的姓名: ");
      scanf("%s", name);
      insert_rand(head, name);
      printf("【插入成功】\n");
      break;

    case '2':
      printf("请输入所添加的学生的姓名: ");
      scanf("%s", name);
      printf("请输入 %s 的学号: ", name);
      scanf("%d", &id);
      printf("请输入 %s 的性别: ", name);
      scanf("%s", sex);
      printf("请输入 %s 的语文成绩: ", name);
      scanf("%f", &Chin);
      printf("请输入 %s 的英语成绩: ", name);
      scanf("%f", &Eng);
      printf("请输入 %s 的数学成绩: ", name);
      scanf("%f", &Math);
      printf("请输入 %s 的c语言成绩: ", name);
      scanf("%f", &Clang);
      insert_tail(head, name, id, sex, Eng, Math, Chin, Clang);
      printf("【插入成功】\n");
      break;

    case '3':
      display(head);
      break;

    case '4':
    G:
      printf("请输入所删除的学生的学号: ");
      scanf("%d", &id);
      if (id == 0)
        break;
      tmp = Remove(head, id);
      if (tmp != NULL)
      {
        free(tmp);
        printf("【删除成功】\n");
      }
      else
      {
        printf("erro: 未查找到学号为 %d 的学生，请检查是否输入有误!\n", id);
        printf("[重新输入请按“1”, 任意键退出]\n");
        while (getchar() != '\n');
        char ch = getchar();
        if (ch == '1')
          goto G;
      }
      break;

    case '5':
      //将链表的数据写入文件 stu_message.txt 中
      write_file(head);
      //写入成功后，释放链表
      destroy(head);
      printf("【保存成功】\n");
      break;

    case '0':
      if (!isEmpty(head)) //如果链表不为空，即还未保存，则提醒保存
      {
        printf("\t【您还未保存插入记录!】\n");
        printf("1-保存并退出  2-取消退出  0-直接退出\n");
        while (getchar() != '\n');
        char ch = getchar();
        switch (ch)
        {
        case '1':
          write_file(head);
          destroy(head); //写入成功后，释放链表
          printf("【保存成功】\n");
          return;

        case '0':
          destroy(head); //不写入文件，直接释放链表
          return;

        default:
          break;
        }
      }
      else
      {
        printf("是否确定退出？\n");
        printf("0-是   1-否\n");
        while (getchar() != '\n')
          ;
        ch = getchar();

        if (ch == '0')
        {
          printf("【退出成功】\n");
          return;
        }
      }
      break;
    }
  }
}

//教师功能页面
void teach_function()
{
  student *head = initNode();
  student *tmp;
  char name[NAMEMAX];
  int id = 0;
  char sex[SEXMAX];
  float Eng, Math, Chin, Clang;
  char ch;

  while (1)
  {
    printf("\n*******教师功能页面*******\n");
    printf("\na-插入  d-删除  c-显示  f-查找  s-排序  0-退出\n");
    ch = getchar();
    switch (ch)
    {
    case 'a':
      destroy(head); //插入之前先将链表释放
      teach_insert_function(head);
       break;
    case 'd':
      /* G:
          printf("请输入所删除的学生的学号: ");
          scanf("%d", &id);
          if (id == 0)
            break;
          tmp = Remove(head, id);
          if (tmp != NULL)
          {
            free(tmp);
            printf("删除成功！\n");
          }
          else
          {
            printf("erro: 未查找到学号为 %d 的学生，请检查是否输入有误!\n", id);
            goto G;
          }*/
      break;

    case 'c':
      //将文件的数据读到链表
      read_file(head);
      display(head);
      break;

    case 'f':
      /* L:
         printf("请选择你要查找的方式（i-学号 n-名字）：");
         getchar();
         ch = getchar();
         switch (ch)
         {
         case 'i':
           printf("请输入所查找的学生的学号: ");
           scanf("%d", &id);
           tmp = NULL;
           tmp = search_id(head, id);
           if (tmp == NULL)
           {
             printf("erro: 未查找到学号为 %d 的学生，请检查是否输入有误!\n", id);
           }
           display_node(tmp);*/
      break;
    case 'n':
      /*  printf("请输入所查找的学生的姓名: ");
        scanf("%s", name);
        tmp = NULL;
        tmp = search_name(head, name);
        if (tmp == NULL)
        {
          printf("erro: 未查找到姓名为 %s 的学生，请检查是否输入有误!\n", name);
        }
        display_node(tmp);
        break;
      case '0':
        break;
      default:
        printf("输入错误，重新输入\n");
        goto L;
      }*/
      break;

    case 's':
      /*     printf("请选择你要排序的对象（i-学号  s-总分 c-语文 m-数学 e-英语）：");
           getchar();
           ch = getchar();
           switch (ch)
           {
           case 's':
           case 'e':
           case 'c':
           case 'm':
           case 'i':
             Sort(head, ch);
             display(head);
             break;
           default:
             printf("输入错误，重新输入\n");
           }
           break;

         case '0':
           exit(1);
           break;

         default:
           printf("输入错误，重新输入\n");*/
      break;
    }
    while (getchar() != '\n');
  }

  destroy(head);
  free(head);
  return;
}

int main()
{
  srand((int)time(NULL));

  //打开存放学生信息的文件，如果还没创建的话就创建,文件在path路径下
  stu_fp = fopen("2247/stu_message.txt","a+");
  if (stu_fp == NULL)
  {
    printf("erro: stu_message.txt open fail\n");
    return 0;
  }

  teach_function();

  fclose(stu_fp);
  return 0;
} 