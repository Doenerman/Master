#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QCheckBox>
#include <QLabel>
#include "gui_input_output.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // ################# //
    // ##  PushBotton ## //
    // ################# //
    /**
     * @var pbStart
     * The button for starting the writting process
     */
    QPushButton* pbStart = new QPushButton(this);

    int readCardID();
    int readUserID();
    int writeOnConsole();


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


    // ####################### //
    // ##   PlainTextEdit   ## //
    // ####################### //
    /**
      * @var pteUserID
      * The plain text edit field for the user id
      */
    QPlainTextEdit* pteUserID = new QPlainTextEdit(this);
    /**
      * @var pteCardID
      * The plain text edit field for the card id
      */
    QPlainTextEdit* pteCardID = new QPlainTextEdit(this);
    /**
      * @var pteCardAmount
      * The plain text edit field for the amount of cards that
      * should be written
      */
    QPlainTextEdit* pteCardAmount = new QPlainTextEdit(this);
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


};

#endif // MAINWINDOW_H
