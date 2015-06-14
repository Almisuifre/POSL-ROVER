#include "mainwindow.h"

#include "qmessagebox.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow()
{
    //if(m_serial->isOpen()) m_serial->close();
    //delete m_serial;
}


void
MainWindow::on_btnConnectionFTDI_clicked()
{
    console->append("Début de connection sur FTDI...");

    m_serial = new QSerialPort("/dev/ttyUSB0");

    m_serial->open(QIODevice::ReadWrite);

    if(m_serial->isOpen())
    {
        m_serial->write("!,2,90,90,90,90,*");
        m_serial->close();
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
