//
// Created by utti on 08.03.17.
//
#include "TestCalculator.h"
#include <iostream>

/**
* @brief Tests the methods from \link Calculator.hpp \endlink .
*
* There is a short output for each tested method of the form "<methodname>: <result>".
* A method passed a test if and only if its result equals 1.
*/
int main(int argc, char *argv[]) {


    std::cout << std::endl;
    std::cout << "    Test 'Calculator'" << std::endl;
    std::cout << "simpleIntToHex:  " << testSimpleIntToHex() << std::endl;
    std::cout << "intToHex:        " << testIntToHex() << std::endl;
    std::cout << "calcCRC16_added: " << testCalcCRC16_added() << std::endl;
    std::cout << "calcCRC16:       " << testCalcCRC16_ibm() << std::endl;
    std::cout << "calcMD5:         " << testCalcMD5() << std::endl;
    std::cout << "calcMD5Xor:      " << testCalcMD5_Xor() << std::endl;

    return 0;
}

/////////////////////////////////////////////////
/////////   Test methods for Calculator   ///////
/////////////////////////////////////////////////
/**
 * @brief Tests the method \link simpleIntToHex \endlink with fix parameter.
 *
 * @return 1 	If and only if the method \link simpleIntToHex \endlink
 * 		   		passed the test
 */
int testSimpleIntToHex() {

    const int i = 10;
    unsigned char tempBuffer[1];
    simpleIntToHex(i, &tempBuffer[0]);
    char buffer[2] = { (char)tempBuffer[0], '\r' };
    return (i == std::strtol(&buffer[0], NULL, 16));
}
/**
 * @brief Tests the method \link intToHex \endlink with fix parameter.
 *
 * @return 1 	If and only if the method \link intToHex \endlink passed the test
 */
int testIntToHex() {
    const int bufferLength = BLOCKSIZE_ON_CARD;
    const int i = 12345;
    int calcVal = 0;
    unsigned char tempBuffer[bufferLength];
    intToHex( i, &tempBuffer[0]);
    char buffer [bufferLength];
    for(int i = 0; i < bufferLength; i++) {
        buffer[i] = (char) tempBuffer[i];
    }

    for(int iter = 0; iter < BLOCKSIZE_ON_CARD; iter++) {
        calcVal = (calcVal | (hex2char(buffer[iter]) << MAXIMUM_NIBBLE_SHIFT - iter * SHIFT_NIBBLE) );
    }


    return (i == calcVal);
}
/**
 * @brief Tests the method \link calcCRC16_added \endlink with fix parameter.
 *
 * return 1 If and only if the method \link calcCRC16_added \endlink passed the test
 */
int testCalcCRC16_added() {
    int i0, i1, i2, i3, i4, crc;
    i0 = TESTCARD.card_type;
    i1 = TESTCARD.record_rev;
    i2 = TESTCARD.locNr;
    i3 = TESTCARD.kunden_nr;
    i4 = TESTCARD.card_nr;

    const int crc_calc_by_hand = TESTCARD.crc16_added;

    calcCRC16_added( i0, i1, i2, i3, i4, &crc);


    return (crc == crc_calc_by_hand);
}
/**
 * @brief Tests the method \link calcCRC16 \endlink with fix parameter
 *
 * return 1 If and only if the method \link calcCRC16 \endlink passed the test
 */
int testCalcCRC16_ibm() {


    // calculate the crc
    uint16_t crcVal = calcCRC16_ibm((uint8_t*)(&TESTCARD.card_type), 12);


    return (crcVal == TESTCARD.crc16_ibm);
}
/**
 * @brief Test the method \link calcMD5 \endlink with fix parameter.
 *
 * Tests the md5 calculation with the word "hello".
 *
 * @return 1 If and only if \link calcMD5 \endlink passes the test
 */
int testCalcMD5() {

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

    //@todo call Test function

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


    return succ;
}
/**
 * @brief Tests the method \link calcMD5Xor \endlink with fix parameter.
 *
 * There are different parameter available. The parameter can be changed hardcoding
 * them into the method or changing the \link TESTCARD \endlink .
 *
 * @return 1 If and only if the method \calcMD5Xor \endlink passes the test.
 */
int testCalcMD5_Xor() {


    int succ = true;
    unsigned char calculatedXoredMD5[2*BYTE_PER_BLOCK];



    for(int i = 0; i<2*BYTE_PER_BLOCK; i++) {
        calculatedXoredMD5[i] = '-';
    }


    // @todo call Test function

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
    return succ;

}