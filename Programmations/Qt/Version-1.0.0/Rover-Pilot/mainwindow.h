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
    void on_btnConnectionFTDI_clicked();
};

#endif // MAINWINDOW_H
