/*
 * CardInformation.hpp
 *
 *  Created on: 30.09.2016
 *      Author: LabView
 */

#ifndef CARDINFORMATION_HPP_
#define CARDINFORMATION_HPP_

#include <cstdint>

/**
 * @def BLOCKSIZE_ON_CARD
 * @brief   The maximal length of a hex 
 *          value written on the card in
 *          a single block
 */
#define BLOCKSIZE_ON_CARD 8
/**
 * @def BYTE_PER_BLOCK 
 * @brief   The amount of Bytes that can
 *          be written in one block of the
 *          card
 */
#define BYTE_PER_BLOCK 4

#define PREFIX_ID_RESPONSE 6
#define SUFFIX_RESPONSE 1

/////////////////////////////////////
// List of read and write requests //
/////////////////////////////////////
#define CARD_TYPE_REQUEST 0
#define RECORD_REV_REQUEST 1
#define LOCATION_NUMBER_REQUEST 2
#define ID_TYPE_USER 3
#define ID_TYPE_CARD 4
#define CRC_ADDED 5
#define CRC_IBM 6
#define ID_TYPE_INVALID -1




///////////////////////////////
// List of block allocations //
///////////////////////////////
#define CARD_TYPE_BLOCK 0
#define RECORD_REV_BLOCK 0
#define LOCATION_NUMBER_BLOCK 0
#define USER_ID_BLOCK 1
#define CARD_ID_BLOCK 2
#define CRC_ADDED_BLOCK 3
#define CRC_IBM_BLOCK 3
#define MD5_FIRST_BLOCK 6
#define MD5_SECOND_BLOCK 7
#define INVALID_BLOCK -1

/**
 * @def FIRST_BLOCK
 * @brief   Value of to address the first block
 *          in \link writeDataToBlock \endlink
 */
#define FIRST_BLOCK 0
/**
 * @def FOURTH_BLOCK
 * @brief   Value of to address the fourth block
 *          in \link writeDataToBlock \endlink
 */
#define FOURTH_BLOCK 3
/** 
 * @def BLOCK_RESERVED_BLOCK_4
 * @brief   Value to adress the block for the information
 *          of reserved_block4 on the card
 */
#define BLOCK_RESERVED_BLOCK_4 4
/** 
 * @def BLOCK_RESERVED_BLOCK_5
 * @brief   Value to adress the block for the information
 *          of reserved_block5 on the card
 */
#define BLOCK_RESERVED_BLOCK_5 5
//////////////////////////////////////
// List of start position in blocks //
//////////////////////////////////////
/*  This is only for the blocks where 
    more then one information is in */
#define CARD_TYPE_BYTE_IN_BLOCK 0
#define RECREV_BYTE_IN_BLOCK 1
#define LOCNR_BYTE_IN_BLOCK 2
#define CRC_ADDED_STARTPOS_IN_BLOCK 4
#define CRC_STARTPOS_IN_BLOCK 0


/////////////////////////////////
// List of information lengths //
/////////////////////////////////
#define CARD_TYPE_LENGTH 2
#define RECORD_REV_LENGTH 2
#define LOCATION_NUMBER_LENGTH 2
#define CRC_ADDED_LENGTH 4
#define CRC_IBM_LENGTH 4
#define MAX_LENGTH_UNIQUE_ID 8


#define STARTPOS_UNIQUE_CARD_ID 11
#define BUFFER_TO_SHORT_FOR_UNIQUE_CARD_ID -1
#define RESPONSE_FAIL -2

/** 
 * @def MAX_CARD_TYPE
 * @brief   Maximal possible value of card_type in
 *          \link card_info \endlink
 */
#define MAX_CARD_TYPE 0xFF
/**
 * @def MAX_RECORD_REV
 * @brief   Maximal possible value of recordRev in
 *          \link card_info \endlink
 */
#define MAX_RECORD_REV 0xFF
/** 
 * @def MAX_LOCATION_NUMBER
 * @brief   Maximal possible value of locNr in
 *          \link card_info \endlink
 */
#define MAX_LOCATION_NUMBER 0xFF
/**
 * @def MAX_CRC_ADDED_VAL
 * @brief   The maximal value the crc_added can reach
 */
#define MAX_CRC_ADDED_VAL 0xFFFF
/**
 * @def MAX_CRC_IBM_VAL
 * @brief   The maximal value the crc_ibm can reach
 */
#define MAX_CRC_IBM_VAL 0xFFFF

/** 
 * \struct card_info CardInformation.hpp "CardInformation.hpp"
 * \brief   Informations that are used to write an RFID card.
 */
typedef struct __attribute__((packed, aligned(1))) {
    /** 
     * @var uid
     * @brief The array where the unique card id is stored in.
     */
	uint8_t uid[8];
	
    /**
     * @var card_type
     * @brief   The variable for the card type.
     *          In genereal it is 0. The card type is stored
     *          in the first Byte for the first block of the card.
     */
	uint8_t card_type;
    /**
     * @var record_rev
     * @brief   The variable for the revision number. The revision 
     *          number is stored in the second Byte of the first block
     *          of the card.
     */
	uint8_t record_rev;
    /**
     * @var locNr
     * @brief   The variable for the specification for which country the
     *          card is made for. The location specification is stored in
     *          the third Byte of the first block of the card.
     *
     * The following numbers are allready allocated:
     * 0x00 United Kingdom, 0x01 Germany
     */
	uint8_t locNr;
    /**
     * @var reserved_block0
     * @brief   The variable representing the last Byte of the first Block
     *          on the card. The variable should allways be zero.
     *
     * The variable is important for the calculation of the md5 and can
     * not dropped out.
     */
	uint8_t reserved_block0;

    /**
     * @var kunden_nr
     * @brief   The variable where the user id is stored in. The user id
     *          is stored in the complete second block of the card.
     */
	uint32_t kunden_nr;
    /**
     * @var card_nr
     * @brief   The variable where the card id is stored in. The card id
     *          is stored in the complete third block of the card.
     */
	uint32_t card_nr;
	
    /**
     * @var crc16_added
     * @brief   The variable where the bytewise added checksum of the
     *          first three blocks of the card is stored in. This checksum
     *          is stored in the first half of the fourth block of the card.
     */
	uint16_t crc16_added;
    /**
     * @var crc16_ibm
     * @brief   The variable where the checksum calculated by an ibm mechanism,
     *          that has the first three blocks as input, is stored in. This checksum
     *          is stored in the second half of the fourth block of the card.
     */
	uint16_t crc16_ibm;
    /** 
     * @var reserved_block4
     * @brief   The variable representing the fourth block of the card. The fourth
     *          block of the card is reserved and filled with zero.
     *
     * The variable is important for the calculation of the md5 and can
     * not dropped out.
     */
	uint32_t reserve_block4;
	/** 
     * @var reserved_block5
     * @brief   The variable representing the fiveth block of the card. The fourth
     *          block of the card is reserved and filled with zero.
     *
     * The variable is important for the calculation of the md5 and can
     * not dropped out.
     */
    uint32_t reserve_block5;
	
    /** 
     * @var key1
     * @brief   The first key that is used to calculate the MD5 for the card.
     *          This key is fix and must be \link KEY_1 \endlink
     */
	uint8_t key1[23];
    /** 
     * @var key2
     * @brief   The second key that is used to calculate the MD5 for the card.
     *          This key is fix and must be \link KEY_2 \endlink
     */
	uint8_t key2[23];
    /** 
     * @var key1
     * @brief   The third key that is used to calculate the MD5 for the card.
     *          This key is fix and must be \link KEY_3 \endlink
     */
	uint8_t key3[23];
	
    /**
     * @var md5_arr
     * @brief   An array for the md5 of the above information written in.
     *          So the md5 gets all above information, include the keys and
     *          the buffer containing zeros only as input.
     */
	uint8_t md5_arr[8];
    uint8_t correctMD5;
} card_info;
#endif /* CARDINFORMATION_HPP_ */
