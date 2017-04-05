//
// Created by utti on 25.03.17.
//

#include "JobFile.h"
#include "CardInformation.hpp"


QString defaultFileName("job.json");

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
            break;
    }

    return result;
}


int JobFile::findLineReadResult(QString fileName, const int searchTag,
                       QString* result) {

    QFile jobFile(fileName);
    QString temp, searchString;
    int readLength, prefixBeforeResult, suffixAfterResult;

    getInfoFromSearchTag(searchTag, &searchString, &prefixBeforeResult,
                         &suffixAfterResult, &readLength);

    int succRead = FAIL_FOUND_LINE;
    QByteArray searchArray = searchString.toLatin1();


    result->clear();

    if(jobFile.open(QIODevice::ReadOnly)){
        QTextStream in(&jobFile);
        //the first line
        temp = in.readLine();

        bool lineFound = false;
        bool endOfFile = false;
        int iter;

        // Find the line with the specific search tag
        while(!lineFound && !endOfFile) {
            temp = in.readLine();
            QByteArray readArray = temp.toLatin1();
            bool found = true;

            int maxRead = min(readLength, readArray.size());

            for(iter = 0;((iter < maxRead) && found);iter++){
                found &= (readArray.at(FIX_PREFIX_ALL_LINES + iter) ==
                            searchArray.at(iter));
            }
            lineFound = found;
            endOfFile = in.atEnd();

            // if the searched line is found write the result
            if(found && !endOfFile) {
                for(iter = 0;
                    iter < temp.size() - prefixBeforeResult -
                                   suffixAfterResult;
                    iter++) {

                    result->append(readArray.at(prefixBeforeResult+iter));
                }
                succRead = SUCC_FOUND_LINE_READ_RESULT;
            }
        }



    }
    else{
        succRead = FAIL_OPEN_FILE;
    }

    return succRead;
}

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
        rUserID = JobFile::findLineReadResult(fileName, USERID_TAG, &job->userID);
        rInitCardID = JobFile::findLineReadResult(fileName, INITCARDID_TAG,
                                          &initCardID);
        rCardAm = JobFile::findLineReadResult(fileName, CARDAMOUNT_TAG,
                                          &cardAmount);



        // check whether everything was read correctly
        response = rCust;
        if( (rJobID != SUCC_FOUND_LINE_READ_RESULT)
            && (response == SUCC_FOUND_LINE_READ_RESULT) ) {
            response = rJobID;
        }
        if( (rUserID != SUCC_FOUND_LINE_READ_RESULT)
            && (response == SUCC_FOUND_LINE_READ_RESULT)) {
            response = rUserID;
        }
        if( (rInitCardID != SUCC_FOUND_LINE_READ_RESULT)
            && (response == SUCC_FOUND_LINE_READ_RESULT)) {
            response = rInitCardID;
        }
        if( (rCardAm != SUCC_FOUND_LINE_READ_RESULT)
            && (response == SUCC_FOUND_LINE_READ_RESULT)) {
            response = rCardAm;
        }


        // in case everything was read correctly for the job file
        if(response == SUCC_FOUND_LINE_READ_RESULT) {
            int intCards = cardAmount.toInt(NULL, 10);
            // remove all cards in case there exists one
            card_info tempCard;
            for (iter = 0; iter < intCards; iter++) {
                tempCard.card_type = 0;
                tempCard.record_rev = 0;
                tempCard.locNr = 0;
                tempCard.record_rev = 0;
                tempCard.kunden_nr = (uint32_t) userID.toInt(NULL, 10);
                tempCard.card_nr = (uint32_t) (initCardID.toInt(NULL, 10) +
                                               iter);
                int crcAdd;
                calcCRC16_added(tempCard, &crcAdd);
                tempCard.crc16_ibm = calcCRC16_ibm(&tempCard.card_type,
                                                   INFORMATION_LENGTH_IN_BYTE);
                job->cards.append(tempCard);
            }

        }


    } else {
        response = FAIL_OPEN_FILE;
    }

    return response;
}


int JobFile::readJobFile(Job* job) {
    JobFile::readJobFile(defaultFileName, job);
}



/**
 * Writes a jobfile in the given filename.
 * @param fileName
 * @param job
 * @return
 */
int JobFile::createJobFile(const QString fileName, const Job job) {
    //@todo impelment
    return 0;
}
