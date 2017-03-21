//
// Created by utti on 09.03.17.
//

#ifndef GUI_TESTEVENTHANDLER_H
#define GUI_TESTEVENTHANDLER_H

#include "../CardInformation.hpp"
#include "../../eventhandler.h"
#include "TestCards.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <QString>


// 255 = 2^8  equals the maximal value of an uint_8
// 65535 = 2^16 equals the maximal value of an uint_16
// 4294967296 = 2^32 equals the maximal value of an uint_32
#define CARDTYPE_RANGE 255
#define RECORDREV_RANGE 255
#define LOCNR_RANGE 255
#define USERID_RANGE 4294967296
#define CARDID_RANGE 4294967296

#define AMOUNT_CONVERSION_TESTS 5

static int testStartWrittingProcess();
static int testCalculateChecksums();
static int testConvertQStringsToCard();


#endif //GUI_TESTEVENTHANDLER_H
