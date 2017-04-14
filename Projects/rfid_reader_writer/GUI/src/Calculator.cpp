/*
 * Calculator.cpp
 *
 *  Created on: 30.09.2016
 *      Author: LabView
 */

#include "Calculator.hpp"
#include "CardInformation.hpp"

/**
 * @brief Converts integer from 0 to 15 into the equivalent hex value
 *
 *
 * @param[in] inputValue 	the integer that will be converted
 * @param[out] out			a pointer to a string where the hex value will be written in
 * @return 				1 iff the conversion was succesful
 */
int simpleIntToHex (const int inputValue, unsigned char *const out) {

	bool succ = true;
	switch(inputValue) {
		case 0: *out = '0'; break;
		case 1: *out = '1'; break;
		case 2: *out = '2'; break;
		case 3: *out = '3'; break;
		case 4: *out = '4'; break;
		case 5: *out = '5'; break;
		case 6: *out = '6'; break;
		case 7: *out = '7'; break;
		case 8: *out = '8'; break;
		case 9: *out = '9'; break;
		case 10: *out = 'A'; break;
		case 11: *out = 'B'; break;
		case 12: *out = 'C'; break;
		case 13: *out = 'D'; break;
		case 14: *out = 'E'; break;
		case 15: *out = 'F'; break;
		default: succ = false;
	}

	if(succ) {
		return 1;
	}
	else{
		std::cout << "Invalid transformation: " << inputValue << " to hex in one Byte" << std::endl;
		return 0;
	}

}
/**
 * @brief Converts an integer to a hex.
 *
 *  In the conversion calculates the least significant Bytes last. The amount of Bytes
 *  calculated is exactly \link BLOCKSIZE_ON_CARD \endlink. This method uses the method
 *  \link simpleIntToHex \endlink to convert values, calculated here, in the range from 0 to 15
 *  to the corresponding Hex value.
 *
 * @param[in] input 	The integer that will be converted
 * @param[out] out		The first entry of the array where the hex string will be written in.
 *                      The length of the array must be at least \link BLOCKSIZE_ON_CARD \endlink
 *                      
 *
 * @return 1            If and only if the calculat
 */
int intToHex(const int input, unsigned char *const out){

	int succCalc = 1;
	int intValues[BLOCKSIZE_ON_CARD];

	// decompose input to the form i = x0*16^0 + x1*16^1 + x2*16^2 ...
	// and store the x
	// -> x0 = i % 16
	// -> x1 = ((i - x0)/16)%16
	for(unsigned int i = 0; i < BLOCKSIZE_ON_CARD; i++) {
		int tempSum = input;
		for(unsigned int j = 0; j < i; j++) {

			tempSum = (tempSum - intValues[j])/16;
		}
		intValues[i] = tempSum % 16;

	}


	// in order to check the calculation
	// sum the int values of the calculated hex array and sum them up
	int sum = 0;
	for(unsigned int i = 0; i < BLOCKSIZE_ON_CARD; i++) {
		simpleIntToHex(intValues[BLOCKSIZE_ON_CARD-i-1], &out[i]);
		sum += out[BLOCKSIZE_ON_CARD - i]*pow(16,i);
	}

	if(sum == input) {
		succCalc = 1;
	}
	else
		succCalc = 0;

	return succCalc;
}

/**
 * @brief Calculates the integer value of the given character.
 *
 * In case the input character is neither in the integer range
 * zero to ten, nor in the range of 'a' to 'f' or 'A' to 'F' the
 * method returns the value the equals the decimal value if the 
 * input is handle like an hexadecimal value.
 *
 * @return  The decimal value in case the input is handle like and 
 *          hexadecimal value.
 */
char hex2char(char nibble)
{

    switch (nibble)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return nibble - '0';
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            return nibble - 'a' + 10;
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            return nibble - 'A' + 10;
        default:
            return 0;
    }
    

    
    return 0;
}
/**
 * @brief Calculates the added checksum of a card.
 *
 * This means the values of the card, beginning with the card type 
 * and ending with the card id, are added up and cut into a unsigned
 * 16 bit integer. This method uses the method 
 * \link calcCRC16_added(card_info, int* const) \endlink to calculate
 * the checksum.
 *
 * @param[in] The card information of the card whose checksum should be
 *            calculated
 *
 * @return The 16 bit value of the checksum
 */
int calcCRC16_added(card_info card) {
	int crc;
	calcCRC16_added(card, &crc);
	return crc;
}

/**
 * @brief Calculates the added checksum of the given card and writes it into
 *        given pointer.
 *
 * The checksum is calculated by the method 
 * \link calcCRC16_added(const int, const int, const int, const int, const int, int *const ) \endlink .
 * and writes it into the given pointer.
 *
 * @param[in] the card information about the card whose checksum should be
 *            calculated
 * @param[out] the calculated 16 bit integer value of the checksum
 */
void calcCRC16_added(card_info card, int* const outPut) {
	calcCRC16_added(card.card_type,
					card.record_rev,
					card.locNr,
	                card.kunden_nr,
	                card.card_nr,
	                outPut);
}

/**
 * @brief 	Calculates a checksum where the input parameter are summed bytewise.
 * 			The calculated checksum is written in 'outPut'.
 *
 * Calculates the checksum of the input parameter. The value of the checksum is
 * is cut in an 16 bit integer and is written into the given pointer.
 *
 * @param[in] cardType		value representing the cardType
 * @param[in] recordRev		value representing the recordRev
 * @param[in] locationNr	value representing the location number
 * @param[in] userID		value represending the user ID
 * @param[in] cardID		value representing the card ID
 * @param[out] outPut		a pointer to the integer wherethe checksum will be written in
 */
void calcCRC16_added(const int cardType,
					const int recordRev,
					const int locationNr,
					const int userID,
					const int cardID,
					int *const outPut){



	int sum = 0;

	// split user ID in four uint8
	int uID0 = (FIRST_8_BIT_OF_UINT16 & userID) >> 24;
	int uID1 = (SECOND_8_BIT_OF_UINT16 & userID) >> 16;
	int uID2 = (THIRD_8_BIT_OF_UINT16 & userID) >> 8;
	int uID3 = FOURTH_8_BIT_OF_UINT16 & userID;
	// split cardID int four uint8
	int cID0 = (FIRST_8_BIT_OF_UINT16 & cardID) >> 24;
	int cID1 = (SECOND_8_BIT_OF_UINT16 & cardID) >> 16;
	int cID2 = (THIRD_8_BIT_OF_UINT16 & cardID) >> 8;
	int cID3 = (FOURTH_8_BIT_OF_UINT16 & cardID);

	//Add cardType
	sum += (cardType & LAST_8_BIT_OF_INT);
	//Add recordRev
	sum += (recordRev & LAST_8_BIT_OF_INT);
	// Add locationNr
	sum += (locationNr & LAST_8_BIT_OF_INT);
	// Add userID
	sum += uID0 + uID1 + uID2 + uID3;
	// Add cardID
	sum += cID0 +cID1 + cID2 + cID3;
	

	*outPut = UINT_16_BITMAP & sum;

}
/**
 * @var crc16_ibm_table_hi
 * @brief Table of CRC16-IBM values for high-order byte 
 */
static const uint8_t crc16_ibm_table_hi[256]={
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
  0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
  0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
  0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
  0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
  0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
  0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
  0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
  0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
  0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
  0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
  0x40
};

/**
 * @var crc16_ibm_table_lo
 * @brief Table of CRC16-IBM values for low-order byte
 */
static const uint8_t crc16_ibm_table_lo[256]={
  0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
  0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
  0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
  0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
  0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
  0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
  0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
  0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
  0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
  0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
  0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
  0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
  0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
  0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
  0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
  0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
  0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
  0x40
};
/**
 * @brief Calculates the checksum by using CRC16-IBM algorithm.
 *
 * The method uses the table \link crc16_ibm_table_lo \endlink and 
 * \link crc16_ibtm_table_hi \endlink to calculate the checksum of the data
 * the pointer is pointing on and the given length.
 *
 * @param[in] Start adress of the data buffer
 * @param[in] The length of the data buffer
 *
 * @return The value of the calculated checksum
 */
uint16_t calcCRC16_ibm (const uint8_t* data, uint16_t len) {
    uint8_t uchCRCHi=0xff;
    uint8_t uchCRCLo=0xff;
    uint8_t uIndex;

    while (len-->0) {
        uIndex=(uchCRCLo^((uint8_t)*(data++))); // calc crc
        uchCRCLo=(uchCRCHi^crc16_ibm_table_hi[uIndex]);
        uchCRCHi=crc16_ibm_table_lo[uIndex];
    }

    return (((uint16_t)uchCRCHi<<8)|(uint16_t)uchCRCLo);
}

/**
 * @brief Calculates the MD5 of the given input data using the QT library.
 *
 * Using the QT cryptographic hash library for calculate the MD5 of the input
 * data. After the MD5 is computed it is written in the given array.
 *
 * @param[in] The start adress of the data the MD5 should be calculated of.
 * @param[in] The length of the data the MD5 should be calculated of.
 * @param[out] The calculated MD5 of the given data
 */
void calculateQTMD5(const unsigned char* inputData, const int length, unsigned char md5Data[MD5_SIZE]) {
    QByteArray convertedInput(QByteArray::fromRawData( (const char*) inputData, length));

	QByteArray outPut = QCryptographicHash::hash(convertedInput,QCryptographicHash::Md5);

	char* tempData = outPut.data();

	for(int arrayIter = 0; arrayIter < MD5_SIZE; arrayIter++) {
		md5Data[arrayIter] = (unsigned char) tempData[arrayIter];
	}

}

/**
 * @brief Calculate the md5 of the input and Xors it pairwise.
 * 
 * The md5 is calculated by the method <calcMd5()>  with the input data given
 * to this method. Then the bytes i and i+1, where i is even, are xored and written in the
 * array for the output.
 *
 * @param[in] inputData 	The data the md5 is calculated for. The data must be \link MD5_DATA_SIZE \endlink
 * 						+ \link MD5_KEY_SIZE \endlink bytes long.
 * @param[out] md5Data	The array where the xored md5 is written in
 */
void calcMD5Xor(const unsigned char* inputData, unsigned char *const md5Data) {

	unsigned char tempData[MD5_SIZE];


	for(int i = 0; i < MD5_SIZE; i++) {
		tempData[i] = '0';
	}

	calculateQTMD5(&inputData[0], MD5_DATA_SIZE + MD5_KEY_SIZE, &tempData[0]);


	// Xor pairs of the calculated md5
	for(int i = 0; i < (2*BYTE_PER_BLOCK); i++) {
		md5Data[i] = (tempData[2*i] ^ tempData[2*i+1]);
	}
}

