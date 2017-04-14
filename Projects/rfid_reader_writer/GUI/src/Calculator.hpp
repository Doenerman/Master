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

/**
 * \def KEY_1
 * @brief First part of the key that is used for the MD5 calculation.
 * 
 * The key consists of three parts.
 */
#define KEY_1 {\
				0x70,0x65,0x69,0x62,0x61,0x68,0x25,0x70,\
				0x68,0x34,0x73,0x65,0x69,0x53,0x36,0x65,\
				0x69,0x52,0x61,0x69,0x77,0x24,0x61\
				}
/**
 * \def KEY_2
 * @brief Second part of the key that is used for the MD5 calculation.
 * 
 * The key consists of three parts.
 */
#define KEY_2 {\
				0x61,0x68,0x77,0x61,0x75,0x58,0x37,0x4f,\
				0x65,0x5c,0x73,0x68,0x6f,0x68,0x38,0x6d,\
				0x61,0x68,0x2a,0x64,0x61,0x68,0x7e\
				}
/**
 * \def KEY_3
 * @brief Third part of the key that is used for the MD5 calculation.
 * 
 * The key consists of three parts.
 */
#define KEY_3 {\
				0x03,0x07,0x15,0xD2,0x71,0x4C,0x39,0x01,\
				0x0A,0x0D,0xFD,0x00,0x02,0x37,0x04,0xFC,\
				0x00,0x0F,0x17,0x1B,0x2E,0x4D,0x02\
				}

/**
 * \def MD5_SIZE
 * @brief The length of the MD5 that is written on the card.
 */
#define MD5_SIZE 16
/**
 * \def MD5_DATA_SIZE
 * @brief The size of the data on the card that is used to calculate the MD5 of a card.
 * 
 * This includes the unique card id and the first five blocks of the card.
 */
#define MD5_DATA_SIZE 32 // the first 5 blocks + unique card ID
/**
 * \def MD5_KEY_SIZE
 * @brief The length of the key the MD5 calculation uses.
 */
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
 * @brief  The maximum of bits shifted such that the shifted nibble 
 *         still covers a nibble of same block part on the card. 
 *
 *  So the most left
 *  nibble of the crc_added can be shifted up to
 *  this amount and still covers a nibble of card
 *  part that deals with the crc_added.
 */
#define MAXIMUM_CRC_NIBBLE_SHIFT 12

/**
 * \def FIRST_8_BIT_OF_UINT16
 * @brief A bit map that is used to calculate the first 8 bit of an unsigned
 *        16 bit integer.
 *
 * The first 8 bit can be calculated by using the '&'  operator.
 */
#define FIRST_8_BIT_OF_UINT16 0xFF000000
/**
 * \def SECOND_8_BIT_OF_UINT16
 * @brief A bit map that is used to calculate the second 8 bit of an unsigned 
 *        16 bit integer.
 *
 * The second 8 bit can be calculated by using the '&' operator.
 */
#define SECOND_8_BIT_OF_UINT16 0x00FF0000
/**
 * \def THIRD_8_BIT_OF_UINT16
 * @brief A bit map that is used to calculate the third 8 bit of an unsigned
 *        16 bit integer.
 * 
 * The third 8 bit can be calculated by using the '&' operator.
 */
#define THIRD_8_BIT_OF_UINT16 0x0000FF00
/**
 * \def FOURTH_8_BIT_OF_UINT16
 * @brief A bit map that is used to calculate the fourth 8 bit of an unsigned
 *        16 bit integer.
 *
 * The fourth 8 bit can be calculated by using the '&' operator.
 */
#define FOURTH_8_BIT_OF_UINT16 0x000000FF
/**
 * \def LAST_8_BIT_OF_INT
 * @brief A bit map that is used to calculate the last 8 bit of an integer.
 * 
 * The last 8 bit can be calculated by using the '&' operator.
 */
#define LAST_8_BIT_OF_INT 0xFF
/** @todo check the define below and its meaning */
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
