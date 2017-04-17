//
// Created by utti on 09.03.17.
//

#ifndef GUI_TESTCARDS_H
#define GUI_TESTCARDS_H

#include "../CardInformation.hpp"
#include "../Calculator.hpp"

#define TESTCARD card1



// a card created from information collected with 'Director'
const card_info card0 = {
        //unique card ID
        {
                0xE0, 0x04, 0x01, 0x00,
                0x79, 0x2D, 0x0B, 0xA1
        },
        // block 0
        0,
        0,
        0,
        0,
        // block 1
        15,
        // block 2
        123456,

        // block 3
        0x132,
        0x2490,
        // block 4
        0,
        // block 5
        0,
        KEY_1,
        KEY_2,
        KEY_3,
        {
                0xF5, 0x70, 0x6D, 0x99,
                0xC2,0xD7, 0x0E, 0xDB
        },
        1
};
// a card created from information collected with 'Director' with an
// invalid xored md5
const card_info card0_invalid = {
        //unique card ID
        {
                0xE0, 0x04, 0x01, 0x00,
                0x79, 0x2D, 0x01, 0x5A
        },
        // block 0
        0,
        0,
        0,
        0,
        // block 1
        123456,
        // block 2
        15,

        // block 3
        0x132,
        0xF9A0,
        // block 4
        0,
        // block 5
        0,
        KEY_1,
        KEY_2,
        KEY_3,
        {
                0x98, 0xB5, 0x60, 0x2E,
                0x1C, 0xBF, 0x97, 0xB3
        },
        0
};
// a card created from information collected with 'Director'
const card_info card1 = {
        //unique card ID
        {
                0xE0, 0x04, 0x01, 0x00,
                0x79, 0x2D, 0x28, 0xE9
        },
        // block 0
        0,
        0,
        0,
        0,
        // block 1
        654321,
        // block 2
        15,

        // block 3
        0x204,
        0xC8E3,
        // block 4
        0,
        // block 5
        0,
        KEY_1,
        KEY_2,
        KEY_3,
        {
                0x6E, 0xFD, 0x73, 0x55,
                0x54, 0xC9, 0xA6, 0x59
        },
        1
};
// a card created from information collected with 'Director'
// with an invalid md5
const card_info card1_invalid = {
        //unique card ID
        {
                0xE0, 0x04, 0x01, 0x00,
                0x79, 0x2D, 0x28, 0xE9
        },
        // block 0
        0,
        0,
        0,
        0,
        // block 1
        654321,
        // block 2
        15,

        // block 3
        0x204,
        0xC8E3,
        // block 4
        0,
        // block 5
        0,
        KEY_1,
        KEY_2,
        KEY_3,
        {
                0x71, 0xFD, 0xA0, 0x55,
                0x00, 0x50, 0xDF, 0x1A
        },
        0
};
// a card created from information collected with 'Director'
const card_info card2 = {
        //unique card ID
        {
                0xE0, 0x04, 0x01, 0x00,
                0x79, 0x2D, 0x0B, 0xA1
        },
        // block 0
        0,
        0,
        0,
        0,
        // block 1
        15,
        // block 2
        123456,

        // block 3
        0x132,
        0x2490,
        // block 4
        0,
        // block 5
        0,
        KEY_1,
        KEY_2,
        KEY_3,
        {
                0xF5, 0x70, 0x6D, 0x99,
                0xC2, 0xD7, 0x0E, 0xDB
        },
        1
};
// a card created from information collected with 'Director'
// with an invalid md5
const card_info card2_invalid = {
        //unique card ID
        {
                0xE0, 0x04, 0x01, 0x00,
                0x79, 0x2D, 0x0B, 0xA1
        },
        // block 0
        0,
        0,
        0,
        0,
        // block 1
        15,
        // block 2
        123456,

        // block 3
        0x132,
        0x2490,
        // block 4
        0,
        // block 5
        0,
        KEY_1,
        KEY_2,
        KEY_3,
        {
                0xF7, 0x70, 0xED, 0xF9,
                0x02, 0x1E, 0x0E, 0xDB
        },
        0
};
// a card created from information collected with 'Director'
const card_info card3 = {
        //unique card ID
        {
                0xE0, 0x04, 0x01, 0x50,
                0x32, 0x85, 0x49, 0xA0
        },
        // block 0
        0,
        1,
        0,
        0,
        // block 1
        2000,
        // block 2
        1184,

        // block 3
        0x17c,
        0x9A2D,
        // block 4
        0,
        // block 5
        0,
        KEY_1,
        KEY_2,
        KEY_3,
        {
                0x48, 0x8F, 0x3B, 0x12,
                0x48, 0xB1, 0xAF, 0xC5
        },
        1
};
// a card created from information collected with 'Director'
// with an invalid md5
const card_info card3_invalid = {
        //unique card ID
        {
                0xE0, 0x04, 0x01, 0x50,
                0x32, 0x85, 0x49, 0xA0
        },
        // block 0
        0,
        0,
        1,
        0,
        // block 1
        2000,
        // block 2
        1184,

        // block 3
        0x17c,
        0x9A2D,
        // block 4
        0,
        // block 5
        0,
        KEY_1,
        KEY_2,
        KEY_3,
        {
                0x48, 0x1F, 0x3B, 0x12,
                0x48, 0xB1, 0xA0, 0xA5
        },
        0
};
const card_info card4 = {
        {
                0xE0, 0x04, 0x01, 0x50,
                0x32, 0x85, 0x49, 0xA0
        },
        0,
        0,
        0,
        0,
        //block 1
        1234,
        4321,
        (uint16_t) Calculator::calcCRC16_added(card4),
        Calculator::calcCRC16_ibm((uint8_t *) &card4.card_type, 12),
        0,
        0,
        KEY_1,
        KEY_2,
        KEY_3,
        {
                0, 0, 0, 0,
                0, 0, 0, 0
        },
        0
};
const card_info card5 = {
        {
                0xE0, 0x04, 0x01, 0x50,
                0x32, 0x85, 0x49, 0xA0
        },
        0,
        0,
        0,
        0,
        //block 1
        1234,
        4322,
        (uint16_t) Calculator::calcCRC16_added(card5),
        Calculator::calcCRC16_ibm((uint8_t *) &card5.card_type, 12),
        0,
        0,
        KEY_1,
        KEY_2,
        KEY_3,
        {
                0, 0, 0, 0,
                0, 0, 0, 0
        },
        0
};



#endif //GUI_TESTCARDS_H
