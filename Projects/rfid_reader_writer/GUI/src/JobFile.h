//
// Created by utti on 25.03.17.
//

#ifndef GUI_JOBFILE_H
#define GUI_JOBFILE_H

#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QVector>
#include <QString>
#include "Calculator.hpp"

#define FIX_PREFIX_CUSTOMER 15
#define FIX_SUFFIX_CUSTOMER 1
#define FIX_LENGTH_CUSTOMER (FIX_PREFIX_CUSTOMER + FIX_SUFFIX_CUSTOMER)
#define FIX_PREFIX_JOBID 15
#define FIX_SUFFIX_JOBID 1
#define FIX_LENGTH_JOBID (FIX_PREFIX_JOBID + FIX_SUFFIX_JOBID)
#define FIX_PREFIX_USERID 22
#define FIX_SUFFIX_USERID 1
#define FIX_LENGTH_USERID (FIX_PREFIX_USERID + FIX_SUFFIX_USERID)
#define FIX_PREFIX_INITCARDID 29
#define FIX_SUFFIX_INITCARDID 2
#define FIX_LENGTH_INITCARDID (FIX_PREFIX_INITCARDID + FIX_SUFFIX_INITCARDID)
#define FIX_PREFIX_CARDAMOUNT 21
#define FIX_SUFFIX_CARDAMOUNT 1
#define FIX_LENGTH_CARDAMOUNT (FIX_PREFIX_CARDAMOUNT + FIX_SUFFIX_CARDAMOUNT)

/*+
 * \struct Job
 * Includes all neccery Information about the job to write the cards and the
 * log files. The information include the name of the customer and the unique
 * job id so it can be tracked after the writting proccess.
 */
typedef struct {
    QString customer;
    QString jobID;
    QVector<card_info> cards;
}Job;

class JobFile : public QObject {
    Q_OBJECT

public slots:
//    static void setJobFile(QFile file);


public:
    static int readJobFile(Job* job);
    static int readJobFile(QString fileName, Job* job);

};

#endif //GUI_JOBFILE_H
