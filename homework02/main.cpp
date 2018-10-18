#include <QDebug>

#include <QVector>

#include <QTextStream>

#include <QFile>

#include <QCoreApplication>



namespace SK {

enum SortKind{

    col01    =   0x00000001<<0,         //!< 第1列

    col02    =   0x00000001<<1,         //!< 第2列

    col03    =   0x00000001<<2,         //!< 第3列

    col04    =   0x00000001<<3,         //!< 第4列

    col05    =   0x00000001<<4,         //!< 第5列

    col06    =   0x00000001<<5,         //!< 第6列

    col07    =   0x00000001<<6,         //!< 第7列

    col08    =   0x00000001<<7,         //!< 第8列

    col09    =   0x00000001<<8,         //!< 第9列

    col10    =   0x00000001<<9,         //!< 第10列

    col11    =   0x00000001<<10,        //!< 第11列

    col12    =   0x00000001<<11,        //!< 第12列

    col13    =   0x00000001<<12,        //!< 第13列

    col14    =   0x00000001<<13,        //!< 第14列

    col15    =   0x00000001<<14,        //!< 第15列

    col16    =   0x00000001<<15,        //!< 第16列

    col17    =   0x00000001<<16,        //!< 第17列

    col18    =   0x00000001<<17,        //!< 第18列

    col19    =   0x00000001<<18,        //!< 第19列

    col20    =   0x00000001<<19,        //!< 第20列

    col21    =   0x00000001<<20,        //!< 第21列

    col22    =   0x00000001<<21,        //!< 第22列

    col23    =   0x00000001<<22,        //!< 第23列

    col24    =   0x00000001<<23,        //!< 第24列

    col25    =   0x00000001<<24,        //!< 第25列

    col26    =   0x00000001<<25,        //!< 第26列

    col27    =   0x00000001<<26,        //!< 第27列

    col28    =   0x00000001<<27,        //!< 第28列

    col29    =   0x00000001<<28,        //!< 第29列

    col30    =   0x00000001<<29,        //!< 第30列

    col31    =   0x00000001<<30,        //!< 第31列

    col32    =   0x00000001<<31,        //!< 第32列
};
}
typedef struct{
    QStringList s;// 请补全结构定义
} studData;

QDebug operator<< (QDebug d, const studData &data)
{
    for(int i=0;i<data.s.size();i++)

        d.noquote().nospace()<<QString(data.s.at(i))<<"\t" ;

        return d;// 请补全运算符重载函数，可以直接输出studData结构

}





class myCmp {

public:

    myCmp(int selectedColumn) { this->currentColumn = selectedColumn; }

    bool operator() (const studData& d1,const studData& d2);

private:

    int currentColumn;

};



#define comp(a)   (d1.s.at(a)>=d2.s.at(a))?  1:0

bool myCmp::operator()(const studData &d1, const studData &d2)

{

    bool result = false;

    quint32 sortedColumn = 0x00000001<<currentColumn;

    switch (sortedColumn)

  {

    case SK::col01:result=comp(1);break;

    case SK::col02:result=comp(2);break;

    case SK::col03:result=comp(3);break;

    case SK::col04:result=comp(4);break;

    case SK::col05:result=comp(5);break;

    case SK::col06:result=comp(6);break;

    case SK::col07:result=comp(7);break;

    case SK::col08:result=comp(8);break;

    case SK::col09:result=comp(9);break;

    case SK::col10:result=comp(10);break;

    case SK::col11:result=comp(11);break;

    case SK::col12:result=comp(12);break;

    case SK::col13:result=comp(13);break;

    case SK::col14:result=comp(14);break;

    case SK::col15:result=comp(15);break;

    case SK::col16:result=comp(16);break;

    case SK::col17:result=comp(17);break;

    case SK::col18:result=comp(18);break;

    case SK::col19:result=comp(19);break;

    case SK::col20:result=comp(20);break;

    case SK::col21:result=comp(21);break;

    case SK::col22:result=comp(22);break;

    case SK::col23:result=comp(23);break;

    case SK::col24:result=comp(24);break;

    case SK::col25:result=comp(25);break;

    case SK::col26:result=comp(26);break;

    case SK::col27:result=comp(27);break;

    case SK::col28:result=comp(28);break;

    case SK::col29:result=comp(29);break;

    case SK::col30:result=comp(30);break;

    case SK::col31:result=comp(31);break;

    case SK::col32:result=comp(32);break;

       default:;break;

    }

    return result;



}





class ScoreSorter



{



public:



    ScoreSorter(QString dataFile);

    void readFile();                //读取文件

    void doSort();                  //实现排序功能

    friend QDebug operator << (QDebug d, const studData &data);

private:

    QString path;                   //定义

    QList<studData > data;

    studData title;

    void expdata(quint8 list);     //实现将排序好后的数据写入文档

};





ScoreSorter::ScoreSorter(QString dataFile)

{

    path=dataFile;                             //初始化



}





void ScoreSorter::readFile()

{

    QFile file("E:/Qt/0222wyy/homework02/data.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))      //判断是否能够打开

    {

        qDebug()<<"Can't open the file!"<<endl;

    }



    QString titile(file.readLine());

    title.s = titile.split(" ", QString::SkipEmptyParts);

    if((title.s).last() == "\n") title.s.removeLast();

    studData eachdata;



    while(!file.atEnd())                                       //查找数据

    {

        QByteArray line = file.readLine();

        QString str(line);

        eachdata.s = str.split(" ", QString::SkipEmptyParts);

        if((eachdata.s).last() == "\n") eachdata.s.removeLast();

        if(eachdata.s.size()==0) continue;

        data.append(eachdata);

    }

    file.close();                                                            //关闭文件



}





void ScoreSorter::doSort()

{



    for(int i=1;i<title.s.size();i++)



    {

        myCmp stducmp(i-1);

        std::sort(data.begin() , data.end() , stducmp );       //排序

        qDebug()<<"排序后输出，当前排序第 "<<i+1 <<" 列：";

        qDebug() << '\t'<< (title);

        for(int i=0;i<data.size();i++)  qDebug() << data.at(i);

        qDebug()<<"-------------------------------------------------------\n";

        expdata(i+1);

    }

}


void ScoreSorter::expdata(quint8 list)


{

    QFile file("sorted_"+path);

    file.open(QIODevice::ReadWrite | QIODevice::Append);

    QTextStream stream(&file);

    stream.setCodec("UTF-8");

    stream<<QString("排序后输出，当前排序第 ")<<list <<QString(" 列：")<<"\r\n";

    stream<<"\t";

    for(int j=0;j<title.s.size();j++)

        stream<<title.s.at(j)<<"\t";

        stream<<"\r\n";

    for(int a=0;a<data.size();a++)

    {

        for(int b=0;b<title.s.size();b++)

        stream<<data.at(a).s.at(b)<<"\t";

        stream<<"\r\n";

    }

    stream<<"-------------------------------------------------------"<<"\r\n\r\n";

    file.close();

}





int main(int argc, char *argv[])

{

    QCoreApplication a(argc, argv);

    QString datafile = "data.txt";

    QFile f("sorted_"+datafile);

    if (f.exists())  f.remove();

    ScoreSorter s(datafile);

    s.readFile();     //读文件

    s.doSort();       //写文件

    return a.exec();



}
