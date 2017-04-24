//
// Created by utti on 07.04.17.
//

#ifndef GUI_GENERALDEFINES_H
#define GUI_GENERALDEFINES_H


/**
 * \def CONVERSION_SUCC
 * The method  was able to convert the
 * QString cardType, QString recRev, QString locNr,QString userID, QString
 * initCardID and QString cardAmount to the respective integer value
 */
#define CONVERSION_SUCC 1
/**
 * \def NO_CONVERSION_ERROR_YET
 * The method was able to convert the given QSTrings to the respective
 * integer values until this moment
 */
#define NO_CONVERSION_ERROR_YET 0
/**
 * \def INITCARDID_CONVERSION_FAILED
 * The method was not able to convert the
 * QString initCardID to the respective integer value
 */
#define INITCARDID_CONVERSION_FAILED -100
/**
 * \def CARDAMOUNT_CONVERSION_FAILED
 * The method was not able to convert the
 * QString cardAmount the respective integer value
 */
#define CARDAMOUNT_CONVERSION_FAILED -1000
/**
 * \def USERID_CONVERSION_FAILED
 * The method was not able to convert the
 * QString userID to the respective integer value
 */
#define USERID_CONVERSION_FAILED -10000
/**
 * \def CARDTYPE_CONVERSION_FAILED
 * The method was not able to convert the
 * QString cardType to the respective integer value
 */
#define CARDTYPE_CONVERSION_FAILED -100000
/**
 * \def RECREV_CONVERSION_FAILED
 * The method was not able to convert the
 * QString recRev to the respective integer value
 */
#define RECREV_CONVERSION_FAILED -1000000
/**
 * \def LOCNR_CONVERSION_FAILED
 * The method was not able to convert the
 * QString locNr to the respective integer value
 */
#define LOCNR_CONVERSION_FAILED -10000000
/**
 * \def JOBID_EMPTY
 * The given job id is empty and thus not valid
 */
#define JOBID_EMPTY -100000000


/**
 * \def MAX_WRITE_ATTEMPTS
 * @brief The maximum amount of attempts the write something on the card.
 */
#define MAX_WRITE_ATTEMPTS 3
/**
 * \def WRITTING_SUCCESSFULL
 * @brief The value in case the attempt of writing something on a card was
 *        successful
 */
#define WRITING_SUCCESSFULL 1

#endif //GUI_GENERALDEFINES_H
