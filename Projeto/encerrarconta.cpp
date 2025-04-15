#include "encerrarconta.h"
#include "ui_encerrarconta.h"
#include "menuprincipal.h"
#include <qevent.h>

EncerrarConta::EncerrarConta(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EncerrarConta),
    MenuPrin(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Encerrar Conta");]setAttribute(Qt::WA_DeleteOnClose);


    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
}

EncerrarConta::~EncerrarConta()
{
    delete ui;
}

void EncerrarConta::voltarMenu()
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    MenuPrin->show();
    close();
}

void EncerrarConta::closeEvent(QCloseEvent *event)
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    if (MenuPrin)
        MenuPrin->show();  // Mostra a MainWindow

    event->accept();
}
