#include "eventhandler.h"

/**
 * @brief This method starts the writting process.
 *
 * It converts the QStrings into integer and checks whether the given QStrings
 * can be converted to integers. If the QStrings can not be converted to Integer
 * A notification is printed to the QPlainTextEdit field. If the conversion
 * is done successful given Information about the different IDs and the amount
 * of cards that should be written is printed in the given QPLainTextEdit field.
 *
 * @param pte   pointer to the QPlainTextEdit where possible notifications
 *              can be printed
 * @return  1 iff and only if no error occured.Iff an error occured the
 *          the corresponding error code is returned
 *
 * @todo implement the connection to the background programm
 */
int EventHandler::startWrittingProcess(int locNr,
                                        int revNr,
                                        int userID,
                                        int cardID,
                                        int cardAmount) {

    return ERROR_NOT_IMPLEMENTED;
}

