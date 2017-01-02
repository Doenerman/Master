/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QCheckBox *checkBoxCardIterate;
    QTextBrowser *textCheckSummAdded;
    QTextBrowser *textCheckSumIBM;
    QTextBrowser *textConsoleOutput;
    QPlainTextEdit *inputUserID;
    QPlainTextEdit *inputCardID;
    QLabel *labelUserID;
    QLabel *labelCardID;
    QPlainTextEdit *inputCardIterations;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(562, 430);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(230, 330, 115, 32));
        checkBoxCardIterate = new QCheckBox(centralWidget);
        checkBoxCardIterate->setObjectName(QStringLiteral("checkBoxCardIterate"));
        checkBoxCardIterate->setGeometry(QRect(40, 100, 89, 20));
        textCheckSummAdded = new QTextBrowser(centralWidget);
        textCheckSummAdded->setObjectName(QStringLiteral("textCheckSummAdded"));
        textCheckSummAdded->setGeometry(QRect(40, 240, 131, 31));
        textCheckSummAdded->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textCheckSummAdded->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textCheckSumIBM = new QTextBrowser(centralWidget);
        textCheckSumIBM->setObjectName(QStringLiteral("textCheckSumIBM"));
        textCheckSumIBM->setGeometry(QRect(40, 280, 131, 31));
        textCheckSumIBM->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textCheckSumIBM->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textConsoleOutput = new QTextBrowser(centralWidget);
        textConsoleOutput->setObjectName(QStringLiteral("textConsoleOutput"));
        textConsoleOutput->setGeometry(QRect(280, 130, 256, 192));
        inputUserID = new QPlainTextEdit(centralWidget);
        inputUserID->setObjectName(QStringLiteral("inputUserID"));
        inputUserID->setGeometry(QRect(40, 30, 101, 21));
        inputUserID->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        inputUserID->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        inputCardID = new QPlainTextEdit(centralWidget);
        inputCardID->setObjectName(QStringLiteral("inputCardID"));
        inputCardID->setGeometry(QRect(40, 71, 101, 20));
        inputCardID->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        inputCardID->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        labelUserID = new QLabel(centralWidget);
        labelUserID->setObjectName(QStringLiteral("labelUserID"));
        labelUserID->setGeometry(QRect(150, 30, 70, 20));
        labelCardID = new QLabel(centralWidget);
        labelCardID->setObjectName(QStringLiteral("labelCardID"));
        labelCardID->setGeometry(QRect(150, 70, 59, 16));
        inputCardIterations = new QPlainTextEdit(centralWidget);
        inputCardIterations->setObjectName(QStringLiteral("inputCardIterations"));
        inputCardIterations->setEnabled(false);
        inputCardIterations->setGeometry(QRect(50, 130, 101, 20));
        inputCardIterations->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        inputCardIterations->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(280, 100, 59, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 562, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        checkBoxCardIterate->setText(QApplication::translate("MainWindow", "Iterieren", Q_NULLPTR));
        labelUserID->setText(QApplication::translate("MainWindow", "Kunden ID", Q_NULLPTR));
        labelCardID->setText(QApplication::translate("MainWindow", "Karten ID", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Output", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
