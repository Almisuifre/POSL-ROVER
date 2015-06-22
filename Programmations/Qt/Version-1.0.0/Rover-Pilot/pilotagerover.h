#ifndef PILOTAROVER_H
#define PILOTAROVER_H

#include <QWidget>
#include "ui_pilotagerover.h"

#include <communicationserie.h>
#include <pilotagemoteurs.h>

class PilotageRover : public QWidget, private Ui_PilotageRover
{
    Q_OBJECT

    public:
        explicit PilotageRover(QWidget *parent = 0, CommunicationSerie *comSerie = 0, PilotageMoteurs *pilotageMoteur = 0);
        ~PilotageRover();

    private:
        CommunicationSerie  *m_comSerie;
        PilotageMoteurs     *m_pilotageMoteurs;


    private slots:
        /* Marche */
        void on_btnAvance_clicked();
        void on_btnRecule_clicked();
        void on_btnRouesMarcheTransbordeurGauche_clicked();
        void on_btnRouesMarcheTransbordeurDroite_clicked();
        void on_btnMarcheDirGauche_clicked();
        void on_btnMarcheDirDroite_clicked();

        /* Roues */
        void on_btnRouesAuCentre_clicked();
        void on_btnRouesAGauche_clicked();
        void on_btnRouesADroite_clicked();
        void on_btnRouesDiagonaleGauche_clicked();
        void on_btnRouesDiagonaleDroite_clicked();
        void on_btnRoueTransbordeur_clicked();
        void on_btnRoueSurPlace_clicked();


    signals:
        void sendInformations(QString informations);
};

#endif // PILOTAROVER_H
