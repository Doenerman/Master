#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QCheckBox>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void readCardID();
    void readUserID();


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


    // ################### //
    // ##  TextBrowser  ## //
    // ################### //
    /**
      * @var tbConsole
      * The text browser for information that are given during the
      * process
      */
    QTextBrowser* tbConsole = new QTextBrowser(this);
    /**
      * @var tbChecksumAdded
      * The text browser for the added checksum of the above given
      * information or the added checksum of the given card.
      */
    QTextBrowser* tbChecksumAdded = new QTextBrowser(this);
    /**
      * @var tbChecksumIBM
      * The text browser for the added checksum of the above given
      * information or the ibm checksum of the given card.
      */
    QTextBrowser* tbChecksumIBM = new QTextBrowser(this);


    // ################ //
    // ##  CheckBox  ## //
    // ################ //
    /**
      * @var cbIterate
      * The checkbox for the option to write a specific amount of cards
      */
    QCheckBox* cbIterate = new QCheckBox(this);

    // ################# //
    // ##  PushBotton ## //
    // ################# //
    /**
     * @var pbStart
     * The button for starting the writting process
     */
    QPushButton* pbStart = new QPushButton(this);

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

};

#endif // MAINWINDOW_H
