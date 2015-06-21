#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <communicationserie.h>
#include <pilotagemoteurs.h>
#include <pilotageplateau.h>
#include <pilotagerover.h>


#include <QDebug>

class MainWindow : public QMainWindow, private Ui_MainWindow
{
    Q_OBJECT

    private:

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private :
        CommunicationSerie  *m_comSerie;
        PilotageMoteurs     *m_pilotageMoteurs;
        PilotagePlateau     *m_pilotagePlateau;
        PilotageRover       *m_pilotageRover;

    private slots:
        /* Actions */
        void on_actionQuitter_triggered();
        void on_actionDeconnection_triggered();
        void on_actionClearConsole_triggered();

        void diplayInformations(QString informations);
};

#endif // MAINWINDOW_H
