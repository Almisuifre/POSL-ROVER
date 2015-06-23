#ifndef COMMUNICATIONSERIE_H
#define COMMUNICATIONSERIE_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "ui_communicationserie.h"

#define DELAY_RECEPTION_MS 3000


class CommunicationSerie : public QWidget, private Ui_CommunicationSerie
{
    Q_OBJECT

    private:
        QSerialPort *m_serial;
        bool m_connectionOK;

    public:
        explicit CommunicationSerie(QWidget *parent = 0);
        ~CommunicationSerie();

        void deconnection();
        void envoyerData(QString data);

    private slots:
        void on_btnConnectionPort_clicked();
        void on_btnRechercheCarte_clicked();

        void on_cbListeTTY_currentIndexChanged(int);
        void readData();

   signals:
        void sendInformations(QString informations);
};

#endif // COMMUNICATIONSERIE_H
