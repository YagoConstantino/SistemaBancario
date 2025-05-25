#include "verextrato.h"
#include "ui_verextrato.h"

#include "menuprincipal.h"
#include <qevent.h>

VerExtrato::VerExtrato(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerExtrato),
    MenuPrin(nullptr)
    ,DadosExtrato()
{
    ui->setupUi(this);
    setWindowTitle("Ver Extrato");
    setAttribute(Qt::WA_DeleteOnClose);

    setarExtrato();

    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
}

VerExtrato::~VerExtrato()
{
    delete ui;
}

void VerExtrato::voltarMenu()
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    MenuPrin->show();
    close();
}

void VerExtrato::closeEvent(QCloseEvent *event)
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    if (MenuPrin)
        MenuPrin->show();

    event->accept();
}

void VerExtrato::setarExtrato(){
    Conta* conta = Conta::getInstancia();

    QString extrato = conta->getExtrato();

    ui->textEdit->setPlainText(extrato);
}
