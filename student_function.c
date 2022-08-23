#include "teach_function.h"

#define KEY_LEN 5

char key[KEY_LEN] = {"a172k"}; //设置密钥为 a172k
int key_index;                 //密钥的下标

//检查帐号是否存在
bool account_check(int fa, struct student_acc *usr);
//验证码
void captcha();


//给密码添加密钥
void add_key(char *buff)
{
  for (int i = 0; i < strlen(buff); i++)
  {
    if (key_index < KEY_LEN)
    {
      buff[i] = buff[i] ^ key[key_index];
      key_index++;
    }
    else
    {
      key_index = 0;
      buff[i] = buff[i] ^ key[key_index];
      key_index++;
    }
  }
}


//登录
bool signIn(student *head)
{
  //将文件的数据读到链表
  read_file(head);
  student *p = head;
  int fa = 0,
      fp = 0;
  int reta = 1, retp = 1;
  key_index = 0; //将密钥的下标置0

  char buff[SIZE] = {0}; //用数组当缓冲区

  printf("请输入帐号：\n");
  scanf("%s", buff);

  // while()

  bool exit = account_check(fa, buff);
  if (exit == false)
  {
    printf("[帐号输入错误]\n");
    close(fa);
    close(fp);
    return false;
  }
  else
  {
    //光标直接移到密码所在的地方
    lseek(fp, (flag - 1) * SIZE, SEEK_SET);

    //将password.txt 的数据读入缓存区
    retp = read(fp, buff, SIZE);
    //通过密钥为密码解密
    add_key(buff);

    if (retp == -1)
    {
      printf("erro: password.txt read fail\n");
      //读取失败的话要把之前已经打开的文件关闭
      close(fa);
      close(fp);
      return false;
    }

    printf("请输入密码：\n");
    scanf("%s", usr->password);
    captcha();
    if (strcmp(buff, usr->password) == 0)
    {
      memset(buff, 0, SIZE);
      printf("[帐号密码验证成功，欢迎使用系统]\n");
      return true;
    }
    else
    {
      memset(buff, 0, SIZE);
      printf("[密码输入错误]\n");
      return false;
    }
  }
}

bool student_register(student *head)
{
  
}