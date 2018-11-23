#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "dataworker.h"
#include <QDateTime>

mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);
    ui->chartview->setRenderHint(QPainter::Antialiasing);

    initComboCity();
    initComboMonth();

    resetChart("南京气温");
    addLineSeries(ui->chartview->chart(),"",Qt::red);

    worker = new dataWorker(this);
    connect(worker,&dataWorker::dataParseFinished,this,&mainWidget::updateDataChart);

}

mainWidget::~mainWidget()
{
    delete ui;
}


//void mainWidget::initComboMonth()
//{
//    QStringList month;
//    for(int i=10;i>0;i--){
//        month<<QString("2018-%1").arg(i,2,10,QChar('0'));
//    }
//    ui->comboMonth->clear();
//    ui->comboMonth->addItems(month);

//}

void mainWidget::initComboMonth()
{
    ui->comboMonth->clear();
    for(int i=1;i<=10;i++){
        ui->comboMonth->addItem(QDateTime::currentDateTime().addMonths(-i).toString("yyyy-MM"));
    }

}

void mainWidget::initComboCity()
{
//    ui->comboCity->addItem("南京");
//    ui->comboCity->addItem("北京");
//    ui->comboCity->addItem("上海");
//    ui->comboCity->addItem("苏州");
//    ui->comboCity->addItem("扬州");

//    ui->comboCity->setCurrentIndex(0);
    QStringList city;
    QStringList pinyin;

    city<<"南京"<<"北京"<<"上海"<<"苏州"<<"扬州";
    pinyin<<"nanjing"<<"beijing"<<"shanghai"<<"suzhou"<<"yangzhou";

    ui->comboCity->clear();
    for(int i=0;i<city.count();i++){
        ui->comboCity->addItem(city.at(i),pinyin.at(i));
    }

}

/**
 * @brief 重置chart图表对象
 *
 * 重置chart对象，包括以下几个内容：<br/>
 * 1) 对chart中的各个序列，删除序列数据，并清空序列列表<br/>
 * 2) 因为后面使用时，chart的图注(Legend)使用了非贴附模式(not attatched)，<br/>
 *    因此这里设置为贴附模式(attatchToChart)，并将其隐藏，<br/>
 * 3) 清空控制器对象列表，对QList<pointer*>对象，清空时需要首先删除个对象，<br/>
 *    然后清除列表。如下代码所示：
 *  @code{.cpp}
 *      if(controllerList.count()>0){
 *          qDeleteAll(controllerList);
 *          controllerList.clear();
 *       }
 *  @endcode
 * 4) 最后设置计算线程的计数值为0，同时复位进度条
 *
 */
void mainWidget::resetChart(const QString &title)
{
    QChart* chart = ui->chartview->chart();


    //chart->setTitle(QString("单向开关函数的傅里叶变换%1").arg("\u03c0"));
    chart->setTitle(title);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // 在后面的显示中，Legend被设为浮动模式，
    // 因此，这里在清除数据时，需要先attach一下
    if(!chart->legend()->isAttachedToChart())
        chart->legend()->attachToChart();

    chart->legend()->hide();
    chart->legend()->setAlignment(Qt::AlignBottom);
    // removeAllSeries函数即将包含的个序列delete掉，
    // 同时也清空序列列表
    chart->removeAllSeries();
}


/**
 * @brief 向Chart中添加序列（Series）
 * @param chart 指向QChart对象指针
 * @param color 序列颜色
 * @param lineWidth 序列线宽（默认值为1）
 */
void mainWidget::addLineSeries(QChart *chart, const QString &seriesName, const QColor color, const int lineWidth)
{

    // 新建一个序列
    QLineSeries* series = new QLineSeries;
    // 将序列添加入chart中
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // 设置序列的线宽和颜色
    QPen pen(color);
    pen.setWidth(lineWidth);
    series->setPen(pen);

    series->setPointsVisible(true);

    // 序列名称，显示在legend中
    series->setName(seriesName);

    if(chart->series().count() == 1){
        // 第一次添加序列，新增一个Axes，
        chart->createDefaultAxes();

        // 设置2个坐标轴
        QDateTimeAxis *mAxisX = new QDateTimeAxis;
        mAxisX->setFormat("MM-dd");
        mAxisX->setTitleText("日期");
        mAxisX->setTickCount(9+1);
        mAxisX->setRange(QDateTime::currentDateTime().addMonths(-1),QDateTime::currentDateTime());

        QValueAxis *mAxisY = new QValueAxis;

        if(worker->switch_Num==0)
        {
             mAxisY->setRange(-10,40);
             mAxisY->setLabelFormat("%g");
             mAxisY->setTitleText("摄氏度(°C)");
        }

        if(worker->switch_Num==1)
        {
            mAxisY->setRange(0,100);
            mAxisY->setTitleText("污染物指数");
        }

        chart->setAxisX(mAxisX,series);
        chart->setAxisY(mAxisY,series);
    }else{
        // 将新增加的列与现有坐标轴连接上
        QDateTimeAxis *mAxisX = qobject_cast<QDateTimeAxis*>(chart->axisX());
        QValueAxis *mAxisY = qobject_cast<QValueAxis*>(chart->axisY());
        chart->setAxisX(mAxisX,series);
        chart->setAxisY(mAxisY,series);
    }
}


/**
 * @brief 连接序列中所有Legend（图注）中Marker的信号与槽
 */
void mainWidget::connectMarkers()
{
    QChart* chart = ui->chartview->chart();
    // 将所有的marker的信号与槽进行连接
    for (QLegendMarker* marker: chart->legend()->markers()) {
        // 连接前先断开原先的信号槽连接，避免多次连接信号槽
        disconnect(marker, &QLegendMarker::clicked, this, &mainWidget::handleMarkerClicked);
        connect(marker, &QLegendMarker::clicked, this, &mainWidget::handleMarkerClicked);
    }
}

/**
 * @brief 处理用户点击界面中图注的Marker
 *
 * 本函数实现用户点击时，隐藏或显示序列。<br/>
 * 在序列隐藏时，图注里的Marker也跟着隐藏，因此需要将其显示出来；<br/>
 * 为了区分正常显示与隐藏图注，将被隐藏图注设置为半透明。<br/>
 * 设置隐藏序列的图注包括三部分工作：<br/>
 * 1) 设置Marker的文本颜色(使用labelBrush)<br/>
 * 2) 设置Marker前图标的填充颜色(使用brush)<br/>
 * 3) 设置Marker前图标的边框颜色(使用pen)<br/>
 *
 */
void mainWidget::handleMarkerClicked()
{
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
    Q_ASSERT(marker);

    switch (marker->type()){
    case QLegendMarker::LegendMarkerTypeXY:{
        // 切换选中序列的可见性，
        marker->series()->setVisible(!marker->series()->isVisible());

        // 使图注(Legend)的marker也显示出来，因为当隐藏序列series时，
        // marker也跟着隐藏，从而使用户无法看到marker
        marker->setVisible(true);

        // 隐藏序列后虽然显示marker，这里使marker变暗，表明该序列已经被隐藏
        qreal alpha = 1.0;

        if (!marker->series()->isVisible()) {
            alpha = 0.3;
        }

        QColor color;
        QBrush brush = marker->labelBrush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setLabelBrush(brush);

        brush = marker->brush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setBrush(brush);

        QPen pen = marker->pen();
        color = pen.color();
        color.setAlphaF(alpha);
        pen.setColor(color);
        marker->setPen(pen);

        break;
    }
    default:{
        qDebug() << "未知的marker类型";
        break;
    }

    }
}

void mainWidget::on_btnStart_clicked()
{
    //查询气温
    if(ui->btnWeather->isChecked())
    {
        QString chartTitle = "";

        if(ui->comboMonth->count()>0){
            chartTitle = ui->comboMonth->currentText().replace("-","年");
            QString city=ui->comboCity->currentText();
            city=city+"气温";
            chartTitle.append("月 "+city);
        }else{
            chartTitle="南京气温";
        }

        resetChart(chartTitle);

        // 设置dataWorker对象的请求年月
        worker->setRequestDate(ui->comboMonth->currentText());
        worker->setRequestCity(ui->comboCity->currentData().toString());
        worker->setSwitchNum(0);

        // 发起HTTP请求
        worker->doRequest();
    }


    //查询AQI
    if(ui->btnAQI->isChecked())
    {
        QString chartTitle = "";

        if(ui->comboMonth->count()>0){
            chartTitle = ui->comboMonth->currentText().replace("-","年");
            QString city=ui->comboCity->currentText();
            city=city+"空气质量";
            chartTitle.append("月 "+city);
        }else{
            chartTitle="南京空气质量";
        }

        resetChart(chartTitle);

        // 设置dataWorker对象的请求年月
        worker->setRequestDate(ui->comboMonth->currentText());
        worker->setRequestCity(ui->comboCity->currentData().toString());
        worker->setSwitchNum(1);

        // 发起HTTP请求
        worker->doRequest();
    }

}

void mainWidget::updateDataChart(QList<QDateTime> date, QList<qreal> tempHigh, QList<qreal> tempLow)
{
    QChart* chart = ui->chartview->chart();

    if(worker->switch_Num==0)
    {
        // 添加第一条数据曲线
        addLineSeries(chart,"日最高温度",Qt::red,2);
        QLineSeries* seriesHigh = qobject_cast<QLineSeries*> (chart->series().last());
        seriesHigh->setPointsVisible(ui->cbShowPoint->isChecked());

        // 添加第二条数据曲线
        addLineSeries(chart,"日最低温度",Qt::blue,2);
        QLineSeries* seriesLow = qobject_cast<QLineSeries*> (chart->series().last());
        seriesLow->setPointsVisible(ui->cbShowPoint->isChecked());

        // 向每条曲线中添加数据
        for (int i=0; i<date.count();i++){
            seriesHigh->append(date.at(i).toMSecsSinceEpoch(),tempHigh.at(i));
            seriesLow->append(date.at(i).toMSecsSinceEpoch(),tempLow.at(i));
        }

        // 设置坐标轴
        QDateTimeAxis *mAxisX = qobject_cast<QDateTimeAxis*>(chart->axisX());
        mAxisX->setRange(date.first(),date.last());

        connectMarkers();
        // 显示图注
        chart->legend()->show();
        // 更新图表
        chart->update();
    }

    if(worker->switch_Num==1)
    {
        // 添加第一条数据曲线
        addLineSeries(chart,"AQI",Qt::red,2);
        QLineSeries* seriesAQI = qobject_cast<QLineSeries*> (chart->series().last());
        seriesAQI->setPointsVisible(ui->cbShowPoint->isChecked());

        // 添加第二条数据曲线
        addLineSeries(chart,"PM2.5",Qt::blue,2);
        QLineSeries* seriesPM25 = qobject_cast<QLineSeries*> (chart->series().last());
        seriesPM25->setPointsVisible(ui->cbShowPoint->isChecked());

        // 向每条曲线中添加数据
        for (int i=0; i<date.count();i++){
            seriesAQI->append(date.at(i).toMSecsSinceEpoch(),tempHigh.at(i));
            seriesPM25->append(date.at(i).toMSecsSinceEpoch(),tempLow.at(i));
        }

        // 设置坐标轴
        QDateTimeAxis *mAxisX = qobject_cast<QDateTimeAxis*>(chart->axisX());
        mAxisX->setRange(date.first(),date.last());

        QValueAxis *mAxisY = qobject_cast<QValueAxis*>(chart->axisY());

        qreal max;
        qreal min;

        for (int i=0; i<date.count();i++)
        {
            if(max<tempHigh.at(i))
                max=tempHigh.at(i);
            if(min>tempLow.at(i))
                min=tempLow.at(i);
        }
        mAxisY->setRange(min-15,max+15);

        connectMarkers();
        // 显示图注
        chart->legend()->show();
        // 更新图表
        chart->update();

    }

    // 使能三个按钮
    ui->comboCity->setEnabled(true);
    ui->comboMonth->setEnabled(true);
    ui->btnStart->setEnabled(true);
}

void mainWidget::on_cbShowPoint_clicked()
{
    QChart* chart = ui->chartview->chart();
    for(QAbstractSeries* series: chart->series() ){
        qobject_cast<QLineSeries*>(series)->setPointsVisible(ui->cbShowPoint->isChecked());
    }
}

void mainWidget::on_btnLegendAlign_clicked()
{
     QPushButton *button = qobject_cast<QPushButton *>(sender());
     QChart* chart = ui->chartview->chart();
     Qt::Alignment align = chart->legend()->alignment();
     switch (align) {
     case Qt::AlignLeft:{
         align = Qt::AlignTop;
         if(button)
             button->setText("图注(顶)");
     }
         break;
     case Qt::AlignTop:{
         align = Qt::AlignRight;
         if(button)
             button->setText("图注(右)");
     }
         break;
     case Qt::AlignRight:{
         align = Qt::AlignBottom;
         if(button)
             button->setText("图注(底)");
     }
         break;
     case Qt::AlignBottom:{
         align = Qt::AlignLeft;
         if(button)
             button->setText("图注(左)");
     }
         break;
     default:
         break;
     }
     chart->legend()->setAlignment(align);

}

void mainWidget::on_cbLegendBold_clicked()
{
    QChart* chart = ui->chartview->chart();
    QFont font = chart->legend()->font();
    font.setBold(!font.bold());
    chart->legend()->setFont(font);
}

void mainWidget::on_cbLegendItalic_clicked()
{
    QChart* chart = ui->chartview->chart();
    QFont font = chart->legend()->font();
    font.setItalic(!font.italic());
    chart->legend()->setFont(font);
}

void mainWidget::on_btnWeather_clicked()
{
    qDebug()<<"click btnWeather";
    switch_num=0;
    worker->setSwitchNum(0);
}

void mainWidget::on_btnAQI_clicked()
{
    qDebug()<<"click btnAQI";
    switch_num=1;
    worker->setSwitchNum(1);
}
