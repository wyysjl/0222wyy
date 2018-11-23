/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCharts/QChartView>
#include <QtCharts/chartsnamespace.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QtCharts::QChartView *chartview;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QComboBox *comboCity;
    QLabel *label;
    QComboBox *comboMonth;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *cbShowPoint;
    QCheckBox *cbLegendBold;
    QCheckBox *cbLegendItalic;
    QPushButton *btnLegendAlign;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *btnWeather;
    QRadioButton *btnAQI;
    QPushButton *btnStart;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *mainWidget)
    {
        if (mainWidget->objectName().isEmpty())
            mainWidget->setObjectName(QStringLiteral("mainWidget"));
        mainWidget->setEnabled(true);
        mainWidget->resize(745, 588);
        horizontalLayout = new QHBoxLayout(mainWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        chartview = new QtCharts::QChartView(mainWidget);
        chartview->setObjectName(QStringLiteral("chartview"));

        horizontalLayout->addWidget(chartview);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 0, -1, -1);
        label_2 = new QLabel(mainWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setIndent(0);

        verticalLayout_3->addWidget(label_2);

        comboCity = new QComboBox(mainWidget);
        comboCity->setObjectName(QStringLiteral("comboCity"));
        comboCity->setEnabled(true);
        comboCity->setEditable(false);

        verticalLayout_3->addWidget(comboCity);

        label = new QLabel(mainWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);

        comboMonth = new QComboBox(mainWidget);
        comboMonth->setObjectName(QStringLiteral("comboMonth"));
        comboMonth->setInsertPolicy(QComboBox::InsertAtBottom);

        verticalLayout_3->addWidget(comboMonth);

        groupBox = new QGroupBox(mainWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        cbShowPoint = new QCheckBox(groupBox);
        cbShowPoint->setObjectName(QStringLiteral("cbShowPoint"));
        cbShowPoint->setChecked(true);

        verticalLayout_2->addWidget(cbShowPoint);

        cbLegendBold = new QCheckBox(groupBox);
        cbLegendBold->setObjectName(QStringLiteral("cbLegendBold"));

        verticalLayout_2->addWidget(cbLegendBold);

        cbLegendItalic = new QCheckBox(groupBox);
        cbLegendItalic->setObjectName(QStringLiteral("cbLegendItalic"));

        verticalLayout_2->addWidget(cbLegendItalic);

        btnLegendAlign = new QPushButton(groupBox);
        btnLegendAlign->setObjectName(QStringLiteral("btnLegendAlign"));

        verticalLayout_2->addWidget(btnLegendAlign);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(mainWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btnWeather = new QRadioButton(groupBox_2);
        btnWeather->setObjectName(QStringLiteral("btnWeather"));

        verticalLayout->addWidget(btnWeather);

        btnAQI = new QRadioButton(groupBox_2);
        btnAQI->setObjectName(QStringLiteral("btnAQI"));

        verticalLayout->addWidget(btnAQI);


        verticalLayout_3->addWidget(groupBox_2);

        btnStart = new QPushButton(mainWidget);
        btnStart->setObjectName(QStringLiteral("btnStart"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(btnStart);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_3);


        retranslateUi(mainWidget);

        QMetaObject::connectSlotsByName(mainWidget);
    } // setupUi

    void retranslateUi(QWidget *mainWidget)
    {
        mainWidget->setWindowTitle(QApplication::translate("mainWidget", "\345\256\236\351\252\214\344\270\211 \347\275\221\347\273\234\346\225\260\346\215\256\350\216\267\345\217\226\344\270\216\346\230\276\347\244\272", Q_NULLPTR));
        label_2->setText(QApplication::translate("mainWidget", "\351\200\211\346\213\251\345\237\216\345\270\202", Q_NULLPTR));
        label->setText(QApplication::translate("mainWidget", "\351\200\211\346\213\251\346\227\266\351\227\264", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("mainWidget", "\346\230\276\347\244\272\351\200\211\351\241\271", Q_NULLPTR));
        cbShowPoint->setText(QApplication::translate("mainWidget", "\346\230\276\347\244\272\346\225\260\346\215\256\347\202\271", Q_NULLPTR));
        cbLegendBold->setText(QApplication::translate("mainWidget", "\345\233\276\346\263\250\347\262\227\344\275\223", Q_NULLPTR));
        cbLegendItalic->setText(QApplication::translate("mainWidget", "\345\233\276\346\263\250\346\226\234\344\275\223", Q_NULLPTR));
        btnLegendAlign->setText(QApplication::translate("mainWidget", "\345\233\276\346\263\250(\345\272\225)", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("mainWidget", "\346\237\245\350\257\242\351\200\211\351\241\271", Q_NULLPTR));
        btnWeather->setText(QApplication::translate("mainWidget", "\346\237\245\350\257\242\346\260\224\346\270\251", Q_NULLPTR));
        btnAQI->setText(QApplication::translate("mainWidget", "\346\237\245\350\257\242AQI", Q_NULLPTR));
        btnStart->setText(QApplication::translate("mainWidget", "\345\274\200\345\247\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainWidget: public Ui_mainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
