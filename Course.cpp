#include"mymanage.h"
#include"mymanage.h"

void Course::readcourse(istream& in) {//读取课程文本

    in >> cid >> cname >> credit;
}

QString Course::showcourse(QString &str) {//显示课程
    //QString(cid).QString::toStdString()
    str+=("\n"+QString(cid)+"\t"+QString(cname)+"\t\t"+QString::number(credit));
    return str;
}

void Course::inputcourse() {//存放课程
    qDebug() << "请输入课程编号："; cin >> cid;
    qDebug() << "请输入课程名称："; cin >> cname;
    qDebug() << "请输入课程学分："; cin >> credit;
}
