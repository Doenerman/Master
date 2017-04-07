/*
 * Calculator.hpp
 *
 *  Created on: 30.09.2016
 *      Author: LabView
 */
#include <cstdint>
#ifndef CALCULATOR_HPP_
#define CALCULATOR_HPP_

#include <iostream>
#include <cstdlib>
#include <math.h>
#include "CardInformation.hpp"
#include <iomanip>
#include <QCryptographicHash>
#include <QByteArray>

#define KEY_1 {\
				0x70,0x65,0x69,0x62,0x61,0x68,0x25,0x70,\
				0x68,0x34,0x73,0x65,0x69,0x53,0x36,0x65,\
				0x69,0x52,0x61,0x69,0x77,0x24,0x61\
				}
#define KEY_2 {\
				0x61,0x68,0x77,0x61,0x75,0x58,0x37,0x4f,\
				0x65,0x5c,0x73,0x68,0x6f,0x68,0x38,0x6d,\
				0x61,0x68,0x2a,0x64,0x61,0x68,0x7e\
				}
#define KEY_3 {\
				0x03,0x07,0x15,0xD2,0x71,0x4C,0x39,0x01,\
				0x0A,0x0D,0xFD,0x00,0x02,0x37,0x04,0xFC,\
				0x00,0x0F,0x17,0x1B,0x2E,0x4D,0x02\
				}


#define MD5_SIZE 16
#define MD5_DATA_SIZE 32 // the first 5 blocks + unique card ID
#define MD5_KEY_SIZE 69


/** 
 * @def SHIFT_NIBBLE
 * @brief   The amount of bits that must be
 *          shifted to shift a complete nibble
 */
#define SHIFT_NIBBLE 4
/** 
 * @def MAXIMUM_NIBBLE_SHIFT
 * @brief   The maximum of bits shifted such that the
 *          shifted nibble still covers a nibble of
 *          a Byte and would be on the same block on
 *          the card
 */
#define MAXIMUM_NIBBLE_SHIFT 28
/** 
 * @def MAXIMUM_CRC_NIBBLE_SHIFT
 * };
 *  The maximum of bits shifted such that the
 *  shifted nibble still covers a nibble of
 *  same block part on the card. So the most left
 *  nibble of the crc_added can be shifted up to
 *  this amount and still covers a nibble of card
 *  part that deals with the crc_added.
 */
#define MAXIMUM_CRC_NIBBLE_SHIFT 12

#define SHIFT_OPERATOR_UINT8_TO_UINT16 8
#define SHIFT_OPERATOR_UINT32_TO_UINT16 16
#define FIRST_8_BIT_OF_UINT16 0xFF000000
#define SECOND_8_BIT_OF_UINT16 0x00FF0000
#define THIRD_8_BIT_OF_UINT16 0x0000FF00
#define FOURTH_8_BIT_OF_UINT16 0x000000FF
#define LAST_8_BIT_OF_INT 0xFF

#define UINT_16_BITMAP 0x0000FFFF

int simpleIntToHex (const int, unsigned char *const);
int intToHex(const int, unsigned char *const);
char hex2char(char nibble);
int calcCRC16_added(card_info card);
void calcCRC16_added(card_info card, int* const outPut);
void calcCRC16_added(const int,
					const int,
					const int,
					const int,
					const int,
					int *const);
uint16_t calcCRC16_ibm (const uint8_t*, uint16_t);
void calculateQTMD5(const unsigned char* inputData, const int length, unsigned char md5Data[MD5_SIZE]);
void calcMD5Xor(const unsigned char* inputData, unsigned char *const md5Data);
#endif /* CALCULATOR_HPP_ */
