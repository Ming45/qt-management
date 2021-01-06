#ifndef MYMANAGE_H
#define MYMANAGE_H

#include<iostream>
#include <fstream>//和文件有关的输入输出类声明
#include<sstream>///C++风格的串流控制
#include<string>
//#include<cmath>
#include <stdio.h>
#include <algorithm>
#include <windows.h>
#include<QByteArray>
#include<QString>
#include<QDebug>
#include <QCoreApplication>
#include<QFile>
#include<QTextStream>
#include<QTextCodec>

#include"mainwindow.h"

using namespace std;

class Course {
public:
    char cname[50];//课程名字
    char cid[50];//课程编号
    int credit;//学分
    int ctime;//学时
    bool bixuanxiu;//必选修性质（1代表必修，0代表选修）
    double score;//成绩

    Course* cnext;////用于别的对课程对象的处理

    QString showcourse(QString &str);//显示课程

    void inputcourse();//存放课程

    void readcourse(istream& in);//读取课程文本

};
class Major {
public:
    char mname[50];//专业名字
    char mid[50];//专业编号
    char bimajor[50];//必修课
    double majorcredit;//专业学分要求
};
class Student {//学生模块，     数据成员，显示，存放，读取
public:
    char sname[50];//学生名字
    char sid[50];//学生学号
    char sclass[50];//班级
    char major[50];//专业
    Course scourse;//选修的课程

    Student* snext;//用于别的对学生对象的处理
    Student* ssnext;//用于别的对学生成绩对象的处理

    void showstudent();//显示学生
    void showscore();//显示成绩
    void inputscore();//存放成绩
    void inputstudent();//添加新学生

//    QString sinputcourse(QString &str,char name,char ke,char hh);//选修添加课程

    void readscore(istream& in);//读取成绩文本中的内容
    void readstudent(istream& in);//读取学生文本中的内容

};
class Studentwork {//学生操作模块，   操作函数，文本操作，
public:
    //Student() = default;//构造函数
    ~Studentwork();//析构函数 ,删去指针内容

    Student* shead, * send;//对学生的处理  (处理学生文本)

    Student* sshead, * ssend;//对学生成绩的处理  (处理成绩文本)

    Course* schead, * scend;//学生对课程的处理  (处理课程文本)

    ifstream instudent;//用于对学生文本的输入输出
    ofstream outstudent;

    ifstream inscore;//用于对成绩文本的输入输出
    ofstream outscore;

    ifstream incourse;//用于对课程文本的输入输出
    ofstream outcourse;

    int panduan[4] = { 0 };//用于判断是否进行了文本操作（各位代表标志位，1代表进行了），进而在析构时选择是否删除

    void getscoretxt();//录入学生成绩文本的进行管理    （判断位的第一位）
    void savescoretxt();//对更改后的成绩文本保存

    void getstudenttxt();//录入学生文本的进行管理    （判断位的第二位）
    void savestudenttxt();//对更改后的学生文本保存

    void getcoursetxt();//录入课程文本的进行管理    （判断位的第三位）
    void savecoursetxt();//对更改后的课程文本保存


    QString getcoursecredit(QString &str,int w,char *thing);//显示某学生的所有课程的学分以及现总学分,用于选课

    QString getstudentscore(QString &str,int x,char *who);//显示某学生的所有课程成绩


    QString showallcourse(QString &str);//显示所有课程及学分，供学生选课

 //   QString choosecourse(QString &str,char name,char ke,char hh);//学生选择添加要选修的课到学生成绩文本，成绩为-1

    QString sremovecourse(QString &str,char *name,char*ke);//学生退选课到成绩文本

    Course* sfindcname(char* name);//由课程名字找课程
    Course* sfindcid(char* id);//由课程编码找课程

    Student* sfindsname(char* name);//由学生名字找人
    Student* sfindsid(char* id);//由学生学号找人
};

class Teacher {
public:
    char tname[50];//教师名字
    char tid[50];//教师编号
    Course tcourse;//教授的课程
    Teacher* tnext;//其他对教师对象的操作

    void showteacher();//显示教师

    void showteachercourse();//显示教师教授的课程

    void inputteacher();//存放添加教师

    void readteacher(istream& in);//读取教师文本中的内容
};
class Teacherwork {
public:

    Teacherwork() = default;//构造函数
    ~Teacherwork();//析构函数 ,删去动态内存的tshead, tsend，ssnext,thead, tend，snext所指

    int panduan[4] = { 0 };//用于判断是否进行了文本操作（各位代表标志位，1代表进行了），进而在析构时选择是否删除

    Student* tshead, * tsend;//教师对学生成绩对象的处理  (处理成绩文本)

    Student* thead, * tend;//教师对学生对象的处理  (处理学生文本)

    Teacher* tthead, * ttend;//教师对教师对象的处理  (处理教师文本)（获取自己教授的课程）


    ifstream inscore;//用于对成绩文本的输入输出
    ofstream outscore;

    ifstream instudent;//用于对学生文本的输入输出
    ofstream outstudent;

    ifstream inteacher;//用于对教师文本的输入输出
    ofstream outteacher;

    void getscoretxt();//录入学生成绩文本的进行管理
    void savescoretxt();//对更改后的成绩文本保存

    void getstudenttxt();//录入学生文本的进行管理
    void savestudenttxt();//对更改后的学生文本保存

    void getteachertxt();//录入教师文本的进行管理
    void saveteachertxt();//对更改后的教师文本保存


    void showallstudent();//读取显示所有学生
    QString showstudentscore(QString &str,int x,char *who);//由学生名字或学号读取显示目标学生所有课程成绩以及总分
    void showcoursestudent();//查找某门课程成绩处于指定分数段内的学生名单

    void addscore();//添加录入学生成绩

    void modifyscore();//由学生名字或学号找人修改学生具体某课成绩

    int LC();//统计链表记录总数

    QString countclass(QString &str,char *who);//统计某班级学生所有学生的单科成绩
    QString countcourse(QString &str,char *who);//统计某课程的学生成绩，以及平均值，标准差，及格率
    void swap(Student*, Student*);//用于排序时的交换
    QString sortcourse(QString &str,char *who);//某课程的学生成绩从小到大排序


    Student* tfindsname(char* name);//教师由学生名字找人
    Student* tfindsid(char* id);//教师由学生学号找人

    Student* tfindcnamesname(char* name,double high,double low);//教师由课程名字，,成绩最高值，成绩最低值   找学生名字
    Student* tfindcidsid(char* id,  double high, double low);//教师由课程名字，,成绩最高值，成绩最低值   找学生名字

    Student* tfindclasssname(char* name);//教师由教室编号找人

    Student* tfindcourse(char* name);//教师由课程名称找选修了的学生

};

class Manage{
public:

    Manage() = default;//构造函数
    ~Manage();//析构函数 ,删去动态内存的指针所指

    int panduan[4] = { 0 };//用于判断是否进行了文本操作（各位代表标志位，1代表进行了），进而在析构时选择是否删除

    Course* mchead, * mcend;//系统对课程对象的处理  (处理课程文本)

    Student* mshead, * msend;//系统对学生对象的处理  (处理学生文本)

    Teacher* mthead, * mtend;//系统对教师对象的处理  (处理教师文本)


    ifstream incourse;//用于对课程文本的输入输出
    ofstream outcourse;

    ifstream instudent;//用于对学生文本的输入输出
    ofstream outstudent;

    ifstream inteacher;//用于对教师文本的输入输出
    ofstream outteacher;

    void getcoursetxt();//录入课程文本的进行管理
    void savecoursetxt();//对更改后的课程文本保存

    void getstudenttxt();//录入学生文本的进行管理
    void savestudenttxt();//对更改后的学生文本保存

    void getteachertxt();//录入教师文本的进行管理
    void saveteachertxt();//对更改后的教师文本保存

    void addstudent();//添加录入学生
    void addteacher();//添加录入教师
    void addcourse();//添加录入课程

    void mremovestudent();//由学生名字删去学生信息
    void mremoveteacher();//由教师名字删去教师信息
    void mremovecourse();//由课程名字删去课程信息

    Student* mfindsname(char* name);//由学生名字找学生
    Teacher* mfindtname(char* name);//由教师名字找教师
    Course* mfindcname(char* name);//由课程名字找课程
};

#endif // MYMANAGE_H
