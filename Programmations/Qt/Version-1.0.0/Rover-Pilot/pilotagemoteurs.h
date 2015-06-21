#ifndef PILOTAGEMOTEURS_H
#define PILOTAGEMOTEURS_H

#include <QWidget>

#include "ui_pilotagemoteurs.h"


class PilotageMoteurs : public QWidget, private Ui_PilotageMoteurs
{
    Q_OBJECT

    private:
        int m_power;

    public:
        explicit PilotageMoteurs(QWidget *parent = 0);
        ~PilotageMoteurs();

        int delayFromDistanceAndPower();
        int getPowerValue();

    private slots:
        void on_btnPower_valueChanged();

};

#endif // PILOTAGEMOTEURS_H
