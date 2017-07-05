#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include <iostream>
#include <QPlainTextEdit>
#include <QWidget>
#include <QMessageBox>
#include <QtCore/QTextStream>



#include "../mainwindow.h"
#include "GeneralDefines.h"
#include "Calculator.hpp"
#include "CardInformation.hpp"
#include "LogFile.h"
#include "JobFile.h"
#include "Tester/TestCards.h"

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
#define WRITEPROCESS WRITING_SUCCESSFULL

#define CORRECTNESS_ERROR_AMOUNT 3
#define CRCADD_ERROR 0
#define CRCIBM_ERROR 1
#define MD5SUM_ERROR 2

#define CRCADD_ERROR_POS 0
#define CRCIBM_ERROR_POS 1
#define MD5SUM_ERROR_POS 2

#define NO_CHECKSUM_ERROR 0
#define CHECKSUM_ERROR -1

class EventHandler : public QObject
{
    Q_OBJECT



public slots:
    static int initWrittingProcess(
            const QString jobID,
            const QString cardType,
            const QString recRev,
            const QString locNr,
            const QString userID,
            const QString cardID,
            const QString amount,
            const bool iterate,
            QString *const consoleOutput);
    static int calculateChecksums(
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
    static void tempWrite(
        const QString cardType,
        const QString recRev,
        const QString locNr,
        const QString userID,
        const QString cardID);
    static bool checkCardCorrectness(const card_info card, 
                                  QVector<int>* results);
private:
    static int writeProcess(const Job job,
                            QString* const consoleOutput,
                            QString* const cardsLeft,
                            QString* const nextCardID);

    static int writeCard(const card_info card,
                         QVector<int>* error);


};



#endif // EVENTHANDLER_H
