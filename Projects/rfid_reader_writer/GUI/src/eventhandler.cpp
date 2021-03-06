#include "eventhandler.h"


/**
 * @brief   Interprets the given QStrings as card information and
 *          writes them into the given \link card_info \endlink
 *
 * In order to interpret the given QStringsthe all have to be converted into an
 * integer. After all conversions are done successfully the information are
 * written to the given card. In case one conversion failed no information will
 * be written on the card and the return value is the sum of all failed
 * conversions.
 *
 *
 * @param[in] stringCardType  the type of the card
 * @param[in] stringRecRev    the record Rev of the card
 * @param[in] stringLocNr     the location number of the card
 * @param[in] stringUserID    the user ID of the card
 * @param[in] stringCardID    the card ID of the card
 * @param[out] card     the \link card_info \endlink where the
 *                            converted information is stored in
 * @return              \link CONVERSION_SUCC \endlink in case no conversion
 *                      appeared. If at least one conversion error appeared this
 *                      value is the sum of all conversion errors. With the help
 *                      of this sum it is possible to determine which conversion
 *                      failed.
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

    if( succConversion == CONVERSION_SUCC ) {
      card->card_type = (uint8_t)cardType;
      card->record_rev = (uint8_t)recRev;
      card->locNr = (uint8_t)locNr;
      card->reserved_block0 = 0;
      card->kunden_nr = (uint32_t)userID;
      card->card_nr = (uint32_t)cardID;
      card->reserve_block4 = 0;
      card->reserve_block5 = 0;
    }

    return succConversion;
}






void EventHandler::tempWrite(
        const QString cardType,
        const QString recRev,
        const QString locNr,
        const QString userID,
        const QString cardID) {
  card_info tempCard;
  QVector<int> res;
  QString crcAdd, crcIBM;
  unsigned char md5CharArr[2*BLOCKSIZE_ON_CARD];
  EventHandler::convertQStringsToCard(cardType, recRev, locNr, userID, cardID, &tempCard);
  tempCard.crc16_added = Calculator::calcCRC16_added(tempCard);
  tempCard.crc16_ibm = Calculator::calcCRC16_ibm(&tempCard.card_type,
                                    INFORMATION_LENGTH_IN_BYTE);

  Calculator::calcMD5Xor(&tempCard.uid[0], md5CharArr);
  for(int iter = 0; iter < (BLOCKSIZE_ON_CARD); iter++) {
    tempCard.md5_arr[iter] = md5CharArr[iter];
  }


  Writer::writeCompleteCard(tempCard, &res);

}
/**
 * @brief This method starts the writting process.
 *
 * It converts the QStrings into integer and checks whether the given
 * QStrings can be converted to integers. If the QStrings can not be
 * converted to Integer a notification is printed. If the conversion is done
 * successful given Information about the different IDs and the amount of cards that
 * should be written are printed.
 *
 * @param[in] jobID             The QString of the current jobID
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
 *
 * @return  \link WRITTING_SUCCESSFULL \endlink iff the writting
 *                              process was seccessful
 * @todo implement the connection to the background programm
 */
int EventHandler::initWrittingProcess(
        const QString jobID,
        const QString cardType,
        const QString recRev,
        const QString locNr,
        const QString userID,
        const QString cardID,
        const QString amount,
        const bool iterate,
        QString *const consoleOutput) {

    card_info tempCard;
    bool readyToWrite, cardAmount_conv;
    int jobCreated;
    int cardAmount = amount.toInt(&cardAmount_conv, 10);
    int succWritting = 0;
    Job job;

    jobCreated = JobFile::createJob(userID,jobID, cardType,recRev,locNr,
                                    userID, cardID, amount, &job);


    // Output for converion error
    // output console

    // @todo set alarm because of the appeared error
    if( jobCreated != JOBCREATION_SUCC ) {
        readyToWrite = false;
        consoleOutput->append(QString::fromUtf8("Fehler:\n"));
        if( jobCreated <= JOBID_EMPTY ) {
            jobCreated -= JOBID_EMPTY;
            consoleOutput->append(QString::fromUtf8("  Es ist keine "
                                                    "Auftragsnummer "
                                                    "angegeben\n"));
            MainWindow::conversionErrorWindow(JOBID_EMPTY);
        }
        if( jobCreated <= LOCNR_CONVERSION_FAILED ) {
            jobCreated -= LOCNR_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Die Landeskennung kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
            MainWindow::conversionErrorWindow(LOCNR_CONVERSION_FAILED);
        }
        if( jobCreated <= RECREV_CONVERSION_FAILED ) {
            jobCreated -= RECREV_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Die Record Rev kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
            MainWindow::conversionErrorWindow(RECREV_CONVERSION_FAILED);
        }
        if( jobCreated <= CARDTYPE_CONVERSION_FAILED ) {
            jobCreated -= CARDTYPE_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Der Kartentyp kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
            MainWindow::conversionErrorWindow(CARDTYPE_CONVERSION_FAILED);
        }
        if( jobCreated <= USERID_CONVERSION_FAILED ) {
            jobCreated -= USERID_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Die Kundennummer kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
            MainWindow::conversionErrorWindow(USERID_CONVERSION_FAILED);
        }
        if( jobCreated <= CARDAMOUNT_CONVERSION_FAILED ) {
            jobCreated -= CARDAMOUNT_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Die Kundenanzahl kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
            MainWindow::conversionErrorWindow(CARDAMOUNT_CONVERSION_FAILED);
        }
        if( jobCreated <= INITCARDID_CONVERSION_FAILED ) {
            jobCreated -= INITCARDID_CONVERSION_FAILED;
            consoleOutput->append(QString::fromUtf8("  Die Kartennummer kann"
                                                    " nicht interpretiert "
                                                    "werden\n"));
            MainWindow::conversionErrorWindow(INITCARDID_CONVERSION_FAILED);
        }
        if( jobCreated < 0) {
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
        if (jobCreated == JOBCREATION_SUCC) {


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
 * @brief Writes the cards of the given jobs.
 *
 * Write the cards of the job with the help of the method
 * \link EventHandler::writeCard() \endlink. 
 *
 * @param[in] job               The description of the current job
 * @param[out] consoleOutput    A pointer where the output of for
 *                              the console will be
 *                              written in
 * @param[out] cardsLeft        A pointer where the cards left will
 *                              be written in
 * @param[out] nextCardID       A pointer where the next cardID will
 *                              be written in
 * @return
 */
int EventHandler::writeProcess(const Job job,
                               QString *const consoleOutput,
                               QString *const cardsLeft,
                               QString *const nextCardID) {


    QVector<QVector<int>> error = QVector<QVector<int>>(0);
    int iter = 0;
    int succWritting = WRITING_SUCCESSFULL;


    for(iter = 0; iter < job.cards.size(); iter++) {
        QVector<int> currError = QVector<int>(0);
        error.append(currError);

        // @todo check cast (QVector<int> *) below
        EventHandler::writeCard(job.cards.at(iter),
                                (QVector<int> *) &error.at(iter));
        // @todo kontrollesen
        
        int innerIter =0;
        int succWrite = error.at(iter).at(error.at(iter).size()-1);

        switch(succWrite) {

          case WRITING_SUCCESSFULL:
                    consoleOutput->append(QString::fromUtf8("Kunden Nummer: "));
                    consoleOutput
                      ->append(QString::number(job.cards.at(iter).kunden_nr,
                                          10));
                    consoleOutput->append(QString::fromUtf8("\n"));
                    consoleOutput->append(QString::fromUtf8("Karten Nummer: "));
                    consoleOutput->append(QString::number(job.cards.at(iter).card_nr,
                                          10));
                    consoleOutput->append(QString::fromUtf8("\n"));
                    consoleOutput->append(
                            QString::fromUtf8("Anzahl zu schreibender Karten: "));
                    consoleOutput->append(QString::number(
                            SINGLE_WRITE_PROCESS_CARD_LEFT_TO_WRITE));
                    consoleOutput->append(QString::fromUtf8("\n"));
        }
        
    }

    LogFile::writeLogFile(job.customer, job.jobID, job.cards, error);

    return succWritting;
}

/**
 * @brief Calculates the checksums with input.
 *
 * The checksums are calculated with the help of
 * \link Calculator \endlink. The calculated checksums are written in
 * 'crcAdded' and 'crcIBM'. The
 * 'crcAdded' is a byte-wise added checksum. The
 * 'crcIBM' checksum is calculated
 * with an algorithm created by IBM.
 *
 * @param[in] stringCardType    Type of the card
 * @param[in] stringRecRev      Record Rev of the card
 * @param[in] stringLocNr       Location number of the card
 * @param[in] stringUserID      User ID of the card
 * @param[in] stringCardID      Card ID of the card
 * @param[out] crcAdded         The calculated added checksum
 * @param[out] crcIBM           The calculated IBM checksum
 * @return the success or error message that is returned by \link
 *        EventHandler::convertQStringsToCard() \endlink
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

        Calculator::calcCRC16_added(tempCard.card_type,
                        tempCard.record_rev,
                        tempCard.locNr,
                        tempCard.kunden_nr,
                        tempCard.card_nr,
                        &tempCrcAdded);

        tempCrcIBM = Calculator::calcCRC16_ibm(&tempCard.card_type,
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
 * 'error'.
 *
 * @param[in] card  The \link card_info \endlink that should be written
 * @param[out] error  A QVector<int> where all error that occured while writting are
 *                    logged
 */
int EventHandler::writeCard(const card_info card,
                            QVector<int>* error) {
    // @todo impelment


  return -1;
    
}

bool EventHandler::checkCardCorrectness(const card_info card, QVector<int>* results) {

  bool correctCard = true;

  QByteArray uniqueID, md5Sum;


  for(int iter = 0; iter < 2*BLOCKSIZE_ON_CARD; iter++) {
    md5Sum.append(card.md5_arr[iter]);
  }
  

  // calculate checksums
  uint16_t crcAdd_calc, crcIBM_calc;
  crcAdd_calc = Calculator::calcCRC16_added(card);
  crcIBM_calc = Calculator::calcCRC16_ibm ((uint8_t*)(&card.card_type), 12);
  unsigned char md5Calc[2*BYTE_PER_BLOCK];
  for(int i = 0; i<2*BYTE_PER_BLOCK; i++) {
      md5Calc[i] = '-';
  }
  Calculator::calcMD5Xor((uint8_t*)(&TESTCARD.uid[0]), &md5Calc[0]);

  results->clear();
  for(int iter = 0; iter < CORRECTNESS_ERROR_AMOUNT; iter++) {
    results->append(NO_CHECKSUM_ERROR);
  }


  // check equality of the calculated checksums
  if(crcAdd_calc != card.crc16_added) {
    results->replace(CRCADD_ERROR_POS, CHECKSUM_ERROR);
    correctCard = false;
  }
  if(crcIBM_calc != card.crc16_ibm) {
    results->replace(CRCIBM_ERROR_POS, CHECKSUM_ERROR);
    correctCard = false;
  }

  QString tempString;
  for(int iter = 0; iter < 2*BYTE_PER_BLOCK; iter++) {
    QByteArray temp;
    Calculator::intToHex(card.md5_arr[iter], &temp);
    if(temp.size()%2 != 0)
      temp.insert(0, '0');
    tempString.append(temp);
  }
  if( 0 ==
      QString::compare(QString(md5Sum), tempString, Qt::CaseInsensitive)) {
    results->replace(MD5SUM_ERROR_POS, CHECKSUM_ERROR);
    correctCard = false;
  }

  std::cout << "calc md5: ";
  for(int iter = 0; (iter < tempString.size()) && (iter < BLOCKSIZE_ON_CARD); iter++) {
    std::cout << tempString.toUtf8().at(iter);
  } std::cout<< std::endl;
  std::cout << "read md5: " << md5Sum.data() << std::endl;
  Reader::printCard(card);


  if(!correctCard) {
    SystemCommands::beep(50);
  }


  return correctCard;
}
