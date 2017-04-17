/*
 * Calculator.cpp
 *
 *  Created on: 30.09.2016
 *      Author: LabView
 */

#include "Calculator.hpp"


constexpr uint8_t Calculator::crc16_ibm_table_hi[256];
constexpr uint8_t Calculator::crc16_ibm_table_lo[256];

/**
 * @brief Converts integer from 0 to 15 into the equivalent hex value
 *
 *
 * @param[in] inputValue 	the integer that will be converted
 * @param[out] out			a pointer to a string where the hex value will be written in
 * @return 				1 iff the conversion was succesful
 */
int Calculator::simpleIntToHex (const int inputValue, unsigned char *const out) {

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
 *  calculated is exactly \link BLOCKSIZE_ON_CARD \endlink. This method uses the 
 *  method \link simpleIntToHex \endlink to convert values, calculated here, in the
 *  range from 0 to 15 to the corresponding Hex value.
 *
 * @param[in] input 	The integer that will be converted
 * @param[out] out		The first entry of the array where the hex string will be
 *                    written in. The length of the array must be at least 
 *                    \link BLOCKSIZE_ON_CARD \endlink
 *                      
 *
 * @return 1            If and only if the calculat
 */
int Calculator::intToHex(const int input, unsigned char *const out){

	int succCalc;
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
char Calculator::hex2char(char nibble)
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
 * @param[in] card  The card information of the card whose checksum should be
 *                  calculated
 *
 * @return The 16 bit value of the checksum
 */
int Calculator::calcCRC16_added(card_info card) {
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
 * @param[in] card    The card information about the card whose checksum should be
 *                    calculated
 * @param[out] outPut The calculated 16 bit integer value of the checksum
 */
void Calculator::calcCRC16_added(card_info card, int* const outPut) {

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
void Calculator::calcCRC16_added(const int cardType,
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
 * @brief Calculates the checksum by using CRC16-IBM algorithm.
 *
 * The method uses the table \link crc16_ibm_table_lo \endlink and 
 * \link crc16_ibm_table_hi \endlink to calculate the checksum of the data
 * the pointer is pointing on and the given length.
 *
 * @param[in] data  Start adress of the data buffer
 * @param[in] len   The length of the data buffer
 *
 * @return The value of the calculated checksum
 */
uint16_t Calculator::calcCRC16_ibm (const uint8_t* data, uint16_t len) {
    uint8_t uchCRCHi=0xff;
    uint8_t uchCRCLo=0xff;
    uint8_t uIndex;

    while (len-->0) {
        uIndex=(uchCRCLo^((uint8_t)*(data++))); // calc crc
        uchCRCLo=(uchCRCHi^Calculator::crc16_ibm_table_hi[uIndex]);
        uchCRCHi=Calculator::crc16_ibm_table_lo[uIndex];
    }

    return (((uint16_t)uchCRCHi<<8)|(uint16_t)uchCRCLo);
}

/**
 * @brief Calculates the MD5 of the given input data using the QT library.
 *
 * Using the QT cryptographic hash library for calculate the MD5 of the input
 * data. After the MD5 is computed it is written in the given array.
 *
 * @param[in] inputData The start adress of the data the MD5 should be calculated of.
 * @param[in] length    The length of the data the MD5 should be calculated of.
 * @param[out] md5Data  The calculated MD5 of the given data
 */
void Calculator::calculateQTMD5(const unsigned char* inputData,
                                const int length,
                                unsigned char md5Data[MD5_SIZE]) {
    QByteArray convertedInput(QByteArray::fromRawData( (const char*) inputData,
                                                      length));

	QByteArray outPut = QCryptographicHash::hash(convertedInput,
                                               QCryptographicHash::Md5);

	char* tempData = outPut.data();

	for(int arrayIter = 0; arrayIter < MD5_SIZE; arrayIter++) {
		md5Data[arrayIter] = (unsigned char) tempData[arrayIter];
	}

}

/**
 * @brief Calculate the md5 of the input and Xors it pairwise.
 * 
 * The md5 is calculated by the method <calcMd5()>  with the input data given
 * to this method. Then the bytes i and i+1, where i is even, are xored and written 
 * in the array for the output.
 *
 * @param[in] inputData 	The data the md5 is calculated for. The data must be
 *                        \link MD5_DATA_SIZE \endlink plus \link MD5_KEY_SIZE 
 *                        \endlink bytes long.
 * @param[out] md5Data	The array where the xored md5 is written in
 */
void Calculator::calcMD5Xor(const unsigned char* inputData,
                            unsigned char *const md5Data) {

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

