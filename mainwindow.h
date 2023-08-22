/**
 * mainwindow file includes all packages, widgets, slots and methods of class MainWindow which 
 * defines project interface.
 */
#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QVector>
#include <QListWidget>
#include <QMessageBox>
#include <bits/stdc++.h>
#include "command.h"

/**
 * defining the MainWindow class public and private widgets and slots
 * This class is defined to make the interface of the program.
 */
class MainWindow : public QMainWindow
{
 Q_OBJECT
 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
 
 private slots:
    void handleInput();
    void showPopUp(QListWidgetItem *);

 private:
    MainWindow *ui;
    QPushButton *button;
    QLabel *inputLabel;
    QLineEdit *input;
    QLineEdit *status;
    QLabel *outputLabel;
    QTextEdit *output;
    QLabel *historyLabel;
    std::vector<Command> commandsList;
    QListWidget *historyList;
    QListWidgetItem *newItem;
    QMessageBox msg;
};

#endif // WINDOW_H