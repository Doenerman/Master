#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>

#include "eventhandler.h"
#include "cardinformationwindow.h"

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
    /**
     * @var lPBConsole
     * The label for the plain text edit representing the console
     */
    QLabel* lPBConsole = new QLabel(this);
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



    // ####################### //
    // ##   PlainTextEdit   ## //
    // ####################### //
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

private slots:
    void pushStartButton();
    void pushReadButton();
    void enable_disable_iterativeWrittingInput();

};

#endif // MAINWINDOW_H
