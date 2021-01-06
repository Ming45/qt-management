#include"mymanage.h"

void Student::showstudent() {//显示学生
    qDebug() << sid << "\t" << sname << endl;
}

void Student::showscore() {//显示学生成绩

    cout <<  "学号:"<< "\t姓名:" << "\t选修课程:" << "\t\t课程成绩:" << endl;
    qDebug() << sid << "\t" << sname << "\t" << scourse.cname << "\t\t" << scourse.score << endl;
}

void Student::inputscore() {
    qDebug() << "请输入学生的姓名："; cin >> sname;
    qDebug() << "请输入学生的学号："; cin >> sid;
    qDebug() << "请输入学生选修的课程："; cin >> scourse.cname;
    qDebug() << "请输入学生课程的成绩："; cin >> scourse.score;

}

void Student::inputstudent() {//添加学生
    qDebug() << "请输入学生的姓名："; cin >> sname;
    qDebug() << "请输入学生的学号："; cin >> sid;
    qDebug() << "请输入学生的班级："; cin >> sclass;
    qDebug() << "请输入学生的专业："; cin >> major;
}
/*
void Student::sinputcourse() {
    qDebug() << "请输入自己的姓名："; cin >> sname;
    qDebug() << "请输入自己的学号："; cin >> sid;
    qDebug() << "请输入学生选修的课程："; cin >> scourse.cname;

    scourse.score=-1;//成绩设为-1
}*/

void Student::readscore(istream& in) {//读取成绩文本

    in >> sid >> sname >> scourse.cname >> scourse.score;

}
void Student::readstudent(istream& in) {//读取学生文本

    in >> sid >> sname >> sclass >> major;
}
