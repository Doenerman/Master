#include "eventhandler.h"
#include <stdlib.h>
#include <iostream>

/**
 * @brief This method starts the writting process.
 * @param pte   pointer to the QPlainTextEdit where possible notifications
 *              can be printed
 *
 * @todo implement the connection to the background programm
 */
void EventHandler::startWrittingProcess(QPlainTextEdit* const pte,
                                        QString initCardID,
                                        QString initUserID,
                                        bool iterate,
                                        QString cardAmount) {
    bool cardConversion, userConversion, cardAmountConversion;
    const int cardID = initCardID.toInt(&cardConversion, 10);
    std::cout << cardID << " " << cardConversion << std::endl;
    const int userID = initUserID.toInt(&userConversion);
    std::cout << userID << std::endl;
    int cards = 0;
    int conversionCheckPassed = CONVERSIONCHECK_PASSED;
    if(iterate) {
        cards = cardAmount.toInt(&cardAmountConversion);
    }
    else {
        cards = 1;
    }


    // conversion check
    if( !cardConversion ) {
        conversionCheckPassed = CONVERSIONCHECK_FAILED_CARDID;
    }
    if( !userConversion ) {
        conversionCheckPassed = CONVERSIONCHECK_FAILED_USERID;
    }
    if(0 != (iterate) && (!cardAmountConversion)) {
        conversionCheckPassed = CONVERSIONCHECK_FAILED_CARDAMOUNT;
    }

    std::cout << conversionCheckPassed << std::endl;



    // Output if conversion passed succesfull
    if(conversionCheckPassed == CONVERSIONCHECK_PASSED) {
        // Output for the inital user ID
        pte->appendPlainText(QString::fromUtf8("Initiale Kunden Nummer: "));
        pte->moveCursor(QTextCursor::End);
        pte->insertPlainText(QString::number(userID));
        pte->moveCursor(QTextCursor::End);

        // Output for the initial card ID
        pte->appendPlainText(QString::fromUtf8("Initiale Karten Nummer: "));
        pte->moveCursor(QTextCursor::End);
        pte->insertPlainText(QString::number(cardID));
        pte->moveCursor(QTextCursor::End);

        // Output for the amount of cards that should be written
        pte->appendPlainText(QString::fromUtf8("Anzahl an zu schreibenden Karten: "));
        pte->moveCursor(QTextCursor::End);
        pte->insertPlainText(QString::number(cards));
        pte->moveCursor(QTextCursor::End);
    }
    // Output if conversion failedg
    else {
        switch(conversionCheckPassed) {
        case CONVERSIONCHECK_FAILED_CARDID:
            pte->appendPlainText(QString::fromUtf8("Fehler:"));
            pte->appendPlainText(QString::fromUtf8("  Die Kartennummer ist keine ganze Zahl"));
            break;
        case CONVERSIONCHECK_FAILED_USERID:
            pte->appendPlainText(QString::fromUtf8("Fehler:"));
            pte->appendPlainText(QString::fromUtf8("  Die Kundennummer ist keine ganze Zahl"));
            break;
        case CONVERSIONCHECK_FAILED_CARDAMOUNT:
            pte->appendPlainText(QString::fromUtf8("Fehler:"));
            pte->appendPlainText(QString::fromUtf8("  Die Anzahl an zu schreibenden Karten"
                                                   " ist keine ganze Zahl"));
            break;
        default:
            pte->appendPlainText(QString::fromUtf8("Something unexpected happend"
                                                   "while reading the input data"));
        }
    }





    pte->appendPlainText(QString::fromUtf8("So nicht!"));
}

