#include "fazerdeposito.h"
#include "ui_fazerdeposito.h"
#include "menuprincipal.h"
#include "confirmarsenha.h"
#include "conta.h"
#include <QMessageBox>
#include <qevent.h>

FazerDeposito::FazerDeposito(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FazerDeposito),
    MenuPrin(nullptr)
    ,QtdDeposito(0)
{
    ui->setupUi(this);
    setWindowTitle("Deposito");
    setAttribute(Qt::WA_DeleteOnClose);


    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
    connect(ui->ConfirmaButton,SIGNAL(clicked()),this,SLOT(confirmarSenha()));
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

void FazerDeposito::confirmarSenha()
{
    Conta* conta = Conta::getInstancia();

    QString valor = ui->QtdDeposito->text();
    QtdDeposito = valor.toDouble();

    MenuPrincipal *menu = qobject_cast<MenuPrincipal*>(parentWidget());
    ConfirmarSenha dlg(menu);
    // exec() retorna QDialog::Accepted (1) ou QDialog::Rejected (0)
    if(valor.isEmpty()) QMessageBox::information(this,"Erro","Coloque algum valor ");
    //if(valor.toDouble() < 0) QMessageBox::information(this,"Erro","Coloque uma valor válido");
    else
    {
        if(dlg.exec() == QDialog::Accepted)
        {
            if(conta->fazerDeposito(QtdDeposito))
            {
                QMessageBox::information(this,"Sucesso","Deposito feito com Sucesso");
            }
            else
                QMessageBox::information(this,"Erro","Deposito não concluido");
            //mostrar mensagem de sucesso ??
            voltarMenu();
        }
    }
}


