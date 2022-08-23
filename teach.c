#include "teach_function.h"
//#include <unistd.h>

// char *Class[20] = {0}; //班级
// char *major[20] = {0};
// const int stu_size = sizeof(student); //结构体大小
char *Class[20] = {0}; //班级


void teach_insert_function(student * head)
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
        while (getchar() != '\n');
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

//教师排序功能
void teach_sort_function(student *head)
{
  char ch;
  while (1)
 { 
  printf("请按提升选择你要排序的对象：\n（i-学号  s-总分 c-语文 m-数学 e-英语 l-C语言）\nd-显示数据\n1-保存修改\n 0-退出\n");
  while(getchar()!='\n');
  getchar();
  ch = getchar();
  switch (ch)
  {
  case 'l':
  case 's':
  case 'e':
  case 'c':
  case 'm':
  case 'i':
    if (isEmpty(head))
       read_file(head); //重新读入
    Sort(head, ch);
    display(head);
    break;
  case 'd':
    if(isEmpty(head))
      read_file(head);  //重新读入
    display(head);
    break;
  case '1':
    write_file_cover(head);
    destroy(head);
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
        write_file_cover(head);
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
      while (getchar() != '\n');
      ch = getchar();

      if (ch == '0')
      {
        printf("【退出成功】\n");
        return;
      }
    }
   break;
  default:
    printf("输入错误，重新输入\n");
  }
 }
}

//教师查询功能
void teach_search_function(student *head)
{
  char ch;
  char *sear_class = NULL;
  student *tmp;
  int id = 0;
  char *name = NULL;
  int i = 0;
  float Chin,Math,Eng,Clang;
  //求现有班级个数
  while(!strcmp(Class[i],"0"))
    i++;

  printf("i = %d\n",i);
  printf("请输入你要查询的班级：");
  scanf("%s", sear_class);
  while (i)
  {
    if (strcmp(Class[i - 1], sear_class) == 0)
      break;
    i--;
  }
  if (i == 0)
  {
    printf("未找到 %s 班级，请检查输入是否有误\n", sear_class);
  }else 
  {
    read_file(head);
  while (1)
  {
    printf("1-学号查询  2-姓名查询  3-显示全部  4-删除学生  5-修改学生   6-保存  0-退出\n");
    getchar();
    ch = getchar();
    switch (ch)
    {
    case 'l':
      printf("请输入所查找的学生的学号: ");
      scanf("%d", &id);
      if(isEmpty(head))
        write_file(head);
      tmp = NULL;
      tmp = search_id(head, id);
      if (tmp == NULL)
      {
        printf("erro: 未查找到学号为 %d 的学生，请检查是否输入有误!\n", id);
      }
      displayNode(tmp);
      break;
    case '2':
      printf("请输入所查找的学生的姓名: ");
      scanf("%s", name);
      if (isEmpty(head))
        write_file(head);
      tmp = NULL;
      tmp = search_name(head, name);
      if (tmp == NULL)
      {
        printf("erro: 未查找到姓名为 %s 的学生，请检查是否输入有误!\n", name);
      }
      displayNode(tmp);
      break;
    case '3':
      if (isEmpty(head))
        write_file(head);
      display(head);
      break;
    case '4':
      printf("请输入所删除的学生的学号: ");
      scanf("%d", &id);
      if (isEmpty(head))
        write_file(head);
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
      }
      break;

    case '5':
      printf("请输入所修改的学生的学号: ");
      scanf("%d", &id);
      if (isEmpty(head))
        write_file(head);
      if (id == 0)
        break;
      tmp = search_id(head, id);
      if (tmp == NULL)
      {
        printf("erro: 未查找到姓名为 %s 的学生，请检查是否输入有误!\n", name);
      }
      printf("1-修改语文成绩  2-修改英语成绩  3-修改数学成绩  4-修改c语言成绩  0-退出\n");
      while (getchar() != '\n');
      getchar();
      ch = getchar();
      switch (ch)
      {
      case '1':
        printf("请修改 %s 的语文成绩：\n",tmp->name);
        scanf("%f",&Chin);
        tmp->Chin = Chin;
        printf("【修改成功】\n");
        break;
      case '2':
        printf("请修改 %s 的英语成绩：\n", tmp->name);
        scanf("%f", &Eng);
        tmp->Eng = Eng;
        printf("【修改成功】\n");
        break;
      case '3':
        printf("请修改 %s 的数学成绩：\n", tmp->name);
        scanf("%f", &Math);
        tmp->Math = Math;
        printf("【修改成功】\n");
        break;

      case '4':
        printf("请修改 %s 的数学成绩：\n", tmp->name);
        scanf("%f", &Clang);
        tmp->Clang = Clang;
        printf("【修改成功】\n");
        break;

      case '0':
        printf("是否确定退出？\n");
        printf("0-是   1-否\n");
        while (getchar() != '\n');
        char c = getchar();
        if (c == '0')
        {
          printf("【退出成功】\n");
          return;
        }
        break;

      default:
        break;
      }
        break;

      case '6':
        write_file_cover(head);
        destroy(head);
        break;
      case '0':
        if (!isEmpty(head)) //如果链表不为空，即还未保存，则提醒保存
        {
          printf("\t【您还未保存插入记录!】\n");
          printf("1-保存并退出  2-取消退出  0-直接退出\n");
          while (getchar() != '\n')
            ;
          char ch = getchar();
          switch (ch)
          {
          case '1':
            write_file_cover(head);
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
      default:
        printf("输入错误，重新输入\n");
      }
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
    printf("\na-插入  d-删除  c-显示  f-查询  s-排序  m-修改  0-退出\n");
    ch = getchar();
    switch (ch)
    {
    case 'a':
      destroy(head); //插入之前先将链表释放
      teach_insert_function(head);
       break;
    case 'd':
     
      break;

    case 'c':
      //将文件的数据读到链表
      read_file(head);
      display(head);
      break;

    case 'f':
      teach_search_function(head);
       break;

    case 's':
      teach_sort_function(head);
       break;

    case '0':
      printf("是否确定退出？\n");
      printf("0-是   1-否\n");
      while (getchar() != '\n') ;
      ch = getchar();

      if (ch == '0')
      {
        printf("【退出成功】\n");
        return;
      }
       break;
    }
    while (getchar() != '\n');
  }

  destroy(head);
  free(head);
  return;
}

//管理员代码
void administrator_function()
{
   
}

int main()
{
  stu_size = sizeof(student);
  srand((int)time(NULL));

  Class[0] = "2247";
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