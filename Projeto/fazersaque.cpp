#include "fazersaque.h"
#include "ui_fazersaque.h"
#include "menuprincipal.h"
#include <qevent.h>

FazerSaque::FazerSaque(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FazerSaque),
    MenuPrin(nullptr)
    ,QtdSaque(0)
{
    ui->setupUi(this);
    setWindowTitle("Saque");
    setAttribute(Qt::WA_DeleteOnClose);


    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
    connect(ui->ConfirmaButton,SIGNAL(clicked()),this,SLOT(confirmarSenha()));
}

FazerSaque::~FazerSaque()
{
    delete ui;
}

void FazerSaque::voltarMenu()
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    MenuPrin->show();
    close();
}

void FazerSaque::confirmarSenha()
{

}

void FazerSaque::closeEvent(QCloseEvent *event)
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    if (MenuPrin)
        MenuPrin->show();

    event->accept();
}


