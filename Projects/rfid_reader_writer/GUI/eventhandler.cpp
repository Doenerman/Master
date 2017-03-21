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
 * @param stringCard[out]     the \link card_info \endlink where the converted
 *                      information is stored in
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
    bool    succConversion = true;
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
        succConversion = CONVERSIONCHECK_FAILED_CARDTYPE;
    }
    if( !recRevConversion ) {
        recRev = 0;
        succConversion = CONVERSIONCHECK_FAILED_RECREV;
    }
    if( !locNrConversion ) {
        locNr = 0;
        succConversion = CONVERSIONCHECK_FAILED_LOCNR;
    }
    if( !userIDConversion ) {
        userID = 0;
        succConversion = CONVERSIONCHECK_FAILED_USERID;
    }
    if( !cardIDConversion ) {
        cardID = 0;
        succConversion = CONVERSIONCHECK_FAILED_CARDID;
    }


    card->card_type = cardType;
    card->record_rev = recRev;
    card->locNr = locNr;
    card->kunden_nr = userID;
    card->card_nr = cardID;

    return succConversion;
}
/**
 * @brief This method starts the writting process.
 *
 * It converts the QStrings into integer and checks whether the given QStrings
 * can be converted to integers. If the QStrings can not be converted to Integer
 * A notification is printed to the QPlainTextEdit field. If the conversion
 * is done successful given Information about the different IDs and the amount
 * of cards that should be written is printed in the given QPLainTextEdit field.
 *
 * @param[in] cardType          A QString that will be converted to the card type
 * @param[in] recRev            A QString that will be converted to the record Rev
 * @param[in] locNr             A QString that will be converted to the location number
 * @param[in] userID            A QString that will be converted to the user ID
 * @param[in] cardID            A QString that will be converted to the card ID
 * @param[in] amount            A QString that will be interpreted as the amount of cards
 *                              that should be written
 * @param[in] iterate           The bool that indecates whether there is more than one card
 *                              written
 * @param[out] consoleOutput    A pointer where the output of for the console will be
 *                              written in
 * @param[out] cardsLeft        A pointer where the cards left will be written in
 * @param[out] nextCardID       A pointer where the next cardID will be written in
 *
 * @return  \link WRITTING_SUCCSESSFULL \endlink iff the writting process was seccessful
 *
 *
 * @todo implement the connection to the background programm
 */
int EventHandler::startWrittingProcess(
                                        const QString cardType,
                                        const QString recRev,
                                        const QString locNr,
                                        const QString userID,
                                        const QString cardID,
                                        const QString amount,
                                        const bool iterate,
                                        QString* const consoleOutput,
                                        QString* const cardsLeft,
                                        QString* const nextCardID) {

    card_info tempCard;
    int succConversion;
    int cardAmount;
    int nextCardID_int;
    int succWritting;
    succConversion = EventHandler::convertQStringsToCard(cardType,recRev,locNr,
                                                         userID,cardID,&tempCard);


    // Calculate the amount of cards that should be written
    if(iterate) {
        bool cardAmountConversion, nextCardIDConversion;
        cardAmount = amount.toInt(&cardAmountConversion,10);
        nextCardID_int = cardID.toInt(&nextCardIDConversion,10) -1;
        if( !cardAmountConversion ) {
            cardAmount = 0;
            succConversion = CONVERSIONCHECK_FAILED_CARDAMOUNT;
        }
        if( !nextCardIDConversion ) {
            nextCardID_int = 0;
            succConversion = CONVERSIONCHECK_FAILED_CARDAMOUNT;
        }

    }
    else {
        cardAmount = 1;
    }
    //////////////////////
    // Writting Process //
    //////////////////////

    if( (iterate && cardAmount > 0) || (!iterate) ) {
        succWritting = WRITTING_SUCCESSFULL;
    }
    if( iterate && (cardAmount <= 0) ) {
        succWritting = NO_CARD_LEFT_TO_WRITE;
    }


    ////////////////////////
    // Output Preperation //
    ////////////////////////

    consoleOutput->clear();
    // conversion of all data was successfull
    if( succConversion == CONVERSIONCHECK_PASSED ) {


        // console output
        consoleOutput->append(QString::fromUtf8("Kunden Nummer: "));
        consoleOutput->append(QString::number(tempCard.kunden_nr, 10));
        consoleOutput->append(QString::fromUtf8("\n"));
        consoleOutput->append(QString::fromUtf8("Karten Nummer: "));
        consoleOutput->append(QString::number(tempCard.card_nr, 10));
        consoleOutput->append(QString::fromUtf8("\n"));
        consoleOutput->append(QString::fromUtf8("Anzahl zu schreibender Karten: "));
        consoleOutput->append(QString::number(cardAmount));
        consoleOutput->append(QString::fromUtf8("\n"));

    }

    // output if an error occures while conversion
    // output console
    if( succConversion != CONVERSIONCHECK_PASSED ) {
        switch (succConversion) {
            case CONVERSIONCHECK_FAILED_CARDTYPE:
                consoleOutput->append(QString::fromUtf8("Fehler:\n"));
                consoleOutput->append(QString::fromUtf8("  Der Kartentyp kann nicht "
                                                        "interpretiert werden"));
                break;
            case CONVERSIONCHECK_FAILED_RECREV:
                consoleOutput->append(QString::fromUtf8("Fehler:\n"));
                consoleOutput->append(QString::fromUtf8("  Die Record Rev kann nicht "
                                                        "interpretiert werden"));
                break;
            case CONVERSIONCHECK_FAILED_LOCNR:
                consoleOutput->append(QString::fromUtf8("Fehler:\n"));
                consoleOutput->append(QString::fromUtf8("  Die Landeskennung kann nicht "
                                                        "interpretiert werden"));
                break;
            case CONVERSIONCHECK_FAILED_USERID:
                consoleOutput->append(QString::fromUtf8("Fehler:\n"));
                consoleOutput->append(QString::fromUtf8("  Die Kundennummber kann nicht "
                                                        "interpretiert werden"));
                break;
            case CONVERSIONCHECK_FAILED_CARDID:
                consoleOutput->append(QString::fromUtf8("Fehler:\n"));
                consoleOutput->append(QString::fromUtf8("  Die Kartennummer kann nicht "
                                                        "interpretiert werden"));
                break;
            case CONVERSIONCHECK_FAILED_CARDAMOUNT:
                consoleOutput->append(QString::fromUtf8("Fehler:\n"));
                consoleOutput->append(QString::fromUtf8("  Die Anzahl an zu "
                                                        "schreibenden Karten "
                                                        "kann nicht interpertiert"
                                                        " werden"));
                break;
            default:
                consoleOutput->append(QString::fromUtf8("Fehler:\n"));
                consoleOutput->append(QString::fromUtf8("  unbekannter Fehler"));
                break;
        }

    }



    switch(succWritting) {
        case WRITTING_SUCCESSFULL:
            cardsLeft->setNum(cardAmount - 1);      /* - 1 because one card is written
                                                     * and one card less must be written */
            nextCardID->setNum(tempCard.card_nr + 1); /* + 1 because one card is written
                                                     * and the next cardID must be used */
            break;
        case NO_CARD_LEFT_TO_WRITE:
            cardsLeft->setNum(cardAmount);
            nextCardID->setNum(tempCard.card_nr);
            consoleOutput->append(QString::fromUtf8("\n"));
            consoleOutput->append(QString::fromUtf8("Fehler:\n"));
            consoleOutput->append(QString::fromUtf8("  unzulaessige Kartenanzahl"));
            break;
        default:
            consoleOutput->append(QString::fromUtf8("\n"));
            consoleOutput->append(QString::fromUtf8("Fehler:\n"));
            consoleOutput->append(QString::fromUtf8("  unbekannter Fehler beim Schreiben"));
    }

    return succWritting;

}

/**
 * @brief Calculates the checksums with input.
 *
 * The checksums are calculated with the help of
 * \link Calculator.cpp \enlink. The calculated checksums are written in
 * \link crcAdded \endlink and \link crcIBM \endlink. The \link crcAdded \endlink
 * is a bytewise added checksum. The \link crcIBM \endlink checksum is calculated
 * with an algorithm created by IBM.
 *
 * @param stringCardType[in]    Type of the card
 * @param stringRecRev[in]      Record Rev of the card
 * @param stringLocNr[in]       Location number of the card
 * @param stringUserID[in]      User ID of the card
 * @param stringCardID[in]      Card ID of the card
 * @param crcAdded[out]         The calculated added checksum
 * @param crcIBM[out]           The calculated IBM checksum
 */
void EventHandler::calculateChecksums(
                         const QString stringCardType,
                         const QString stringRecRev,
                         const QString stringLocNr,
                         const QString stringUserID,
                         const QString stringCardID,
                         QString* const crcAdded,
                         QString* const crcIBM) {

    card_info tempCard;
    int tempCrcAdded, tempCrcIBM;

    convertQStringsToCard(stringCardType, stringRecRev,
                          stringLocNr, stringUserID,
                          stringCardID, &tempCard);



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




