#ifndef PILOTAGEPLATEAU_H
#define PILOTAGEPLATEAU_H

#include <QWidget>

#include "ui_pilotageplateau.h"

class PilotagePlateau : public QWidget, private Ui_PilotagePlateau
{
    Q_OBJECT

    public:
        explicit PilotagePlateau(QWidget *parent = 0);
        ~PilotagePlateau();

    private:

};

#endif // PILOTAGEPLATEAU_H
