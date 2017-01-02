#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // ############## //
    // ## Checkbox ## //
    // ############## //
    cbIterate->setObjectName(QString::fromUtf8("iterate_enable"));
    cbIterate->setGeometry(QRect(30,150,100,30));
    cbIterate->setText(QString::fromUtf8("Iterieren"));

    // ########### //
    // ## Label ## //
    // ########### //
    lPBConsole->setObjectName(QString::fromUtf8("label_console"));
    lPBConsole->setGeometry(QRect(250,70,150,30));
    lPBConsole->setText(QString::fromUtf8("Output"));

    lPBChecksumAdded->setObjectName(QString::fromUtf8("label_checksumAdded"));
    lPBChecksumAdded->setGeometry(QRect(30,325,150,30));
    lPBChecksumAdded->setText(QString::fromUtf8("addierte Prüfsumme"));

    lPBChecksumIBM->setObjectName(QString::fromUtf8("label_checksumIBM"));
    lPBChecksumIBM->setGeometry(QRect(30,375,150,30));
    lPBChecksumIBM->setText(QString::fromUtf8("IBM Prüfsumme"));

    // ##################### //
    // ## PlainTextFields ## //
    // ##################### //
    pteUserID->setObjectName(QString::fromUtf8("userID_input"));
    pteUserID->setPlaceholderText(QString::fromUtf8("Kunden Nummer"));
    pteUserID->setGeometry(QRect(20,30,150,30));
    pteUserID->setReadOnly(true);

    pteCardID->setObjectName(QString::fromUtf8("cardID_input"));
    pteCardID->setPlaceholderText(QString::fromUtf8("Karten Nummer"));
    pteCardID->setGeometry(QRect(20,70,150,30));
    pteUserID->setReadOnly(true);

    pteCardAmount->setObjectName(QString::fromUtf8("cardAmount_input"));
    pteCardAmount->setPlaceholderText(QString::fromUtf8("Kartenanzahl"));
    pteCardAmount->setGeometry(QRect(50,175,120,30));
    pteCardAmount->setReadOnly(true);

    // ################ //
    // ## PushButton ## //
    // ################ //
    pbStart->setObjectName(QString::fromUtf8("start_button"));
    pbStart->setGeometry(QRect(150,470,200,50));
    pbStart->setText(QString::fromUtf8("Beschreiben Starten"));

    // ################# //
    // ## TextBrowser ## //
    // ################# //
    tbConsole->setObjectName(QString::fromUtf8("console_output"));
    tbConsole->setGeometry(QRect(250,100,200,300));

    tbChecksumAdded->setObjectName(QString::fromUtf8("checksumAdded_output"));
    tbChecksumAdded->setGeometry(QRect(30,350,150,30));

    tbChecksumIBM->setObjectName(QString::fromUtf8("checksumIBM_out"));
    tbChecksumIBM->setGeometry(QRect(30,400,150,30));
}

MainWindow::~MainWindow()
{

}
