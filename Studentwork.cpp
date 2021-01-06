#include"mymanage.h"
#include "ui_mainwindow.h"

Studentwork::~Studentwork() {//析构，将动态内存delete
    if (panduan[0] == 1) {//判断是否进行了成绩文本操作
        for (Student* temp; sshead->ssnext != ssend;) {//删去对成绩处理指针
            temp = sshead->ssnext;
            sshead->ssnext = sshead->ssnext->ssnext;
            delete temp;
        }
        delete sshead;
        delete ssend;
    }

    if (panduan[1] == 1) {//判断是否进行了学生文本操作
        for (Student* temp; shead->snext != send;) {//删去对学生处理指针
            temp = shead->snext;
            shead->snext = shead->snext->snext;
            delete temp;
        }
        delete shead;
        delete send;
    }

    if (panduan[2] == 1) {//判断是否进行了课程文本操作
        for (Course* temp; schead->cnext != scend;) {//删去对课程处理指针
            temp = schead->cnext;
            schead->cnext = schead->cnext->cnext;
            delete temp;
        }
        delete schead;
        delete scend;
    }
}
void Studentwork::savescoretxt() {//保存成绩文本，用sshead,ssend来处理（保存删除后的）

     QFile data("D:/C++qt/work/managetest/sort.txt");
    if (data.open(QFile::WriteOnly | QIODevice::Truncate))
    {
        QTextStream outscore(&data);
        outscore.setCodec("UTF-8");

        for (Student* p = sshead->ssnext; p->sid[0]>='0'&&p->sid[0]<='9'; p = p->ssnext){//从头指针的后一个ssnext到尾指针
            outscore << QString(p->sid) << "\t" << QString(p->sname) << "\t" << QString(p->scourse.cname) << "\t" << QString::number(p->scourse.score) << '\n';

        }

        data.close();
    }

   // QTextCodec::setCodecForCStrings(QTextCodec::codecForName(“UTF-8”));

    //QString s = QString::fromUtf8(u8"中国");

  /* outscore.open("D:/C++qt/work/managetest/sort.txt");

    if (outscore) {//用来判断open操作是否成功
        for (Student* p = sshead->ssnext; p != ssend; p = p->ssnext)//从头指针的后一个ssnext到尾指针
            outscore << p->sid << "\t" << p->sname << "\t" << p->scourse.cname << "\t" << p->scourse.score << '\n';
        outscore.close();//关闭文件
    }*/
}
void  Studentwork::getscoretxt() {//获取成绩文本，用tshead,tsend来处理
    panduan[0] = 1;//代表进行了成绩文本的读取
    sshead = new Student;//先开一个头指针sshead，指向Student对象
    sshead->ssnext = new Student;//头指针指向的ssnext，也开个，指向Student对象
    ssend = sshead->ssnext;//用一个尾指针来获取那个ssnext
    inscore.open("D:/C++qt/work/managetest/sort.txt");//读取
    if (!inscore)
        qDebug() << "这是一个新系统，请先输入。" << endl;
    else {

        while (!inscore.eof()) {//没到结尾
            ssend->readscore(inscore);//读取尾指针的内容
            if (ssend->sname[0] == '\0') {//如果尾指针的内容中姓名为0，即没了，就结束
                //end->scourse.pop_back();
                break;
            }
            ssend->ssnext = new Student;//为尾指针指向的ssnext开一个
            ssend = ssend->ssnext;//用更改尾指针为尾指针指向的ssnext
        }
        inscore.close();
        qDebug() << "读取学生成绩信息成功!" << endl;
    }
}

void Studentwork::savestudenttxt() {//保存学生文本，用shead,send来处理
    QFile data("D:/C++qt/work/managetest/sortstudent.txt");
   if (data.open(QFile::WriteOnly | QIODevice::Truncate))
   {
       QTextStream outstudent(&data);
       outstudent.setCodec("UTF-8");
       for (Student* p = shead->snext; p != send; p = p->snext)//从头指针的后一个ssnext到尾指针
           outstudent << QString(p->sid) << "\t" << QString(p->sname) << "\t" << QString(p->sclass) << "\t" << QString(p->major) << '\n';
       data.close();
   }
    /*outstudent.open("D:/C++qt/work/managetest/sortstudent.txt");
    if (outstudent) {//用来判断open操作是否成功
        for (Student* p = shead->snext; p != send; p = p->snext)
            outstudent << p->sid << "\t" << p->sname << "\t" << p->sclass << "\t" << p->major << '\n';
        outstudent.close();//关闭文件
    }*/
}
void  Studentwork::getstudenttxt() {//获取学生文本，用thead,tend来处理
    panduan[1] = 1;//代表进行了学生文本的读取
    shead = new Student;//动态内存函数结束后会自动销毁
    shead->snext = new Student;//用snext获取
    send = shead->snext;
    instudent.open("D:/C++qt/work/managetest/sortstudent.txt");//读取
    if (!instudent)
        qDebug() << "这是一个新系统，请先输入。" << endl;
    else {
        while (!instudent.eof()) {//没到结尾
            send->readstudent(instudent);
            if (send->sid[0] == '\0') {
                //end->scourse.pop_back();
                break;
            }
            send->snext = new Student;
            send = send->snext;
        }
        instudent.close();
        qDebug() << "读取学生信息成功!" << endl;
    }
}

void Studentwork::savecoursetxt() {//保存课程文本
    outcourse.open("D:/C++qt/work/managetest/sortcourse.txt");
    if (outcourse) {//用来判断open操作是否成功
        for (Course* p = schead->cnext; p != scend; p = p->cnext)
            outcourse << p->cid << "\t" << p->cname << "\t" << p->credit << '\n';
        outcourse.close();//关闭文件
    }
}
void  Studentwork::getcoursetxt() {//获取课程文本
    panduan[2] = 1;//代表进行了课程文本的读取
    schead = new Course;//动态内存函数结束后会自动销毁
    schead->cnext = new Course;
    scend = schead->cnext;
    incourse.open("D:/C++qt/work/managetest/sortcourse.txt");//读取
    if (!incourse) {
        qDebug() << "这是一个新系统，请先输入。" << endl;

    }
    else {
        while (!incourse.eof()) {//没到结尾
            scend->readcourse(incourse);
            if (scend->cid[0] == '\0') {
                //end->scourse.pop_back();
                break;
            }
            scend->cnext = new Course;
            scend = scend->cnext;
        }
        incourse.close();
        qDebug() << "读取学生成绩信息成功!" << endl;
    }
}

Course* Studentwork::sfindcname(char* name) {//由名字找课程(课程文本)
    for (Course* p = schead; p->cnext != scend; p = p->cnext)
        if (!strcmp(p->cnext->cname, name))return p;
    return NULL;
}
Course* Studentwork::sfindcid(char* Id) {//由学号找课程(课程文本)
    for (Course* p = schead; p->cnext != scend; p = p->cnext)
        if (!strcmp(p->cnext->cid, Id))return p;
    return NULL;
}


Student* Studentwork::sfindsname(char* name) {//由名字找学生(成绩文本，用sshead,ssnext....)
    for (Student* p = sshead; p->ssnext != ssend; p = p->ssnext)
        if (!strcmp(p->ssnext->sname, name))return p;
    return NULL;
}
Student* Studentwork::sfindsid(char* Id) {//由学号找学生(成绩文本，用tshead,ssnext....)
    for (Student* p = sshead; p->ssnext != ssend; p = p->ssnext)
        if (!strcmp(p->ssnext->sid, Id))return p;
    return NULL;
}


QString Studentwork::getstudentscore(QString &str,int x,char *who) {//读取显示目标学生所有课程成绩，用sshead,ssend来处理
    str+="\n\n学生的所有成绩：";
    if (x == 1) {
        if (sfindsname(who)) {
            double zong = 0;//用于计算总分
            for (Student* pp = sshead; pp->ssnext != ssend; pp = pp->ssnext) {
                if (!strcmp(pp->ssnext->sname, who)) {
                    if (pp->ssnext->scourse.score != -1) {
                        str+=("\n课程：" +QString(pp->ssnext->scourse.cname)+ "\t成绩："+QString::number(pp->ssnext->scourse.score));
                        zong += pp->ssnext->scourse.score;
                    }
                    else
                        str+=("\n课程：" +QString(pp->ssnext->scourse.cname)+ "\t未参加考试，无成绩：");
                }
            }
            str+=("\n总分为："+QString::number(zong));
        }
        else {
            str+="\n没有找到";
        }
    }
    else {
        if (sfindsid(who)) {
            double zong = 0;//用于计算总分
            for (Student* pp = sshead; pp->ssnext != ssend; pp = pp->ssnext) {
                if (!strcmp(pp->ssnext->sid, who)) {
                    if (pp->ssnext->scourse.score != -1) {
                        str+=("\n课程：" +QString(pp->ssnext->scourse.cname)+ "\t成绩："+QString::number(pp->ssnext->scourse.score));
                        zong += pp->ssnext->scourse.score;
                    }
                    else
                        str+=("\n课程：" +QString(pp->ssnext->scourse.cname)+ "\t未参加考试，无成绩：");
                }
            }
            str+=("\n总分为："+QString::number(zong));
        }
        else {
            str+="\n没有找到";
        }
    }
    return str;
}

QString Studentwork::getcoursecredit(QString &str,int x,char *who) {//读取显示目标学生所有课程学分
        str+="\n\n学生的所有课程：";
    if (x == 1) {
        if ( sfindsname(who)) {
            int zong = 0;//用于算现有总学分
            for (Student* pp = sshead; pp->ssnext != ssend; pp = pp->ssnext) {//找到学生
                if (!strcmp(pp->ssnext->sname, who)) {//当指针的对象的姓名是目标学生姓名时

                    for (Course* pc = schead; pc != scend; pc = pc->cnext) {//找到课程          （注意判断时，是直接判断pc是否有到底）
                        if (!strcmp(pp->ssnext->scourse.cname, pc->cname)) {//当指针的对象的课程名是目标课程名时
                            str+=("\n课程：" +QString(pc->cname)+ "\t学分："+QString::number(pc->credit));
                            zong += pc->credit;
                        }
                    }
                }
            }
            str+=("\n现有总学分："+QString::number(zong));
        }
        else {
            str+="\n没有找到!";
        }
    }
    else {
        if ( sfindsid(who)) {
            int zong = 0;//用于算现有总学分
            for (Student* pp = sshead; pp->ssnext != ssend; pp = pp->ssnext) {//找到学生
                if (!strcmp(pp->ssnext->sid, who)) {//当指针的对象的学号是目标学生学号时

                    for (Course* pc = schead; pc != scend; pc = pc->cnext) {//找到课程          （注意判断时，是直接判断pc是否有到底）
                        if (!strcmp(pp->ssnext->scourse.cname, pc->cname)) {//当指针的对象的课程名是目标课程名时
                            str+=("\n课程：" +QString(pc->cname)+ "\t学分："+QString::number(pc->credit));
                            zong += pc->credit;
                        }
                    }
                }
            }
            str+=("\n现有总学分："+QString::number(zong));
        }
        else {
            str+="\n没有找到!";
        }
    }
    return str;
}

QString Studentwork::showallcourse(QString &str) {//获取显示所有课程，用于选课
    str+="\n\n课程编号:\t课程名称:\t课程学分:";
    for (Course* p = schead->cnext; p != scend; p = p->cnext) {
        str=p->showcourse(str);//显示课程
    }
    return str;

}
/*
QString Studentwork::choosecourse(QString &str,char cname,char sid,char sname) {//添加选择课程到成绩文本
        str+="\n请填写选课信息";
        //ssend->sinputcourse(QString &str,char *name,char*ke,char*hh);
        QString::strncpy(ssend->sname,cname);
        ssend->ssnext = new Student;
        ssend = ssend->ssnext;
        str+="\n添加成功!";
        return str;
}*/

// 删除信息
QString Studentwork::sremovecourse(QString &str,char *name,char*ke) {//学生退选课到成绩文本
    if (sfindcname(name)) {
        for (Student* pp = sshead; pp->ssnext != ssend; pp = pp->ssnext)
                    if ((!strcmp(pp->ssnext->sname, name))&&(!strcmp(pp->ssnext->scourse.cname,ke))) {
                        Student* temp = NULL;
                        temp = pp->ssnext;
                        pp->ssnext = pp->ssnext->ssnext;
                        delete temp;
                        str+="\n删除成功";
                    }
                   else
                        str+="\n没有找到该课程";
    }
    else {
        str+="\n没有找到该学生";
    }
    return str;
}
