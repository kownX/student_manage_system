#include "teach_function.h"
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
  // printf("Id: %d\n", Id);
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

//显示节点
void displayNode(student *head)
{
  if (head == NULL)
    return;

  student *p = head;

  printf("姓名    学号    性别     语文  数学  英语 c语言  总分  平均分\n");
  printf("%-6s%-8d  %-3s    %-3g   %-3g   %-3g   %-3g   %-3g   %-3g\n", p->name, p->Id, p->sex, p->Chin, p->Math, p->Eng, p->Clang, p->Sum, p->Avg);
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

student *Sort(student *head, char ch)
{
  if (isEmpty(head) || head == NULL)
    return NULL;

  student *p = head;
  //设置新链表头节点
  student *newhead = initNode();
  if (newhead == NULL)
  {
    printf("malloc fail\n");
    return NULL;
  }

  while (p)
  {
    student *cur = newhead->next;
    student *pre = newhead;
    switch (ch)
    {
    case 'l':
      while (cur && p->Clang > cur->Clang)
      {
        pre = cur; //指针前移
        cur = cur->next;
      }
      break;
    case 's':
      while (cur && p->Sum > cur->Sum)
      {
        pre = cur; //指针前移
        cur = cur->next;
      }
      break;
    case 'c':
      while (cur && p->Chin > cur->Chin)
      {
        pre = cur; //指针前移
        cur = cur->next;
      }
      break;
    case 'm':
      while (cur && p->Math > cur->Math)
      {
        pre = cur; //指针前移
        cur = cur->next;
      }
      break;
    case 'e':
      while (cur && p->Eng > cur->Eng)
      {
        pre = cur; //指针前移
        cur = cur->next;
      }
      break;
    case 'i':
      while (cur && p->Id > cur->Id)
      {
        pre = cur; //指针前移
        cur = cur->next;
      }
      break;
    }
    //逐一把旧链表的节点插到新链表合适的位置：pre和cur之间
    pre->next = p;
    p = p->next;
    pre->next->next = cur; //不可以p->next = cur;因为p在旧链表上
  }

  free(newhead);
  newhead = NULL;
  p = NULL;
  return head;
}


//查找节点 根据姓名查找
student *search_name(student *head, char *name)
{
  if (head == NULL || isEmpty(head))
    return NULL;

  student *p = head;
  p = p->next;

  while (p != NULL)
  {
    if (strcmp(p->name, name) == 0)
    {
      break;
    }
    p = p->next;
  }
  if (p == NULL)
    return NULL;

  return p;
}

//查找节点 根据学号查找
student *search_id(student *head, int id)
{
  if (head == NULL || isEmpty(head))
    return NULL;

  student *p = head;
  p = p->next;

  while (p != NULL)
  {
    if (p->Id == id)
    {
      break;
    }
    p = p->next;
  }
  if (p == NULL)
    return NULL;

  return p;
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


//将链表的数据写入文件结尾，以追加的方式写入
void write_file_tail(student *head)
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
    ret = fwrite(p, stu_size, 1, stu_fp);
    if (ret != 1)
    {
      printf("erro: stu_message.txt write fail\n");
      return;
    }

    p = p->next;
  }

  return;
}

//将链表的数据从开头写入文件，以覆盖的方式写入
void write_file_cover(student *head)
{
  if (isEmpty(head) || head == NULL)
    return;

  //关闭文件
  fclose(stu_fp);
  //以覆盖的方式打开
  stu_fp = fopen("2247/stu_message.txt", "w+");
  int ret = 0;
  student *p = head;

  fseek(stu_fp, 0, SEEK_SET);
  p = p->next;
  while (p)
  {
    // stu_size 即结构体大小
    ret = fwrite(p, stu_size, 1, stu_fp);
    if (ret != 1)
    {
      printf("erro: stu_message.txt write fail\n");
      return;
    }

    p = p->next;
  }

  return;
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
    ret = fwrite(p, stu_size, 1, stu_fp);
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
    ret = fread(tmp, stu_size, 1, stu_fp);
    if (ret < 1)
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

