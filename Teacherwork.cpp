#include"mymanage.h"

Teacherwork::~Teacherwork() {//析构，将动态内存delete

    if (panduan[0] == 1) {//判断是否进行了成绩文本操作
        for (Student* temp; tshead->ssnext != tsend;) {//删去tshead, tsend，ssnext所指
            temp = tshead->ssnext;
            tshead->ssnext = tshead->ssnext->ssnext;
            delete temp;
        }
        delete tshead;
        delete tsend;
    }

    if (panduan[1] == 1) {//判断是否进行了学生文本操作
        for (Student* temp; thead->snext != tend;) {//删去thead, tend，snext所指
            temp = thead->snext;
            thead->snext = thead->snext->snext;
            delete temp;
        }
        delete thead;
        delete tend;
    }

    if (panduan[2] == 1) {//判断是否进行了教师文本操作
        for (Teacher* temp; tthead->tnext != ttend;) {
            temp = tthead->tnext;
            tthead->tnext = tthead->tnext->tnext;
            delete temp;
        }
        delete tthead;
        delete ttend;
    }

}
void Teacherwork::savescoretxt() {//保存成绩文本，用tshead,tsend来处理
    QFile data("D:/C++qt/work/managetest/sort.txt");
   if (data.open(QFile::WriteOnly | QIODevice::Truncate))
   {
       QTextStream outscore(&data);
       outscore.setCodec("UTF-8");

       for (Student* p = tshead->ssnext; p->sid[0]>='0'&&p->sid[0]<='9'; p = p->ssnext){//从头指针的后一个ssnext到尾指针
           outscore << QString(p->sid) << "\t" << QString(p->sname) << "\t" << QString(p->scourse.cname) << "\t" << QString::number(p->scourse.score) << '\n';

       }

       data.close();
   }
    /*outscore.open("D:/C++qt/work/managetest/sort.txt");
    if (outscore) {//用来判断open操作是否成功
        for (Student* p = tshead->ssnext; p != tsend; p = p->ssnext)
            outscore << p->sid << "\t" << p->sname << "\t" << p->scourse.cname << "\t" << p->scourse.score << '\n';
        outscore.close();//关闭文件
    }*/
}
void  Teacherwork::getscoretxt() {//获取成绩文本，用tshead,tsend来处理
    panduan[0] = 1;//代表进行了成绩文本的读取
    tshead = new Student;//动态内存函数结束后会自动销毁
    tshead->ssnext = new Student;
    tsend = tshead->ssnext;
    inscore.open("D:/C++qt/work/managetest/sort.txt");//读取
    if (!inscore)
        qDebug() << "这是一个新系统，请先输入。" << endl;
    else {
        while (!inscore.eof()) {//没到结尾
            tsend->readscore(inscore);
            if (tsend->sname[0] == '\0') {
                //end->scourse.pop_back();
                break;
            }
            tsend->ssnext = new Student;
            tsend = tsend->ssnext;
        }
        inscore.close();
        qDebug() << "读取学生成绩信息成功!" << endl;
    }
}

void Teacherwork::savestudenttxt() {//保存学生文本，用thead,tend来处理
    outstudent.open("D:/C++qt/work/managetest/sortstudent.txt");
    if (outstudent) {//用来判断open操作是否成功
        for (Student* p = thead->snext; p != tend; p = p->snext)
            outstudent << p->sid << "\t" << p->sname << "\t" << p->sclass << "\t" << p->major << '\n';
        outstudent.close();//关闭文件
    }
}
void  Teacherwork::getstudenttxt() {//获取学生文本，用thead,tend来处理
    panduan[1] = 1;//代表进行了学生文本的读取
    thead = new Student;//动态内存函数结束后会自动销毁
    thead->snext = new Student;//用snext获取
    tend = thead->snext;
    instudent.open("D:/C++qt/work/managetest/sortstudent.txt");//读取
    if (!instudent)
        qDebug() << "这是一个新系统，请先输入。" << endl;
    else {
        while (!instudent.eof()) {//没到结尾
            tend->readstudent(instudent);
            if (tend->sname[0] == '\0') {
                //end->scourse.pop_back();
                break;
            }
            tend->snext = new Student;
            tend = tend->snext;
        }
        instudent.close();
        qDebug() << "读取学生信息成功!" << endl;
    }
}

void Teacherwork::saveteachertxt() {//保存教师文本
    outteacher.open("D:/C++qt/work/managetest/sortteacher.txt");
    if (outteacher) {//用来判断open操作是否成功
        for (Teacher* p = tthead->tnext; p != ttend; p = p->tnext)
            outteacher << p->tid << "\t" << p->tname << "\t" << p->tcourse.cname << '\n';
        outteacher.close();//关闭文件
    }
}
void  Teacherwork::getteachertxt() {//获取教师文本
    panduan[2] = 1;//代表进行了教师文本的读取
    tthead = new Teacher;//动态内存函数结束后会自动销毁
    tthead->tnext = new Teacher;
    ttend = tthead->tnext;
    inteacher.open("D:/C++qt/work/managetest/sortteacher.txt");//读取
    if (!inteacher)
        qDebug() << "这是一个新系统，请先输入。" << endl;
    else {
        while (!inteacher.eof()) {//没到结尾
            ttend->readteacher(inteacher);
            if (ttend->tname[0] == '\0') {
                //end->scourse.pop_back();
                break;
            }
            ttend->tnext = new Teacher;
            ttend = ttend->tnext;
        }
        inteacher.close();
        qDebug() << "读取学生信息成功!" << endl;
    }
}


void Teacherwork::showallstudent() {//获取显示所有学生，用thead,tend来处理
    qDebug() << "学号:" << "\t姓名:" << endl;
    for (Student* p = thead->snext; p != tend; p = p->snext) {
        p->showstudent();//显示学生
    }

}
void Teacherwork::addscore() {//添加成绩
    int A = 1;
    while (A == 1) {
        tsend->inputscore();
        tsend->ssnext = new Student;
        tsend = tsend->ssnext;
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
QString Teacherwork::showstudentscore(QString &str,int x,char *who) {//读取显示目标学生所有课程成绩以及总分
    str+=("\n\n学生:"+QString(who)+"的所有成绩：");
    if (x == 1) {
        if (tfindsname(who)) {
            double zong = 0;//用于计算总分
            //qDebug() << "已找到学生的信息，他的课程及成绩如下" << endl;
            for (Student* pp = tshead; pp->ssnext != tsend; pp = pp->ssnext) {
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
        if (tfindsid(who)) {
            double zong = 0;//用于计算总分
            for (Student* pp = tshead; pp->ssnext != tsend; pp = pp->ssnext) {
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
void Teacherwork::modifyscore() {//修改学生具体某课成绩
    char who[100];
    //Student* p = NULL;
    int x = 0;
    qDebug() << "请选择由姓名还是学号查找修改(1代表名字，2代表学号)";
    cin >> x;
    if (x == 1) {
        qDebug() << "请输入要修改的人的姓名:";
        cin >> who;
        if (tfindsname(who)) {
            qDebug() << "已找到学生的信息，请输入选择其选修的课程" << endl;
            char coursename[100];
            cin >> coursename;
            for (Student* pp = tshead; pp->ssnext != tsend; pp = pp->ssnext) {
                if (!strcmp(pp->ssnext->sname, who)) {//确保是目标学生
                    if (!strcmp(pp->ssnext->scourse.cname, coursename)) {//确保是某门课
                        pp->ssnext->inputscore();
                    }
                }
            }
            int _getch(void);
            system("pause");
        }
        else {
            qDebug() << "没有找到!" << endl;
            int _getch(void);
            system("pause");
        }
    }
    else {
        qDebug() << "请输入要修改的人的学号:";
        cin >> who;
        if (tfindsid(who)) {
            qDebug() << "已找到学生的信息，请输入选择其选修的课程" << endl;
            char coursename[100];
            cin >> coursename;
            for (Student* pp = tshead; pp->ssnext != tsend; pp = pp->ssnext) {
                if (!strcmp(pp->ssnext->sname, who)) {//确保是目标学生
                    if (!strcmp(pp->ssnext->scourse.cname, coursename)) {//确保是某门课
                        pp->ssnext->inputscore();
                    }
                }
            }
            int _getch(void);
            system("pause");
        }
        else {
            qDebug() << "没有找到!" << endl;
            int _getch(void);
            system("pause");
        }
    }
}


Student* Teacherwork::tfindsname(char* name) {//由名字找学生(成绩文本，用tshead,ssnext....)
    for (Student* p = tshead; p->ssnext != tsend; p = p->ssnext)
        if (!strcmp(p->ssnext->sname, name))return p;//strcmp函数是string compare(字符串比较)的缩写，用于比较两个字符串并根据比较结果返回整数。
                                                  //基本形式为strcmp(str1,str2)，若str1=str2，则返回零；若str1<str2，则返回负数；若str1>str2，则返回正数
    return NULL;
}
Student* Teacherwork::tfindsid(char* Id) {//由学号找学生(成绩文本，用tshead,ssnext....)
    for (Student* p = tshead; p->ssnext != tsend; p = p->ssnext)
        if (!strcmp(p->ssnext->sid, Id))return p;
    return NULL;
}

Student* Teacherwork::tfindcnamesname(char* name, double high, double low) {//由课程名字,成绩最高值，成绩最低值   找学生(成绩文本，用tshead,ssnext....)
    for (Student* p = tshead; p->ssnext != tsend; p = p->ssnext)
        if (!strcmp(p->ssnext->scourse.cname, name)) {
            if(low<=p->ssnext->scourse.score&&p->ssnext->scourse.score<=high)//如果在成绩区间内
                return p;
        }
    return NULL;
}
Student* Teacherwork::tfindcidsid(char* id, double high, double low) {//由课程编号,成绩最高值，成绩最低值   找学生(成绩文本，用tshead,ssnext....)
    for (Student* p = tshead; p->ssnext != tsend; p = p->ssnext)
        if (!strcmp(p->ssnext->scourse.cid, id)) {
            if (low <= p->ssnext->scourse.score <= high)//如果在成绩区间内
                return p;
        }
    return NULL;
}

Student* Teacherwork::tfindclasssname(char* name) {//教师由教室编号找人(用学生文本)
    for (Student* p = thead; p->snext != tend; p = p->snext)
        if (!strcmp(p->snext->sclass, name))return p;
    return NULL;
}

Student* Teacherwork::tfindcourse(char* name) {//教师由课程名称找选修了的学生(用成绩文本)
    for (Student* p = tshead; p->ssnext != tsend; p = p->ssnext)
        if (!strcmp(p->ssnext->scourse.cname, name))return p;
    return NULL;
}

void Teacherwork::showcoursestudent() {//查找某门课程成绩处于指定分数段内的学生名单，在成绩文本里找
    char who[100];
    double high = 0, low = 0;
    //Student* p = NULL;
    int x = 0;
    qDebug() << "请选择由课程名字还是课程编号查找修改(1代表名字，2代表学号)";
    cin >> x;
    if (x == 1) {
        qDebug() << "请输入要查找的课程名字:";
        cin >> who;
        qDebug() << "请输入要查找成绩范围最高值:";
        cin >> high;
        qDebug() << "请输入要查找成绩范围最低值:";
        cin >> low;
        if (tfindcnamesname(who,high,low)) {
            qDebug() << "已找到该课程成绩范围内学生" << endl;
            for (Student* pp = tshead; pp->ssnext != tsend; pp = pp->ssnext) {
                if (!strcmp(pp->ssnext->scourse.cname, who)) {
                     if (low <= tfindcnamesname(who,high,low)->ssnext->scourse.score <= high){//如果在成绩区间内
                        qDebug() << "学生：" << pp->ssnext->sname << "\t成绩：" << pp->ssnext->scourse.score << endl;
                    }
                }
            }
            int _getch(void);
            system("pause");
        }
        else {
            qDebug() << "没有找到该课程成绩范围内学生!" << endl;
            int _getch(void);
            system("pause");
        }
    }
    else {
        qDebug() << "请输入要查找的课程编号:";
        cin >> who;
        qDebug() << "请输入要查找成绩范围最高值:";
        cin >> high;
        qDebug() << "请输入要查找成绩范围最低值:";
        cin >> low;
        if (tfindcidsid(who, high, low)) {
            qDebug() << "已找到该课程成绩范围内学生" << endl;
            for (Student* pp = tshead; pp->ssnext != tsend; pp = pp->ssnext) {
                if (!strcmp(pp->ssnext->scourse.cid, who)) {
                    if (low <= tfindcidsid(who, high, low)->ssnext->scourse.score <= high) {//如果在成绩区间内
                        qDebug() << "学生：" << pp->ssnext->sname << "\t成绩：" << pp->ssnext->scourse.score << endl;
                    }
                }
            }
            int _getch(void);
            system("pause");
        }
        else {
            qDebug() << "没有找到该课程成绩范围内学生!" << endl;
            int _getch(void);
            system("pause");
        }
    }
}

//统计链表记录总数
int Teacherwork::LC() {
    if (!tshead)
        return 0;
    int n = 0;
    for (Student* p = tshead->ssnext; p != tsend; p = p->ssnext) {
        n++;
    }
    return n;
}


void Teacherwork::swap(Student* p1, Student* p2) {//仅仅为排序时需要的成绩文本的进行排序
    Student* temp = new Student;

    //存放p1到temp
    strcpy_s(temp->sname, p1->sname); //名字                   //strcpy_s函数，将p1->sname字符串给temp->sname
    strcpy_s(temp->sid, p1->sid);//学号
    strcpy_s(temp->scourse.cname, p1->scourse.cname);//课程名字
    temp->scourse.score=p1->scourse.score;//课程成绩

    //将p2放到p1
    strcpy_s(p1->sname, p2->sname); //名字
    strcpy_s(p1->sid, p2->sid);//学号
    strcpy_s(p1->scourse.cname, p2->scourse.cname);//课程名字
    p1->scourse.score = p2->scourse.score;//课程成绩

    //将temp的p1放到p2
    strcpy_s(p2->sname, temp->sname); //名字
    strcpy_s(p2->sid, temp->sid);//学号
    strcpy_s(p2->scourse.cname, temp->scourse.cname);//课程名字
    p2->scourse.score = temp->scourse.score;//课程成绩
}



QString Teacherwork::sortcourse(QString &str,char *which) {

   // Student* p = NULL;
    //char which[50];//要找的课程
    //qDebug() << "请输入要排序的课程：";
   // cin >> which;
    if (tfindcourse(which)) {
        //qDebug() <<  << endl;
        str+="\n\n已找到选修了该门课的学生";
        for (Student* pp = tshead->ssnext; pp != tsend; pp = pp->ssnext) {//从成绩文本里找对应课程的名字，从而找到该学生成绩
            if (!strcmp(pp->scourse.cname, which)) {//成绩文本里的学生选修课程的名字，等于找的课程的名字
                if (pp->scourse.score != -1) {//确保不是-1，未考试的

                    for (Student* ppp = pp->ssnext; ppp != tsend; ppp = ppp->ssnext) {
                        if (!strcmp(ppp->scourse.cname, which)) {
                            if (ppp->scourse.score != -1) {

                                if (ppp->scourse.score < pp->scourse.score) {//如果比之前的小，则交换
                                    swap(ppp, pp);
                                }
                                //cout << "该选修了该门课程的学生：" << ppp->ssnext->sname << "\t成绩：" <<  << endl;
                            }
                        }
                    }

                }
            }
        }
        //qDebug() <<  << endl;
        str+="\n排序完成！";
    }
    else {
        //qDebug() <<  << endl;
        str+="\n\n没有找到选修了该门课的学生";
    }
    return str;
}



QString Teacherwork::countclass(QString &str,char *which)//统计某班级学生所有学生的单科成绩，
{

    if (tfindclasssname(which)) {
        str+="\n\n已找到该班级";
        for (Student* pp = thead; pp->snext != tend; pp = pp->snext)//从学生文本里找班级
            if (!strcmp(pp->snext->sclass, which)) {//找到该班级
                str+="\n该班级的学生：" + QString(pp->snext->sname);
                double zong = 0;//用于计算总分
                for (Student* ppp = tshead; ppp->ssnext != tsend; ppp = ppp->ssnext) {//从成绩文本里找对应学生的名字，从而找到成绩
                    if (!strcmp(ppp->ssnext->sname, pp->snext->sname)) {//成绩文本里的学生的名字，等于学生文本找的学生的名字
                        if (ppp->ssnext->scourse.score != -1) {//确保不是-1，未考试的
                            str+="\n\t\t课程：" +QString(ppp->ssnext->scourse.cname) + "\t成绩：" +QString::number(ppp->ssnext->scourse.score);
                            zong += ppp->ssnext->scourse.score;
                        }
                        else{
                            str+="\n\t\t课程：" +QString(ppp->ssnext->scourse.cname) +"\t未参加考试，无成绩" ;
                        }
                    }
                }
                //qDebug() <<  << "\n"<<endl;
                str+="\n\t\t总分为：" +QString::number(zong);
            }
    }
    else {
        //qDebug() << << endl;
        str+= "\n\n没有找到该班级";
    }
    return str;
}

QString Teacherwork::countcourse(QString &str,char *which)//统计某课程的学生成绩，以及平均值分数，及格率
{
    double renshu = 0, zong = 0, jige = 0;
    if (tfindcourse(which)) {
        str+="\n\n已找到选修了该门课的学生";
        for (Student* ppp = tshead; ppp->ssnext != tsend; ppp = ppp->ssnext) {//从成绩文本里找对应课程的名字，从而找到该学生成绩
            if (!strcmp(ppp->ssnext->scourse.cname, which)) {//成绩文本里的学生选修课程的名字，等于找的课程的名字
                if (ppp->ssnext->scourse.score != -1) {//确保不是-1，未考试的
                    renshu++;//总人数加一

                    str+="\n该选修了该门课程的学生：" +QString(ppp->ssnext->sname) + "\t成绩：" + QString::number(ppp->ssnext->scourse.score);
                    zong += ppp->ssnext->scourse.score;
                    if (ppp->ssnext->scourse.score >= 60)
                        jige++;//及格人数加一
                }
                else{
                    str+="\n该选修了该门课程的学生：" + QString(ppp->ssnext->sname) + "\t未参加考试，无成绩" ;
                }
            }
        }
        str+="\n参加考试的有效人数：" +QString::number(renshu);
        str+="\n平均成绩：" +QString::number( zong / renshu);
        str+="\n及格率：" +QString::number( jige / renshu);
    }
    else {
        //qDebug() <<  << endl;
        str+="\n\n没有找到选修了该门课的学生";
    }
    return str;
}
