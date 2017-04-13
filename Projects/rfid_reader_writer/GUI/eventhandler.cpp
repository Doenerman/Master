#include "eventhandler.h"
#include "src/CardInformation.hpp"


/**
 * @brief   Interprets the given QStrings as card information and
 *          writes them into the given \link card_info \endlink
 *
 *
 * @param stringCardType[in]  the type of the card
 * @param stringRecRev[in]    the record Rev of the card
 * @param stringLocNr[in]     the location number of the card
 * @param stringUserID[in]    the user ID of the card
 * @param stringCardID[in]    the card ID of the card
 * @param stringCard[out]     the \link card_info \endlink where the
 *                            converted information is stored in
 * @return          true if and only if the QStrings were successfully
 *                  interpreted as card information
 */
int EventHandler::convertQStringsToCard(  QString stringCardType,
                                   QString stringRecRev,
                                   QString stringLocNr,
                                   QString stringUserID,
                                   QString stringCardID,
                                   card_info* card)
{
    int cardType;
    int recRev;
    int locNr;
    int userID;
    int cardID;

    // succConversion is set to fails if any conversion fails
    int    succConversion = NO_CONVERSION_ERROR_YET;
    bool    cardTypeConversion = false;
    bool    recRevConversion = false;
    bool    locNrConversion = false;
    bool    userIDConversion = false;
    bool    cardIDConversion = false;


    cardType = stringCardType.toInt(&cardTypeConversion, 10);
    recRev = stringRecRev.toInt(&recRevConversion, 10);
    locNr = stringLocNr.toInt(&locNrConversion, 10);
    userID = stringUserID.toInt(&userIDConversion, 10);
    cardID = stringCardID.toInt(&cardIDConversion, 10);


    // conversion check
    if( !cardTypeConversion ) {
        cardType = 0;
        succConversion += CARDTYPE_CONVERSION_FAILED;
    }
    if( !recRevConversion ) {
        recRev = 0;
        succConversion += RECREV_CONVERSION_FAILED;
    }
    if( !locNrConversion ) {
        locNr = 0;
        succConversion += LOCNR_CONVERSION_FAILED;
    }
    if( !userIDConversion ) {
        userID = 0;
        succConversion += USERID_CONVERSION_FAILED;
    }
    if( !cardIDConversion ) {
        cardID = 0;
        succConversion += INITCARDID_CONVERSION_FAILED;
    }

    if(succConversion == NO_CONVERSION_ERROR_YET) {
        succConversion = CONVERSION_SUCC;
    }


    card->card_type = (uint8_t)cardType;
    card->record_rev = (uint8_t)recRev;
    card->locNr = (uint8_t)locNr;
    card->reserved_block0 = 0;
    card->kunden_nr = (uint32_t)userID;
    card->card_nr = (uint32_t)cardID;
    card->reserve_block4 = 0;
    card->reserve_block5 = 0;

    return succConversion;
}
/**
 * @brief This method starts the writting process.
 *
 * It converts the QStrings into integer and checks whether the given
 * QStrings can be converted to integers. If the QStrings can not be
 * converted to Integer. A notification is printed to the
 * QPlainTextEdit field. If the conversion is done successful given
 * Information about the different IDs and the amount of cards that
 * should be written is printed in the given QPLainTextEdit field.
 *
 * @param[in] cardType          A QString that will be converted to
 *                              the card type
 * @param[in] recRev            A QString that will be converted to
 *                              the record Rev
 * @param[in] locNr             A QString that will be converted to
 *                              the location number
 * @param[in] userID            A QString that will be converted to
 *                              the user ID
 * @param[in] cardID            A QString that will be converted to
 *                              the card ID
 * @param[in] amount            A QString that will be interpreted
 *                              as the amount of cards
 *                              that should be written
 * @param[in] iterate           The bool that indecates whether there
 *                              is more than one card
 *                              written
 * @param[out] consoleOutput    A pointer where the output of for
 *                              the console will be
 *                              written in
 * @param[out] cardsLeft        A pointer where the cards left will
 *                              be written in
 * @param[out] nextCardID       A pointer where the next cardID will
 *                              be written in
 *
 * @return  \link WRITTING_SUCCSESSFULL \endlink iff the writting
 *                              process was seccessful
 * @todo implement the connection to the background programm
 */
int EventHandler::initWrittingProcess(
        const QString cardType,
        const QString recRev,
        const QString locNr,
        const QString userID,
        const QString cardID,
        const QString amount,
        const bool iterate,
        QString *const consoleOutput) {

    card_info tempCard;
    bool readyToWrite;
    int succConversion;
    int cardAmount = amount.toInt(NULL, 10);
    int succWritting = 0;
    succConversion =
            EventHandler::convertQStringsToCard(cardType,recRev,
                                                locNr,userID,
                                                cardID,&tempCard);
    // Output for converion error
    // output console

    // @todo set alarm because of the appeared error
    if( succConversion != CONVERSION_SUCC ) {
        readyToWrite = false;
        consoleOutput->append(QString::fromUtf8("Fehler:\n"));
        if( succConversion <= LOCNR_CONVERSION_FAILED ) {
            std::cout << "rofl die kuh weg" << std::endl;
            succConversion -= LOCNR_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Die Landeskennung kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
            MainWindow::conversionErrorWindow(LOCNR_CONVERSION_FAILED);
        }
        if( succConversion <= RECREV_CONVERSION_FAILED ) {
            succConversion -= RECREV_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Die Record Rev kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
        }
        if( succConversion <= CARDTYPE_CONVERSION_FAILED ) {
            succConversion -= CARDTYPE_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Der Kartentyp kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
        }
        if( succConversion <= USERID_CONVERSION_FAILED ) {
            succConversion -= USERID_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Die Kundennummer kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
        }
        if( succConversion <= CARDTYPE_CONVERSION_FAILED ) {
            succConversion -= CARDTYPE_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Die Kundenanzahl kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
        }
        if( succConversion <= INITCARDID_CONVERSION_FAILED ) {
            succConversion -= INITCARDID_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Die Kartennummer kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
        }
        if( succConversion < 0) {
            consoleOutput->append(QString::fromUtf8("  unbekannter Fehler"));
        }

    }
    else {
        readyToWrite = true;
    }



    if(readyToWrite ) {
        //@todo call writeProcess(..)


        //////////////////////
        // Writting Process //
        //////////////////////

        if ((iterate && cardAmount > 0) || (!iterate)) {
            succWritting = WRITEPROCESS;
        }
        if (iterate && (cardAmount <= 0)) {
            succWritting = NO_CARD_LEFT_TO_WRITE;
        }

        //@todo kontrolllesen

        ///////////////////
        // Write Logfile //
        ///////////////////

    consoleOutput->clear();
        // conversion of all data was successfull
        if (succConversion == CONVERSIONCHECK_PASSED) {


            // console output
            consoleOutput->append(QString::fromUtf8("Kunden Nummer: "));
            consoleOutput->append(QString::number(tempCard.kunden_nr, 10));
            consoleOutput->append(QString::fromUtf8("\n"));
            consoleOutput->append(QString::fromUtf8("Karten Nummer: "));
            consoleOutput->append(QString::number(tempCard.card_nr, 10));
            consoleOutput->append(QString::fromUtf8("\n"));
            consoleOutput->append(
                    QString::fromUtf8("Anzahl zu schreibender Karten: "));
            consoleOutput->append(QString::number(cardAmount));
            consoleOutput->append(QString::fromUtf8("\n"));

        }
    }
    // output if an error occures while conversion

    return succWritting;

}

/**
 * @brief Writes a single card only.
 *
 * Writes the card \link card \endlink.
 *
 * @param cards              The card information that should be written
 * @param[out] consoleOutput    A pointer where the output of for
 *                              the console will be
 *                              written in
 * @param[out] cardsLeft        A pointer where the cards left will
 *                              be written in
 * @param[out] nextCardID       A pointer where the next cardID will
 *                              be written in
 * @return
 */
int EventHandler::writeProcess(const QVector<card_info> cards,
                               const QString customer,
                               const QString jobID,
                               QString *const consoleOutput,
                               QString *const cardsLeft,
                               QString *const nextCardID) {


    QVector<QVector<int>> error = QVector<QVector<int>>(0);
    int iter = 0;
    int succWritting = WRITTING_SUCCESSFULL;


    for(iter = 0; iter < cards.size(); iter++) {
        QVector<int> currError = QVector<int>(0);
        error.append(currError);

        // @todo check cast (QVector<int> *) below
        EventHandler::writeCard(cards.at(iter),
                                (QVector<int> *) &error.at(iter));
        // @todo kontrollesen


        switch (succWritting) {
            case WRITTING_SUCCESSFULL:/* - 1 because one cards is written
                                       * and one cards less must be written */
                cardsLeft->setNum(SINGLE_WRITE_PROCESS_NEXT_CARDID);
                /* + 1 because one cards is written
                 * and the next cardID must be used */
                nextCardID->setNum(cards.at(iter).card_nr + 1);
                // console output
                consoleOutput->append(QString::fromUtf8("Kunden Nummer: "));
                consoleOutput->append(QString::number(cards.at(iter).kunden_nr, 10));
                consoleOutput->append(QString::fromUtf8("\n"));
                consoleOutput->append(QString::fromUtf8("Karten Nummer: "));
                consoleOutput->append(QString::number(cards.at(iter).card_nr, 10));
                consoleOutput->append(QString::fromUtf8("\n"));
                consoleOutput->append(
                        QString::fromUtf8("Anzahl zu schreibender Karten: "));
                consoleOutput->append(QString::number(
                        SINGLE_WRITE_PROCESS_CARD_LEFT_TO_WRITE));
                consoleOutput->append(QString::fromUtf8("\n"));
                break;
            case NO_CARD_LEFT_TO_WRITE:
                cardsLeft->setNum(SINGLE_WRITE_PROCESS_CARD_LEFT_TO_WRITE);
                nextCardID->setNum(cards.at(iter).card_nr);
                consoleOutput->append(QString::fromUtf8("\n"));
                consoleOutput->append(QString::fromUtf8("Fehler:\n"));
                consoleOutput->append(QString::fromUtf8(
                        "  unzulaessige Kartenanzahl"));
                break;
            default:
                consoleOutput->append(QString::fromUtf8("\n"));
                consoleOutput->append(QString::fromUtf8("Fehler:\n"));
                consoleOutput->append(QString::fromUtf8(
                        "  unbekannter Fehler beim Schreiben"));
        }
    }

    LogFile::writeLogFile(customer, jobID, cards, error);

    return succWritting;
}

/**
 * @brief Calculates the checksums with input.
 *
 * The checksums are calculated with the help of
 * \link Calculator.cpp \enlink. The calculated checksums are written in
 * \link crcAdded \endlink and \link crcIBM \endlink. The
 * \link crcAdded \endlink is a bytewise added checksum. The
 * \link crcIBM \endlink checksum is calculated
 * with an algorithm created by IBM.
 *
 * @param stringCardType[in]    Type of the card
 * @param stringRecRev[in]      Record Rev of the card
 * @param stringLocNr[in]       Location number of the card
 * @param stringUserID[in]      User ID of the card
 * @param stringCardID[in]      Card ID of the card
 * @param crcAdded[out]         The calculated added checksum
 * @param crcIBM[out]           The calculated IBM checksum
 * @return the success or error message that is returned by \link
 *        convertQStringsToCard \endlink
 */
int EventHandler::calculateChecksums(
                         const QString stringCardType,
                         const QString stringRecRev,
                         const QString stringLocNr,
                         const QString stringUserID,
                         const QString stringCardID,
                         QString* const crcAdded,
                         QString* const crcIBM) {

    card_info tempCard;
    int tempCrcAdded, tempCrcIBM, response;

    response = convertQStringsToCard(stringCardType, stringRecRev,
                          stringLocNr, stringUserID,
                          stringCardID, &tempCard);


    if(response == CONVERSION_SUCC ) {

        calcCRC16_added(tempCard.card_type,
                        tempCard.record_rev,
                        tempCard.locNr,
                        tempCard.kunden_nr,
                        tempCard.card_nr,
                        &tempCrcAdded);

        tempCrcIBM = calcCRC16_ibm(&tempCard.card_type,
                                   INFORMATION_LENGTH_IN_BYTE);


        crcAdded->setNum(tempCrcAdded);
        crcIBM->setNum(tempCrcIBM);
    }

    return response;
  
}

/**
 * @brief Writes the information of the input card and writes it on the
 *        card.
 *
 * This method writes the given information on a card. The writting process
 * has \link MAX_WRITE_ATTEMPTS \endlink to perform. In case an error occured
 * during the writting process the error is logged in the QVector
 * \link error \endlink .
 *
 * @param card  The \link card_info \endlink that should be written
 * @param error A QVector<int> where all error that occured while writting are
 *              logged
 */
void EventHandler::writeCard(const card_info card,
                            QVector<int>* error) {
    // @todo impelment
}
