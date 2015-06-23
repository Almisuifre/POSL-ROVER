#include "communicationserie.h"

CommunicationSerie::CommunicationSerie(QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    m_serial = NULL;
    m_connectionOK = false;

    // remplissage de la combobox
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        cbListeTTY->addItem(serialPortInfo.portName());
}

CommunicationSerie::~CommunicationSerie()
{
    if(m_connectionOK)
    {
        if(m_serial->isOpen()) m_serial->close();
        delete m_serial;
    }
}


void
CommunicationSerie::on_btnConnectionPort_clicked()
{
    QString port = cbListeTTY->currentText();

    emit sendInformations(QString("Début de connection sur %1 ...").arg(port));


    m_serial = new QSerialPort(port);

    connect(m_serial, SIGNAL(readyRead()), this, SLOT(readData()));

    m_serial->open(QIODevice::ReadWrite);

    if(m_serial->isOpen())
    {
        emit sendInformations(QString("Connection réussie sur %1 !").arg(port));
        m_connectionOK = true;
    }

/*
    console->append("Number of serial ports:" + QSerialPortInfo::availablePorts().count());

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        console->append("");
        console->append("Port:" + serialPortInfo.portName());
        console->append("Location:" + serialPortInfo.systemLocation());
        console->append("Description:" + serialPortInfo.description());
        console->append("Manufacturer:" + serialPortInfo.manufacturer());
        console->append("Vendor Identifier:" + (serialPortInfo.hasVendorIdentifier() ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) : QByteArray()));
        console->append("Product Identifier:" + (serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : QByteArray()));
        console->append("Busy:" + (serialPortInfo.isBusy() ? QObject::tr("Yes") : QObject::tr("No")));

        QSerialPort *port = new QSerialPort(serialPortInfo);

        if (port->open(QIODevice::ReadWrite))
        {
            console->append("Baud rate:" + port->baudRate());
            console->append("Data bits:" + port->dataBits());
            console->append("Stop bits:" + port->stopBits());
            console->append("Parity:" + port->parity());
            console->append("Flow control:" + port->flowControl());
            console->append("Read buffer size:" + port->readBufferSize());
            port->close();
        }
        else
        {
            console->append("Unable to open port, error code" + port->error());
        }
        delete port;
    }
*/
}

void
CommunicationSerie::on_btnRechercheCarte_clicked()
{
    emit sendInformations("Recherche de carte connecté ...");

    // remplissage de la combobox
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        cbListeTTY->addItem(serialPortInfo.portName());
}


void
CommunicationSerie::on_cbListeTTY_currentIndexChanged(int)
{
    btnConnectionPort->setText(QString("Connection sur %1").arg(cbListeTTY->currentText()));
}

void
CommunicationSerie::deconnection()
{
    if(m_serial->isOpen())
    {
        m_serial->close();
        m_connectionOK = false;
        emit sendInformations(QString("Déconnection de %1 réussie.").arg(m_serial->portName()));
    }
}

void
CommunicationSerie::envoyerData(QString data)
{
    /*if(m_connectionOK && m_serial->isOpen()) m_serial->write(data.toStdString().c_str());


    if(!m_serial->waitForReadyRead(DELAY_RECEPTION_MS))
    {
        emit sendInformations("Aucune confirmation de bonne réception n'a été reçue !");
    }*/

    if(m_connectionOK && m_serial->isOpen())
    {
        m_serial->write(data.toStdString().c_str());

        if(!m_serial->waitForReadyRead(DELAY_RECEPTION_MS))
        {
            emit sendInformations("Aucune confirmation de bonne réception n'a été reçue !");
        }
    }
    else
    {
        emit sendInformations("Aucune carte n'est connecté.");
    }
}

void
CommunicationSerie::readData()
{
    QByteArray ba = m_serial->readAll();
    emit sendInformations(QString(ba));
}
