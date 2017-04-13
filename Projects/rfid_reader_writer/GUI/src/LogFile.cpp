//
// Created by utti on 21.03.17.
//
#include "LogFile.h"


void LogFile::getUserLogin(QString *username) {
    *username = QString::fromUtf8("unknown");
#ifdef Q_OS_LINUX
    *username = qgetenv("USER");
#endif
}

void LogFile::writeUser(QTextStream *out) {
    QString user;
    getUserLogin(&user);
    const char sep = 0x22;
    *out << "    " << sep << "Benutzer" << sep << ": "
         << sep << user << sep << "," << endl;
}


/**
 * @brief Writes the given customer name into the given output stream.
 *
 * @param customerName
 * @param out
 */
void LogFile::writeCustomer(const QString customerName, QTextStream* out) {
    const char sep = 0x22;
    *out << "    " << sep << "Kunde" << sep << ": " << sep
         << customerName << sep << "," << endl;
}

void LogFile::writeJobID(const QString jobNr, QTextStream *out) {
    const char sep = 0x22;
    *out << "    " << sep << "Auftragsnummer" << sep << ": "
         << sep << jobNr << sep << "," << endl;
}

void LogFile::writeDate(const QDateTime date, QTextStream *out) {
    const char sep = 0x22;
    *out << "    " << sep << "Datum" << sep << ": "
         << sep << date.toString("yyyy-MM-dd")
         << "T" << date.toString("hh:mm") << sep << "," << endl;
}

void LogFile::writeCards(const QVector<card_info> cards,
                         const QVector<QVector<int>> error,
                         QTextStream* const out) {
    const char sep = 0x22;
    int innerIter, outerIter;
    const int amount = cards.size();
    int last = amount -1;
    *out << "    " << sep << "Karte" << sep << ": [" << endl;

    for(outerIter = 0; outerIter < amount; outerIter++) {
        *out << "         {" << endl;
        *out << "         " << sep << "unique id" << sep << ": "
             << sep;
        for (innerIter = 0; innerIter < MAX_LENGTH_UNIQUE_ID; innerIter++) {
            *out << cards.at(outerIter).uid[innerIter];
        }
        *out << sep << "," << endl;

        *out << "         " << sep << "cardtype" << sep << ": ";
        *out << cards.at(outerIter).card_type << "," << endl;
        *out << "         " << sep << "location number" << sep << ": "
             << cards.at(outerIter).locNr << "," << endl;
        *out << "         " << sep << "user id" << sep << ": "
             << cards.at(outerIter).kunden_nr << "," << endl;
        *out << "         " << sep << "card id" << sep << ": "
             << cards.at(outerIter).card_nr << "," << endl;
        *out << "         " << sep << "crcAdd" << sep << ": "
             << cards.at(outerIter).crc16_added << "," << endl;
        *out << "         " << sep << "md5" << sep << ": ";
        for (innerIter = 0; innerIter < MAX_MD5_LENGTH_IN_BYTE; innerIter++) {
            *out << cards.at(outerIter).md5_arr[innerIter];
        }
        *out << "," << endl;

        bool succ = false;
        *out << "         " << sep << "error" << sep << ": [";
        for (innerIter = 0; ((innerIter < error.at(outerIter).size()) && (!succ));
             innerIter++) {
            *out << error.at(outerIter).at(innerIter);
            if (error[outerIter][innerIter] == WRITTING_SUCCESSFULL) {
                succ = true;
                *out << "]" << endl;
            }
            else if (innerIter < MAX_WRITE_ATTEMPTS - 1) {
                *out << ", ";
            } else {
                *out << endl;
            }
        }
        if(outerIter != last) {
            *out << "        }," << endl;
        }
        else {
            *out << "        }" << endl;
        }

    }
    *out << "         ]" << endl;
}

/**
 * Writes the logfile in case a single card is written.
 * @param customer
 * @param jobID
 * @param card
 * @param errors
 */
void LogFile::writeLogFile(const QString customer,
                           const QString jobID,
                           const QVector<card_info> cards,
                           const QVector<QVector<int>> errors) {

    QDateTime dateTime = QDateTime::currentDateTime();

    /* Try and open a file for output */
    QString outputFilename = "logfile.json";
    QFile outputFile(outputFilename);
    if(outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {


        /* Point a QTextStream object at the file */
        QTextStream outStream(&outputFile);

        /* Write the line to the file */
        outStream << "{" << endl;

        writeUser(&outStream);
        writeCustomer(customer, &outStream);
        writeJobID(jobID, &outStream);
        writeDate(dateTime, &outStream);
        LogFile::writeCards(cards, errors, &outStream);


        outStream << "}";
    }

    /* Close the file */
    outputFile.close();

}

