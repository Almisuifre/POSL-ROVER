#include "pilotagerover.h"

#include <QDebug>

PilotageRover::PilotageRover(QWidget *parent, CommunicationSerie *comSerie, PilotageMoteurs *pilotageMoteur) : QWidget(parent)
{
    setupUi(this);

    m_pilotageMoteurs   = pilotageMoteur;
    m_comSerie          = comSerie;
}

PilotageRover::~PilotageRover()
{

}

void
PilotageRover::on_btnAvance_clicked()
{
    int distanceRoute = m_pilotageMoteurs->delayFromDistanceAndPower();
    QString data = QString("!,1,1,%1,1,%1,1,%1,1,%1,").arg(m_pilotageMoteurs->getPowerValue());
    data.append(QString::number(distanceRoute));
    data.append(",*");
    m_comSerie->envoyerData(data);
    emit sendInformations(QString("%1 : %2 sur %3").arg("Avance", QString::number(m_pilotageMoteurs->getPowerValue()), QString::number(distanceRoute)));

    //m_serial->write(QString("!,1,1,%1,1,%1,1,%1,1,%1,1000,*").arg(btnPower->value()).toStdString().c_str());
    //console->append(QString("%1 : %2 sur %3").arg("Avance", QString::number(btnPower->value()), "1000"));
}

void
PilotageRover::on_btnRecule_clicked()
{
    int distanceRoute = m_pilotageMoteurs->delayFromDistanceAndPower();
    QString data = QString("!,1,0,%1,0,%1,0,%1,0,%1,").arg(m_pilotageMoteurs->getPowerValue());
    data.append(QString::number(distanceRoute));
    data.append(",*");
    m_comSerie->envoyerData(data);
    emit sendInformations(QString("%1 : %2 sur %3").arg("Recule", QString::number(m_pilotageMoteurs->getPowerValue()), QString::number(distanceRoute)));

    //m_comSerie->envoyerData(QString("!,1,0,%1,0,%1,0,%1,0,%1,1000,*").arg(m_pilotageMoteurs->getPowerValue()));
    //emit sendInformations(QString("%1 : %2 sur %3").arg("Recule", QString::number(m_pilotageMoteurs->getPowerValue()), "1000"));
}

void
PilotageRover::on_btnRouesMarcheTransbordeurGauche_clicked()
{
    int distanceRoute = m_pilotageMoteurs->delayFromDistanceAndPower();
    QString data = QString("!,1,1,%1,0,%1,0,%1,1,%1,").arg(m_pilotageMoteurs->getPowerValue());
    data.append(QString::number(distanceRoute));
    data.append(",*");
    m_comSerie->envoyerData(data);
    emit sendInformations(QString("%1 : %2 sur %3").arg("Transbordeur avance à gauche", QString::number(m_pilotageMoteurs->getPowerValue()), QString::number(distanceRoute)));
}

void
PilotageRover::on_btnRouesMarcheTransbordeurDroite_clicked()
{
    int distanceRoute = m_pilotageMoteurs->delayFromDistanceAndPower();
    QString data = QString("!,1,0,%1,1,%1,1,%1,0,%1,").arg(m_pilotageMoteurs->getPowerValue());
    data.append(QString::number(distanceRoute));
    data.append(",*");
    m_comSerie->envoyerData(data);
    emit sendInformations(QString("%1 : %2 sur %3").arg("Transbordeur avance à droite", QString::number(m_pilotageMoteurs->getPowerValue()), QString::number(distanceRoute)));
}

void
PilotageRover::on_btnMarcheDirGauche_clicked()
{
    int distanceRoute = m_pilotageMoteurs->delayFromDistanceAndPower();
    QString data = QString("!,1,0,%1,1,%1,0,%1,1,%1,").arg(m_pilotageMoteurs->getPowerValue());
    data.append(QString::number(distanceRoute));
    data.append(",*");
    m_comSerie->envoyerData(data);
    emit sendInformations(QString("%1 : %2 sur %3").arg("Tourne à gauche", QString::number(m_pilotageMoteurs->getPowerValue()), QString::number(distanceRoute)));
}

void
PilotageRover::on_btnMarcheDirDroite_clicked()
{
    int distanceRoute = m_pilotageMoteurs->delayFromDistanceAndPower();
    QString data = QString("!,1,1,%1,0,%1,1,%1,0,%1,").arg(m_pilotageMoteurs->getPowerValue());
    data.append(QString::number(distanceRoute));
    data.append(",*");
    m_comSerie->envoyerData(data);
    emit sendInformations(QString("%1 : %2 sur %3").arg("Tourne à droite", QString::number(m_pilotageMoteurs->getPowerValue()), QString::number(distanceRoute)));
}

void
PilotageRover::on_btnRouesAuCentre_clicked()
{
    m_comSerie->envoyerData("!,2,90,90,90,90,*");
    emit sendInformations(QString("%1 : %2").arg("Roues au centre", "!,2,90,90,90,90,*"));
}

void
PilotageRover::on_btnRouesAGauche_clicked()
{
    m_comSerie->envoyerData("!,2,70,110,75,105,*");
    emit sendInformations(QString("%1 : %2").arg("Roues à gauche", "!,2,70,110,75,105,*"));
}

void
PilotageRover::on_btnRouesADroite_clicked()
{
    m_comSerie->envoyerData("!,2,105,75,110,70,*");
    emit sendInformations(QString("%1 : %2").arg("Roues à droite", "!,2,105,75,110,70,*"));
}

void
PilotageRover::on_btnRouesDiagonaleGauche_clicked()
{
    m_comSerie->envoyerData("!,2,70,70,70,70,*");
    emit sendInformations(QString("%1 : %2").arg("Roues diagonale à gauche", "!,2,70,70,70,70,*"));
}

void
PilotageRover::on_btnRouesDiagonaleDroite_clicked()
{
    m_comSerie->envoyerData("!,2,110,110,110,110,*");
    emit sendInformations(QString("%1 : %2").arg("Roues diagonale à droite", "!,2,110,110,110,110,*"));
}

void
PilotageRover::on_btnRoueTransbordeur_clicked()
{
    m_comSerie->envoyerData("!,2,0,180,180,0,*");
    emit sendInformations(QString("%1 : %2").arg("Roues transbordeur", "!,2,0,180,180,0,*"));
}

void
PilotageRover::on_btnRoueSurPlace_clicked()
{
    m_comSerie->envoyerData("!,2,140,40,40,140,*");
    emit sendInformations(QString("%1 : %2").arg("Roues tourner sur place", "!,2,140,40,40,140,*"));
}
