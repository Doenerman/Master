#include "cardinformationwindow.h"


CardInformationWindow::CardInformationWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // Set the properties of the different objects
    // Properties:  - geometry (including the placement)
    //              - object name
    //              - possible text
    //              - possible placeholder if no entry is given
    //              - whether the object is enabled
    //              - whether the user can overwrite given text


    // ########### //
    // ## Label ## //
    // ########### //
    lUniquecardID->setObjectName(QString::fromUtf8("label_uniqueID"));
    lUniquecardID->setGeometry(QRect(
                                     LABEL_X_POS_FIRST_COLUMN,
                                     LABEL_Y_POS_UNIQUEID,
                                     2*LABEL_DEFAULT_WIDTH,
                                     LABEL_DEFAULT_HEIGHT));
    lUniquecardID->setText(QString::fromUtf8("eindeutige Karten Nummer"));

    lLocationNumber->setObjectName(QString::fromUtf8("label_locationNumber"));
    lLocationNumber->setGeometry(QRect(LABEL_X_POS_FIRST_COLUMN,
                                       LABEL_Y_POS_LOCNR,
                                       LABEL_DEFAULT_WIDTH,
                                       LABEL_DEFAULT_HEIGHT));
    lLocationNumber->setText(QString::fromUtf8("Landeskennung"));

    lCardType->setObjectName(QString::fromUtf8("label_cardType"));
    lCardType->setGeometry(QRect(LABEL_X_POS_SECOND_COLUMN,
                                 LABEL_Y_POS_LOCNR,
                                 LABEL_DEFAULT_WIDTH,
                                 LABEL_DEFAULT_HEIGHT));

    lRev->setObjectName(QString::fromUtf8("label_revision"));
    lRev->setGeometry(QRect(LABEL_X_POS_SECOND_COLUMN,
                            LABEL_Y_POS_REVNR,
                            LABEL_DEFAULT_WIDTH,
                            LABEL_DEFAULT_HEIGHT));
    lRev->setText(QString::fromUtf8("Revision Nummer"));

    lUserID->setObjectName(QString::fromUtf8("label_userID"));
    lUserID->setGeometry(QRect(LABEL_X_POS_FIRST_COLUMN,
                               LABEL_Y_POS_USERID,
                               LABEL_DEFAULT_WIDTH,
                               LABEL_DEFAULT_HEIGHT));
    lUserID->setText(QString::fromUtf8("Kundennummer"));

    lCardID->setObjectName(QString::fromUtf8("label_cardID"));
    lCardID->setGeometry(QRect(LABEL_X_POS_FIRST_COLUMN,
                               LABEL_Y_POS_CARDID,
                               LABEL_DEFAULT_WIDTH,
                               LABEL_DEFAULT_HEIGHT));
    lCardID->setText(QString::fromUtf8("Kartennummer"));

    lChecksumAdded->setObjectName(QString::fromUtf8("label_checksumAdded"));
    lChecksumAdded->setGeometry(QRect(LABEL_X_POS_FIRST_COLUMN,
                                      LABEL_Y_POS_CHECKADD,
                                      LABEL_DEFAULT_WIDTH,
                                      LABEL_DEFAULT_HEIGHT));
    lChecksumAdded->setText(QString::fromUtf8("Pruefsumme (addiert)"));

    lChecksumIBM->setObjectName(QString::fromUtf8("label_checksumIBM"));
    lChecksumIBM->setGeometry(QRect(LABEL_X_POS_FIRST_COLUMN,
                                    LABEL_Y_POS_CHECKIBM,
                                    LABEL_DEFAULT_WIDTH,
                                    LABEL_DEFAULT_HEIGHT));
    lChecksumIBM->setText(QString::fromUtf8("Preufsumme (IBM)"));

    lMD5->setObjectName(QString::fromUtf8("label_MD5"));
    lMD5->setGeometry(QRect(LABEL_X_POS_FIRST_COLUMN,
                            LABEL_Y_POS_MD5,
                            LABEL_DEFAULT_WIDTH,
                            LABEL_DEFAULT_HEIGHT));
    lMD5->setText(QString::fromUtf8("MD5"));



    // ################### //
    // ## PlainTextEdit ## //
    // ################### //
    pteUniquecardID->setObjectName(QString::fromUtf8("pte_uniqueCardID"));
    pteUniquecardID->setEnabled(false);
    pteUniquecardID->setGeometry(QRect(PLAINTEXTEDIT_X_FIRST_COLUMN,
                                       LABEL_Y_POS_UNIQUEID
                                       + PLAINTEXT_LABEL_PUFFER,
                                       2*PLAINTEXTEDIT_DEFAULT_WIDTH,
                                       PLAINTEXTEDIT_DEFAULT_HEIGHT));

    pteLocationNumber->setObjectName(QString::fromUtf8("pte_locNr"));
    pteLocationNumber->setEnabled(false);
    pteLocationNumber->setGeometry(QRect(PLAINTEXTEDIT_X_FIRST_COLUMN,
                                         LABEL_Y_POS_LOCNR
                                         + PLAINTEXT_LABEL_PUFFER,
                                         PLAINTEXTEDIT_DEFAULT_WIDTH,
                                         PLAINTEXTEDIT_DEFAULT_HEIGHT));


    pteCardType->setObjectName(QString::fromUtf8("pte_cardType"));
    pteCardType->setEnabled(false);
    pteCardType->setGeometry(QRect(PLAINTEXTEDIT_X_SECOND_COLUMN,
                                   LABEL_Y_POS_LOCNR + PLAINTEXT_LABEL_PUFFER,
                                   PLAINTEXTEDIT_DEFAULT_WIDTH,
                                   PLAINTEXTEDIT_DEFAULT_HEIGHT));

    pteRev->setObjectName(QString::fromUtf8("pte_revNr"));
    pteRev->setEnabled(false);
    pteRev->setGeometry(QRect(PLAINTEXTEDIT_X_SECOND_COLUMN,
                              LABEL_Y_POS_REVNR
                              + PLAINTEXT_LABEL_PUFFER,
                              PLAINTEXTEDIT_DEFAULT_WIDTH,
                              PLAINTEXTEDIT_DEFAULT_HEIGHT));

    pteUserID->setObjectName(QString::fromUtf8("pte_userID"));
    pteUserID->setEnabled(false);
    pteUserID->setGeometry(QRect(PLAINTEXTEDIT_X_FIRST_COLUMN,
                                 LABEL_Y_POS_USERID
                                 + PLAINTEXT_LABEL_PUFFER,
                                 PLAINTEXTEDIT_DEFAULT_WIDTH,
                                 PLAINTEXTEDIT_DEFAULT_HEIGHT
                                 ));

    pteCardID->setObjectName(QString::fromUtf8("pte_cardID"));
    pteCardID->setEnabled(false);
    pteCardID->setGeometry(QRect(PLAINTEXTEDIT_X_FIRST_COLUMN,
                                 LABEL_Y_POS_CARDID
                                 + PLAINTEXT_LABEL_PUFFER,
                                 PLAINTEXTEDIT_DEFAULT_WIDTH,
                                 PLAINTEXTEDIT_DEFAULT_HEIGHT
                                 ));

    pteChecksumAdded->setObjectName(QString::fromUtf8("pte_checkAdd"));
    pteChecksumAdded->setEnabled(false);
    pteChecksumAdded->setGeometry(QRect(PLAINTEXTEDIT_X_FIRST_COLUMN,
                                        LABEL_Y_POS_CHECKADD
                                        + PLAINTEXT_LABEL_PUFFER,
                                        PLAINTEXTEDIT_DEFAULT_WIDTH,
                                        PLAINTEXTEDIT_DEFAULT_HEIGHT
                                       ));

    pteChecksumIBM->setObjectName(QString::fromUtf8("pte_checkIBM"));
    pteChecksumIBM->setEnabled(false);
    pteChecksumIBM->setGeometry(QRect(PLAINTEXTEDIT_X_FIRST_COLUMN,
                                      LABEL_Y_POS_CHECKIBM
                                      + PLAINTEXT_LABEL_PUFFER,
                                      PLAINTEXTEDIT_DEFAULT_WIDTH,
                                      PLAINTEXTEDIT_DEFAULT_HEIGHT
                                     ));

    pteMD5->setObjectName(QString::fromUtf8("pte_MD5"));
    pteMD5->setEnabled(false);
    pteMD5->setGeometry(QRect(PLAINTEXTEDIT_X_FIRST_COLUMN,
                              LABEL_Y_POS_MD5
                              + PLAINTEXT_LABEL_PUFFER,
                              2*PLAINTEXTEDIT_DEFAULT_WIDTH,
                              PLAINTEXTEDIT_DEFAULT_HEIGHT
                             ));

    // ################ //
    // ## PushButton ## //
    // ################ //
    pbRefresh->setObjectName(QString::fromUtf8("refresh_button"));
    pbRefresh->setGeometry(QRect(PUSHBOTTEN_X_REFRESH,
                                 PUSHBOTTON_Y,
                                 PUSHBUTTON_DEFAULT_WIDTH,
                                 PUSHBOTTON_DEFAULT_HEIGHT));
    pbRefresh->setText(QString::fromUtf8("Erneut Lesen"));

    pbClose->setObjectName(QString::fromUtf8("close_button"));
    pbClose->setGeometry(QRect(PUSHBOTTON_X_CLOSE,
                               PUSHBOTTON_Y,
                               PUSHBUTTON_DEFAULT_WIDTH,
                               PUSHBOTTON_DEFAULT_HEIGHT));
    pbClose->setText(QString::fromUtf8("Lesen beenden"));





    // ######################### //
    // ## Set the focus order ## //
    // ######################### //
    this->setTabOrder(pbRefresh, pbClose);


    // ########################################### //
    // ## Connections between SIGNALS and SLOTS ## //
    // ########################################### //
    connect(this->pbClose,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(this->pbRefresh,SIGNAL(clicked(bool)),this,SLOT(reload()));

}


/**
 * @brief   Initiate the reload of the information
 *
 * @todo implementation
 */
void CardInformationWindow::reload() {

    int cardType, recRev, locNr, userID, cardID, crcAdd, crcIBM;
    QByteArray uniqueID, md5Sum;
    QVector<int> error;
    bool correctCard = true;

    QPalette pAdd = pteChecksumAdded->palette();
    QPalette pIBM = pteChecksumIBM->palette();
    QPalette pMD5 = pteMD5->palette();

    pAdd.setColor(QPalette::Text, Qt::blue);
    pIBM.setColor(QPalette::Text, Qt::blue);
    pMD5.setColor(QPalette::Text, Qt::blue);


    pteUniquecardID->clear();
    pteLocationNumber->clear();
    pteCardType->clear();
    pteRev->clear();
    pteUserID->clear();
    pteCardID->clear();
    pteChecksumAdded->clear();
    pteChecksumIBM->clear();
    pteMD5->clear();

    Reader::readCard(&uniqueID, &cardType, &recRev, &locNr, &userID, &cardID, &crcAdd, &crcIBM, &md5Sum);


    // calculate checksums
    card_info tempCard;
    for(int iter = 0; iter < uniqueID.size(); iter++) {
      tempCard.uid[iter] = uniqueID.at(iter);
    }
    tempCard.card_type = cardType;
    tempCard.record_rev = recRev;
    tempCard.locNr = locNr;
    tempCard.reserved_block0 = 0;
    tempCard.kunden_nr = userID;
    tempCard.card_nr = cardID;
    tempCard.crc16_added = crcAdd;
    tempCard.crc16_ibm = crcIBM;
    tempCard.reserve_block4 = 0;
    tempCard.reserve_block5 = 0;

    unsigned char* temp;


    bool cardIsCorrect = EventHandler::checkCardCorrectness(tempCard, &error);

    if(!cardIsCorrect) {
      
      if(error.at(CRCADD_ERROR_POS) == CHECKSUM_ERROR) {
        pAdd.setColor(QPalette::Text, Qt::red);
      }
      if(error.at(CRCIBM_ERROR_POS) == CHECKSUM_ERROR) {
        pIBM.setColor(QPalette::Text, Qt::red);
      }
      if(error.at(MD5SUM_ERROR_POS) == CHECKSUM_ERROR) {
        pMD5.setColor(QPalette::Text, Qt::red);
      }

    }

    pteChecksumAdded->setPalette(pAdd);
    pteChecksumIBM->setPalette(pIBM);
    pteMD5->setPalette(pMD5);

    QString uniqueIDString = QString(uniqueID);
    pteUniquecardID->appendPlainText(uniqueIDString);
    pteLocationNumber->appendPlainText(QString::number(locNr, 10));
    pteCardType->appendPlainText(QString::number(cardType, 10));
    pteRev->appendPlainText(QString::number(recRev, 10));
    pteUserID->appendPlainText(QString::number(userID, 10));
    pteCardID->appendPlainText(QString::number(cardID, 10));
    pteChecksumAdded->appendPlainText(QString::number(crcAdd, 10));
    pteChecksumIBM->appendPlainText(QString::number(crcIBM, 10));
    pteMD5->appendPlainText(md5Sum);
}
