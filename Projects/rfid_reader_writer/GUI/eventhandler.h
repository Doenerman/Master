#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include <iostream>
#include <QPlainTextEdit>
#include <QWidget>
#include <QMessageBox>



#include "src/Calculator.hpp"
#include "src/CardInformation.hpp"

#define CONVERSIONCHECK_PASSED 1
#define CONVERSIONCHECK_FAILED_CARDID -1
#define CONVERSIONCHECK_FAILED_USERID -2
#define CONVERSIONCHECK_FAILED_CARDAMOUNT -3
#define CONVERSIONCHECK_FAILED_CARDTYPE -4
#define CONVERSIONCHECK_FAILED_RECREV -5
#define CONVERSIONCHECK_FAILED_LOCNR -6


#define BOX_COLOR_RED "QPlainTextEdit {background-color: red;}"
#define BOX_COLOR_GREEN "QPlainTextEdit {background-color: green;}"

#define ERROR_NOT_IMPLEMENTED -1
#define WRITTING_SUCCESSFULL 1
#define NO_CARD_LEFT_TO_WRITE 2



class EventHandler : public QObject
{
    Q_OBJECT



public slots:
    static int startWrittingProcess(
                                    const QString cardType,
                                    const QString recRev,
                                    const QString locNr,
                                    const QString userID,
                                    const QString cardID,
                                    const QString amount,
                                    const bool iterate,
                                    QString* const consoleOutput,
                                    QString* const cardsLeft,
                                    QString* const nextCardID);
    static void calculateChecksums(
                                    const QString cardType,
                                    const QString recRev,
                                    const QString locNr,
                                    const QString userID,
                                    const QString cardID,
                                    QString* const crcAdded,
                                    QString* const crcIBM);


private:
    static int convertQStringsToCard(  QString stringCardType,
                                const QString stringRecRev,
                                const QString stringLocNr,
                                const QString stringUserID,
                                const QString stringCardID,
                                card_info* card);




};

#endif // EVENTHANDLER_H
