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

// a fix prefix that have all lines in commun except the first and the last one
#define FIX_PREFIX_ALL_LINES 5
#define FIX_PREFIX_CUSTOMER 14
#define FIX_SUFFIX_CUSTOMER 2
#define FIX_LENGTH_CUSTOMER (FIX_PREFIX_CUSTOMER + FIX_SUFFIX_CUSTOMER)
#define FIX_PREFIX_JOBID 14
#define FIX_SUFFIX_JOBID 2
#define FIX_LENGTH_JOBID (FIX_PREFIX_JOBID + FIX_SUFFIX_JOBID)
#define FIX_PREFIX_USERID 21
#define FIX_SUFFIX_USERID 2
#define FIX_LENGTH_USERID (FIX_PREFIX_USERID + FIX_SUFFIX_USERID)
#define FIX_PREFIX_INITCARDID 30
#define FIX_SUFFIX_INITCARDID 2
#define FIX_LENGTH_INITCARDID (FIX_PREFIX_INITCARDID + FIX_SUFFIX_INITCARDID)
#define FIX_PREFIX_CARDAMOUNT 21
#define FIX_SUFFIX_CARDAMOUNT 1
#define FIX_LENGTH_CARDAMOUNT (FIX_PREFIX_CARDAMOUNT + FIX_SUFFIX_CARDAMOUNT)

// define search tags
#define CORRECT_SEARCH_TAG 1
#define CUSTOMER_TAG 1
#define CUSTOMER_TAG_WORD_LENGTH 5
#define JOBID_TAG 2
#define JOBID_TAG_WORD_LENGTH 5
#define USERID_TAG 3
#define USERID_TAG_WORD_LENGTH 12
#define INITCARDID_TAG 4
#define INITCARDID_TAG_LENGTH 21
#define CARDAMOUNT_TAG 5
#define CARDAMOUNT_TAG_WORD_LENGTH 12

#define SUCC_FOUND_LINE_READ_RESULT 1
#define FAIL_OPEN_FILE -1
#define FAIL_FOUND_LINE -2
#define FAIL_READ_RESULT -3
#define UNKNOWN_SEARCH_TAG -4


#define min(a,b) (a<b? a: b)

/*+
 * \struct Job
 * Includes all neccery Information about the job to write the cards and the
 * log files. The information include the name of the customer and the unique
 * job id so it can be tracked after the writting proccess.
 */
typedef struct {
    QString customer;
    QString jobID;
    QString userID;
    QVector<card_info> cards;
}Job;

class JobFile : public QObject {
    Q_OBJECT

public slots:


public:
    static int findLineReadResult(QString fileName, const int searchTag,
                                  QString* result);
    static int readJobFile(Job* job);
    static int readJobFile(QString fileName, Job* job);
    static int createJobFile(const QString fileName, const Job job);

};

#endif //GUI_JOBFILE_H
