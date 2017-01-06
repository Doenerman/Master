#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include <QPlainTextEdit>
#include <QWidget>

#define CONVERSIONCHECK_PASSED 1
#define CONVERSIONCHECK_FAILED_CARDID -1
#define CONVERSIONCHECK_FAILED_USERID -2
#define CONVERSIONCHECK_FAILED_CARDAMOUNT -3

#define ERROR_NOT_IMPLEMENTED -1

class EventHandler : public QObject
{
    Q_OBJECT




public slots:
    static int startWrittingProcess(
                                     int locNr,
                                     int revNr,
                                     int userID,
                                     int cardID,
                                     int cardAmount);
};

#endif // EVENTHANDLER_H
