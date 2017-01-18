#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include <QPlainTextEdit>
#include <QWidget>

#include "src/Calculator.hpp"
#include "src/CardInformation.hpp"

#define CONVERSIONCHECK_PASSED 1
#define CONVERSIONCHECK_FAILED_CARDID -1
#define CONVERSIONCHECK_FAILED_USERID -2
#define CONVERSIONCHECK_FAILED_CARDAMOUNT -3

#define ERROR_NOT_IMPLEMENTED -1
#define WRITTING_SECCESSFULL 1

class EventHandler : public QObject
{
    Q_OBJECT




public slots:
    static int startWrittingProcess(
                                    QString userID,
                                    QString cardID,
                                    QString* const consoleOutput,
                                    QString* const cardsLeft,
                                    QString* const nextCardID);
    static void calculateChecksums(
                                    QString cardType,
                                    QString recRev,
                                    QString locNr,
                                    QString userID,
                                    QString cardID,
                                    QString* const crcAdded,
                                    QString* const crcIBM);
};

#endif // EVENTHANDLER_H
