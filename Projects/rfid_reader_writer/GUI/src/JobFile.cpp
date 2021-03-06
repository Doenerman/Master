//
// Created by utti on 25.03.17.
//

#include "JobFile.h"
#include "CardInformation.hpp"
#include "Tester/TestCards.h"


QString defaultFileName("job.json");
/**
 * Interprets the given search tag and writes the necessary information in
 * the given parameter.
 *
 * First of all the given QString is cleared. Second the search tag is
 * checked. In case there is no predefined search tag that fits to the given
 * one the return value of this function is \link UNKNOWN_SEARCH_TAG \endlink
 * . In case the given search tag is predefined the parameter are set
 * respectively. If the search tag is not predefined the integer
 * output parameter are set to '0' and the QString output parameter is cleared
 * . A list of predefined search tags is given in \link JobFile.h \endlink .
 *
 * @param[in] searchTag              The search tag
 * @param[out] string                The word that represents the search tag in
 *                                   the jobfile.
 * @param[out] prefixBeforeResult    The amount of characters that are before
 *                                   the result corresponding to the search tag.
 * @param[out] suffixAfterResult     the amount of characters that is after
 *                                   the result corresponding to the search tag.
 * @param[out] lengthOfTagWord       The length of the word that represents the
 *                                   search tag in the jobfile. For the search
 *                                   tag \link CUSTOMER_TAG \endlink the value
 *                                   would be '5' because the word 'Kunde',
 *                                   which is written in the jobfile, has a
 *                                   length of 5.
 * @return  The value is either \link CORRECT_SEARCH_TAG \endlink in case the
 *          given search tag has one of the following values
 *              - \link CUSTOMER_TAG \endlink
 *              - \link JOBID_TAG \endlink
 *              - \link USERID_TAG \endlink
 *              - \link INITCARDID_TAG \endlink
 *              - \link CARDAMOUNT_TAG \endlink
 *          or it is
 *          \link UNKNOWN_SEARCH_TAG \endlink. In case the value is
 *          \link UNKNOWN_SEARCH_TAG \endlink the integer output parameter are
 *          set to '0' and the QString output parameter is cleared.
 */
int getInfoFromSearchTag(const int searchTag, QString* string,
                         int* prefixBeforeResult,
                         int* suffixAfterResult,
                         int* lengthOfTagWord) {
    int result = CORRECT_SEARCH_TAG;
    string->clear();
    switch(searchTag) {
        case CUSTOMER_TAG:
            string->append("Kunde");
            *prefixBeforeResult = FIX_PREFIX_CUSTOMER;
            *suffixAfterResult = FIX_SUFFIX_CUSTOMER;
            *lengthOfTagWord = CUSTOMER_TAG_WORD_LENGTH;
            break;
        case JOBID_TAG:
            string->append("JobID");
            *prefixBeforeResult = FIX_PREFIX_JOBID;
            *suffixAfterResult = FIX_SUFFIX_JOBID;
            *lengthOfTagWord = JOBID_TAG_WORD_LENGTH;
            break;
        case USERID_TAG:
            string->append("Kundennummer");
            *prefixBeforeResult = FIX_PREFIX_USERID;
            *suffixAfterResult = FIX_SUFFIX_USERID;
            *lengthOfTagWord = USERID_TAG_WORD_LENGTH;
            break;
        case INITCARDID_TAG:
            string->append("Initiale Kartennummer");
            *prefixBeforeResult = FIX_PREFIX_INITCARDID;
            *suffixAfterResult = FIX_SUFFIX_INITCARDID;
            *lengthOfTagWord = INITCARDID_TAG_LENGTH;
            break;
        case CARDAMOUNT_TAG:
            string->append("Kartenanzahl");
            *prefixBeforeResult = FIX_PREFIX_CARDAMOUNT;
            *suffixAfterResult = FIX_SUFFIX_CARDAMOUNT;
            *lengthOfTagWord = CARDAMOUNT_TAG_WORD_LENGTH;
            break;
        default:
            result = UNKNOWN_SEARCH_TAG;
            *prefixBeforeResult = 0;
            *suffixAfterResult = 0;
            *lengthOfTagWord = 0;
            break;
    }

    return result;
}

/**
 * @brief Reads the result of the search for the search tag and writes it in the
 *        QString. The return value indicates the success of the search.
 *
 * This method uses the function \link getInfoFromSearchTag \endlink to
 * gather necessary information about the search. If \link
 * getInfoFromSearchTag \endlink returns an error value this method returns the
 * same error value. If the information was gather successful this methods
 * tries toread from the named file. If this is not possible this method returns
 * \link FAIL_OPEN_FILE \endlink. In case the file can be read the method reads
 * line by line and looks for the phrase that represents the search tag. If
 * there is no line that fit the search tag the value \link FAIL_FOUND_LINE
 * \endlink is returned.
 *
 * @param[in] fileName  The name of the file in which the line specified by
 *                      the search tag should be found and the corresponding
 *                      result be read.
 * @param[in] searchTag A predefined search tag. A list of the predefined
 *                      search tags is given in \link JobFile.h \endlink
 * @param[out] result   In case the search was successful the result is
 *                      written in this QString. A result for \link
 *                      INITCARDID_TAG \endlink could be '4' which means the
 *                      initial card id would be '4'
 * @return  The value depends on the given search tag and the given filename.
 *          In case the search tag is not one of the predefined of \link
 *          getInfoFromSearchTag \endlink this method returns the value
 *          from \link getInfoFromSearchTag \endlink . In case the search tag
 *          is predefined in \link getInfoFromSearchTag \endlink the return
 *          value is either \link FAIL_OPEN_FILE \endlink in case the file
 *          could not be read, \link FAIL_FOUND_LINE \endlink in case the
 *          line corresponding to the search tag was not found, \link
 *          FAIL_READ_RESULT \endlink in case the result of the corresponding
 *          search tag is too short or \link SUCC_FOUND_LINE_READ_RESULT
 *          \endlink if the line was found and the result was read.
 */
int JobFile::findLineReadResult(QString fileName, const int searchTag,
                       QString* result) {

    QFile jobFile(fileName);
    QString temp, searchString;
    int succRead, readLength, prefixBeforeResult, suffixAfterResult;

    succRead = getInfoFromSearchTag(searchTag, &searchString,
                                   &prefixBeforeResult,
                         &suffixAfterResult, &readLength);



    QByteArray searchArray = searchString.toLatin1();

    result->clear();

    // can the file be read and is the given search tag correct?
    if((jobFile.open(QIODevice::ReadOnly)) && (succRead == CORRECT_SEARCH_TAG)){
        // line not found yet
        succRead = FAIL_FOUND_LINE;
        QTextStream in(&jobFile);
        //the first line
        temp = in.readLine();

        bool lineFound = false;
        bool endOfFile = false;
        int iter;

        // read each line successivly and check if this line fits the search tag
        while(!lineFound && !endOfFile) {
            temp = in.readLine();
            QByteArray readArray = temp.toLatin1();
            bool found = true;

            int maxRead = min(readLength, readArray.size());

            // read the word the represents the search tag
            // the word for JOBID_TAG would be 'JobID'
            for(iter = 0;((iter < maxRead) && found);iter++){
                found &= (readArray.at(FIX_PREFIX_ALL_LINES + iter) ==
                            searchArray.at(iter));
            }
            lineFound = found;
            endOfFile = in.atEnd();

            // if the searched line is found write the result
            if(found && !endOfFile) {
                // does the 'result' in the jobfile has a length of 0
                // -> this means that the 'result' does not exist
                if(temp.size() - prefixBeforeResult - suffixAfterResult == 0) {
                    succRead = FAIL_READ_RESULT;
                }
                // the 'result' has a length of at least 1
                // read the result and write it into result
                else {
                    for (iter = 0;
                         iter < temp.size() - prefixBeforeResult -
                                suffixAfterResult;
                         iter++) {
                        result->append(readArray.at(prefixBeforeResult + iter));
                    }
                    succRead = SUCC_FOUND_LINE_READ_RESULT;
                }
            }
        }
        jobFile.close();

    }
    else{
        succRead = FAIL_OPEN_FILE;
    }

    return succRead;
}

/**
 * @brief Reads the jobfile with the given input name. It is read correctly the job
 *        described by the named file is written in the given job.
 *
 * This file tries to open the named jobfile and search in the file for
 *  - \link CUSTOMER_TAG \endlink
 *  - \link JOBID_TAG \endlink
 *  - \link USERID_TAG \endlink
 *  - \link INITCARDID_TAG \endlink
 *  - \link CARDAMOUNT_TAG \endlink
 *
 * and reads the corresponding result. In case the file can not be opened
 * this method returns the value \link FAIL_OPEN_FILE \endlink.
 * The search is done by the method \link JobFile::findLineReadResult
 * \endlink. In case that at least on of the
 * reading tries failed the return value of this method mentions the first
 * one that failed. If every search of the above tags was successful the job
 * that the jobfile represents is written in the given paratmeter.
 *
 * @param[in] fileName  The name of the file that contains the job
 * @param[out] job      A job where the information of the jobfile are written in
 * @return  In case the job was created successful the return value of this
 *          method is \link SUCC_FOUND_LINE_READ_RESULT \endlink which means
 *          that all necessary information about the job were read from the
 *          given jobfile. All other return values are forwarded for the method
 *          \link JobFile::findLineReadResult() \endlink.
 */
int JobFile::readJobFile(QString fileName, Job *job) {

    QString temp;
    QString userID = QString();
    QString initCardID = QString();
    QString cardAmount = QString();
    QByteArray tempArray;
    QFile jobFile(fileName);
    int response = 0;
    int iter;



    if(jobFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&jobFile);
        temp = in.readLine();
        int rCust, rJobID, rUserID, rInitCardID, rCardAm;

        // Read Customer
        rCust = JobFile::findLineReadResult(fileName, CUSTOMER_TAG,
                                         &job->customer);
        rJobID = JobFile::findLineReadResult(fileName, JOBID_TAG,
                                               &job->jobID);
        rUserID = JobFile::findLineReadResult(fileName, USERID_TAG, &userID);
        rInitCardID = JobFile::findLineReadResult(fileName, INITCARDID_TAG,
                                          &initCardID);
        rCardAm = JobFile::findLineReadResult(fileName, CARDAMOUNT_TAG,
                                          &cardAmount);



        // check whether everything was read correctly
        response = rCust;
        if( response == SUCC_FOUND_LINE_READ_RESULT ) {
            response = rJobID;
        }
        if( response == SUCC_FOUND_LINE_READ_RESULT) {
            response = rUserID;
        }
        if( response == SUCC_FOUND_LINE_READ_RESULT) {
            response = rInitCardID;
        }
        if( response == SUCC_FOUND_LINE_READ_RESULT) {
            response = rCardAm;
        }



        // in case everything was read correctly for the job file
        if(response == SUCC_FOUND_LINE_READ_RESULT) {
            int intAmountCards = cardAmount.toInt(NULL, 10);
            // remove all cards in case there exists one
            card_info tempCard;
            if( intAmountCards > 0) {
                for (iter = 0; iter < intAmountCards; iter++) {
                    tempCard.card_type = 0;
                    tempCard.record_rev = 0;
                    tempCard.locNr = 0;
                    tempCard.record_rev = 0;
                    tempCard.kunden_nr = (uint32_t) userID.toInt(NULL, 10);
                    tempCard.card_nr = (uint32_t) (initCardID.toInt(NULL, 10) +
                                                   iter);
                    int crcAdd;
                    Calculator::calcCRC16_added(tempCard, &crcAdd);
                    tempCard.crc16_ibm = Calculator::calcCRC16_ibm(&tempCard
                                                                          .card_type,
                                                       INFORMATION_LENGTH_IN_BYTE);
                    job->cards.append(tempCard);
                }
            }
            else {
                response = INVALID_JOB_NO_CARDS;
            }
        }
        jobFile.close();
    }
    else {
        response = FAIL_OPEN_FILE;
    }

    return response;
}

/**
 * @brief Reads the default jobfile. Is it read correctly the job is written in the
 *        given input.
 *
 * Calls the method \link JobFile::readJobFile(QString, Job*) \endlink with
 * the default jobfile name \link defaultFileName \endlink
 *
 * @param job       A job where the information of the jobfile are written in
 * @return  Forwards the value of the call
 *          \link JobFile::readJobFile(QString, Job*) \endlink
 */
int JobFile::readJobFile(Job* job) {
    return JobFile::readJobFile(defaultFileName, job);
}

/**
 * @brief Writes the given job information in the given \link Job \endlink
 *
 * The method interprets the given information and write them respectively in
 * the given job. If the given information can be converted into the
 * corresponding data type the return value of this method is 
 * \link JOBCREATION_SUCC \endlink . In case the return value is not 
 * \link JOBCREATION_SUCC \endlink it is the sum of all conversion that failed.
 * So if the given card type and the given locNr could not be converted to an
 * integer the return value would be \link CARDTYPE_CONVERSION_FAILED \endlink
 * plus \link LOCNR_CONVERSION_FAILED \endlink. Because each conversion error that
 * could happen during this method has pairwise different amounts of zeros after
 * the first non-zero digit, the return value of the method contains all failed
 * conversion.
 *
 * @param[in] customer  A QString that is handle as the customer name.
 * @param[in] jobID     A QSTRING that is handle as the jobID. This does not
 *                      necessarily have to be a sequence of numbers.
 * @param[in] cardType  A QString that will be converted to an integer and will
 *                      be the card type of all cards this job contains.
 * @param[in] recRev    A QString that will be converted to an integer and will
 *                      be the record Rev of all cards this job contains.
 * @param[in] locNr     A QString that will be converted to an integer and will
 *                      be the location number of all cards this job contains.
 * @param[in] userID    A QString that will be coverted to an integer and will
 *                      the user id of all cards this job contains.
 * @param[in] initCardID  A QString that will be converted to an integer and
 *                        will be card id of the first card this job contains.
 *                        The following cards are increasing by one for each new
 *                        card.
 * @param[in] cardAmount  A QString that will be converted to an integer and
 *                        sets the amount of cards that this job contains.
 *
 * @param[out] job      The job that all of the above information are stored in.
 *
 * @return    In case all conversion were done successfully this method returns 
 *            \link JOBCREATION_SUCC \endlink otherwise it is the sum of the
 *            failed conversions.
 */
int JobFile::createJob(const QString customer, const QString jobID,
                       const QString cardType,
                       const QString recRev, const QString locNr,
                       const QString userID, const QString initCardID,
                       const QString cardAmount, Job *job) {
    int succConversion, cardType_int, locNr_int, recRev_int, initCardID_int,
            cardAmount_int, userID_int;
    bool convCardType, convLocNr, convRecRev, convInitID, convCardAm,
            convUserID;

    succConversion = NO_CONVERSION_ERROR_YET;
    cardType_int = cardType.toInt(&convCardType, 10);
    locNr_int = locNr.toInt(&convLocNr, 10);
    recRev_int = recRev.toInt(&convRecRev,10);
    initCardID_int = initCardID.toInt(&convInitID, 10);
    cardAmount_int = cardAmount.toInt(&convCardAm, 10);
    userID_int = userID.toInt(&convUserID, 10);

    // check if the conversion from qstring to integer was successful
    if( !convUserID ) {
        succConversion += USERID_CONVERSION_FAILED;
    }
    if( !convCardAm ) {
        succConversion += CARDAMOUNT_CONVERSION_FAILED;
    }
    if( !convInitID ) {
        succConversion += INITCARDID_CONVERSION_FAILED;
    }
    if( !convCardType ) {
        succConversion += CARDTYPE_CONVERSION_FAILED;
    }
    if( !convRecRev ) {
        succConversion += RECREV_CONVERSION_FAILED;
    }
    if( !convLocNr ) {
        succConversion += LOCNR_CONVERSION_FAILED;
    }
    if( jobID.isEmpty() ) {
        succConversion += JOBID_EMPTY;
    }

    // all conversion checks passed and no error appeared
    if( succConversion == NO_CONVERSION_ERROR_YET ) {
        succConversion = CONVERSION_SUCC;
    }


    if(succConversion == CONVERSION_SUCC) {
        if(cardAmount_int > 0) {
            int iter;
            job->customer = customer;
            job->jobID = jobID;

            for(iter = 0; iter < cardAmount_int; iter++) {
                card_info tempCard;
                // block 0
                tempCard.card_type = (uint8_t) cardType_int;
                tempCard.record_rev = (uint8_t) recRev_int;
                tempCard.locNr = (uint8_t) locNr_int;
                tempCard.reserved_block0 = 0;
                //block 1
                tempCard.kunden_nr = (uint32_t) userID_int;
                //block 2
                tempCard.card_nr = (uint32_t) initCardID_int +  iter;
                //block 3
                tempCard.crc16_added =
                        (uint16_t) Calculator::calcCRC16_added(tempCard);
                tempCard.crc16_ibm =
                        Calculator::calcCRC16_ibm(&(tempCard.card_type),
                                                   12);
                tempCard.reserve_block4 = 0;
                tempCard.reserve_block5 = 0;
                job->cards.append(tempCard);
            }
            succConversion = JOBCREATION_SUCC;
        }
        else {
            succConversion = INVALID_JOB_NO_CARDS;
        }
    }


    return succConversion;
}


/**
 * @brief Writes the given job in a file.
 *
 * This method writes the given job in a file such that the method 
 * \link JobFile::readJobFile \endlink is able to recreate the given job.
 * It is not defined what the job file looks in case the already exists a file
 * with the same name.
 *
 * @param fileName  A QString of the file name. It is expected to be an file of
 *                  the type '.json'.
 * @param job       The job that should be written in a file.
 * @return          One of the following values:
 *                  - \link INVALID_JOB_NO_CARDS \endlink if the given job does
 *                    not contain any cards
 *                  - \link FAIL_OPEN_FILE \endlink if the method was not able
 *                    to write the file
 *                  - \link JOBFILE_WRITTEN \endlink if no of the above error
 *                    appeared
 */
int JobFile::createJobFile(const QString fileName, const Job job) {
    //@todo impelment

    QFile jobFile(fileName);
    int succ;

    if(job.cards.size() > 0) {
        if (jobFile.open(QIODevice::WriteOnly)) {
            QTextStream out(&jobFile);

            if (job.cards.size() > 0) {

                const char brackOpen = 0x7b;
                const char brackClose = 0x7d;
                const char sep = 0x22;

                // |{
                out << brackOpen << endl;
                // |    "Kunde": "'customername'",
                out << "    " << sep << "Kunde" << sep << ": "
                    << sep << job.customer.toLatin1().data() << sep << ","
                    << endl;
                // |    "JobID": "'jobid'",
                out << "    " << sep << "JobID" << sep << ": "
                    << sep << job.jobID.toLatin1().data() << sep << "," << endl;
                // |    "Kundennummer": "'userid'",
                out << "    " << sep << "Kundennummer" << sep << ": "
                    << sep << job.cards.at(0).kunden_nr << sep << "," << endl;
                // |    "Initiale Kartennummer": "'initcardid'",
                out << "    " << sep << "Initiale Kartennummer" << sep << ": "
                    << sep << job.cards.at(0).kunden_nr << sep << "," << endl;
                // |    "Kartenanzahl": "'cardamount'"
                out << "    " << sep << "Kartenanzahl" << sep << ": "
                    << sep << job.cards.size() << sep << endl;
                // |}
                out << brackClose << endl;
            }

            jobFile.close();
            succ = JOBFILE_WRITTEN;
        } else {
            succ = FAIL_OPEN_FILE;
        }
    }
    else {
        succ = INVALID_JOB_NO_CARDS;
    }

    return succ;
}
