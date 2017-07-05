#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QCheckBox>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>

#include "src/eventhandler.h"
#include "src/Writer.h"
#include "src/CardInformation.hpp"
#include "cardinformationwindow.h"
#include "src/GeneralDefines.h"

// ############################## //
// ## Layout depending defines ## //
// ############################## //
#define MAINWINDOW_HEIGHT 650
#define MAINWINDOW_WIDTH 600
#define PUSHBUTTON_MAINWINDOW_WIDTH 200
#define PUSHBUTTON_MAINWINDOW_HEIGHT 50
#define PUSHBUTTON_MAINWINDOW_X_GAP ((MAINWINDOW_WIDTH-2*PUSHBUTTON_MAINWINDOW_WIDTH)/3)
#define PUSHBUTTON_MAINWINDOW_X_START PUSHBUTTON_MAINWINDOW_X_GAP
#define PUSHBUTTON_MAINWINDOW_X_READ (PUSHBUTTON_MAINWINDOW_X_START+PUSHBUTTON_MAINWINDOW_WIDTH+PUSHBUTTON_MAINWINDOW_X_GAP)
#define PUSHBUTTON_MAINWINDOW_X_CLOSE (((MAINWINDOW_WIDTH-PUSHBUTTON_MAINWINDOW_WIDTH)/2))
#define PUSHBUTTON_Y_FIRST_ROW 470
#define PUSHBUTTON_Y_SECOND_ROW 550
#define LABEL_SMALL_WIDTH 100
#define LABEL_LARGE_WIDTH 150
#define LABEL_DEFAULT_HEIGHT 30
#define LABEL_X_FIRST_COLUMN 20
#define LABEL_X_SECOND_COLUMN (LABEL_X_FIRST_COLUMN + LABEL_SMALL_WIDTH)
#define LABEL_GAP 45
#define LABEL_Y_RECREV LABEL_Y_CARDTYPE
#define LABEL_Y_LOCNR (LABEL_Y_CARDTYPE + LABEL_GAP)
#define LABEL_GAP_TO_LINEEDIT_HORIZONTAL 5
#define LINEEDIT_LABEL_Y_GAP 25
#define LINEEDIT_X_FIRST_COLUMN LABEL_X_FIRST_COLUMN
#define LINEEDIT_X_SECOND_COLUMN LABEL_X_SECOND_COLUMN
#define LINEEDIT_Y_RECREV (LABEL_Y_RECREV + LINEEDIT_LABEL_Y_GAP)
#define LINEEDIT_Y_LOCNR (LABEL_Y_LOCNR + LINEEDIT_LABEL_Y_GAP)
#define LINEEDIT_SMALL_WIDTH LABEL_SMALL_WIDTH
#define LINEEDIT_LARGE_WIDTH LABEL_LARGE_WIDTH
#define LINEEDIT_DEFAULT_HEIGHT 30
#define PLAINTEXTEDIT_LABEL_GAP_VERTICAL 25
#define PLAINTEXTEDIT_FIRST_COLUMN_X LABEL_X_FIRST_COLUMN
#define PLAINTEXTEDIT_DEFAULT_HEIGHT 30
#define PLAINTEXTEDIT_DEFAULT_WIDTH 150

#define LABEL_Y_CARDTYPE  210
#define LINEEDIT_Y_CARDTYPE (LABEL_Y_CARDTYPE + LINEEDIT_LABEL_Y_GAP)


#define LINEEDIT_USERID_X LINEEDIT_X_FIRST_COLUMN
#define LINEEDIT_USERID_Y 30
#define LABEL_USERID_X LINEEDIT_USERID_X + LABEL_GAP_TO_LINEEDIT_HORIZONTAL + LINEEDIT_LARGE_WIDTH
#define LABEL_USERID_Y LINEEDIT_USERID_Y

#define LINEEDIT_CARDID_X LINEEDIT_X_FIRST_COLUMN
#define LINEEDIT_CARDID_Y 70
#define LABEL_CARDID_X LINEEDIT_CARDID_X + LABEL_GAP_TO_LINEEDIT_HORIZONTAL + LINEEDIT_LARGE_WIDTH
#define LABEL_CARDID_Y LINEEDIT_CARDID_Y

#define LINEEDIT_JOBID_X 300
#define LINEEDIT_JOBID_Y LINEEDIT_CARDID_Y
#define LABEL_JOBID_X LINEEDIT_JOBID_X + LABEL_GAP_TO_LINEEDIT_HORIZONTAL + LINEEDIT_LARGE_WIDTH
#define LABEL_JOBID_Y LINEEDIT_JOBID_Y

#define CHECKBOX_ITER_X LINEEDIT_X_FIRST_COLUMN
#define CHECKBOX_ITER_Y 150
#define CHECKBOX_WIDTH 100
#define CHECKBOX_HIGHT 30

#define CARDAMOUNT_GAP_X 30
#define LINEEDIT_CARDAMOUNT_X LINEEDIT_X_FIRST_COLUMN + CARDAMOUNT_GAP_X
#define LINEEDIT_CARDAMOUNT_Y 175
#define LINEEDIT_CARDAMOUNT_WIDTH 120
#define LINEEDIT_CARDAMOUNT_HIGHT 30

#define PTE_CHECKSUM_ADD_X PLAINTEXTEDIT_FIRST_COLUMN_X
#define PTE_CHECKSUM_ADD_Y 350
#define LABEL_CHECKSUM_ADD_X PTE_CHECKSUM_ADD_X
#define LABEL_CHECKSUM_ADD_Y PTE_CHECKSUM_ADD_Y - PLAINTEXTEDIT_LABEL_GAP_VERTICAL

#define PTE_CHECKSUM_IBM_X PLAINTEXTEDIT_FIRST_COLUMN_X
#define PTE_CHECKSUM_IBM_Y 400
#define LABEL_CHECKSUM_IBM_X PTE_CHECKSUM_IBM_X
#define LABEL_CHECKSUM_IBM_Y PTE_CHECKSUM_IBM_Y - PLAINTEXTEDIT_LABEL_GAP_VERTICAL

#define LABEL_CONSOLE_X 250
#define LABEL_CONSOLE_Y 110
#define PTE_CONSOLE_X 250
#define PTE_CONSOLE_Y 140
#define PTE_CONSOLE_HIGHT 300
#define PTE_CONSOLE_WIDTH 300

#define LIGHT_BOX_X 500
#define LIGHT_BOX_Y 15
#define LIGHTBOX_HIGHT 50
#define LIGHTBOX_WIDTH LIGHTBOX_HIGHT
#define LIGHTBOX_GREEN 1
#define LIGHTBOX_RED 2



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();



    int readCardID();
    int readUserID();


private:
    // ################ //
    // ##  CheckBox  ## //
    // ################ //
    /**
      * @var cbIterate
      * The checkbox for the option to write a specific amount of cards
      */
    QCheckBox* cbIterate = new QCheckBox(this);


    // ############ //
    // ##  Label ## //
    // ############ //
    /** @var lUserID
     * The label for the lineEdit field representing the user id
     */
     QLabel* lUserID = new QLabel(this);
    /** @var lCardID
     * The label for the lineEdit field representing the cardi id
     */
     QLabel* lCardID = new QLabel(this);
    /**
     * @var lPBConsole
     * The label for the plain text edit representing the console
     */
    QLabel* lPBConsole = new QLabel(this);
    /** @var lCardType
      * The label for the lineEdit field representing the card type
      */
    QLabel* lCardType = new QLabel(this);
    /** @var lJobID
     * The label for the line edit representing the job id
     */
    QLabel* lJobID = new QLabel(this);
    /**
      * @var lRecRev
      * The label for the LineEdit field representing the Record Rev
      */
    QLabel* lRecRev = new QLabel(this);
    /**
      * @var lLocNr
      * The label for the LineEdit field representing the location number
      */
    QLabel* lLocNr = new QLabel(this);
    /**
      * @var lPBChecksumAdded
      * The label for the plain text edit representing the calculated
      * added checksum
      */
    QLabel* lPBChecksumAdded = new QLabel(this);
    /**
      * @var lPBChecksumIBM
      * The label for the plain text edit representing the calculated
      * ibm checksum
      */
    QLabel* lPBChecksumIBM = new QLabel(this);

    // ############## //
    // ## LineEdit ## //
    // ############## //
    /**
      * @var leCardID
      * The line edit field for the user id as input
      */
    QLineEdit* leCardID = new QLineEdit(this);
    /**
      * @var leUserID
      * The line edit field for the user id as input
      */
    QLineEdit* leUserID = new QLineEdit(this);
    /**
      * @var leCardAmount
      * The line edit field for the amount of cards that
      * should be written
      */
    QLineEdit* leCardAmount = new QLineEdit(this);
    /**
      * @var leCardType
      * The line edit field for the card type
      */
    QLineEdit* leCardType = new QLineEdit(this);
    /**
     * @var leJobID
     * The line edit for the job id
     */
    QLineEdit* leJobID = new QLineEdit(this);
    /**
      * @var leRecRev
      * The line edit field for the recRev
      */
    QLineEdit* leRecRev = new QLineEdit(this);
    /**
      * @var leLocNr
      * The line edit field for the location number of the card
      */
    QLineEdit* leLocNr = new QLineEdit(this);

    // ####################### //
    // ##   PlainTextEdit   ## //
    // ####################### //
    /**
      * @var pteLightBox
      * The plain text edit field for the light box that shows the success of
      * the writting process
      */
    QPlainTextEdit* pteLightBox = new QPlainTextEdit(this);
    /**
      * @var pteConsole
      * The plain text edit field for possible output of the programm
      */
    QPlainTextEdit* pteConsole = new QPlainTextEdit(this);
    /**
      * @var pteChecksumAdded
      * The plain text edit field for the calculated added checksum
      */
    QPlainTextEdit* pteChecksumAdded = new QPlainTextEdit(this);
    /**
      * @var pteChecksumIBM
      * The plain text edit field for the calculated IBM checksum
      */
    QPlainTextEdit* pteChecksumIBM = new QPlainTextEdit(this);

    // ################# //
    // ##  PushBotton ## //
    // ################# //
    /**
     * @var pbStart
     * The button for starting the writting process
     */
    QPushButton* pbStart = new QPushButton(this);
    /**
      * @var pbRead
      * The button for opening a new window that shows the card information
      */
    QPushButton* pbRead = new QPushButton(this);
    /**
      * @var pbClose
      * The button that closes the programm
      */
    QPushButton* pbClose = new QPushButton(this);

public slots:
 static void conversionErrorWindow(const int conversionErrorNumber);
public:
    void printOutputConsole(QString output);
    void setLightBoxColor(int color);
private slots:
    void pushStartButton();
    void pushStartButton2();
    void pushReadButton();
    void enable_disable_iterativeWrittingInput();
    void updateChecksums();
//    QString selectFileNameDialog();

};

#endif // MAINWINDOW_H
