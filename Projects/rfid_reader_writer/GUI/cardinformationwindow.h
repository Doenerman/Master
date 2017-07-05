#ifndef CARDINFORMATIONWINDOW_H
#define CARDINFORMATIONWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QtSerialPort/QSerialPort>
#include <QPalette>


#include "src/eventhandler.h"
#include "src/Communicator.hpp"
#include "src/Reader.hpp"
#include "src/Tester/TestCards.h"


// ################################### //
// ## Defines for the window layout ## //
// ################################### //
#define LABEL_DEFAULT_WIDTH 150
#define LABEL_DEFAULT_HEIGHT 30
#define LABEL_X_POS_FIRST_COLUMN 20
#define LABEL_X_POS_SECOND_COLUMN 170
#define LABEL_Y_POS_UNIQUEID 30
#define LABEL_Y_POS_LOCNR 100
#define LABEL_Y_POS_REVNR 170
#define LABEL_Y_POS_USERID 240
#define LABEL_Y_POS_CARDID 310
#define LABEL_Y_POS_CHECKADD 380
#define LABEL_Y_POS_CHECKIBM 450
#define LABEL_Y_POS_MD5 520
#define PUSHBUTTON_DEFAULT_WIDTH 150
#define PUSHBOTTON_DEFAULT_HEIGHT 50
#define PUSHBOTTEN_X_REFRESH 50
#define PUSHBOTTON_X_CLOSE 200
#define PUSHBOTTON_Y 600
#define PLAINTEXT_LABEL_PUFFER 25
#define PLAINTEXTEDIT_DEFAULT_WIDTH 150
#define PLAINTEXTEDIT_DEFAULT_HEIGHT 30
#define PLAINTEXTEDIT_X_FIRST_COLUMN LABEL_X_POS_FIRST_COLUMN
#define PLAINTEXTEDIT_X_SECOND_COLUMN LABEL_X_POS_SECOND_COLUMN


class CardInformationWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CardInformationWindow(QWidget *parent = 0);

signals:

private:


    // ########### //
    // ## Label ## //
    // ########### //
    /**
      * @var lUniquecardID
      * QLabel to inform the user that the QPlainTextEdit below shows the
      * unique card ID
      */
    QLabel* lUniquecardID = new QLabel(this);
    /**
      * @var lLocationNumber
      * QLabel to inform the user that the QPLainTextEdit below shows the
      * location number
      */
    QLabel* lLocationNumber = new QLabel(this);
    /**
     * @var lCardType
     * QLabel to inform the user that the QPlainTextEdit below shows the card
     * type
     */
    QLabel* lCardType = new QLabel(this);
    /**
      * @var lRev
      * QLabel to inform the user that the QPlainTextEdit below shows the
      * Revision number
      */
    QLabel* lRev = new QLabel(this);
    /**
      * @var lUserID
      * QLabel to inform the user that the QPlainTextEdit below shows the
      * user ID of the card
      */
    QLabel* lUserID = new QLabel(this);
    /**
      * @var lCardId
      * QLabel to inform the user that the QPLainTextEdit below shows the
      * card ID
      */
    QLabel* lCardID = new QLabel(this);
    /**
      * @var lChecksumAdded
      * QLabel to inform the user that the QPlainTextEdit below shows the
      * added checksum of the card
      */
    QLabel* lChecksumAdded = new QLabel(this);
    /**
      * @var lChecksumIBM
      * QLabel to inform the user that the QPlainTextEdit below shows the
      * IBM checksum
      */
    QLabel* lChecksumIBM = new QLabel(this);
    /**
      * @var lMD5
      * QLabel to inform the user that the QPlainTextEdit below shows the
      * MD5 checksum of the card
      */
    QLabel* lMD5 = new QLabel(this);


    // ################### //
    // ## PlainTextEdit ## //
    // ################### //
    /**
      * @var pteUniquecardID
      * A QPlainTextEdit field for the output of the read unique card ID
      */
    QPlainTextEdit* pteUniquecardID = new QPlainTextEdit(this);
    /**
      * @var pteLocationNumber
      * A QPlainTextEdit field for the output of the read location number
      */
    QPlainTextEdit* pteLocationNumber = new QPlainTextEdit(this);
    /**
     * @var pteCardType
     * A QPlainTextEdit field for the output of the read card type
     */
    QPlainTextEdit* pteCardType = new QPlainTextEdit(this);
    /**
      * @var pteRev
      * A QPlainTextEdit field for the output of the read revision number
      */
    QPlainTextEdit* pteRev = new QPlainTextEdit(this);
    /**
      * @var pteUserID
      * A QPlainTextEdit field for the output of the read user ID
      */
    QPlainTextEdit* pteUserID = new QPlainTextEdit(this);
    /**
      * @var pteCardID
      * A QPlainTextEdit field for the output of the read card ID
      */
    QPlainTextEdit* pteCardID = new QPlainTextEdit(this);
    /**
      * @var pteChecksumAdded
      * A QPlainTextEdit field for the output of the read added Checksum
      */
    QPlainTextEdit* pteChecksumAdded = new QPlainTextEdit(this);
    /**
      * @var pteChecksummIBM
      * A QPLainTextEdit field for the output of the read IBM checksum
      */
    QPlainTextEdit* pteChecksumIBM = new QPlainTextEdit(this);
    /**
      * @var pteMD5
      * A QPlainTextEdit field for the output of the read MD5
      */
    QPlainTextEdit* pteMD5 = new QPlainTextEdit(this);


    // ################ //
    // ## PushButton ## //
    // ################ //
    /**
      * @var pbRefresh
      * The QPushButton that is used to refresh the information this class
      * collects and updates the corresponding QPlainTextEdit fields
      */
    QPushButton* pbRefresh = new QPushButton(this);
    /**
      * @var pbClose
      * The QPushButton that is used to close this window
      */
    QPushButton* pbClose = new QPushButton(this);

private slots:
    void reload();

};

#endif // CARDINFORMATIONWINDOW_H
