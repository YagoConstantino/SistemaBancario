#include "fazertransferencia.h"
#include "ui_fazertransferencia.h"
#include "menuprincipal.h"
#include "confirmarsenha.h"
#include <qevent.h>

FazerTransferencia::FazerTransferencia(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FazerTransferencia),
    MenuPrin(nullptr)
    ,DadosConta()
    ,QtdTransferencia(0)
{
    ui->setupUi(this);
    setWindowTitle("Transferências");
    setAttribute(Qt::WA_DeleteOnClose);


    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
    connect(ui->ConfirmaButton,SIGNAL(clicked()),this,SLOT(confirmarSenha()));
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

void FazerTransferencia::confirmarSenha()
{
    MenuPrincipal *menu = qobject_cast<MenuPrincipal*>(parentWidget());
    QString cpfReceptor = ui->DestinoText->text();
    QtdTransferencia = ui->QtdValor->text().toDouble();
    double saldo = menu->getConta()->getSaldo();
    if(QtdTransferencia > saldo)
    {
        QMessageBox::information(this,"Erro","Saldo insuficiente para a Transferência");
        return;
    }

    if(QtdTransferencia < 0)
    {
        QMessageBox::information(this,"Erro","Valores Negativos não são permitidos em Transferências");
        ui->QtdValor->clear();
        return;
    }

    ConfirmarSenha dlg(menu);
    // exec() retorna QDialog::Accepted (1) ou QDialog::Rejected (0)
    if(dlg.exec() == QDialog::Accepted)
    {
        if(menu->getConta()->fazerTransf(QtdTransferencia,cpfReceptor))
        {
            QMessageBox::information(this,"Sucesso","Transferencia feita com Sucesso");
        }
        voltarMenu();
    }
}
