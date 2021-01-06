#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include<QDebug>
#include "mymanage.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    static QString look=0;//用引用来获取
    static int whichwork=0;//用于切换功能

    ui->schooseone->hide();
    ui->schoosename->hide();
    ui->schoosenum->hide();
    ui->sgetthing->hide();

    ui->tchooseone->hide();
    ui->tchoosename->hide();
    ui->tchoosenum->hide();
    ui->tgetthing->hide();

    ui->mget4->hide();//学生专业输入

    ui->yescourse->hide();
    ui->getsid->hide();
    ui->getcname->hide();

    ui->tyesscore->hide();
    ui->tgetsid->hide();
    ui->tgetsname->hide();
    //设置菜单栏切换页面
    connect(ui->teacherwork,&QAction::hovered,
                [=]()
        {
            ui->wanttosee->adjustSize();
            ui->workname->setText("教师模块");
            ui->stackedWidget->setCurrentWidget(ui->teacher);
        }

                );
    connect(ui->studentwork,&QAction::hovered,
                [=]()
        {
            ui->wanttosee->adjustSize();
            ui->workname->setText("学生模块");
            ui->stackedWidget->setCurrentWidget(ui->student);
        }

                );
    connect(ui->managework,&QAction::hovered,
                [=]()
        {
            ui->wanttosee->adjustSize();
            ui->workname->setText("系统模块");
            ui->stackedWidget->setCurrentWidget(ui->manage);
        }

                );

    //学生模块，
    connect(ui->showallcourse,&QPushButton::pressed,//显示所有课程及其学分供选课用
                [&]()
        {
                Studentwork y;
                y.getcoursetxt();

                QString &str=look;//用于获取输出，从而在ui上输出
                //str="课程编号:\t课程名称:\t课程学分:\n";
                //str=;
               ui->wanttosee->setText(y.showallcourse(str));
        }
                );
    connect(ui->getcoursecredit,&QPushButton::pressed,//显示学生选的所有课程及其学分
                [=]()
        {
                whichwork=1;//切换模式
                ui->schooseone->show();
                ui->schoosename->show();
                ui->schoosenum->show();
                ui->sgetthing->show();
                ui->schooseone->setText("我的课程：请先输入信息·");
        }
                );
    connect(ui->getstudentscore,&QPushButton::pressed,//显示获取学生的课程成绩
                [&]()
        {
                 whichwork=2;//切换模式
                 ui->schooseone->show();
                 ui->schoosename->show();
                 ui->schoosenum->show();
                 ui->sgetthing->show();
                 ui->schooseone->setText("我的成绩：请先输入信息");
        }
                );
    connect(ui->choosecourse,&QPushButton::pressed,//选课
                [&]()
        {
                 whichwork=1;//切换模式.选课
                 ui->schooseone->show();
                 ui->schoosename->hide();
                 ui->schoosenum->hide();
                 ui->getcoursecredit->hide();
                 ui->getstudentscore->hide();
                 ui->showallcourse->hide();

                 ui->getcname->show();
                 ui->getsid->show();
                 ui->sgetthing->show();
                 ui->yescourse->show();
                 ui->schooseone->setText("选课:请依次输入姓名，学号，课程 再按下确认键");


        }
                );
    connect(ui->sremovecourse,&QPushButton::pressed,//退课
                [&]()
        {
                 whichwork=2;//切换模式，退课
                 ui->schooseone->show();
                 ui->schoosename->hide();
                 ui->schoosenum->hide();
                 ui->getcoursecredit->hide();
                 ui->getstudentscore->hide();
                 ui->showallcourse->hide();

                 ui->getcname->show();
                 ui->getsid->show();
                 ui->sgetthing->show();
                 ui->yescourse->show();
                 ui->schooseone->setText("退课:请依次输入姓名，学号，课程 再按下确认键");


        }
                );
    connect(ui->yescourse,&QPushButton::pressed,//确认选课信息,退课信息
                [&]()
        {
             if(whichwork==1){//进行选课确认操作
                Studentwork y;
                y.getcoursetxt();
                y.getstudenttxt();
                y.getscoretxt();


                QString ss1=ui->sgetthing->text();
                QString ss2=ui->getsid->text();
                 QString ss3=ui->getcname->text();

                 string tr;
                 tr=ss3.toStdString();
                 const char *cpc=tr.data();
                 char* ccname=new char[100];
                 strcpy(ccname,cpc);

                 string tr2;
                 tr=ss1.toStdString();
                 const char *cpc2=tr.data();
                 char* ssname=new char[100];
                 strcpy(ssname,cpc2);

                 string tr3;
                 tr=ss2.toStdString();
                 const char *cpc3=tr.data();
                 char* ssid=new char[100];
                 strcpy(ssid,cpc3);

                 if(y.sfindcname(ccname)&&y.sfindsname(ssname)&&y.sfindsid(ssid)){//确保有该学生姓名，有学生学号，有该课程
                 //QString转char*
                       ui->schooseone->setText("添加成功!");
                       QString &str=look;
                       str+="\n\n选课成功\n姓名："+ss1+"\t学号："+ss2+"\t课程："+ss3;
                       ui->wanttosee->setText(str);

                       //直接在文本后面添加
                       QFile data("D:/C++qt/work/managetest/sort.txt");
                      if (data.open(QFile::WriteOnly | QIODevice::Append))//在后增加的打开方式
                      {
                          QTextStream outscore(&data);
                          outscore.setCodec("UTF-8");//设置为UTF-8编码
                          outscore <<"\n"<< ss2 << "\t" << ss1 << "\t" << ss3 << "\t" << QString::number(-1) ;//用QString来写入
                          data.close();
                      }
                    }
                   else{
                           ui->schooseone->setText("信息错误，请重新核对更改输入的信息");
                           QString &str=look;
                           str+="\n\n刚刚输入的错误信息\n姓名："+ss1+"\t学号："+ss2+"\t课程："+ss3;
                           ui->wanttosee->setText(str);
                    }

                 ui->getcoursecredit->show();

                 ui->yescourse->hide();
                 ui->schooseone->show();
                 ui->getstudentscore->show();
                 ui->showallcourse->show();

                 ui->getcname->hide();
                 ui->getsid->hide();
                }

             else if(whichwork==2){//进行退课确认操作
                    Studentwork y;
                    y.getcoursetxt();
                    y.getstudenttxt();
                    y.getscoretxt();


                    QString ss1=ui->sgetthing->text();
                    QString ss2=ui->getsid->text();
                     QString ss3=ui->getcname->text();

                     string tr;
                     tr=ss3.toStdString();
                     const char *cpc=tr.data();
                     char* ccname=new char[100];
                     strcpy(ccname,cpc);

                     string tr2;
                     tr=ss1.toStdString();
                     const char *cpc2=tr.data();
                     char* ssname=new char[100];
                     strcpy(ssname,cpc2);

                     string tr3;
                     tr=ss2.toStdString();
                     const char *cpc3=tr.data();
                     char* ssid=new char[100];
                     strcpy(ssid,cpc3);

                     if(y.sfindcname(ccname)&&y.sfindsname(ssname)&&y.sfindsid(ssid)){//确保有该学生姓名，有学生学号，有该课程
                           for (Student* pp = y.sshead; pp->ssnext != y.ssend; pp = pp->ssnext){
                               if ((!strcmp(pp->ssnext->sname, ssname))&&(!strcmp(pp->ssnext->scourse.cname,ccname))){
                                      Student* temp = NULL;
                                      temp = pp->ssnext;
                                      pp->ssnext = pp->ssnext->ssnext;
                                      delete temp;
                                      ui->schooseone->setText("删除成功!");
                                      QString &str=look;
                                      str+="\n\n删除成功\n姓名："+ss1+"\t学号："+ss2+"\t课程："+ss3;
                                      ui->wanttosee->setText(str);

                                      y.savescoretxt();//保存
                                      break;
                               }
                           }
                     }
                     else{
                             ui->schooseone->setText("信息错误，请重新核对更改输入的信息");
                             QString &str=look;
                             str+="\n\n刚刚输入的错误信息\n姓名："+ss1+"\t学号："+ss2+"\t课程："+ss3;
                             ui->wanttosee->setText(str);
                      }
                 }
             ui->getcoursecredit->show();

             ui->yescourse->hide();
             ui->schooseone->show();
             ui->getstudentscore->show();
             ui->showallcourse->show();

             ui->getcname->hide();
             ui->getsid->hide();
        }
                );
    connect(ui->schoosename,&QPushButton::pressed,//选择姓名查找方式
                [&]()
        {
               Studentwork y;
               y.getcoursetxt();
               y.getstudenttxt();
               y.getscoretxt();
               QString &str=look;//用于获取输出，从而在ui上输出

               //QString转char*
               string tr;
               QString ss=ui->sgetthing->text();
               tr=ss.toStdString();
               const char *cpc=tr.data();
               char* name=new char[100];
               strcpy(name,cpc);

               switch(whichwork){//选择功能
                 case 1:{

                     ui->wanttosee->setText(y.getcoursecredit(str,1,name));//输入1，名字获取
                     break;
                     }
                 case 2:{

                     ui->wanttosee->setText(y.getstudentscore(str,1,name));//输入1，名字获取
                     break;
                   }
                 }
        }
                );
    connect(ui->schoosenum,&QPushButton::pressed,//选择学号查找方式
                [&]()
        {
                Studentwork y;
                y.getcoursetxt();
                y.getstudenttxt();
                y.getscoretxt();
                QString &str=look;//用于获取输出，从而在ui上输出
                //QString转char*
                string tr;
                QString ss=ui->sgetthing->text();
                tr=ss.toStdString();
                const char *cpc=tr.data();
                char* name=new char[100];
                strcpy(name,cpc);

                switch(whichwork){//选择功能
                  case 1:{
                    ui->wanttosee->setText(y.getcoursecredit(str,2,name));//输入2，学号获取
                    break;
                    }
                  case 2:{

                    ui->wanttosee->setText(y.getstudentscore(str,2,name));//输入1，名字获取
                    break;
                    }
          }
        }
                );


    //教师模块  tshowallcourse
    connect(ui->tshowallcourse,&QPushButton::pressed,//显示所有成绩
                [&]()
        {
                Teacherwork y;
                y.getscoretxt();

                QString &str=look;//用于获取输出，从而在ui上输出
                str+="\n\n所有成绩如下：";
                for (Student* pp = y.tshead; pp->ssnext->sid[0]>='0'&&pp->ssnext->sid[0]<='9'; pp = pp->ssnext) {
                        if (pp->ssnext->scourse.score != -1) {
                            str+=("\n学生：" +QString(pp->ssnext->sname)+"\t课程：" +QString(pp->ssnext->scourse.cname)+ "\t成绩："+QString::number(pp->ssnext->scourse.score));
                        }
                        else
                            str+=("\n学生：" +QString(pp->ssnext->sname)+"\t课程：" +QString(pp->ssnext->scourse.cname)+ "\t未参加考试，无成绩");
                    }
                ui->twanttosee->setText(str);
        }
                );

    connect(ui->tshowallstudent,&QPushButton::pressed,//显示所有学生
                [&]()
        {
                 Teacherwork y;
                 y.getstudenttxt();

                QString &str=look;//用于获取输出，从而在ui上输出
                str+="\n\n所有学生如下：";
               //ui->wanttosee->setText(y.showallcourse(str));
                for (Student* pp = y.thead; pp->snext->sid[0]>='0'&&pp->snext->sid[0]<='9'; pp = pp->snext) {
                     str+=("\n学生：" +QString(pp->snext->sname)+"\t专业：" +QString(pp->snext->major));
                    }
                ui->twanttosee->setText(str);
        }
                );

    connect(ui->showstudentscore,&QPushButton::pressed,//显示目标学生成绩
                [=]()
        {
                whichwork=1;
                ui->tchooseone->show();
                ui->tchoosename->show();
                ui->tchoosenum->show();
                ui->tgetthing->show();
                ui->tchooseone->setText("我的课程：请先输入信息·");
        }
                );

    connect(ui->tchoosename,&QPushButton::pressed,//选择姓名查找方式，获取学生的所有成绩
                [&]()
        {
               Teacherwork y;
               y.getstudenttxt();
               y.getscoretxt();
               QString &str=look;//用于获取输出，从而在ui上输出

               //QString转char*
               string tr;
               QString ss=ui->tgetthing->text();
               tr=ss.toStdString();
               const char *cpc=tr.data();
               char* name=new char[100];
               strcpy(name,cpc);

               ui->twanttosee->setText(y.showstudentscore(str,1,name));//输入1，名字
        }
                );
    connect(ui->tchoosenum,&QPushButton::pressed,//1.选择学号查找方式,获取学生的所有成绩,以及2.成绩排序，3.统计班级，4.统计课程
                [&]()
        {
             if(whichwork==1){
               Teacherwork y;
               y.getstudenttxt();
               y.getscoretxt();
               QString &str=look;//用于获取输出，从而在ui上输出

               //QString转char*
               string tr;
               QString ss=ui->tgetthing->text();
               tr=ss.toStdString();
               const char *cpc=tr.data();
               char* name=new char[100];
               strcpy(name,cpc);

               ui->twanttosee->setText(y.showstudentscore(str,2,name));//输入2，学号             
             }
             else if(whichwork==2){//某课程成绩排序
                 Teacherwork y;
                 y.getstudenttxt();
                 y.getscoretxt();
                 QString &str=look;//用于获取输出，从而在ui上输出

                 //QString转char*
                 string tr;
                 QString ss=ui->tgetthing->text();
                 tr=ss.toStdString();
                 const char *cpc=tr.data();
                 char* name=new char[100];
                 strcpy(name,cpc);

                 ui->twanttosee->setText(y.sortcourse(str,name));

                 y.savescoretxt();

                 ui->tchoosenum->setText("学号");
             }

             else if(whichwork==3){//某课程统计
                 Teacherwork y;
                 y.getstudenttxt();
                 y.getscoretxt();
                 QString &str=look;//用于获取输出，从而在ui上输出

                 //QString转char*
                 string tr;
                 QString ss=ui->tgetthing->text();
                 tr=ss.toStdString();
                 const char *cpc=tr.data();
                 char* name=new char[100];
                 strcpy(name,cpc);

                 ui->twanttosee->setText(y.countcourse(str,name));

                 ui->tchoosenum->setText("学号");
             }

             else if(whichwork==4){//某班级统计
                 Teacherwork y;
                 y.getstudenttxt();
                 y.getscoretxt();
                 QString &str=look;//用于获取输出，从而在ui上输出

                 //QString转char*
                 string tr;
                 QString ss=ui->tgetthing->text();
                 tr=ss.toStdString();
                 const char *cpc=tr.data();
                 char* name=new char[100];
                 strcpy(name,cpc);

                 ui->twanttosee->setText(y.countclass(str,name));

                 ui->tchoosenum->setText("学号");
             }
    }
                );

    connect(ui->tmodifyscore,&QPushButton::pressed,//修改成绩
                [&]()
        {
                 whichwork=1;//切换模式，修改成绩
                 ui->tchooseone->show();
                 ui->tchoosename->hide();
                 ui->tchoosenum->hide();
                 ui->tshowallcourse->hide();
                 ui->tshowallstudent->hide();

                 ui->tgetsname->show();
                 ui->tgetsid->show();
                 ui->tgetthing->show();
                 ui->tyesscore->show();
                 ui->tchooseone->setText("修改:请依次输入姓名，课程，成绩 再确认");

        }
                );

    connect(ui->showcoursestudent,&QPushButton::pressed,//成绩范围内
                [&]()
        {
                 whichwork=2;//切换模式，修改成绩
                 ui->tchooseone->show();
                 ui->tchoosename->hide();
                 ui->tchoosenum->hide();
                 ui->tshowallcourse->hide();
                 ui->tshowallstudent->hide();

                 ui->tgetsname->show();
                 ui->tgetsid->show();
                 ui->tgetthing->show();
                 ui->tyesscore->show();
                 ui->tchooseone->setText("范围:请依次输入课程，最高值，最低值 再确认");



        }
                );

    connect(ui->tyesscore,&QPushButton::pressed,//修改
                [&]()
        {
           if(whichwork==1){//进行选课确认操作
           Teacherwork y;
           y.getstudenttxt();
           y.getscoretxt();


           QString ss1=ui->tgetthing->text();
           QString ss2=ui->tgetsid->text();
           QString ss3=ui->tgetsname->text();

            string tr;

            tr=ss1.toStdString();
            const char *cpc2=tr.data();
            char* ssname=new char[100];
            strcpy(ssname,cpc2);

            tr=ss2.toStdString();
            const char *cpc3=tr.data();
            char* ccname=new char[100];
            strcpy(ccname,cpc3);

            QString &str=look;
            if(y.tfindsname(ssname)){//确保有该学生姓名
            //QString转char*

                     for (Student* pp = y.tshead; pp->ssnext != y.tsend; pp = pp->ssnext) {
                         if (!strcmp(pp->ssnext->sname, ssname)) {//确保是目标学生
                             if (!strcmp(pp->ssnext->scourse.cname, ccname)) {//确保是某门课
                                 ui->tchooseone->setText("修改成功!");
                                 pp->ssnext->scourse.score=ss3.toDouble();
                                 str+="\n\n修改成功\n姓名："+ss1+"\t课程："+ss2+"\t成绩："+ss3;
                                 y.savescoretxt();

                             }
                         }
                 }
            }
            else{
                str+="没找到";
            }
            ui->twanttosee->setText(str);

        }
           else if(whichwork==2){
               Teacherwork y;
               y.getstudenttxt();
               y.getscoretxt();


               QString ss1=ui->tgetthing->text();
               QString ss2=ui->tgetsid->text();//最高值
               QString ss3=ui->tgetsname->text();//最低值

                string tr;

                tr=ss1.toStdString();
                const char *cpc2=tr.data();
                char* ccname=new char[100];
                strcpy(ccname,cpc2);

                QString &str=look;

                if (y.tfindcnamesname(ccname,ss2.toDouble(),ss3.toDouble())) {//由课程名字,成绩最高值，成绩最低值   找学生
                    str+="\n\n找到该课程成绩范围内学生!";
                    for (Student* pp = y.tshead; pp->ssnext != y.tsend; pp = pp->ssnext) {
                        if (!strcmp(pp->ssnext->scourse.cname, ccname)) {//如果是这门课
                             if ((ss3.toDouble() <= pp->ssnext->scourse.score) &&(pp->ssnext->scourse.score<= ss2.toDouble())){//如果在成绩区间内
                                //qDebug() << << endl;
                                 str+="\n学生：" + QString(pp->ssnext->sname) +"\t成绩：" +  QString::number(pp->ssnext->scourse.score) ;
                            }
                        }
                    }
                }
                else {
                    str+="\n\n没有找到该课程成绩范围内学生!";
                }
                ui->twanttosee->setText(str);
           }
           ui->tshowallstudent->show();

           ui->tyesscore->hide();
           ui->tchooseone->show();
           ui->tshowallcourse->show();
           ui->showallcourse->show();

           ui->tgetsname->hide();
           ui->tgetsid->hide();

    }
                );


    connect(ui->sortcourse,&QPushButton::pressed,//某课程成绩排序
                [=]()
        {
                whichwork=2;
                ui->tchooseone->show();
                ui->tchoosename->hide();
                ui->tchoosenum->show();
                ui->tchoosenum->setText("确认");
                ui->tgetthing->show();
                ui->tchooseone->setText("课程成绩排序：请先输入课程");
        }
                );

    connect(ui->countcourse,&QPushButton::pressed,//某课程统计
                [=]()
        {
                whichwork=3;
                ui->tchooseone->show();
                ui->tchoosename->hide();
                ui->tchoosenum->show();
                ui->tchoosenum->setText("确认");
                ui->tgetthing->show();
                ui->tchooseone->setText("课程统计：请先输入课程");
        }
                );
    connect(ui->countclass,&QPushButton::pressed,//某班级统计
                [=]()
        {
                whichwork=4;
                ui->tchooseone->show();
                ui->tchoosename->hide();
                ui->tchoosenum->show();
                ui->tchoosenum->setText("确认");
                ui->tgetthing->show();
                ui->tchooseone->setText("班级统计：请先输入班号");
        }
                );

    //系统模块
    connect(ui->maddcourse,&QPushButton::pressed,//添加课程
                [&]()
        {
                 whichwork=1;//切换模式
                 ui->mgetthing->show();
                 ui->mget3->show();
                 ui->mget2->show();
                 ui->mget4->hide();
                 ui->mchooseone->setText("添加课:请依次输入编号，课名，学分 再确认");
        }
                );
    connect(ui->mmovecourse,&QPushButton::pressed,//删除课程
                [&]()
        {
                 whichwork=2;//切换模式
                 ui->mgetthing->show();
                 ui->mget3->hide();//隐藏第三,二个输入
                 ui->mget2->hide();
                 ui->mget4->hide();
                 ui->mchooseone->setText("删除课:请输入课名 再确认");
        }
                );
    connect(ui->maddstudent,&QPushButton::pressed,//添加学生
                [&]()
        {
                 whichwork=3;//切换模式
                 ui->mgetthing->show();
                 ui->mget3->show();
                 ui->mget2->show();
                 ui->mget4->show();//显示第四个输入
                 ui->mchooseone->setText("加学生:请依次输入学号,姓名,班级号,专业 再确认");
        }
                );
    connect(ui->mmovestudent,&QPushButton::pressed,//删除学生
                [&]()
        {
                 whichwork=4;//切换模式
                 ui->mgetthing->show();
                 ui->mget3->hide();//隐藏第三,二个输入
                 ui->mget2->hide();
                 ui->mget4->hide();
                 ui->mchooseone->setText("删除学生:请输入姓名再确认");
        }
                );
    connect(ui->maddteacher,&QPushButton::pressed,//添加教师
                [&]()
        {
                 whichwork=5;//切换模式
                 ui->mgetthing->show();
                 ui->mget3->show();
                 ui->mget2->show();
                 ui->mget4->hide();
                 ui->mchooseone->setText("添加教师:请依次输入编号，姓名，课程 再确认");
        }
                );
    connect(ui->mmoveteacher,&QPushButton::pressed,//删除教师
                [&]()
        {
                 whichwork=6;//切换模式
                 ui->mgetthing->show();
                 ui->mget3->hide();//隐藏第三,二个输入
                 ui->mget2->hide();
                 ui->mget4->hide();
                 ui->mchooseone->setText("删除教师:请输入姓名 再确认");
        }
                );
    connect(ui->myes,&QPushButton::pressed,//确认信息
                [&]()
        {
             if(whichwork==1){//进行添加课确认操作
                Manage y;
                y.getcoursetxt();
                y.getstudenttxt();
                y.getteachertxt();


                QString ss1=ui->mgetthing->text();
                QString ss2=ui->mget2->text();
                 QString ss3=ui->mget3->text();

                       ui->mchooseone->setText("添加成功!");
                       QString &str=look;
                       str+="\n\n添加课程成功\n编号："+ss1+"\t课程名："+ss2+"\t学分："+ss3;
                       ui->mwanttosee->setText(str);

                       //直接在文本后面添加
                       QFile data("D:/C++qt/work/managetest/sortcourse.txt");
                      if (data.open(QFile::WriteOnly | QIODevice::Append))//在后增加的打开方式
                      {
                          QTextStream outcourse(&data);
                          outcourse.setCodec("UTF-8");//设置为UTF-8编码
                          outcourse <<"\n"<< ss1 << "\t" << ss2 << "\t" << ss3 ;//用QString来写入
                          data.close();
                      }
                      y.savecoursetxt();//保存
                }

             else if(whichwork==2){//进行删除课程确认操作
                    Manage y;
                    y.getcoursetxt();
                    y.getstudenttxt();
                    y.getteachertxt();


                    QString ss1=ui->mgetthing->text();

                     string tr;
                     tr=ss1.toStdString();
                     const char *cpc=tr.data();
                     char* ccname=new char[100];
                     strcpy(ccname,cpc);

                     if(y.mfindcname(ccname)){//确保有该课程
                           for (Course* pp = y.mchead; pp->cnext != y.mcend; pp = pp->cnext){
                               if (!strcmp(pp->cnext->cname, ccname)){
                                      Course* temp = NULL;
                                      temp = pp->cnext;
                                      pp->cnext = pp->cnext->cnext;
                                      delete temp;
                                      ui->mchooseone->setText("删除成功!");
                                      QString &str=look;
                                      str+="\n\n删除成功\n课程："+ss1;
                                      ui->mwanttosee->setText(str);

                                      y.savecoursetxt();//保存
                                      break;
                               }
                           }
                     }
                     else{
                             ui->mchooseone->setText("信息错误，请重新核对更改输入的信息");
                             QString &str=look;
                             str+="\n\n刚刚输入的错误信息\n课程：："+ss1;
                             ui->mwanttosee->setText(str);
                      }

                     ui->mget3->show();//显示第三个输入
                     ui->mget2->show();
                 }

             else if(whichwork==3){//进行添加学生确认操作
                Manage y;
                y.getcoursetxt();
                y.getstudenttxt();
                y.getteachertxt();


                QString ss1=ui->mgetthing->text();
                QString ss2=ui->mget2->text();
                 QString ss3=ui->mget3->text();
                 QString ss4=ui->mget4->text();

                       ui->mchooseone->setText("添加成功!");
                       QString &str=look;
                       str+="\n\n添加学生成功\n学号："+ss1+"\t姓名："+ss2+"\t班级："+ss3+"\t专业："+ss4;
                       ui->mwanttosee->setText(str);

                       //直接在文本后面添加
                       QFile data("D:/C++qt/work/managetest/sortstudent.txt");
                      if (data.open(QFile::WriteOnly | QIODevice::Append))//在后增加的打开方式
                      {
                          QTextStream outstudent(&data);
                          outstudent.setCodec("UTF-8");//设置为UTF-8编码
                          outstudent <<"\n"<< ss1 << "\t" << ss2 << "\t" << ss3 << "\t" << ss4;//用QString来写入
                          data.close();
                      }
                      y.savestudenttxt();//保存
                      ui->mget4->hide();
                }

             else if(whichwork==4){//进行删除学生确认操作
                    Manage y;
                    y.getcoursetxt();
                    y.getstudenttxt();
                    y.getteachertxt();


                    QString ss1=ui->mgetthing->text();

                     string tr;
                     tr=ss1.toStdString();
                     const char *cpc=tr.data();
                     char* ssname=new char[100];
                     strcpy(ssname,cpc);

                     if(y.mfindsname(ssname)){//确保有该学生
                           for (Student* pp = y.mshead; pp->snext != y.msend; pp = pp->snext){
                               if (!strcmp(pp->snext->sname, ssname)){
                                      Student* temp = NULL;
                                      temp = pp->snext;
                                      pp->snext = pp->snext->snext;
                                      delete temp;
                                      ui->mchooseone->setText("删除成功!");
                                      QString &str=look;
                                      str+="\n\n删除成功\n学生："+ss1;
                                      ui->mwanttosee->setText(str);

                                      y.savestudenttxt();//保存
                                      break;
                               }
                           }
                     }
                     else{
                             ui->mchooseone->setText("信息错误，请重新核对更改输入的信息");
                             QString &str=look;
                             str+="\n\n刚刚输入的错误信息\n学生：："+ss1;
                             ui->mwanttosee->setText(str);
                      }

                     ui->mget3->show();//显示第三个输入
                     ui->mget2->show();
                 }
             else if(whichwork==5){//进行添加教师确认操作
                Manage y;
                y.getcoursetxt();
                y.getstudenttxt();
                y.getteachertxt();


                QString ss1=ui->mgetthing->text();
                QString ss2=ui->mget2->text();
                 QString ss3=ui->mget3->text();


                 string tr;
                 tr=ss3.toStdString();
                 const char *cpc3=tr.data();
                 char* ccname=new char[100];
                 strcpy(ccname,cpc3);

                 if(y.mfindcname(ccname)){//确保有该课程

                       ui->mchooseone->setText("添加成功!");
                       QString &str=look;
                       str+="\n\n添加教师成功\n编号："+ss1+"\t姓名："+ss2+"\t教授课程："+ss3;
                       ui->mwanttosee->setText(str);

                       //直接在文本后面添加
                       QFile data("D:/C++qt/work/managetest/sortteacher.txt");
                      if (data.open(QFile::WriteOnly | QIODevice::Append))//在后增加的打开方式
                      {
                          QTextStream outteacher(&data);
                          outteacher.setCodec("UTF-8");//设置为UTF-8编码
                          outteacher <<"\n"<< ss1 << "\t" << ss2 << "\t" << ss3 ;//用QString来写入
                          data.close();
                      }

                      y.saveteachertxt();//保存
                 }
                      else{
                              ui->mchooseone->setText("信息错误，请重新核对更改输入的信息");
                              QString &str=look;
                              str+="\n\n刚刚输入的错误课程信息\t教授课程："+ss3;
                              ui->mwanttosee->setText(str);
                       }
                }

             else if(whichwork==6){//进行删除教师确认操作
                    Manage y;
                    y.getcoursetxt();
                    y.getstudenttxt();
                    y.getteachertxt();


                    QString ss1=ui->mgetthing->text();

                     string tr;
                     tr=ss1.toStdString();
                     const char *cpc=tr.data();
                     char* ssname=new char[100];
                     strcpy(ssname,cpc);

                     if(y.mfindtname(ssname)){//确保有该教师
                           for (Teacher* pp = y.mthead; pp->tnext != y.mtend; pp = pp->tnext){
                               if (!strcmp(pp->tnext->tname, ssname)){
                                      Teacher* temp = NULL;
                                      temp = pp->tnext;
                                      pp->tnext = pp->tnext->tnext;
                                      delete temp;
                                      ui->mchooseone->setText("删除成功!");
                                      QString &str=look;
                                      str+="\n\n删除成功\n教师："+ss1;
                                      ui->mwanttosee->setText(str);

                                      y.saveteachertxt();//保存
                                      break;
                               }
                           }
                     }
                     else{
                             ui->mchooseone->setText("信息错误，请重新核对更改输入的信息");
                             QString &str=look;
                             str+="\n\n刚刚输入的错误信息\n教师：："+ss1;
                             ui->mwanttosee->setText(str);
                      }

                     ui->mget3->show();//显示第三个输入
                     ui->mget2->show();
                 }

        }
                );

}

MainWindow::~MainWindow()
{
    delete ui;
}
