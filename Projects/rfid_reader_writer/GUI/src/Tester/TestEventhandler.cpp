//
// Created by utti on 09.03.17.
//

#include "TestEventhandler.h"
#include "../CardInformation.hpp"


int main(int argc, char* argv[]) {

    std::cout << std::endl;
    std::cout <<"   Test EventHandler" << std::endl;
    std::cout <<"startWrittingProcess:  " << testStartWrittingProcess() << std::endl;
    std::cout <<"calculateChecksum:     " << testCalculateChecksums() << std::endl;
    std::cout <<"convertQStringToCard:  " << testConvertQStringsToCard() << std::endl;
    return 0;
}

int testStartWrittingProcess(){
    return 0;
}

/**
 * @brief Tests the function \link EventHandler::calculateChecksums \endnlink .
 *
 * The test reads information from \link TESTCARD \endlink and calculates
 * the checksums. The results are compared to the checksums written on the
 * card. The test is passed iff both calculated checksums fit the sums
 * written on the card.
 *
 * @return 1 iff the calculated checksums fit the checksums on the card
 */
int testCalculateChecksums() {

    bool add = true;
    bool ibm = true;

    // information of the card
    QString cardType, recRev, locNr, userID, cardID, crcAdded, crcIBM;
    cardType.setNum(TESTCARD.card_type,10);
    recRev.setNum(TESTCARD.record_rev,10);
    locNr.setNum(TESTCARD.locNr,10);
    userID.setNum(TESTCARD.kunden_nr,10);
    cardID.setNum(TESTCARD.card_nr,10);




    EventHandler::calculateChecksums(cardType,recRev,locNr,userID,cardID,
                                     &crcAdded,&crcIBM);

    bool temp1, temp2;
    int intCrcAdd = crcAdded.toInt(&temp1,10);
    int intCrcIbm = crcIBM.toInt(&temp2,10);


    if( intCrcAdd != TESTCARD.crc16_added ){
        add = false;
        std::cout << "  correct Added checksum:    " << TESTCARD.crc16_added << std::endl;
        std::cout << "  calculated Added checksum: " << intCrcAdd << std::endl;

    }
    if( intCrcIbm != TESTCARD.crc16_ibm ){
        ibm = false;
        std::cout << "  correct IBM checksum:    " << TESTCARD.crc16_ibm << std::endl;
        std::cout << "  calculated IBM checksum: " << intCrcIbm << std::endl;

    }

    return (add && ibm);
}

/**
 * @brief Test the conversion from QStrings of cardinformations to
 * a \link card_info \endlink in the method \link convertQStringsToCard \endlink .
 *
 * The test generates random numbers for the input of \link convertQStringToCard \endlink .
 * The range of the different numbers are fixed in \link TestEventhandler.h \endlink .
 * If the converted values do not fit the correct ones there
 * is a print on the console that
 * inform about the correct and the converted values.
 * @return true if and only if the function passed the test
 */
int testConvertQStringsToCard(){

    uint8_t cardType, recRev, locNr;
    uint32_t userID, cardID;
    card_info convertedCard;
    QString stringCardType, stringRecRev, stringLocNr, stringUserID, stringCardID;
    int succTests = 0;

    srand((unsigned int) time(NULL));

    // Generate random input for the test card. The card may not be valid.
    cardType = (uint8_t)(rand() % CARDTYPE_RANGE);
    recRev = (uint8_t)(rand() % RECORDREV_RANGE);
    locNr = (uint8_t)(rand() % LOCNR_RANGE);
    userID = (uint8_t)(rand() % USERID_RANGE);
    cardID = (uint8_t)(rand() % CARDID_RANGE);

    stringCardType.setNum(cardType, 10);
    stringRecRev.setNum(recRev, 10);
    stringLocNr.setNum(locNr, 10);
    stringUserID.setNum(userID, 10);
    stringCardID.setNum(cardID, 10);

    EventHandler::convertQStringsToCard(stringCardType,
                                        stringRecRev,
                                        stringLocNr,
                                        stringUserID,
                                        stringCardID,
                                        &convertedCard);


    // Check calculated values with correct ones
    if (convertedCard.card_type == cardType) {
      succTests++;
    }
    else {
        std::cout <<"correct CardType:      " << cardType << std::endl;
        std::cout <<"converted cardType:    " << convertedCard.card_type << std::endl;
    }
    if( convertedCard.record_rev == recRev) {
        succTests++;
    }
    else {
        std::cout <<"correct RecRev:        " << recRev << std::endl;
        std::cout <<"converted RecRev:      " << convertedCard.record_rev << std::endl;
    }
    if( convertedCard.locNr == locNr) {
        succTests++;
    }
    else {
        std::cout <<"correct locNr:         " << locNr << std::endl;
        std::cout <<"converted locNr:       " << convertedCard.locNr << std::endl;
    }
    if( convertedCard.kunden_nr == userID ) {
        succTests++;
    }
    else {
        std::cout << "correct userID:        " << userID << std::endl;
        std::cout << "converted userID:      " << convertedCard.kunden_nr;
    }
    if (convertedCard.card_nr == cardID) {
        succTests++;
    }
    else {
        std::cout << "correct cardID:         " << cardID << std::endl;
        std::cout << "converted cardID:       " << convertedCard.card_nr << std::endl;
    }
    return succTests == AMOUNT_CONVERSION_TESTS;
}
