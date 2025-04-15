#include "fazertransferencia.h"
#include "ui_fazertransferencia.h"
#include "menuprincipal.h"
#include <qevent.h>

FazerTransferencia::FazerTransferencia(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FazerTransferencia),
    MenuPrin(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Transferências");
    setAttribute(Qt::WA_DeleteOnClose);


    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
}

FazerTransferencia::~FazerTransferencia()
{
    delete ui;
}

void FazerTransferencia::voltarMenu()
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    MenuPrin->show();
    close();
}

void FazerTransferencia::closeEvent(QCloseEvent *event)
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    if (MenuPrin)
        MenuPrin->show();

    event->accept();
}
