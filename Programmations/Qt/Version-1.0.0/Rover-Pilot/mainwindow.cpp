#include "mainwindow.h"

#include "qmessagebox.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    //this->showFullScreen();

    /*
     * Remplissage des onglets des options
     */
    // Connection
    m_comSerie = new CommunicationSerie;
    connect(m_comSerie, SIGNAL(sendInformations(QString)), this, SLOT(diplayInformations(QString)));

    tbMenu->addItem(m_comSerie, "Connection");


    // Pilotage Moteurs
    m_pilotageMoteurs = new PilotageMoteurs;
    tbMenu->addItem(m_pilotageMoteurs, "Pilotage Moteurs");


    // Pilotage Plateau
    m_pilotagePlateau = new PilotagePlateau;
    tbMenu->addItem(m_pilotagePlateau, "Pilotage Plateau");

    // On supprime le premier (qui était nécessaire pour le designer)
    tbMenu->removeItem(0);
    delete pgVide;

    /*
     * Remplissage des onglets centraux
     */
    // Pilotage Général
    m_pilotageRover = new PilotageRover(0, m_comSerie, m_pilotageMoteurs);
    tabCentrale->addTab(m_pilotageRover, "Pilotage Rover");
    connect(m_pilotageRover, SIGNAL(sendInformations(QString)), this, SLOT(diplayInformations(QString)));

    // On supprime le premier (qui était nécessaire pour le designer)
    tabCentrale->removeTab(0);
    delete tabVide;
}

MainWindow::~MainWindow()
{
    delete m_comSerie;
    delete m_pilotageMoteurs;
    delete m_pilotagePlateau;
    delete m_pilotageRover;
}

void
MainWindow::on_actionQuitter_triggered()
{
    if (QMessageBox::question(this, "Quitter ?", "Est-vous sûr de vouloir quitter ?", QMessageBox ::Yes | QMessageBox::No) == QMessageBox::Yes) this->close();
}


void
MainWindow::on_actionClearConsole_triggered()
{
    console->clear();
}


void
MainWindow::on_actionDeconnection_triggered()
{
    m_comSerie->deconnection();
}

void
MainWindow::diplayInformations(QString informations)
{
    console->append(informations);
}
