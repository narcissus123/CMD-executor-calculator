/**
 * MainWindow class is supposed to define the interface of the program.
 * The QT library is used for this purpose.
 */
#include "mainwindow.h"
#include "command.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
 QMainWindow(parent) 
 {

    MainWindow::setWindowTitle("CommandGUI");             //setting the title for the main window of our application
    MainWindow::resize(390, 680);                         //set the size for the mainwindow of our application

    button = new QPushButton("execute", this);            //defining the execute button. It will send signal after user clicked it
    button->setGeometry(290, 20, 90, 33);                 //set the size and position of button in main window
    button->setStyleSheet("QPushButton{font-size: 14px;font-family: Arial;color: rgb(255, 255, 255);background-color: rgb(38,56,76);border-radius: 5%;}");
 
    inputLabel = new QLabel("Command:", this);            //defining the label to indicate what user suppose to eneter
    inputLabel->setGeometry(10, 20, 85, 33);              //set the size and position of "command" label in main window
    inputLabel->setStyleSheet("QLabel{font-size: 17px;font-family: Arial;color: rgb(38,56,76);}");

    input = new QLineEdit(this);                          //defining the widget where the user can enter the input (command)
    input->setAlignment(Qt::AlignLeft);              
    input->setGeometry(95, 20, 200, 33);                  //set the size and position of input widget in main window
    input->setStyleSheet("QLineEdit{font-size: 17px;font-family: Arial;color: rgb(38,56,76);border-radius: 2%;}");

    outputLabel = new QLabel("Output", this);             //defining the output label to indicate where the result of command execution will be shown
    outputLabel->setGeometry(15, 58, 85, 33);             //set the size and position of "output" label in main window
    outputLabel->setStyleSheet("QLabel{font-size: 17px;font-family: Arial;color: rgb(38,56,76);}");

    output = new QTextEdit(this);                         //defining the widget where the result of command execution will be outputed
    output->setReadOnly(true);                            //we set the widget to readOnly because we do not want the user change the result
    output->setOverwriteMode(true);                       //each time the output will be overwritten by the previous one
    output->setGeometry(10, 90, 370, 230);                //set the size and position of output widget in main window
    output->setStyleSheet("QTextEdit{font-size: 17px;font-family: Arial;color: rgb(38,56,76);border: 1px solid #ccc;}");

    QLabel *statusLabel = new QLabel("Exit status:", this);
    statusLabel->setGeometry(15, 335, 100, 33);
    statusLabel->setStyleSheet("QLabel{font-size: 17px;font-family: Arial;color: rgb(38,56,76);border: none; border-bottom: 1px solid red;}");

    status = new QLineEdit(this);                         //defining the widget where we inform user if the command execution succeeded or failed
    status->setReadOnly(true);                            //we do not want the user change the status result
    status->setText("Exit status: 0");                    //by default before executing the command this value is set to zero.
    status->setGeometry(15, 335, 360, 33);                //set the size and position of status widget in main window
    status->setStyleSheet("QLineEdit{font-size: 17px;font-family: Arial;color: rgb(38,56,76);background-color: rgb(240, 240, 240);border: none; border-bottom: 1px solid #ccc;}");

    historyLabel = new QLabel("History", this);           
    historyLabel->setGeometry(15, 380, 85, 33);           //set the size and position of history label in main window
    historyLabel->setStyleSheet("QLabel{font-size: 17px;font-family: Arial;color: rgb(38,56,76);}");

    //history = new QTextEdit(this);                        //defining the widget where the user can see the history of entered commands
    //history->setReadOnly(true);                           //user should not be able to edit the command history. It can only choose it to see the history in pop-up window
    //history->setGeometry(10, 410, 370, 250);              //set the size and position of history widget in main window
    //history->setStyleSheet("QTextEdit{font-size: 17px;font-family: Arial;color: rgb(38,56,76);border: 1px solid #ccc;}");

    historyList = new QListWidget(this);                         //defining the widget where the user can see the history of entered commands
    historyList->setGeometry(10, 410, 370, 250);                 //set the size and position of history widget in main window
    historyList->setStyleSheet("QListWidget{font-size: 17px;font-family: Arial;color: rgb(38,56,76);border: 1px solid #ccc;}");
    connect(button, SIGNAL(clicked()), this, SLOT(handleInput()));   //whenever the execute button is clicked by user, the custom defined LSOT will be called. 
    connect(historyList, SIGNAL(itemPressed(QListWidgetItem *)), this, SLOT(showPopUp(QListWidgetItem *)));   //when the user clickes on one of the items in command list history history, showPopUp() will be executed
 
 }

 

/**
 * this method will perform following steps:
 * get user input from input widget and send it to executeCommand() of Command object
 * sending the result to output widget and save the comm in history widget
 */
 void MainWindow::handleInput(){                                 
    Command comm;                                                 //defining the object of type Command
    std::string userInput = input->text().toStdString();          //getting the user command from input widget
    comm.setCommand(userInput);                                   //setting the commandText attribute of command class
    
    std::string stat = std::to_string(comm.getReturnCode());      //converting the command execution status (returnCode attribute) from integer to string
    status->setText(QString::fromStdString(stat));                //setting the status widget to 0 (successful) or -1 (error)

    std::string result = comm.executeCommand();                   //call the executeCommand() from command class to execute the command that user entered in terminal and save the output in result
    output->setText(QString::fromStdString(result));              //set the result of command execution to output widget

    commandsList.push_back(comm);                                 //adding the comm object to std::vector
    historyList->clear();
    for(int i=0; i < (int)commandsList.size(); i++){              //initialize out QListWidget with values in commandsList vector
        newItem = new QListWidgetItem(historyList);               
        newItem->setText(QString::fromStdString(commandsList[i].getCommand()));  //initializing history list items with user command
    }
}

/**
 * This method will be executed when the user clickes on one of the items in command list history history. 
 * it finds the target command in vector and pop-ups the result of execution of that command in the past.
 * @ param item that is clicked on the list
 */
void MainWindow::showPopUp(QListWidgetItem *)
{
    int ind = historyList->row(historyList->currentItem());                    //getting the index of item in historyList that is clicked
    QString message = QString::fromStdString(commandsList[ind].getResult());   //looking for the execution result of command in commandsList vector at index ind
    msg.setText(message);                                                      //set the QMessageBox widget to the result
    msg.exec();
}

MainWindow::~MainWindow() {                                                    //delete the ui in the destructor
    delete ui;
}

 