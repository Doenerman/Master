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
#include "CardInformation.hpp"
#include "GeneralDefines.h"

// a fix prefix that have all lines in commun except the first and the last one
/**
 * \def FIX_PREFIX_ALL_LINES
 * The fix amount of character all lines have in case they are neither the
 * first nor the last line in the jobfile.
 */
#define FIX_PREFIX_ALL_LINES 5
/**
 * \def FIX_PREFIX_CUSTOMER
 * The fix amount of character before the result of the customer line. These
 * character are in general '    "Kunde": "'.
 */
#define FIX_PREFIX_CUSTOMER 14
/**
 * \def FIX_SUFFIX_CUSTOMER
 * The fix amount of character after the result of the customer line. The
 * character are in general '",'
 */
#define FIX_SUFFIX_CUSTOMER 2
/**
 * \def FIX_PREFIX_JOBID
 * The fix amount of character before the result of the job id line. These
 * character are in general '    "JobID": "'
 */
#define FIX_PREFIX_JOBID 14
/**
 * \def FIX_SUFFIX_JOBID
 * The fix amount of character after the result of the job id line. These
 * character are in general '",'
 */
#define FIX_SUFFIX_JOBID 2
/**
 * \def FIX_PREFIX_USERID
 * The fix amount of character before the result of the user id line. These
 * character are in general '     "Kundennummer": "'
 */
#define FIX_PREFIX_USERID 21
/**
 * \def FIX_SUFFIX_USERID
 * The fix amount of character after the result of the user id line. These
 * character are in general '",'
 */
#define FIX_SUFFIX_USERID 2
/**
 * \def FIX_PREFIX_INITCARDID
 * The fix amount of character before the result of the initial card id line.
 * These character are in general '    "Initiale Kundennummer": "'
 */
#define FIX_PREFIX_INITCARDID 30
/**
 * \def FIX_SUFFIX_INITCARDID
 * The fix amount of character after the result of the initial card id lind.
 * The character are in general '",'
 */
#define FIX_SUFFIX_INITCARDID 2
/**
 * \def FIX_PREFIX_CARDAMOUNT
 * The fix amount of character before the result of the card amount line.
 * These character are in general '    "Kartenanzahl": "'
 */
#define FIX_PREFIX_CARDAMOUNT 21
/**
 * \def FIX_SUFFIX_CARDAMOUNT
 * The fix amount of character after the result of the card amount line.
 * These character are in general '"'
 */
#define FIX_SUFFIX_CARDAMOUNT 1

/**
 * \def CORRECT_SEARCH_TAG
 * The return value in case a given search tag fits the one of the predefined
 * in the function \link gitInfoFromSearchTag() \endlink .
 */
#define CORRECT_SEARCH_TAG 1
/**
 * \def CUSTOMER_TAG
 * One of the predefined search tags the method \link getInfoFromSearchTag
 * \endlink uses. This tag represents a search for the customer name.
 */
#define CUSTOMER_TAG 1
/**
 * \def CUSTOMER_TAG_WORD_LENGTH
 * The length of the word that represents the search tag \link CUSTOMER_TAG
 * \endlink so it is the length of the word 'Kunde'.
 */
#define CUSTOMER_TAG_WORD_LENGTH 5
/**
 * \def JOBID_TAG
 * One of the predefined search tags the method \link getInfoFromSearchTag
 * \endlink uses. This tag represents a search for the job id.
 */
#define JOBID_TAG 2
/**
 * \def JOBID_TAG_WORD_LENGTH
 * The length of the word that represents the seach tag \link JOBID_TAG \endlink
 * so it is the length of the word 'JobID'.
 */
#define JOBID_TAG_WORD_LENGTH 5
/**
 * \def USERID_TAG
 * One of the predefined search tags of the method \link getInfoFromSearchTag
 * \endlink uses. This tag represents the search for the user id.
 */
#define USERID_TAG 3
/**
 * \def USERID_TAG_WORD_LENGTH
 * The length of the word that represents the search tag \link USERID_TAG
 * \endlink so it is the length of the word 'Kundennummer'
 */
#define USERID_TAG_WORD_LENGTH 12
/**
 * \def INITCARDID_TAG
 * One of the predefined search tags of the method \link getInfoFromSearchTag
 * \endlink uses. This tag represents the search for the initial card id.
 */
#define INITCARDID_TAG 4
/**
 * \def INITCARDID_TAG_LENGTH
 * The length of the word that represents the search tag \link INITCARDID_TAG
 * \endlink so it is the length of the word 'Initiale Kartennummer'
 */
#define INITCARDID_TAG_LENGTH 21
/**
 * \def CARDAMOUNT_TAG
 * One of the predefined search tags of the method \link getInfoFromSearchTag
 * \endlink uses. This tag represents the search for the amount of cards.
 */
#define CARDAMOUNT_TAG 5
/**
 * \def CARDAMOUNT_TAG_WORD_LENGTH
 * The length of the word that represents the search tag \link CARDAMOUNT_TAG
 * \endlink so it is the length of the word 'Kartenanzahl'
 */
#define CARDAMOUNT_TAG_WORD_LENGTH 12


/**
 * \def JOBCREATION_SUCC
 * The method was able to create a job with the given input parameter. This
 * means that no conversion error appeared and the given job information were
 * valid.
 */
#define JOBCREATION_SUCC 1
/**
 * \def INVALID_JOB_NO_CARDS
 * The return value of the in case a method like \link JobFile::createJobFile
 * \endlink gets a job that does not include any card that should be written
 */
#define INVALID_JOB_NO_CARDS -10


/**
 * \def SUCC_FOUND_LINE_READ_RESULT
 * The return value in case the method \link JobFile::findLineReadResult
 * \endlink successfully found a line specified by a search tag and read the
 * corresponding result. In case the methods \link JobFile::readJobFile
 * (QString, Job*) \endlink or \link JobFile::readJobFile(Job*) \endlink
 * return this value it means that all information from the jobfile were found
 * and read.
 */
#define SUCC_FOUND_LINE_READ_RESULT 1
/**
 * \def FAIL_OPEN_FILE
 * The return value in case a method is not able to open a file for read or
 * write
 */
#define FAIL_OPEN_FILE -1
/**
 * \def FAIL_FOUND_LINE
 * The return value of \link JobFile::findLineReadResult \endlink in case
 * the line corresponding to the search tag given to the function was not found
 */
#define FAIL_FOUND_LINE -2
/**
 * \def FAIL_READ_RESULT
 * The return value of \link JobFile::findLineReadResult \endlink in case the
 * length of the result is 0, which means that there is not entry for the
 * result is empty
 */
#define FAIL_READ_RESULT -3
/**
 * \def UNKNOWN_SEARCH_TAG
 * The return value of \link getInfoFromSearchtag() \endlink in case the search
 * tag given to the function does not fit one of the predefined ones
 */
#define UNKNOWN_SEARCH_TAG -4

/**
 * \def JOBFILE_WRITTEN
 * The return value of the function \link JobFile::createJobFile \endlink in
 * case the method successfully wrote a the job file
 */
#define JOBFILE_WRITTEN 1


#define min(a,b) (a<b? a: b)

/*+
 * \struct Job
 * Includes all neccery Information about the job to write the cards and the
 * log files. The information include the name of the customer and the unique
 * job id so it can be tracked after the writting proccess.
 */
typedef struct {
    /**
     * @var customer
     * The QString where the customer name of the this job is stored in
     */
    QString customer;
    /**
     * @var jobID
     * The QString where the job id of this job is stored in
     */
    QString jobID;
    /**
     * @var cards
     * @brief A vector of the cards the belong to the job.
     *
     * The cards have all the same user id and have continuous card id.
     */
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
    static int createJob(const QString customer, const QString jobID,
                         const QString cardType,
                         const QString recRev, const QString locNr,
                         const QString userID, const QString initCardID,
                         const QString cardAmount, Job* job);
    static int createJobFile(const QString fileName, const Job job);

};

#endif //GUI_JOBFILE_H
