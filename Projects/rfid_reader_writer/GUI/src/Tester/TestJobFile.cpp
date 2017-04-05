//
// Created by utti on 25.03.17.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE jobfileTest
#include <boost/test/unit_test.hpp>
#include <qt5/QtCore/QByteArray>
#include <QString>
#include "../JobFile.h"
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

        int iter;
        QByteArray tempArray = customer.toLatin1();
        int length = min(tempArray.size(), correctNameSize);
        for( iter = 0; iter < length; iter++) {
            if(correctName[iter] != tempArray.at(iter)) {
                customerName = false;
            }
        }

        BOOST_CHECK((customerName) && (read == SUCC_FOUND_LINE_READ_RESULT));
    }

    BOOST_AUTO_TEST_CASE(readCustomerName) {
        bool customerName;
        customerName = true;

        Job job;

        JobFile::readJobFile(QString("jobReadTest.json"),&job);


        char correctName[4] = {'l', 'u', 'l', 'z'};

        int iter;
        QByteArray tempArray = job.customer.toLatin1();
        for( iter = 0; iter < tempArray.size(); iter++) {
            if(correctName[iter] != tempArray.at(iter))
                customerName = false;
        }

        BOOST_CHECK(customerName);
    }

    BOOST_AUTO_TEST_CASE( readJobID ) {

        bool jobID = true;
        Job job;

        int r = JobFile::readJobFile(QString("jobReadTest.json"),&job);

        const int correctJobIDLength = 3;
        char correctJobID[correctJobIDLength] = {'1', '2', '3'};

        int iter;
        QByteArray tempArray = job.jobID.toLatin1();
        if(correctJobIDLength != tempArray.size()) {
            std::cout << tempArray.size() << std::endl;
            jobID = false;
        }
        for( iter = 0; iter < tempArray.size(); iter++) {
            if(correctJobID[iter] != tempArray.at(iter)) {
                jobID = false;
            }
        }


        BOOST_CHECK(jobID);
    }

    BOOST_AUTO_TEST_CASE( readUserID ) {

        bool succRead;
        Job job;

        int r =JobFile::readJobFile(QString("jobReadTest.json"),&job);

        const int correctUserID = 3;

        succRead = (correctUserID == job.userID.toInt(NULL,10));

        BOOST_CHECK( succRead );
    }

    BOOST_AUTO_TEST_CASE( readInitCardID ) {
        bool succRead;
        Job job;

        int r = JobFile::readJobFile(QString("jobReadTest.json"), &job);

        const int correctInitCardID = 5000;

        if( job.cards.size() > 0) {
            succRead = (correctInitCardID == job.cards.at(0).card_nr);
        }
        else
            succRead = false;

        BOOST_CHECK( succRead );
      }

    BOOST_AUTO_TEST_CASE( readCardAmount ) {
        Job job;

        int r = JobFile::readJobFile(QString("jobReadTest.json"), &job);
        const int correctCardAmount = 40;


        BOOST_CHECK( correctCardAmount == job.cards.size());
    }
BOOST_AUTO_TEST_SUITE_END();