#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>

class MainWindow : public QMainWindow, private Ui_MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private :
    QSerialPort *m_serial;

private slots:
    void on_btnConnectionPort_clicked();
    void on_actionQuitter_triggered();
    void on_cbListeTTY_currentIndexChanged(int);
    void readData();
};

#endif // MAINWINDOW_H
