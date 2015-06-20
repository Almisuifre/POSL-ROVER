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
//    //Conversion valeur
//    int speedBtnValue = btnSpeed->value();
//    QString speedValue;

//    //Conversion requête
//    QString requestData = QString("!,1,1,%1,1,%1,1,%1,1,%1,1000,*").arg(speedBtnValue);
//    QByteArray conv_requestData = requestData.toLatin1();
//    const char *c_requestData = conv_requestData.data();

//    if(m_connectionOK)
//    {
//        m_serial->write(c_requestData);
//        console->append(QString("%1 : %2 sur %3").arg("Avance", speedValue.setNum(speedBtnValue), "1000"));
//    }

    if(m_connectionOK)
    {
        int distanceRoute = distanceToTime(distanceCm->value(), "cm");
        m_serial->write(QString("!,1,1,%1,1,%1,1,%1,1,%1,%2,*").arg(btnSpeed->value(), distanceRoute).toStdString().c_str());
        console->append(QString("%1 : %2 sur %3").arg("Avance", QString::number(btnSpeed->value()), QString::number(distanceRoute)));

        //m_serial->write(QString("!,1,1,%1,1,%1,1,%1,1,%1,1000,*").arg(btnSpeed->value()).toStdString().c_str());
        //console->append(QString("%1 : %2 sur %3").arg("Avance", QString::number(btnSpeed->value()), "1000"));
    }
}

void
MainWindow::on_btnRecule_clicked()
{
//    //Conversion valeur
//    int speedBtnValue = btnSpeed->value();
//    QString speedValue;

//    //Conversion requête
//    QString requestData = QString("!,1,0,%1,0,%1,0,%1,0,%1,1000,*").arg(speedBtnValue);
//    QByteArray conv_requestData = requestData.toLatin1();
//    const char *c_requestData = conv_requestData.data();

//    if(m_connectionOK)
//    {
//        m_serial->write(c_requestData);
//        console->append(QString("%1 : %2 sur %3").arg("Recule", speedValue.setNum(speedBtnValue), "1000"));
//    }

    if(m_connectionOK)
    {
        m_serial->write(QString("!,1,0,%1,0,%1,0,%1,0,%1,1000,*").arg(btnSpeed->value()).toStdString().c_str());
        console->append(QString("%1 : %2 sur %3").arg("Recule", QString::number(btnSpeed->value()), "1000"));
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

int MainWindow::distanceToTime(int distance, QString unite)
{
    double time = 0;
    int speed = 0;

    if(unite == "cm")
    {
        /*
         * C'est moche mais en attendant l'odométrie par capteur à effet hall c'est un delay() dans l'arduilol qui fait le travail
         * delay(3000) = 1 tour de roue = 18cm parcourus
         * temps delay() à tarnsmettre = distance (cm) * 3000 / 18
         * */
//        int distTime = ((distance * 3000)/18);
//        return distTime;


        //on controle les limites
        speed = btnSpeed->value();

        if(speed > 80 && speed <= 255)
        {
            time = (static_cast<double>(distance)) / static_cast<double>((static_cast<double>(speed)) * 0.07);
        }
    }

    return ((static_cast<int>(time))*1000);
}
