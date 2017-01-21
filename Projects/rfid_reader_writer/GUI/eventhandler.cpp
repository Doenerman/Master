#include "eventhandler.h"

/**
 * @brief This method starts the writting process.
 *
 * It converts the QStrings into integer and checks whether the given QStrings
 * can be converted to integers. If the QStrings can not be converted to Integer
 * A notification is printed to the QPlainTextEdit field. If the conversion
 * is done successful given Information about the different IDs and the amount
 * of cards that should be written is printed in the given QPLainTextEdit field.
 *
 * @param pte   pointer to the QPlainTextEdit where possible notifications
 *              can be printed
 * @return  1 iff and only if no error occured.Iff an error occured the
 *          the corresponding error code is returned
 *
 * @todo implement the connection to the background programm
 */
int EventHandler::startWrittingProcess(
                                        QString userID,
                                        QString cardID,
                                        QString* const consoleOutput,
                                        QString* const cardsLeft,
                                        QString* const nextCardID) {

    return ERROR_NOT_IMPLEMENTED;
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
                         QString stringCardType,
                         QString stringRecRev,
                         QString stringLocNr,
                         QString stringUserID,
                         QString stringCardID,
                         QString* const crcAdded,
                         QString* const crcIBM) {

    card_info tempCard;
    int cardType;
    int recRev;
    int locNr;
    int userID;
    int cardID;
    int tempCrcAdded = 0;
    int tempCrcIBM = 0;
    
    bool succConversion;

    cardType = stringCardType.toInt(&succConversion, 10);
    if(!succConversion)
      cardType = 0;
    recRev = stringRecRev.toInt(&succConversion, 10);
    if(!succConversion)
      recRev = 0;
    locNr = stringLocNr.toInt(&succConversion, 10);
    if(!succConversion)
      locNr = 0;
    userID = stringUserID.toInt(&succConversion, 10);
    if(!succConversion)
      userID = 0;
    cardID = stringCardID.toInt(&succConversion, 10);
    if(!succConversion)
      cardID = 0;



    tempCard.card_type = cardType;
    tempCard.record_rev = recRev;
    tempCard.locNr = locNr;
    tempCard.kunden_nr = userID;
    tempCard.card_nr = cardID;

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

