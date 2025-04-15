#include "fazerdeposito.h"
#include "ui_fazerdeposito.h"
#include "menuprincipal.h"
#include <qevent.h>

FazerDeposito::FazerDeposito(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FazerDeposito),
    MenuPrin(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Deposito");

    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
}

FazerDeposito::~FazerDeposito()
{
    delete ui;
}

void FazerDeposito::voltarMenu()
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    MenuPrin->show();
    close();
}

void FazerDeposito::closeEvent(QCloseEvent *event)
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    if (MenuPrin)
        MenuPrin->show();  // Mostra a MainWindow

    event->accept();
}
