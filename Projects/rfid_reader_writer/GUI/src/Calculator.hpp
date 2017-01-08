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
//#include "md5.h"
#include "CardInformation.hpp"
#include <iomanip>



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
 * 
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
void calcCRC16_added(const int,
					const int,
					const int,
					const int,
					const int,
					int *const);
uint16_t calcCRC16_ibm (const uint8_t*, uint16_t);
//void calcMD5(const unsigned char* inputData, const int length, unsigned char *const md5Data);
//void calcMD5Xor(const unsigned char* inputData, unsigned char *const md5Data);
#endif /* CALCULATOR_HPP_ */
