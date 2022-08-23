#include "teach_function.h"

void student_function()
{
  student *head = initNode();
  student *tmp;
  char ch;
  //学生登录
  bool student_register(head);

  while (1)
  {
    printf("\n*******学生功能页面*******\n");
    printf("\n1-查询  2-修改  3-显示  0-退出\n");
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
      while (getchar() != '\n')
        ;
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

int mian()
{
  stu_fp = fopen("2247/stu_message.txt", "a+");
  if (stu_fp == NULL)
  {
    printf("erro: stu_message.txt open fail\n");
    return 0;
  }

  student_function();

  fclose(stu_fp);
  return 0;
}