#include "versaldo.h"
#include "ui_versaldo.h"
#include "menuprincipal.h"
#include <qevent.h>
VerSaldo::VerSaldo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerSaldo)
    , MenuPrin(nullptr)
    ,Saldo()
{
    ui->setupUi(this);

    setWindowTitle("Ver Saldo");
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
    setarSaldoAtual();

}

VerSaldo::~VerSaldo()
{
    delete ui;
}

void VerSaldo::voltarMenu()
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    MenuPrin->show();
    close();
}

void VerSaldo::closeEvent(QCloseEvent *event)
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    if (MenuPrin)
        MenuPrin->show();

    event->accept();
}

void VerSaldo::setarSaldoAtual()
{
    MenuPrincipal *menu = qobject_cast<MenuPrincipal*>(parentWidget());
    double saldo = menu->getConta()->getSaldo();

    //converter o double para QString
    QString textoSaldo = QString::number(saldo,'f',2);
    ui->SaldoText->setText(textoSaldo);
}
