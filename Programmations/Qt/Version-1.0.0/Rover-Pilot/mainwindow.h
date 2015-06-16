#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>

class MainWindow : public QMainWindow, private Ui_MainWindow
{
    Q_OBJECT

private:
     bool m_connectionOK;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private :
    QSerialPort *m_serial;

private slots:
    /* Boutons */
    void on_btnConnectionPort_clicked();
    void on_btnDatasTests_clicked();
    void on_btnAvance_clicked();

    /* Actions */
    void on_actionQuitter_triggered();

    /* Serial */
    void readData();

    /* Divers */
    void on_cbListeTTY_currentIndexChanged(int);

};

#endif // MAINWINDOW_H
