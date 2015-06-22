#include "pilotagerover.h"

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
    emit sendInformations(QString("%1 : %2 sur %3").arg("Avance", QString::number(m_pilotageMoteurs->getPowerValue()), QString::number(distanceRoute)));

    //m_comSerie->envoyerData(QString("!,1,0,%1,0,%1,0,%1,0,%1,1000,*").arg(m_pilotageMoteurs->getPowerValue()));
    //emit sendInformations(QString("%1 : %2 sur %3").arg("Recule", QString::number(m_pilotageMoteurs->getPowerValue()), "1000"));
}

void
PilotageRover::on_btnRouesAuCentre_clicked()
{
    m_comSerie->envoyerData("!,2,90,90,90,90,*");
    emit sendInformations(QString("%1 : %2").arg("Roues au centre", "!,2,90,90,90,90,*"));
}
