#include <QCoreApplication>
#include<QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QVector<QString> name,number,ls1,ls2;
    name<<"鲁智深"<<"林冲"<<"宋江"<<"武松";          //输入数据
    number<< "1403130209"<<"1403140101"<<"1403140102"<<"1403140103";
    ls1<<"80"<<"82"<<"76"<<"88";
    ls2<<"72"<<"76"<<"85"<<"80";
    QVector<QVector<QString>> stu;
    stu<<number<<name<<ls1<<ls2;                        //数据集合
    qDebug("原始成绩单:");                           //输出原数据
    qDebug()<<"学号"<<"\t\t"<<"姓名"<<"\t\t"<<"课程1"<<'\t'<<"课程2";
        for(int i=0;i<4;i++)
            qDebug()<<number.at(i).toInt()<<"\t"
                    <<name.at(i)<<"\t"
                    <<ls1.at(i).toInt()<<"\t"
                    <<ls2.at(i).toInt();
    QVector<QString> title,temp;
    title<<"课程"<<"姓名"<<"课程1"<<"课程2";
    for(int i=1;i<4;i++){
        qDebug()<<'\n'<<"按照"<<title.at(i)<<"降序排序后:";
        temp=stu.at(i);
        std::sort(temp.begin(),temp.end(),std::greater<QString>());//排序
        qDebug()<<"学号"<<"\t\t"<<"姓名"<<"\t\t"<<"课程1"<<'\t'<<"课程2";
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                if(temp.at(j)==stu.at(i).at(k))//定位 {
                qDebug()<<stu.at(0).at(k).toInt()<<'\t'
                        <<stu.at(1).at(k)<<'\t'
                        <<stu.at(2).at(k).toInt()<<'\t'
                        <<stu.at(3).at(k).toInt()<<'\t';

            }
        }
    }
    return a.exec();
}
