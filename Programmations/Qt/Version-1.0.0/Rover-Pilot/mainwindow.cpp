#include "mainwindow.h"

#include "qmessagebox.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
}

MainWindow::~MainWindow()
{

}


void
MainWindow::on_superBouton_clicked()
{
    QMessageBox::warning(this, "Attention !", "Une babache est parmis nous !!!");
}
