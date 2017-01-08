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
    cbIterate->setGeometry(QRect(30,150,100,30));
    cbIterate->setText(QString::fromUtf8("Iterieren"));

    // ########### //
    // ## Label ## //
    // ########### //
    lPBConsole->setObjectName(QString::fromUtf8("label_console"));
    lPBConsole->setGeometry(QRect(250,70,150,30));
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
    pteConsole->setObjectName(QString::fromUtf8("console_output"));
    pteConsole->setReadOnly(true);
    pteConsole->setEnabled(false);
    pteConsole->setGeometry(QRect(250,100,300,300));

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
    this->setTabOrder(leCardID, leUserID);
    this->setTabOrder(leUserID, cbIterate);
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
 */
void MainWindow::pushStartButton() {

    QString initCardID = leCardID->displayText();
    QString initUserID = leUserID->displayText();
    QString cardAmount = leCardAmount->displayText();
    bool iterate = cbIterate->isChecked();

    int succWritting = 0;
    bool cardConversion, userConversion, cardAmountConversion;
    const int cardID = initCardID.toInt(&cardConversion, 10);
    const int userID = initUserID.toInt(&userConversion);
    int cards = 0;
    int conversionCheckPassed = CONVERSIONCHECK_PASSED;
    if(iterate) {
        cards = cardAmount.toInt(&cardAmountConversion);
    }
    else {
        cards = 1;
    }


    // conversion check
    if( !cardConversion ) {
        conversionCheckPassed = CONVERSIONCHECK_FAILED_CARDID;
    }
    if( !userConversion ) {
        conversionCheckPassed = CONVERSIONCHECK_FAILED_USERID;
    }
    if(0 != (iterate) && (!cardAmountConversion)) {
        conversionCheckPassed = CONVERSIONCHECK_FAILED_CARDAMOUNT;
    }


    // ############ //
    // ## Output ## //
    // ############ //
    pteConsole->clear();
    // Output if conversion passed succesfull
    if(conversionCheckPassed == CONVERSIONCHECK_PASSED) {
        // Output for the inital user ID
        pteConsole->appendPlainText(QString::fromUtf8("Initiale Kunden Nummer: "));
        pteConsole->moveCursor(QTextCursor::End);
        pteConsole->insertPlainText(QString::number(userID));
        pteConsole->moveCursor(QTextCursor::End);

        // Output for the initial card ID
        pteConsole->appendPlainText(QString::fromUtf8("Initiale Karten Nummer: "));
        pteConsole->moveCursor(QTextCursor::End);
        pteConsole->insertPlainText(QString::number(cardID));
        pteConsole->moveCursor(QTextCursor::End);

        // Output for the amount of cards that should be written
        pteConsole->appendPlainText(QString::fromUtf8("Anzahl an zu schreibenden"
                                               " Karten: "));
        pteConsole->moveCursor(QTextCursor::End);
        pteConsole->insertPlainText(QString::number(cards));
        pteConsole->moveCursor(QTextCursor::End);

    }
    // Output if conversion failedg
    else {
        switch(conversionCheckPassed) {
        case CONVERSIONCHECK_FAILED_CARDID:
            pteConsole->appendPlainText(QString::fromUtf8("Fehler:"));
            pteConsole->appendPlainText(QString::fromUtf8("  Die Kartennummer ist "
                                                   "keine ganze Zahl"));
            break;
        case CONVERSIONCHECK_FAILED_USERID:
            pteConsole->appendPlainText(QString::fromUtf8("Fehler:"));
            pteConsole->appendPlainText(QString::fromUtf8("  Die Kundennummer ist "
                                                   "keine ganze Zahl"));
            break;
        case CONVERSIONCHECK_FAILED_CARDAMOUNT:
            pteConsole->appendPlainText(QString::fromUtf8("Fehler:"));
            pteConsole->appendPlainText(QString::fromUtf8("  Die Anzahl an zu "
                                                   "schreibenden Karten"
                                                   " ist keine ganze Zahl"));
            break;
        default:
            pteConsole->appendPlainText(QString::fromUtf8("Something unexpected "
                                                   "happend while reading the"
                                                   " input data"));
        }
    }


    switch(succWritting) {
    case ERROR_NOT_IMPLEMENTED:
        pteConsole->appendPlainText(QString::fromUtf8("Das Schreiben ist noch "
                                                      "nicht implementiert"));
        break;
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


} 
