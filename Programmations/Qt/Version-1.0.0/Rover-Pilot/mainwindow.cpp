#include "mainwindow.h"

#include "qmessagebox.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    this->showFullScreen();

    m_serial = NULL;
    m_connectionOK = false;
    btnDatasTests->setEnabled(false);

    // remplissage de la combobox
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        cbListeTTY->addItem(serialPortInfo.portName());

    //Mise à niveau de la vitesse
    lcdSpeed->display(80);
    btnSpeed->setValue(80);
}

MainWindow::~MainWindow()
{
    if(m_connectionOK)
    {
        if(m_serial->isOpen()) m_serial->close();
        delete m_serial;
    }
}


void
MainWindow::on_cbListeTTY_currentIndexChanged(int)
{
    btnConnectionPort->setText(QString("Connection sur %1").arg(cbListeTTY->currentText()));
}


void
MainWindow::on_btnConnectionPort_clicked()
{
    QString port = cbListeTTY->currentText();

    console->append(QString("Début de connection sur %1 ...").arg(port));


    m_serial = new QSerialPort(port);

    connect(m_serial, SIGNAL(readyRead()), this, SLOT(readData()));

    m_serial->open(QIODevice::ReadWrite);

    if(m_serial->isOpen())
    {
        console->append(QString("Connection réussie sur %1 !").arg(port));
        m_connectionOK = true;

        btnDatasTests->setEnabled(true);
        tbMenu->setCurrentIndex(1);
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
MainWindow::on_actionQuitter_triggered()
{
    if (QMessageBox::question(this, "Quitter ?", "Est-vous sûr de vouloir quitter ?", QMessageBox ::Yes | QMessageBox::No) == QMessageBox::Yes) this->close();
}

void
MainWindow::readData()
{
    QByteArray ba = m_serial->readAll();
    console->append(QString(ba));
}

void
MainWindow::on_btnDatasTests_clicked()
{
    m_serial->write("!,1,1,80,1,80,1,80,1,80,100,*");

    if(!m_serial->waitForReadyRead(10000))
    {
        console->append("Aucune confirmation de bonne réception n'a été reçue");
    }
}

void
MainWindow::on_btnAvance_clicked()
{
    //Conversion valeur
    int speedBtnValue = btnSpeed->value();
    QString speedValue;

    //Conversion requête
    QString requestData = QString("!,1,1,%1,1,%1,1,%1,1,%1,1000,*").arg(speedBtnValue);
    QByteArray conv_requestData = requestData.toLatin1();
    const char *c_requestData = conv_requestData.data();

    if(m_connectionOK)
    {
        m_serial->write(c_requestData);
        console->append(QString("%1 : %2 sur %3").arg("Avance", speedValue.setNum(speedBtnValue), "1000"));
    }
}

void
MainWindow::on_btnRecule_clicked()
{
    //Conversion valeur
    int speedBtnValue = btnSpeed->value();
    QString speedValue;

    //Conversion requête
    QString requestData = QString("!,1,0,%1,0,%1,0,%1,0,%1,1000,*").arg(speedBtnValue);
    QByteArray conv_requestData = requestData.toLatin1();
    const char *c_requestData = conv_requestData.data();

    if(m_connectionOK)
    {
        m_serial->write(c_requestData);
        console->append(QString("%1 : %2 sur %3").arg("Recule", speedValue.setNum(speedBtnValue), "1000"));
    }
}

void
MainWindow::on_btnRouesAuCentre_clicked()
{
    if(m_connectionOK)
    {
        m_serial->write("!,2,90,90,90,90,*");
        console->append(QString("%1 : %2").arg("Roues au centre", "!,2,90,90,90,90,*"));
    }
}

void
MainWindow::on_btnSpeed_valueChanged()
{
    lcdSpeed->display(btnSpeed->value());
}
