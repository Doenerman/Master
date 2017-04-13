//
// Created by utti on 21.03.17.
//

#ifndef GUI_LOGFILE_H
#define GUI_LOGFILE_H

#include <QString>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QDir>
#include <QDateTime>
#include <QVector>

#include "CardInformation.hpp"

#define MAX_WRITE_ATTEMPTS 3
#define WRITTING_SUCCESSFULL 1

class LogFile : public QObject {
Q_OBJECT

public:
    static void getUserLogin(QString *username);
    static void writeUser(QTextStream* out);
    static void writeCustomer(const QString customerName, QTextStream* out);
    static void writeJobID(const QString jobNr, QTextStream *out);
    static void writeDate(const QDateTime date, QTextStream* out);
    static void writeCards(const QVector<card_info> card,
                          const QVector<QVector<int>> error,
                          QTextStream* const out);
    static void writeLogFile
            (const QString customer,
             const QString jobID,
             const QVector<card_info> cards,
             const QVector<QVector<int>> errors);
};

#endif //GUI_LOGFILE_H
