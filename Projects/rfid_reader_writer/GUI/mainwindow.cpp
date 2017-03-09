#include "mainwindow.h"

/**
 * @brief   Constructor for the main window.
 *
 * This constructor set several properties for the objectivs of
 * \link MainWindow \endlink . The properties set include the geometry
 * (including where the object is placed), the object name, possible text that
 * is visiable for the user, possible placeholder to explain what this object
 * is used for and whether an object is enabled or not. Furthermore the tab
 * order is set and the connections between buttons, checkboxes and methods
 * are set.
 *
 * @param parent
 */
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
    cbIterate->setGeometry(QRect(CHECKBOX_ITER_X,
                                 CHECKBOX_ITER_Y,
                                 CHECKBOX_WIDTH,
                                 CHECKBOX_HIGHT));
    cbIterate->setText(QString::fromUtf8("Iterieren"));

    // ########### //
    // ## Label ## //
    // ########### //
    lUserID->setObjectName(QString::fromUtf8("label_userID"));
    lUserID->setGeometry(QRect(LABEL_USERID_X,
                               LABEL_USERID_Y,
                               LABEL_LARGE_WIDTH,
                               LABEL_DEFAULT_HEIGHT));
    lUserID->setText(QString::fromUtf8("Kundennummer"));

    lCardID->setObjectName(QString::fromUtf8("label_cardID"));
    lCardID->setGeometry(QRect(LABEL_CARDID_X,
                               LABEL_CARDID_Y,
                               LABEL_LARGE_WIDTH,
                               LABEL_DEFAULT_HEIGHT));
    lCardID->setText(QString::fromUtf8("Kartennummer"));

    lPBConsole->setObjectName(QString::fromUtf8("label_console"));
    lPBConsole->setGeometry(QRect(LABEL_CONSOLE_X,
                                  LABEL_CONSOLE_Y,
                                  LABEL_LARGE_WIDTH,
                                  LABEL_DEFAULT_HEIGHT));
    lPBConsole->setText(QString::fromUtf8("Output"));

    lCardType->setObjectName(QString::fromUtf8("label_cardType"));
    lCardType->setGeometry(QRect(LABEL_X_FIRST_COLUMN,
                                 LABEL_Y_CARDTYPE,
                                 LABEL_SMALL_WIDTH,
                                 LABEL_DEFAULT_HEIGHT));
    lCardType->setText(QString::fromUtf8("Kartentyp"));

    lRecRev->setObjectName(QString::fromUtf8("label_recRev"));
    lRecRev->setGeometry(QRect(LABEL_X_SECOND_COLUMN,
                               LABEL_Y_RECREV,
                               LABEL_SMALL_WIDTH,
                               LABEL_DEFAULT_HEIGHT));
    lRecRev->setText(QString::fromUtf8("Record Rev"));

    lLocNr->setObjectName(QString::fromUtf8("label_locNr"));
    lLocNr->setGeometry(QRect(LABEL_X_FIRST_COLUMN,
                              LABEL_Y_LOCNR,
                              LABEL_SMALL_WIDTH,
                              LABEL_DEFAULT_HEIGHT));
    lLocNr->setText(QString::fromUtf8("Landeskennung"));

    lPBChecksumAdded->setObjectName(QString::fromUtf8("label_checksumAdded"));
    lPBChecksumAdded->setGeometry(QRect(LABEL_CHECKSUM_ADD_X,
                                        LABEL_CHECKSUM_ADD_Y,
                                        LABEL_LARGE_WIDTH,
                                        LABEL_DEFAULT_HEIGHT));
    lPBChecksumAdded->setText(QString::fromUtf8("addierte Prüfsumme"));

    lPBChecksumIBM->setObjectName(QString::fromUtf8("label_checksumIBM"));
    lPBChecksumIBM->setGeometry(QRect(LABEL_CHECKSUM_IBM_X,
                                      LABEL_CHECKSUM_IBM_Y,
                                      LABEL_LARGE_WIDTH,
                                      LABEL_DEFAULT_HEIGHT));
    lPBChecksumIBM->setText(QString::fromUtf8("IBM Prüfsumme"));


    // ############## //
    // ## LineEdit ## //
    // ############## //
    leUserID->setObjectName(QString::fromUtf8("userID_input"));
    leUserID->setPlaceholderText(QString::fromUtf8("Kundennummer"));
    leUserID->setGeometry(LINEEDIT_USERID_X,
                          LINEEDIT_USERID_Y,
                          LINEEDIT_LARGE_WIDTH,
                          LINEEDIT_DEFAULT_HEIGHT);

    leCardID->setObjectName(QString::fromUtf8("cardID_input"));
    leCardID->setPlaceholderText(QString::fromUtf8("Kartennummer"));
    leCardID->setGeometry(LINEEDIT_CARDID_X,
                          LINEEDIT_CARDID_Y,
                          LINEEDIT_LARGE_WIDTH,
                          LINEEDIT_DEFAULT_HEIGHT);

    leCardAmount->setObjectName(QString::fromUtf8("cardAmount_input"));
    leCardAmount->setPlaceholderText(QString::fromUtf8("Kartenanzahl"));
    leCardAmount->setEnabled(false);
    leCardAmount->setGeometry(QRect(LINEEDIT_CARDAMOUNT_X,
                                    LINEEDIT_CARDAMOUNT_Y,
                                    LINEEDIT_CARDAMOUNT_WIDTH,
                                    LINEEDIT_CARDAMOUNT_HIGHT));

    leCardType->setObjectName(QString::fromUtf8("cardType_input"));
    leCardType->setGeometry(QRect(LINEEDIT_X_FIRST_COLUMN,
                                  LINEEDIT_Y_CARDTYPE,
                                  LINEEDIT_SMALL_WIDTH,
                                  LINEEDIT_DEFAULT_HEIGHT));
    leCardType->setText(QString::number(0));

    leRecRev->setObjectName(QString::fromUtf8("recRev_input"));
    leRecRev->setGeometry(QRect(LINEEDIT_X_SECOND_COLUMN,
                                LINEEDIT_Y_RECREV,
                                LINEEDIT_SMALL_WIDTH,
                                LINEEDIT_DEFAULT_HEIGHT));
    leRecRev->setText(QString::number(0));

    leLocNr->setObjectName(QString::fromUtf8("locNr_input"));
    leLocNr->setGeometry(QRect(LINEEDIT_X_FIRST_COLUMN,
                               LINEEDIT_Y_LOCNR,
                               LINEEDIT_SMALL_WIDTH,
                               LINEEDIT_DEFAULT_HEIGHT));
    leLocNr->setText(QString::number(0));
                                  

    // ################### //
    // ## PlainTextEdit ## //
    // ################### //
    pteLightBox->setObjectName(QString::fromUtf8("lightbox_output"));
    pteLightBox->setReadOnly(true);
    pteLightBox->setEnabled(false);
    pteLightBox->setGeometry(LIGHT_BOX_X,
                             LIGHT_BOX_Y,
                             LIGHTBOX_HIGHT,
                             LIGHTBOX_WIDTH);
    pteLightBox->setStyleSheet("QPlainTextEdit {background-color: green;}");

    pteConsole->setObjectName(QString::fromUtf8("console_output"));
    pteConsole->setReadOnly(true);
    pteConsole->setEnabled(false);
    pteConsole->setGeometry(QRect(PTE_CONSOLE_X,
                                  PTE_CONSOLE_Y,
                                  PTE_CONSOLE_HIGHT,
                                  PTE_CONSOLE_WIDTH));

    pteChecksumAdded->setObjectName(QString::fromUtf8("checksumAdded_output"));
    pteChecksumAdded->setReadOnly(true);
    pteChecksumAdded->setEnabled(false);
    pteChecksumAdded->setGeometry(QRect(PTE_CHECKSUM_ADD_X,
                                        PTE_CHECKSUM_ADD_Y,
                                        PLAINTEXTEDIT_DEFAULT_WIDTH,
                                        PLAINTEXTEDIT_DEFAULT_HEIGHT));

    pteChecksumIBM->setObjectName(QString::fromUtf8("checksumIBM_out"));
    pteChecksumIBM->setReadOnly(true);
    pteChecksumIBM->setEnabled(false);
    pteChecksumIBM->setGeometry(QRect(PTE_CHECKSUM_IBM_X,
                                      PTE_CHECKSUM_IBM_Y,
                                      PLAINTEXTEDIT_DEFAULT_WIDTH,
                                      PLAINTEXTEDIT_DEFAULT_HEIGHT));

    // ################ //
    // ## PushButton ## //
    // ################ //
    pbStart->setObjectName(QString::fromUtf8("start_button"));
    pbStart->setGeometry(QRect(PUSHBUTTON_MAINWINDOW_X_START,
                               PUSHBUTTON_Y_FIRST_ROW,
                               PUSHBUTTON_MAINWINDOW_WIDTH,
                               PUSHBUTTON_MAINWINDOW_HEIGHT));
    pbStart->setText(QString::fromUtf8("Beschreiben Starten"));

    pbRead->setObjectName(QString::fromUtf8("read_button"));
    pbRead->setGeometry(QRect(PUSHBUTTON_MAINWINDOW_X_READ,
                              PUSHBUTTON_Y_FIRST_ROW,
                              PUSHBUTTON_MAINWINDOW_WIDTH,
                              PUSHBUTTON_MAINWINDOW_HEIGHT));
    pbRead->setText(QString::fromUtf8("Karte lesen"));

    pbClose->setObjectName(QString::fromUtf8("close_button"));
    pbClose->setGeometry(QRect(PUSHBUTTON_MAINWINDOW_X_CLOSE,
                               PUSHBUTTON_Y_SECOND_ROW,
                               PUSHBUTTON_MAINWINDOW_WIDTH,
                               PUSHBUTTON_MAINWINDOW_HEIGHT));
    pbClose->setText(QString::fromUtf8("Beenden"));




    // ######################### //
    // ## Set the focus order ## //
    // ######################### //
    this->setTabOrder(leUserID, leCardID);
    this->setTabOrder(leCardID, cbIterate);
    this->setTabOrder(pbStart,pbRead);
    this->setTabOrder(pbRead,pbClose);


    // ########################################### //
    // ## Connections between SIGNALS and SLOTS ## //
    // ########################################### //
    connect(this->pbStart,SIGNAL(clicked(bool)),this,SLOT(pushStartButton()));
    connect(this->pbRead,SIGNAL(clicked(bool)),this,SLOT(pushReadButton()));
    connect(this->cbIterate,SIGNAL(stateChanged(int)),
            this, SLOT(enable_disable_iterativeWrittingInput()));
    connect(this->pbClose,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(this->leUserID,SIGNAL(textChanged(QString)),
            this,SLOT(updateChecksums()));
    connect(this->leCardID,SIGNAL(textChanged(QString)),
            this,SLOT(updateChecksums()));
    connect(this->leCardType,SIGNAL(textChanged(QString)),
            this,SLOT(updateChecksums()));
    connect(this->leRecRev,SIGNAL(textChanged(QString)),
            this,SLOT(updateChecksums()));
    connect(this->leLocNr,SIGNAL(textChanged(QString)),
            this,SLOT(updateChecksums()));
}

MainWindow::~MainWindow()
{

}

/**
 * @brief Initiate the writting process.
 *
 * Checks whether the input of the QLineEdit fields is valid card
 * information. If it is not there is a message printed in the output
 * QPlainTextEdit field. If the input is valid the method
 * \link EventHandler::startWrittingProcess \endlink is called to start the
 * writting process.
 *
 * @todo seperate logic to EventHandler. There exists a method for convert QStrings to cardinformation
 */
void MainWindow::pushStartButton() {

    QString cardType = leCardType->displayText();
    QString recRev = leRecRev->displayText();
    QString locNr = leLocNr->displayText();
    QString initCardID = leCardID->displayText();
    QString initUserID = leUserID->displayText();
    QString cardAmount = leCardAmount->displayText();
    bool iterate = cbIterate->isChecked();
    int succWritting = false;


    // If any requiered input is not given an error window appears
    // The window informs that not given input is converted to 0
    if( cardType.isEmpty() || recRev.isEmpty() || locNr.isEmpty()
            || initCardID.isEmpty() || initUserID.isEmpty()
            || (cardAmount.isEmpty() && iterate ) ) {

        QMessageBox::StandardButton msgBox;
        msgBox = QMessageBox::warning(this,QString::fromUtf8("Konvertierungs Warnung"),
                                      QString::fromUtf8("Leere Eintraege werden "
                                                                "zu 0 konvertiert"));
    }

    // If iterating is activated but the amount of cards must be greater 0 or no card is
    // written
    int cardAmountVal = cardAmount.toInt(NULL, 10);
    if( (cardAmountVal < 1) && iterate) {
        QMessageBox::StandardButton msgBox;
        msgBox = QMessageBox::critical(this, QString::fromUtf8("Ungueltige Kartenanzahl"),
                                        QString::fromUtf8("Die angegebene Kartenanzahl"
                                                                  " ist unzulaessig"));
    }




    // ############ //
    // ## Output ## //
    // ############ //
    pteConsole->clear();
    leCardID->clear();
    leCardAmount->clear();

    QString consoleOutput;
    QString tempCardsLeft;
    QString outputNextCardID;

    succWritting = EventHandler::startWrittingProcess( cardType, recRev, locNr,
                                        initUserID, initCardID, cardAmount,
                                        iterate,
                                        &consoleOutput, &tempCardsLeft, &outputNextCardID);

    pteConsole->appendPlainText(consoleOutput);
    leCardID->setText(outputNextCardID);
    leCardAmount->setText(tempCardsLeft);

    if( succWritting == WRITTING_SUCCESSFULL ) {
        pteLightBox->setStyleSheet("QPlainTextEdit {background-color: green;}");
    }
    else {
        pteLightBox->setStyleSheet("QPlainTextEdit {background-color: red;}");
    }

}




/**
 * @brief   Opens a new windows that shows the information on the given card.
 *
 * @todo implement
 */
void MainWindow::pushReadButton() {
    CardInformationWindow* ciw = new CardInformationWindow(this);
    ciw->setFixedWidth(400);
    ciw->setFixedHeight(700);
    ciw->show();


}



/**
 * @brief   Enables and disables the QLineEdit field for the input for the
 *          amount of cards.
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

void MainWindow::updateChecksums() {
  QString crcAdded;
  QString crcIBM;

  EventHandler::calculateChecksums(leCardType->displayText(),
                                   leRecRev->displayText(),
                                   leLocNr->displayText(),
                                   leUserID->displayText(),
                                   leCardID->displayText(),
                                   &crcAdded,
                                   &crcIBM);

  pteChecksumAdded->clear();
  pteChecksumAdded->appendPlainText(crcAdded);
  pteChecksumIBM->clear();
  pteChecksumIBM->appendPlainText(crcIBM);


} 
