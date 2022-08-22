#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <unistd.h>

#define NAMEMAX 12                           //名字长度
#define SEXMAX 6                             //性别长度
#define PATH_2247_stu "2247/stu_message.txt" // 2247班学生信息文件的路径

FILE *stu_fp; //学生信息文件描述符


//char *major[20] = {0};

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



//初始化节点
student *initNode();

bool isEmpty(student *head);

//随机生成学生的数据
void createData(student *stu);

//增加节点  只输入姓名
void insert_rand(student *head, char *name);

//增加节点  输入全部数据 尾插法
void insert_tail(student *head, char *name, int Id, char *sex, float Eng, float Math, float Chin, float Clang);

//释放链表
void destroy(student *head);

//显示节点
void displayNode(student *head);

//显示全链表
void display(student *head);

    //删除节点 根据学号删除
student *Remove(student *head, int id);

student *Sort(student *head, char ch);

//查找节点 根据姓名查找
student *search_name(student *head, char *name);

//查找节点 根据学号查找
student *search_id(student *head, int id);

//查找节点 根据学号查找 返回所查找节点的上一个节点
student *search_prev(student *head, int id);

//删除节点 根据学号删除
student *Remove(student *head, int id);


//将链表的数据写入文件结尾，以追加的方式写入
void write_file_tail(student *head);

//将链表的数据从开头写入文件，以覆盖的方式写入
void write_file_cover(student *head);

//将链表的数据写入文件 stu_message.txt 中
void write_file(student *head);

//将文件的数据读到链表
void read_file(student *head);

//释放链表
void destroy(student *head);