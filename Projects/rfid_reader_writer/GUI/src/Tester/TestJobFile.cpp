//
// Created by utti on 25.03.17.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE jobfileTest
#include <boost/test/unit_test.hpp>
#include <qt5/QtCore/QByteArray>
#include <QString>
#include "../JobFile.h"
#include "TestCards.h"
#include "../CardInformation.hpp"

BOOST_AUTO_TEST_SUITE( jobFileTest )

    BOOST_AUTO_TEST_CASE(findLineReadResult) {
        bool customerName = true;

        QString customer;

        int read = JobFile::findLineReadResult(
                                    QString("jobReadTest.json"),
                                    CUSTOMER_TAG, &customer);


        const char correctNameSize = 4;
        char correctName[correctNameSize] = {'l', 'u', 'l', 'z'};

        if( read == SUCC_FOUND_LINE_READ_RESULT ) {
            int iter;
            QByteArray tempArray = customer.toLatin1();
            int length = min(tempArray.size(), correctNameSize);
            for (iter = 0; iter < length; iter++) {
                if (correctName[iter] != tempArray.at(iter)) {
                    customerName = false;
                }
            }
        }
        else{
            customerName = false;
        }

        BOOST_CHECK((customerName) && (read == SUCC_FOUND_LINE_READ_RESULT));
    }

    BOOST_AUTO_TEST_CASE(readCustomerName) {
        bool customerName;
        customerName = true;
        int iter, r;

        Job job;

        r = JobFile::readJobFile(QString("jobReadTest.json"),&job);


        char correctName[4] = {'l', 'u', 'l', 'z'};

        if( r == SUCC_FOUND_LINE_READ_RESULT ) {
            QByteArray tempArray = job.customer.toLatin1();
            for (iter = 0; iter < tempArray.size(); iter++) {
                if (correctName[iter] != tempArray.at(iter))
                    customerName = false;
            }
        }
        else {
            customerName = false;
        }

        BOOST_CHECK(customerName);
    }
    BOOST_AUTO_TEST_CASE(readCustomerName_defaultFile) {
        bool customerName;
        int iter, r;
        customerName = true;

        Job job;

        r = JobFile::readJobFile(&job);


        char correctName[4] = {'l', 'u', 'l', 'z'};
        if( r == SUCC_FOUND_LINE_READ_RESULT ) {
            QByteArray tempArray = job.customer.toLatin1();
            for (iter = 0; iter < tempArray.size(); iter++) {
                if (correctName[iter] != tempArray.at(iter))
                    customerName = false;
            }
        }
        else {
            customerName = false;
        }

        BOOST_CHECK(customerName);
    }

    BOOST_AUTO_TEST_CASE( readJobID ) {

        bool jobID = true;
        Job job;
        int iter, r;

        r = JobFile::readJobFile(QString("jobReadTest.json"),&job);

        if(r == SUCC_FOUND_LINE_READ_RESULT ) {
            const int correctJobIDLength = 3;
            char correctJobID[correctJobIDLength] = {'1', '2', '3'};

            QByteArray tempArray = job.jobID.toLatin1();
            if (correctJobIDLength != tempArray.size()) {
                std::cout << tempArray.size() << std::endl;
                jobID = false;
            }
            for (iter = 0; iter < tempArray.size(); iter++) {
                if (correctJobID[iter] != tempArray.at(iter)) {
                    jobID = false;
                }
            }
        }
        else{
            jobID = false;
        }


        BOOST_CHECK(jobID);
    }
    BOOST_AUTO_TEST_CASE( readJobID_defaultFile ) {

        bool jobID = true;
        Job job;

        int r = JobFile::readJobFile(&job);

        const int correctJobIDLength = 3;
        char correctJobID[correctJobIDLength] = {'1', '2', '3'};

        if( r == SUCC_FOUND_LINE_READ_RESULT ) {
            int iter;
            QByteArray tempArray = job.jobID.toLatin1();
            if (correctJobIDLength != tempArray.size()) {
                std::cout << tempArray.size() << std::endl;
                jobID = false;
            }
            for (iter = 0; iter < tempArray.size(); iter++) {
                if (correctJobID[iter] != tempArray.at(iter)) {
                    jobID = false;
                }
            }
        }
        else {
            jobID = false;
        }


        BOOST_CHECK(jobID);
    }

    BOOST_AUTO_TEST_CASE( readUserID ) {

        bool succRead;
        Job job;
        int r;
        const int correctUserID = 3;

        r = JobFile::readJobFile(QString("jobReadTest.json"),&job);


        if( r == SUCC_FOUND_LINE_READ_RESULT ) {
            succRead = (correctUserID == job.cards.at(0).kunden_nr);
        }
        else {
            succRead = false;
        }

        BOOST_CHECK( succRead );
    }
    BOOST_AUTO_TEST_CASE( readUserID_defaultFile ) {

        bool succRead;
        Job job;
        int r;
        const int correctUserID = 3;

        r =JobFile::readJobFile(&job);

        if( r == SUCC_FOUND_LINE_READ_RESULT ) {
            succRead = (correctUserID == job.cards.at(0).kunden_nr);
        }
        else {
            std::cout << "readUserID_defaultFile r:" << r << std::endl;
            succRead = false;
        }

        BOOST_CHECK( succRead );
    }

    BOOST_AUTO_TEST_CASE( readInitCardID_defaultFile ) {
        bool succRead;
        Job job;

        int r = JobFile::readJobFile(&job);

        const int correctInitCardID = 5000;

        if( r == SUCC_FOUND_LINE_READ_RESULT ) {
            succRead = (correctInitCardID == job.cards.at(0).card_nr);
        }
        else {
            succRead = false;
        }

        BOOST_CHECK( succRead );
      }

    BOOST_AUTO_TEST_CASE( readCardAmount ) {
        bool cardAmount;
        Job job;

        int r = JobFile::readJobFile(QString("jobReadTest.json"), &job);
        const int correctCardAmount = 40;

        if( r == SUCC_FOUND_LINE_READ_RESULT ) {
            cardAmount = (correctCardAmount == job.cards.size());
        }
        else {
            cardAmount = false;
        }

        BOOST_CHECK( cardAmount);
    }
    BOOST_AUTO_TEST_CASE( readCardAmount_defaultFile ) {
        bool cardAmount;
        Job job;

        int r = JobFile::readJobFile(&job);
        const int correctCardAmount = 40;

        if( r == SUCC_FOUND_LINE_READ_RESULT ) {
            cardAmount = (correctCardAmount == job.cards.size());
        }
        else{
            cardAmount = false;
        }

        BOOST_CHECK( cardAmount );
    }

    BOOST_AUTO_TEST_CASE( createJob ) {
        bool succ;
        QString customer, jobID, cardType, recRev, locrNr, userID, initCardID,
                cardAmount;
        Job job;
        int iter, r;
        QVector<card_info> cards;


        const int userID_int = card4.kunden_nr;
        const int initCardID_int = card4.card_nr;
        const int cardAmount_int = 2;

        cards.clear();
        cards.append(card4);
        cards.append(card5);


        customer = QString("testname");
        jobID = QString("123b13x");

        cardType = QString::number(DEFAULT_CARDTYPE,10);
        recRev = QString::number(DEFAULT_RECORDREV,10);
        locrNr = QString::number(DEFAULT_LOCNR,10);
        userID = QString::number(userID_int,10);
        initCardID = QString::number(initCardID_int, 10);
        cardAmount = QString::number(cardAmount_int,10);

        r = JobFile::createJob(customer, jobID, cardType, recRev, locrNr,
                               userID, initCardID, cardAmount, &job);


        if( r == JOBCREATION_SUCC ) {
            succ = true;
            QByteArray cArr, rArr;
            cArr = customer.toLatin1();
            rArr = job.customer.toLatin1();
            if(cArr.size() == rArr.size()) {
                for (iter = 0; ((iter < cArr.size()) && succ) ; iter++) {
                    succ &= (cArr.at(iter) == rArr.at(iter));
                }
            }
            else{
                succ = false;
            }
            cArr = jobID.toLatin1();
            rArr = job.jobID.toLatin1();
            if(cArr.size() == rArr.size()) {
                for (iter = 0; ((iter < cArr.size()) && succ) ; iter++) {
                    succ &= (cArr.at(iter) == rArr.at(iter));
                }
            }
            else{
                succ = false;
            }
            int outer;
            if(job.cards.size() == cards.size()) {
                for (outer = 0; (outer < cards.size()) && succ; outer++) {
                    succ &= (job.cards.at(outer).card_type
                             == cards.at(outer).card_type);
                    succ &= (job.cards.at(outer).record_rev
                             == cards.at(outer).record_rev);
                    succ &= (job.cards.at(outer).locNr
                             == cards.at(outer).locNr);
                    succ &= (job.cards.at(outer).kunden_nr
                             == cards.at(outer).kunden_nr);
                    succ &= (job.cards.at(outer).card_nr
                             == cards.at(outer).card_nr);
                    succ &= (job.cards.at(outer).crc16_added
                             == cards.at(outer).crc16_added);
                    succ &= (job.cards.at(outer).crc16_ibm
                             == cards.at(outer).crc16_ibm);
                }
            }
            else {
                succ = false;
            }

        }
        else {
            succ = false;
        }

        BOOST_CHECK(succ);
    }
    BOOST_AUTO_TEST_CASE( createJobFile ) {
        bool correctWritten;
        QByteArray cJobArr, rJobArr;
        QString customer, jobID, cardType, recRev, locNr, userID, initCardID,
                cardAmount;
        Job job, rJob;
        int iter, r;
        const QString fileName = QString("createdJobFile.json");
        const int userID_int = 1234;
        const int initCardID_int = 4321;
        const int cardAmount_int = 50;

        correctWritten = true;

        customer = QString("testCustomer");
        jobID = QString("axb120");
        cardType = QString::number(DEFAULT_CARDTYPE,10);
        recRev = QString::number(DEFAULT_RECORDREV,10);
        locNr = QString::number(DEFAULT_LOCNR,10);
        userID = QString::number(userID_int,10);
        initCardID = QString::number(initCardID_int,10);
        cardAmount = QString::number(cardAmount_int,10);

        r = JobFile::createJob(customer,jobID, cardType, recRev, locNr,
                               userID, initCardID, cardAmount, &job);


        if( r == JOBCREATION_SUCC ) {
            r = JobFile::createJobFile(fileName, job);
            if( r == JOBFILE_WRITTEN) {
                r = JobFile::readJobFile(fileName, &rJob);
                if( r == SUCC_FOUND_LINE_READ_RESULT ) {

                    // Check the customer of the read and the written job
                    cJobArr = job.customer.toLatin1();
                    rJobArr = rJob.customer.toLatin1();
                    if (cJobArr.size() != rJobArr.size()) {
                        correctWritten = false;
                    }
                    for (iter = 0;
                         (iter < cJobArr.size()) && correctWritten; iter++) {
                        correctWritten &= (cJobArr.at(iter) ==
                                           rJobArr.at(iter));
                    }

                    // Check the job id of the read and the written job
                    cJobArr = job.jobID.toLatin1();
                    rJobArr = rJob.jobID.toLatin1();
                    if (cJobArr.size() != rJobArr.size()) {
                        correctWritten = false;
                    }
                    for (iter = 0;
                         (iter < cJobArr.size()) && correctWritten; iter++) {
                        correctWritten &= (cJobArr.at(iter) ==
                                           rJobArr.at(iter));
                    }
                    // Check the user id of the read and the written job
                    correctWritten &= (job.cards.at(0).kunden_nr
                                       == rJob.cards.at(0).kunden_nr);
                    for (iter = 0;
                         (iter < cJobArr.size()) && correctWritten; iter++) {
                        correctWritten &= (cJobArr.at(iter) ==
                                           rJobArr.at(iter));
                    }
                }
            }
            else {
                correctWritten = false;
            }

        }

        BOOST_CHECK( correctWritten);
    }
BOOST_AUTO_TEST_SUITE_END();