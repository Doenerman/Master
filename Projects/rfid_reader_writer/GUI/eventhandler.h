#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include <iostream>
#include <QPlainTextEdit>
#include <QWidget>
#include <QMessageBox>
#include <QtCore/QTextStream>




#include "src/Calculator.hpp"
#include "src/CardInformation.hpp"
#include "src/LogFile.h"

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
#define NO_CARD_LEFT_TO_WRITE 2
#define SINGLE_WRITE_PROCESS_NEXT_CARDID 0
#define SINGLE_WRITE_PROCESS_CARD_LEFT_TO_WRITE 0


// used in case there is no real writting process
#define WRITEPROCESS WRITTING_SUCCESSFULL


class EventHandler : public QObject
{
    Q_OBJECT



public slots:
    static int initWrittingProcess(
            const QString cardType,
            const QString recRev,
            const QString locNr,
            const QString userID,
            const QString cardID,
            const QString amount,
            const bool iterate,
            QString *const consoleOutput);
    static void calculateChecksums(
                                    const QString cardType,
                                    const QString recRev,
                                    const QString locNr,
                                    const QString userID,
                                    const QString cardID,
                                    QString* const crcAdded,
                                    QString* const crcIBM);


public:
    static int convertQStringsToCard(  QString stringCardType,
                                const QString stringRecRev,
                                const QString stringLocNr,
                                const QString stringUserID,
                                const QString stringCardID,
                                card_info* card);
private:
    static int writeProcess(const QVector<card_info> card,
                                  const QString customer,
                                  const QString jobID,
                                  QString* const consoleOutput,
                                  QString* const cardsLeft,
                                  QString* const nextCardID);

    static void writeCard(const card_info card,
                         QVector<int>* error);


};



#endif // EVENTHANDLER_H
