#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

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

    int distanceToTime(int distance, QString unite);

private slots:
    /* Boutons */
    void on_btnConnectionPort_clicked();
    void on_btnDatasTests_clicked();

    /* Marche */
    void on_btnAvance_clicked();
    void on_btnRecule_clicked();

    /* Roues */
    void on_btnRouesAuCentre_clicked();

    /* Contrôles */
    void on_btnSpeed_valueChanged();

    /* Actions */
    void on_actionQuitter_triggered();
    void on_actionDeconnection_triggered();
    void on_actionClearConsole_triggered();

    /* Serial */
    void readData();

    /* Divers */
    void on_cbListeTTY_currentIndexChanged(int);

};

#endif // MAINWINDOW_H
