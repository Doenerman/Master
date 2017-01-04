#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set the properties of the different objects //
    // Properties:  - geometry (including the placement)
    //              - object name
    //              - possible text
    //              - possible placeholder if no entry is given
    //              - whether the object is enabled
    //              - whether the user can overwrite given text


    //
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

    // ############## //
    // ## LineEdit ## //
    // ############## //
    leCardID->setObjectName(QString::fromUtf8("cardID_input"));
    leCardID->setPlaceholderText(QString::fromUtf8("Kartennummer"));
    leCardID->setGeometry(20,30,150,30);

    leUserID->setObjectName(QString::fromUtf8("userID_input"));
    leUserID->setPlaceholderText(QString::fromUtf8("Kundennummer"));
    leUserID->setGeometry(20,70,150,30);

    leCardAmount->setObjectName(QString::fromUtf8("cardAmount_input"));
    leCardAmount->setPlaceholderText(QString::fromUtf8("Kartenanzahl"));
    leCardAmount->setEnabled(false);
    leCardAmount->setGeometry(QRect(50,175,120,30));

    // ################### //
    // ## PlainTextEdit ## //
    // ################### //
    pteConsole->setObjectName(QString::fromUtf8("console_output"));
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
    this->setTabOrder(leCardID, leUserID);
    this->setTabOrder(leUserID, cbIterate);


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

/**
 * @brief Initiate the writting process.
 *
 * This method calls \link EventHandler::startWrittingProcess(QPlainTextEdit,
 * QString,QString,bool,QString) \endlink. This method works as SLOT method and
 * ist connected in \link MainWindow::MainWindow() \endlink
 */
void MainWindow::pushStartButton() {
    EventHandler::startWrittingProcess(this->pteConsole,
                                       this->leCardID->displayText(),
                                       this->leUserID->displayText(),
                                       this->cbIterate->isChecked(),
                                       this->leCardAmount->displayText());
}



/**
 * @brief   Enables and disables the QLineEdit field for the input for the amount of
 *          cards.
 *
 * The QLinEdit field for the input for the amount of cards is enabled if and
 * only if the QCheckbox \link cbIterate \endlink is checked. This method works
 * as SLOT method and is connected in \link MainWindow::MainWindow() \endlink
 */
void MainWindow::enable_disable_iterativeWrittingInput() {
    // if iterative card writting is activated
    if(this->cbIterate->isChecked()) {
        this->leCardAmount->setEnabled(true);
    }
    // if iterative card writting is deactivated
    if(!this->cbIterate->isChecked()) {
        this->leCardAmount->setEnabled(false);
    }
}
