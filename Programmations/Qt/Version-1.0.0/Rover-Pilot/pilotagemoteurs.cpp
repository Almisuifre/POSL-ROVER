#include "pilotagemoteurs.h"

//#include <cmath>

//#include <QDebug>


PilotageMoteurs::PilotageMoteurs(QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    m_power = 0;
}

PilotageMoteurs::~PilotageMoteurs()
{

}

int
PilotageMoteurs::getPowerValue()
{
    return m_power;
}


/**
 * @brief PilotageMoteurs::delayFromDistanceAndPower
 *        Attention, cette fonction ce base sur un relevé de mesure,
 *        toute modification du rover entrainera une modification
 *        des vitesses mesurées
 *
 *        Cette fonction est destinée à disparaitre mais est
 *        nécessaire pour les premiers tests du prototype
 * @return delayMS
 */
int
PilotageMoteurs::delayFromDistanceAndPower()
{
    double delayMS = 0;

    double distance = static_cast<double>(distanceCm->value());
    double vitesse = 0;

    switch (m_power)
    {
        // Puissance = 80 => vitesse = 7cm/sec
        case 80:
            vitesse = 7;
        break;

        // Puissance = 100 => vitesse = 8cm/sec
        // Puissance = 120 => vitesse = 8cm/sec
        case 100:
        case 120:
            vitesse = 8;
        break;

        // Puissance = 150 => vitesse = 8.5cm/sec
        case 150:
            vitesse = 8.5;
        break;

        // Puissance = 175 => vitesse = 8.8cm/sec
        case 175:
            vitesse = 8.8;
        break;

        // Puissance = 200 => vitesse = 9cm/sec
        case 200:
            vitesse = 9;
        break;

        // Puissance = 255 => vitesse = 9.5cm/sec
        case 255:
            vitesse = 9.5;
        break;
    }

    if(vitesse > 0)
    {

        delayMS =  distance / vitesse;
        //delayMS += fmod(distance,vitesse);
        delayMS *= 1000;
    }

    return static_cast<int>(delayMS);
}


void
PilotageMoteurs::on_btnPower_valueChanged()
{
    switch (btnPower->value())
    {
        case 0:
             m_power = 0;
        break;

        case 1:
             m_power =80;
        break;

        case 2:
             m_power = 100;
        break;

        case 3:
             m_power = 120;
        break;

        case 4:
             m_power = 150;
        break;

        case 5:
             m_power = 175;
        break;

        case 6:
             m_power = 200;
        break;

        case 7:
             m_power = 255;
        break;
    }

    lcdPower->display(m_power);
}
