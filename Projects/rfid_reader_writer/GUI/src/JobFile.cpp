//
// Created by utti on 25.03.17.
//

#include "JobFile.h"
#include "CardInformation.hpp"


QString defaultFileName("job.json");



int JobFile::readJobFile(QString fileName, Job *job) {

    QString temp;
    QString customer = QString();
    QString jobID = QString();
    QString userID = QString();
    QString initCardID = QString();
    QString cardAmount = QString();
    QByteArray tempArray;
    QFile jobFile(fileName);
    int tempFirstInfo;
    int iter;



    if(jobFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&jobFile);
        temp = in.readLine();

        // Read Customer
        temp = in.readLine();
        tempFirstInfo = FIX_PREFIX_CUSTOMER -1;
        QByteArray tempArray = temp.toLatin1();
        for(iter = 0; iter < (temp.size() - FIX_LENGTH_CUSTOMER); iter++){
            customer.insert(customer.size(),tempArray.at(tempFirstInfo+iter));
        }


        // Read JobID
        temp.clear();
        temp = in.readLine();
        tempFirstInfo = FIX_PREFIX_JOBID-1;
        for(iter = 0; iter < (temp.size() - FIX_LENGTH_JOBID); iter++){
            jobID.append(temp.at(tempFirstInfo+iter));
        }

        // Read user ID
        temp = in.readLine();
        tempFirstInfo = FIX_PREFIX_USERID -1;
        for(iter = 0; iter < (temp.size() - FIX_LENGTH_USERID); iter++){
            userID.append(temp.at(tempFirstInfo+iter));
        }

        // Read init card id
        temp = in.readLine();
        tempFirstInfo = FIX_PREFIX_INITCARDID;
        for(iter = 0; iter < (temp.size() - FIX_LENGTH_INITCARDID);
            iter++) {
            initCardID.append(temp.at(tempFirstInfo+iter));
        }

        // Read card amount
        temp = in.readLine();
        tempFirstInfo = FIX_PREFIX_CARDAMOUNT;
        for(iter = 0; iter < (temp.size() - FIX_LENGTH_CARDAMOUNT); iter++) {
            cardAmount.append(temp.at(tempFirstInfo + iter));
        }


        job->customer = customer;
        job->jobID = jobID;
        int intCards = cardAmount.toInt(NULL, 10);
        // remove all cards in case there exists one
        card_info tempCard;
        for(iter = 0; iter < intCards; iter++) {
            tempCard.card_type = 0;
            tempCard.record_rev = 0;
            tempCard.locNr = 0;
            tempCard.record_rev = 0;
            tempCard.kunden_nr = (uint32_t) userID.toInt(NULL, 10);
            tempCard.card_nr = (uint32_t) (initCardID.toInt(NULL, 10) + iter);
            int crcAdd;
            calcCRC16_added(tempCard, &crcAdd);
            tempCard.crc16_ibm = calcCRC16_ibm( &tempCard.card_type, INFORMATION_LENGTH_IN_BYTE);
            job->cards.append(tempCard);
        }

    } else {
        std::cout << "file not opened" << std::endl;
    }
}


int JobFile::readJobFile(Job* job) {
    JobFile::readJobFile(defaultFileName, job);
}
