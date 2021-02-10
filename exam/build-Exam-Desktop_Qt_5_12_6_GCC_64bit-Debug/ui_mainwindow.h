/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *Problems_table;
    QLabel *label_2;
    QLCDNumber *lcdNumber;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout;
    QListWidget *listUsers;
    QLabel *label;
    QWidget *tab_7;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listProblems;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(801, 625);
        QFont font;
        font.setPointSize(20);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font1;
        font1.setPointSize(15);
        tabWidget->setFont(font1);
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalLayout_3 = new QVBoxLayout(tab_5);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        Problems_table = new QTableWidget(tab_5);
        if (Problems_table->columnCount() < 3)
            Problems_table->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        Problems_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        Problems_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        Problems_table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (Problems_table->rowCount() < 1)
            Problems_table->setRowCount(1);
        Problems_table->setObjectName(QString::fromUtf8("Problems_table"));
        Problems_table->setRowCount(1);
        Problems_table->setColumnCount(3);
        Problems_table->horizontalHeader()->setCascadingSectionResizes(false);
        Problems_table->horizontalHeader()->setDefaultSectionSize(250);
        Problems_table->horizontalHeader()->setHighlightSections(true);
        Problems_table->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        Problems_table->horizontalHeader()->setStretchLastSection(false);
        Problems_table->verticalHeader()->setStretchLastSection(false);

        verticalLayout_3->addWidget(Problems_table);

        label_2 = new QLabel(tab_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        lcdNumber = new QLCDNumber(tab_5);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setMinimumSize(QSize(0, 40));

        verticalLayout_3->addWidget(lcdNumber);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        verticalLayout = new QVBoxLayout(tab_6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listUsers = new QListWidget(tab_6);
        listUsers->setObjectName(QString::fromUtf8("listUsers"));
        listUsers->setFont(font1);

        verticalLayout->addWidget(listUsers);

        label = new QLabel(tab_6);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        verticalLayout_2 = new QVBoxLayout(tab_7);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        listProblems = new QListWidget(tab_7);
        listProblems->setObjectName(QString::fromUtf8("listProblems"));

        verticalLayout_2->addWidget(listProblems);

        tabWidget->addTab(tab_7, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Problems_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Problem type", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Problems_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Problem appeared", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Problems_table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Problem solved", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Total time spent on troublesooting:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Event_Log", nullptr));
        label->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("MainWindow", "Users", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("MainWindow", "Problems", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
