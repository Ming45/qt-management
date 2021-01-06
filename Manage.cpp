#include"mymanage.h"

Manage::~Manage() {//析构，将动态内存delete

    if (panduan[0] == 1) {//判断是否进行了学生文本操作
        for (Student* temp; mshead->snext != msend;) {
            temp = mshead->snext;
            mshead->snext = mshead->snext->snext;
            delete temp;
        }
        delete mshead;
        delete msend;
    }

    if (panduan[1] == 1) {//判断是否进行了课程文本操作
        for (Course* temp; mchead->cnext != mcend;) {//删去对课程处理指针
            temp = mchead->cnext;
            mchead->cnext = mchead->cnext->cnext;
            delete temp;
        }
        delete mchead;
        delete mcend;
    }

    if (panduan[2] == 1) {//判断是否进行了教师文本操作
        for (Teacher* temp; mthead->tnext != mtend;) {
            temp = mthead->tnext;
            mthead->tnext = mthead->tnext->tnext;
            delete temp;
        }
        delete mthead;
        delete mtend;
    }

}

void Manage::savestudenttxt() {//保存学生文本，到新的文本中
    QFile data("D:/C++qt/work/managetest/newsortstudent.txt");
   if (data.open(QFile::WriteOnly | QIODevice::Truncate))
   {
       QTextStream outstudent(&data);
       outstudent.setCodec("UTF-8");

       for (Student* p = mshead->snext; p->sid[0]>='0'&&p->sid[0]<='9'; p = p->snext){
           outstudent << QString(p->sid) << "\t" << QString(p->sname) << "\t" << QString(p->sclass)<< "\t" << QString(p->major) << '\n';
       }

       data.close();
   }
    /*
    outstudent.open("D:/C++qt/work/myscoremanage/newsortstudent.txt");
    if (outstudent) {//用来判断open操作是否成功
        for (Student* p = mshead->snext; p != msend; p = p->snext)
            outstudent << p->sid << "\t" << p->sname << "\t" << p->sclass << "\t" << p->major << '\n';
        outstudent.close();//关闭文件
    }*/
}
void  Manage::getstudenttxt() {//获取学生文本
    panduan[0] = 1;//代表进行了学生文本的读取
    mshead = new Student;//动态内存函数结束后会自动销毁
    mshead->snext = new Student;//用snext获取
    msend = mshead->snext;
    instudent.open("D:/C++qt/work/myscoremanage/sortstudent.txt");//读取
    if (!instudent)
        qDebug() << "这是一个新系统，请先输入。" << endl;
    else {
        while (!instudent.eof()) {//没到结尾
            msend->readstudent(instudent);
            if (msend->sname[0] == '\0') {
                //end->scourse.pop_back();
                break;
            }
            msend->snext = new Student;
            msend = msend->snext;
        }
        instudent.close();
        qDebug() << "读取学生信息成功!" << endl;
    }
}

void Manage::savecoursetxt() {//保存课程文本，到新的文本中
    QFile data("D:/C++qt/work/managetest/newsortcourse.txt");
   if (data.open(QFile::WriteOnly | QIODevice::Truncate))
   {
       QTextStream outcourse(&data);
       outcourse.setCodec("UTF-8");

       for (Course* p = mchead->cnext; p->cid[0]>='0'&&p->cid[0]<='9'; p = p->cnext){
           outcourse << QString(p->cid) << "\t" << QString(p->cname) << "\t" << QString::number(p->credit) << '\n';
       }

       data.close();
   }
    /*
    outcourse.open("D:/C++qt/work/myscoremanage/newsortcourse.txt");
    if (outcourse) {//用来判断open操作是否成功
        for (Course* p = mchead->cnext; p != mcend; p = p->cnext)
            outcourse << p->cid << "\t" << p->cname << "\t" << p->credit << '\n';
        outcourse.close();//关闭文件
    }*/
}
void  Manage::getcoursetxt() {//获取课程文本
    panduan[1] = 1;//代表进行了课程文本的读取
    mchead = new Course;//动态内存函数结束后会自动销毁
    mchead->cnext = new Course;
    mcend = mchead->cnext;
    incourse.open("D:/C++qt/work/myscoremanage/sortcourse.txt");//读取
    if (!incourse) {
        qDebug() << "这是一个新系统，请先输入。" << endl;

    }
    else {
        while (!incourse.eof()) {//没到结尾
            mcend->readcourse(incourse);
            if (mcend->cid[0] == '\0') {
                //end->scourse.pop_back();
                break;
            }
            mcend->cnext = new Course;
            mcend = mcend->cnext;
        }
        incourse.close();
        qDebug() << "读取学生成绩信息成功!" << endl;
    }
}
void Manage::saveteachertxt() {//保存教师文本，到新的文本中
    QFile data("D:/C++qt/work/managetest/newsortteacher.txt");
   if (data.open(QFile::WriteOnly | QIODevice::Truncate))
   {
       QTextStream outteacher(&data);
       outteacher.setCodec("UTF-8");

       for (Teacher* p = mthead->tnext; p->tid[0]>='0'&&p->tid[0]<='9'; p = p->tnext){
           outteacher << QString(p->tid) << "\t" << QString(p->tname) << "\t" << QString(p->tcourse.cname) << '\n';
       }

       data.close();
   }
    /*
    outteacher.open("D:/C++qt/work/myscoremanage/newsortteacher.txt");
    if (outteacher) {//用来判断open操作是否成功
        for (Teacher* p = mthead->tnext; p != mtend; p = p->tnext)
            outteacher << p->tid << "\t" << p->tname << "\t" << p->tcourse.cname << '\n';
        outteacher.close();//关闭文件
    }*/
}
void Manage::getteachertxt() {//获取教师文本
    panduan[2] = 1;//代表进行了教师文本的读取
    mthead = new Teacher;//动态内存函数结束后会自动销毁
    mthead->tnext = new Teacher;
    mtend = mthead->tnext;
    inteacher.open("D:/C++qt/work/myscoremanage/sortteacher.txt");//读取
    if (!inteacher)
        qDebug() << "这是一个新系统，请先输入。" << endl;
    else {
        while (!inteacher.eof()) {//没到结尾
            mtend->readteacher(inteacher);
            if (mtend->tname[0] == '\0') {
                //end->scourse.pop_back();
                break;
            }
            mtend->tnext = new Teacher;
            mtend = mtend->tnext;
        }
        inteacher.close();
        qDebug() << "读取学生信息成功!" << endl;
    }
}

void Manage::addstudent() {//添加学生
    int A = 1;
    while (A == 1) {
        msend->inputstudent();
        msend->snext = new Student;
        msend = msend->snext;
        qDebug() << "添加成功!" << endl;
        qDebug() << " 继续添加吗?1是确定，0是否定";
        cin >> A;
        if (A != 1) {
            if (A == 0) { break; }
            else {
                qDebug() << "错误，请重输：";
                cin >> A;
            }
        }
    }
    int _getch(void);
    system("pause");
}

void Manage::addteacher() {//添加教师
    int A = 1;
    while (A == 1) {
        mtend->inputteacher();
        mtend->tnext = new Teacher;
        mtend = mtend->tnext;
        qDebug() << "添加成功!" << endl;
        qDebug() << " 继续添加吗?1是确定，0是否定";
        cin >> A;
        if (A != 1) {
            if (A == 0) { break; }
            else {
                qDebug() << "错误，请重输：";
                cin >> A;
            }
        }
    }
    int _getch(void);
    system("pause");
}
void Manage::addcourse() {//添加课程
    int A = 1;
    while (A == 1) {
        mcend->inputcourse();
        mcend->cnext = new Course;
        mcend = mcend->cnext;
        qDebug() << "添加成功!" << endl;
        qDebug() << " 继续添加吗?1是确定，0是否定";
        cin >> A;
        if (A != 1) {
            if (A == 0) { break; }
            else {
                qDebug() << "错误，请重输：";
                cin >> A;
            }
        }
    }
    int _getch(void);
    system("pause");
}

Student* Manage::mfindsname(char* name) {//由名字找学生(学生文本)
    for (Student* p = mshead; p->snext != msend; p = p->snext)
        if (!strcmp(p->snext->sname, name))return p;
    return NULL;
}

Teacher* Manage::mfindtname(char* name) {//由名字找教师(教师文本)
    for (Teacher* p = mthead; p->tnext != mtend; p = p->tnext)
        if (!strcmp(p->tnext->tname, name))return p;
    return NULL;
}
Course* Manage::mfindcname(char* name) {//由名字找课程(课程文本)
    for (Course* p = mchead; p->cnext != mcend; p = p->cnext)
        if (!strcmp(p->cnext->cname, name))return p;
    return NULL;
}

// 删除信息
void Manage::mremovestudent() {//删除学生到学生文本
    char name[20];
    Student* p = NULL, * temp = NULL;
    qDebug() << "请输入要删除的学生的姓名:" << endl;
    cin >> name;
    if (p == mfindsname(name)) {
        int A;
        temp = p->snext;
        p->snext = p->snext->snext;
        qDebug() << "确定删除吗？1是确定，0是否定" << endl;
        qDebug() << "请输入：";
        cin >> A;
        if (A == 1) {
            delete temp;
            qDebug() << "删除成功!" << endl;
        }
        else qDebug() << "删除失败" << endl;
        int _getch(void);
        system("pause");
    }
    else {
        qDebug() << "没有找到!" << endl;
        int _getch(void);
        system("pause");
    }
}

void Manage::mremoveteacher() {//删除教师到教师文本
    char name[20];
    Teacher* p = NULL, * temp = NULL;
    qDebug() << "请输入要删除的学生的姓名:" << endl;
    cin >> name;
    if (p == mfindtname(name)) {
        int A;
        temp = p->tnext;
        p->tnext = p->tnext->tnext;
        qDebug() << "确定删除吗？1是确定，0是否定" << endl;
        qDebug() << "请输入：";
        cin >> A;
        if (A == 1) {
            delete temp;
            qDebug() << "删除成功!" << endl;
        }
        else qDebug() << "删除失败" << endl;
        int _getch(void);
        system("pause");
    }
    else {
        qDebug() << "没有找到!" << endl;
        int _getch(void);
        system("pause");
    }
}

void Manage::mremovecourse() {//删除课程到课程文本
    char name[20];
    Course* p = NULL, * temp = NULL;
    qDebug() << "请输入要删除的学生的姓名:" << endl;
    cin >> name;
    if (p == mfindcname(name)) {
        int A;
        temp = p->cnext;
        p->cnext = p->cnext->cnext;
        qDebug() << "确定删除吗？1是确定，0是否定" << endl;
        qDebug() << "请输入：";
        cin >> A;
        if (A == 1) {
            delete temp;
            qDebug() << "删除成功!" << endl;
        }
        else qDebug() << "删除失败" << endl;
        int _getch(void);
        system("pause");
    }
    else {
        qDebug() << "没有找到!" << endl;
        int _getch(void);
        system("pause");
    }
}
