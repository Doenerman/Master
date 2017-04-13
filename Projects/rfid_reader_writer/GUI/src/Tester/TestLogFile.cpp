//
// Created by utti on 21.03.17.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE logfileTest
#include <QString>
#include <boost/test/unit_test.hpp>
#include "../LogFile.h"
#include "TestCards.h"
#include <iostream>
#include <QByteArray>

#ifdef linux
    #define TESTUSERNAME "utti"
    #define USERNAMELENGTH 4
#endif

BOOST_AUTO_TEST_SUITE( logfileTest )
    BOOST_AUTO_TEST_CASE( getUserLogin )
    {
        QString user;
        LogFile::getUserLogin(&user);
        QByteArray userQByteArray = user.toLatin1();
        char* userChar = userQByteArray.data();
        char* handwrittenUser = (char *) TESTUSERNAME;

        bool equal = true;
        int iter;
        for(iter = 0; iter < USERNAMELENGTH; iter++ ) {
            if (userChar[iter] != handwrittenUser[iter])
                equal = false;
        }

        BOOST_CHECK( equal );
    }

    BOOST_AUTO_TEST_CASE( writeCustomer ) {
        bool equal = true;


        const int customerNameLength = 8;
        const int fixOutputLength = 14;
        const int fixSuffixLength = 2;
        const char* customerName = "testName";

        QString qstringCustomer = QString(customerName);
        QByteArray tempNameArray = qstringCustomer.toLatin1();

        char correctLine[fixOutputLength+customerNameLength];
        int iter = 0;
        for(iter = 0; iter < 4; iter++) {
            correctLine[iter] = ' ';
        }
        correctLine[4] = 0x22; correctLine[5] = 'K';
        correctLine[6] = 'u'; correctLine[7] = 'n';
        correctLine[8] = 'd'; correctLine[9] = 'e';
        correctLine[10] = 0x22; correctLine[11] = ':';
        correctLine[12] = ' '; correctLine [13] = 0x22;
        for(iter = 0; iter < customerNameLength; iter++) {
            correctLine[fixOutputLength+iter] = customerName[iter];
        }
        correctLine[fixOutputLength+customerNameLength] = 0x22;
        correctLine[fixOutputLength+customerNameLength + 1] = ',';



        QString filename = "logfileTestKunde.json";
        QFile testFile(filename);
        if(testFile.open(QIODevice::ReadWrite)) {
            QTextStream testStream(&testFile);
            LogFile::writeCustomer(customerName, &testStream);
            testFile.close();
        }
        if(testFile.open(QIODevice::ReadWrite)) {
            QTextStream testStream(&testFile);
            QString textOutput =
                    testStream.readLine(fixOutputLength
                                        + customerNameLength
                                        + fixSuffixLength);
            QByteArray byteArrayReadData = textOutput.toLatin1();
            char *readData = byteArrayReadData.data();

            for (iter = 0; iter < (fixOutputLength
                                   + customerNameLength
                                   + fixSuffixLength);
                 iter++) {
                if (readData[iter] != correctLine[iter]) {
                    equal = false;
                    std::cout << iter << std::endl;
                }
            }
            if (!equal) {
                std::cout << textOutput.toUtf8().constData() << std::endl;
                std::cout << correctLine << std::endl;
            }
        }
        else{
            std::cout << "File was not opened" << std::endl;
            equal = false;
        }

        testFile.close();

        BOOST_CHECK( equal );
    }

    BOOST_AUTO_TEST_CASE( writeJobNr ) {
        bool equal = true;


        const int customerNameLength = 8;
        const char* jobNr = "testName";
        const int fixOutputLength = 23;
        const int fixSuffixLength = 2;

        QString qstringCustomer = QString(jobNr);
        QByteArray tempNameArray = qstringCustomer.toLatin1();

        char correctLine[fixOutputLength+customerNameLength];
        int iter = 0;
        for(iter = 0; iter < 4; iter++) {
            correctLine[iter] = ' ';
        }
        correctLine[4] = 0x22; correctLine[5] = 'A';
        correctLine[6] = 'u'; correctLine[7] = 'f';
        correctLine[8] = 't'; correctLine[9] = 'r';
        correctLine[10] = 'a'; correctLine[11] = 'g';
        correctLine[12] = 's'; correctLine[13] = 'n';
        correctLine[14] = 'u'; correctLine[15] = 'm';
        correctLine[16] = 'm'; correctLine[17] = 'e';
        correctLine[18] = 'r'; correctLine[19] = 0x22;
        correctLine[20] = ':'; correctLine[21] = ' ';
        correctLine[22] = 0x22;
        for(iter = 0; iter < customerNameLength; iter++) {
            correctLine[fixOutputLength+iter] = jobNr[iter];
        }
        correctLine[fixOutputLength+customerNameLength] = 0x22;
        correctLine[fixOutputLength+customerNameLength + 1] = ',';



        QString filename = "logfileTestJobNr.json";
        QFile testFile(filename);
        if(testFile.open(QIODevice::ReadWrite)) {
            QTextStream testStream(&testFile);
            LogFile::writeJobID(jobNr, &testStream);
            testFile.close();
        }
        if(testFile.open(QIODevice::ReadWrite)) {
            QTextStream testStream(&testFile);
            QString textOutput =
                    testStream.readLine(fixOutputLength
                                        + customerNameLength
                                        + fixSuffixLength);
            QByteArray byteArrayReadData = textOutput.toLatin1();
            char *readData = byteArrayReadData.data();

            for (iter = 0; iter < (fixOutputLength
                                   + customerNameLength
                                   + fixSuffixLength);
                 iter++) {
                if (readData[iter] != correctLine[iter]) {
                    equal = false;
                    std::cout << iter <<  " " << readData[iter] <<
                              " " << correctLine[iter] << std::endl;
                }
            }
            if (!equal) {
                std::cout << textOutput.toUtf8().constData() << std::endl;
                std::cout << correctLine << std::endl;
            }
        }
        else{
            std::cout << "File was not opened" << std::endl;
            equal = false;
        }

        testFile.close();

        BOOST_CHECK( equal );
    }

    BOOST_AUTO_TEST_CASE( testDate ) {

        bool equal = true;


        const int dateLength = 10;
        const int timeLength = 5;
        QDateTime date = QDateTime::currentDateTime();
        const int fixPrefixLength = 14;
        const int fixInfixLength = 1;
        const int fixSuffixLength = 2;

        QString stringDate = date.toString("yyyy-MM-dd");
        QString stringTime = date.toString("hh:mm");
        QByteArray tempDateArray = stringDate.toLatin1();
        QByteArray tempTimeArray = stringTime.toLatin1();
        char charDate[dateLength];
        int iter = 0;
        for(iter = 0; iter < dateLength; iter++) {
            charDate[iter] = tempDateArray[iter];
        }
        charDate[dateLength] = 'T';
        for(iter = 0; iter < timeLength; iter++) {
            charDate[dateLength + fixInfixLength + iter] = tempTimeArray[iter];
        }



        char correctLine[fixPrefixLength
                         +dateLength
                         +timeLength
                         +fixSuffixLength
                         +fixInfixLength];
        for(iter = 0; iter < 4; iter++) {
            correctLine[iter] = ' ';
        }
        correctLine[4] = 0x22; correctLine[5] = 'D';
        correctLine[6] = 'a'; correctLine[7] = 't';
        correctLine[8] = 'u'; correctLine[9] = 'm';
        correctLine[10] = 0x22; correctLine[11] = ':';
        correctLine[12] = ' '; correctLine[13] = 0x22;
        for(iter = 0; iter < dateLength
                             + fixInfixLength
                             + timeLength; iter++) {
            correctLine[fixPrefixLength+iter] = charDate[iter];
        }
        correctLine[fixPrefixLength
                    +dateLength
                    +fixInfixLength
                    +timeLength] = 0x22;
        correctLine[fixPrefixLength
                    +dateLength
                    +fixInfixLength
                    +timeLength+1] = ',';


        QString filename = "logfileTestDate.json";
        QFile testFile(filename);
        if(testFile.open(QIODevice::ReadWrite)) {
            QTextStream testStream(&testFile);
            LogFile::writeDate(date, &testStream);
            testFile.close();
        }
        if(testFile.open(QIODevice::ReadWrite)) {
            QTextStream testStream(&testFile);
            QString textOutput = testStream.readLine(fixPrefixLength
                                                     + dateLength
                                                     + fixInfixLength
                                                     + timeLength
                                                     + fixSuffixLength);
            QByteArray byteArrayReadData = textOutput.toLatin1();
            char *readData = byteArrayReadData.data();

            for (iter = 0; iter < (fixPrefixLength
                                   + dateLength
                                   + fixInfixLength
                                   + timeLength
                                   + fixSuffixLength); iter++) {
                if (readData[iter] != correctLine[iter]) {
                    equal = false;
                    std::cout << iter <<  " " << readData[iter] <<
                              " " << correctLine[iter] << std::endl;
                }
            }
            if (!equal) {
                std::cout << textOutput.toUtf8().constData() << std::endl;
                std::cout << correctLine << std::endl;
            }
        }
        else{
            std::cout << "File was not opened" << std::endl;
            equal = false;
        }

        testFile.close();

        BOOST_CHECK( equal );
    }



BOOST_AUTO_TEST_SUITE_END();
