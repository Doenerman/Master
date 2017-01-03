#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include <QPlainTextEdit>
#include <QWidget>

#define CONVERSIONCHECK_PASSED 1
#define CONVERSIONCHECK_FAILED_CARDID -1
#define CONVERSIONCHECK_FAILED_USERID -2
#define CONVERSIONCHECK_FAILED_CARDAMOUNT -3

class EventHandler : public QObject
{
    Q_OBJECT




public slots:
    static void startWrittingProcess(QPlainTextEdit* const pte,
                                            QString initCardID,
                                            QString initUserID,
                                            bool iterate,
                                            QString cardAmount);
};

#endif // EVENTHANDLER_H
