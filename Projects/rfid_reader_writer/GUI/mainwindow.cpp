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

    // ################### //
    // ## PlainTextEdit ## //
    // ################### //
    pteUserID->setObjectName(QString::fromUtf8("userID_input"));
    pteUserID->setPlaceholderText(QString::fromUtf8("Kunden Nummer"));
    pteUserID->setTabChangesFocus(true);
    pteUserID->setGeometry(QRect(20,30,150,30));

    pteCardID->setObjectName(QString::fromUtf8("cardID_input"));
    pteCardID->setPlaceholderText(QString::fromUtf8("Karten Nummer"));
    pteCardID->setTabChangesFocus(true);
    pteCardID->setGeometry(QRect(20,70,150,30));

    pteCardAmount->setObjectName(QString::fromUtf8("cardAmount_input"));
    pteCardAmount->setPlaceholderText(QString::fromUtf8("Kartenanzahl"));
    pteCardAmount->setTabChangesFocus(true);
    pteCardAmount->setEnabled(false);
    pteCardAmount->setGeometry(QRect(50,175,120,30));


    pteConsole->setObjectName(QString::fromUtf8("console_output"));
    pteConsole->setOverwriteMode(true);
    pteConsole->setReadOnly(true);
    pteConsole->setEnabled(false);
    pteConsole->setGeometry(QRect(250,100,200,300));

    pteChecksumAdded->setObjectName(QString::fromUtf8("checksumAdded_output"));
    pteChecksumAdded->setReadOnly(true);
    pteChecksumAdded->setEnabled(false);
    pteChecksumAdded->setGeometry(QRect(30,350,150,30));

    pteChecksumIBM->setObjectName(QString::fromUtf8("checksumIBM_out"));
    pteChecksumIBM->setReadOnly(true);
    pteChecksumIBM->setEnabled(false);
    pteChecksumIBM->setGeometry(QRect(30,400,150,30));

    // ################ //
    // ## PushButton ## //
    // ################ //
    pbStart->setObjectName(QString::fromUtf8("start_button"));
    pbStart->setGeometry(QRect(150,470,200,50));
    pbStart->setText(QString::fromUtf8("Beschreiben Starten"));


    // ######################### //
    // ## Set the focus order ## //
    // ######################### //
    this->setTabOrder(pteUserID, pteCardID);
    this->setTabOrder(pteCardID, cbIterate);


    // ########################################### //
    // ## Connections between SIGNALS and SLOTS ## //
    // ########################################### //
    connect(this->pbStart,SIGNAL(clicked(bool)), this, SLOT(pushStartButton()));
    connect(this->cbIterate,SIGNAL(stateChanged(int)),
            this, SLOT(enable_disable_iterativeWrittingInput()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::pushStartButton() {
    EventHandler::startWrittingProcess(this->pteConsole,
                                       this->pteCardID->toPlainText(),
                                       this->pteUserID->toPlainText(),
                                       this->cbIterate->isChecked(),
                                       this->pteCardAmount->toPlainText());
}



void MainWindow::enable_disable_iterativeWrittingInput() {
    // if iterative card writting is activated
    if(this->cbIterate->isChecked()) {
        this->pteCardAmount->setEnabled(true);
    }
    // if iterative card writting is deactivated
    if(!this->cbIterate->isChecked()) {
        this->pteCardAmount->setEnabled(false);
    }
}
