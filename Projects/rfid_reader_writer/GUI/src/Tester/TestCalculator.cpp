//
// Created by utti on 08.03.17.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE calculator
#include <boost/test/unit_test.hpp>
#include "../Calculator.hpp"
#include "TestCards.h"


/////////////////////////////////////////////////
/////////   Test methods for Calculator   ///////
/////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE( calculatorTest )
    /**
     * @brief Tests the method \link intToHex \endlink with fix parameter.
     */
    BOOST_AUTO_TEST_CASE( intToHexTest ) {
        const int bufferLength = BLOCKSIZE_ON_CARD;
        const int i = 12345;
        int calcVal = 0;
        unsigned char tempBuffer[bufferLength];
        Calculator::intToHex( i, &tempBuffer[0]);
        char buffer [bufferLength];
        for(int i = 0; i < bufferLength; i++) {
            buffer[i] = (char) tempBuffer[i];
        }

        for(int iter = 0; iter < BLOCKSIZE_ON_CARD; iter++) {
            calcVal = (calcVal | (Calculator::hex2char(buffer[iter]) <<
                                                          MAXIMUM_NIBBLE_SHIFT - iter * SHIFT_NIBBLE) );
        }


        BOOST_CHECK(i == calcVal);
    }

    /**
     * @brief Tests the method \link calcCRC16_added \endlink with fix parameter.
     */
    BOOST_AUTO_TEST_CASE( calcCRC16AddTest ) {
        int i0, i1, i2, i3, i4, crc;
        i0 = TESTCARD.card_type;
        i1 = TESTCARD.record_rev;
        i2 = TESTCARD.locNr;
        i3 = TESTCARD.kunden_nr;
        i4 = TESTCARD.card_nr;

        const int crc_calc_by_hand = TESTCARD.crc16_added;

        Calculator::calcCRC16_added( i0, i1, i2, i3, i4, &crc);


        BOOST_CHECK( crc == crc_calc_by_hand );
    }
    /**
     * @brief Tests the method \link calcCRC16 \endlink with fix parameter
     */
    BOOST_AUTO_TEST_CASE( calcCRC16IBMTest ) {


        // calculate the crc
        uint16_t crcVal = Calculator::calcCRC16_ibm((uint8_t*)(&TESTCARD
                                                           .card_type),
                                            12);


        BOOST_CHECK( crcVal == TESTCARD.crc16_ibm );
    }
    /**
     * @brief Test the method \link calcMD5 \endlink with fix parameter.
     *
     * Tests the md5 calculation with the word "dont look @ me".
     */
    BOOST_AUTO_TEST_CASE( calcMD5Test ){

        int succ = true;
        const int lengthOfWord = 14;
        const unsigned char testData[lengthOfWord] = { 	'd', 'o', 'n', 't', ' ',
                                                          'l', 'o', 'o', 'k', ' ', '@',
                                                          ' ', 'm', 'e'
        };

        unsigned char correctMD5[MD5_SIZE] = {
                0x3b, 0x1c, 0xe8, 0x58,
                0xe3, 0x23, 0x15, 0x65,
                0xa1, 0x35, 0xc4, 0x7c,
                0x46, 0xb4, 0x26, 0x48
        };


        unsigned char calculatedMD5[MD5_SIZE];
        for(int i = 0; i < MD5_SIZE; i++) {
            calculatedMD5[i] = '-';
        }

        Calculator::calculateQTMD5(testData, lengthOfWord, calculatedMD5);

        // compare correct md5 with the calculated one
        for(int i = 0; i < MD5_SIZE; i++) {
            if(calculatedMD5[i] != correctMD5[i]) {
                succ = false;
                std::cout << i << " ";
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)correctMD5[i];
                std::cout << " ";
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)calculatedMD5[i];
                std::cout << std::endl;
            }
        }
        // print both in case the calculation was not succesful
        if(!succ) {
            for(int i = 0; i < MD5_SIZE; i++) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)correctMD5[i];
            }
            std::cout << std::endl;
            for(int i = 0; i < MD5_SIZE; i++) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)calculatedMD5[i];
            }
            std::cout << std::endl;
        }


        BOOST_CHECK( succ );
    }
    /**
     * @brief Tests the method \link calcMD5Xor \endlink with fix parameter.
     *
     * There are different parameter available. The parameter can be changed hardcoding
     * them into the method or changing the \link TESTCARD \endlink .
     */
    BOOST_AUTO_TEST_CASE( calcMD5XorTest ) {


        int succ = true;
        unsigned char calculatedXoredMD5[2*BYTE_PER_BLOCK];



        for(int i = 0; i<2*BYTE_PER_BLOCK; i++) {
            calculatedXoredMD5[i] = '-';
        }

        Calculator::calcMD5Xor((uint8_t*)(&TESTCARD.uid[0]),
                              &calculatedXoredMD5[0]);

        // compare correct md5 with the calculated one
        for(int i = 0; i < 2*BYTE_PER_BLOCK; i++) {
            if(calculatedXoredMD5[i] != TESTCARD.md5_arr[i]) {
                succ = false;
                std::cout << i << " ";
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)TESTCARD.md5_arr[i];
                std::cout << " ";
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)calculatedXoredMD5[i];
                std::cout << std::endl;
            }
        }
        // print both in case the calculation was not succesful
        if(!succ) {
            for(int i = 0; i < 2*BYTE_PER_BLOCK; i++) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)TESTCARD.md5_arr[i];
            }

            std::cout << std::endl;
            for(int i = 0; i < 2*BYTE_PER_BLOCK; i++) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)calculatedXoredMD5[i];
            }
            std::cout << std::endl;
        }
        BOOST_CHECK( succ );

    }

BOOST_AUTO_TEST_SUITE_END()