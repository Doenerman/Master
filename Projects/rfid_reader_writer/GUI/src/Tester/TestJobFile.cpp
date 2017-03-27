//
// Created by utti on 25.03.17.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE jobfileTest
#include <boost/test/unit_test.hpp>
#include <qt5/QtCore/QByteArray>
#include <QString>
#include "../JobFile.h"

BOOST_AUTO_TEST_SUITE( jobFileTest )

    BOOST_AUTO_TEST_CASE(readCustomerName) {
        bool customerName;
        customerName = true;

        Job job;

        JobFile::readJobFile(QString("jobCustomerTest.json"),&job);


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

        JobFile::readJobFile(QString("jobJobIDTest.json"),&job);


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

        JobFile::readJobFile(QString("jobUserIDTest.json"),&job);


        const int correctUserID = 3;

        if(job.cards.size() > 0 )
            succRead = (correctUserID == job.cards.at(0).kunden_nr);
        else
            succRead = false;


        BOOST_CHECK( succRead );
    }

    BOOST_AUTO_TEST_CASE( readInitCardID ) {
        bool succRead;
        Job job;

        JobFile::readJobFile(QString("jobInitCardIDTest.json"), &job);

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

        JobFile::readJobFile(QString("jobCardAmountTest.json"), &job);

        const int correctCardAmount = 40;


        BOOST_CHECK( correctCardAmount == job.cards.size());
    }
BOOST_AUTO_TEST_SUITE_END();