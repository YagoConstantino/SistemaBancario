#include "fazersaque.h"
#include "ui_fazersaque.h"
#include "menuprincipal.h"
#include "confirmarsenha.h"
#include <qevent.h>
#include <QMessageBox>

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

    QString valor = ui->QuantidadeSaque->text();

    QtdSaque = valor.toDouble();
    MenuPrincipal *menu = qobject_cast<MenuPrincipal*>(parentWidget());
    ConfirmarSenha dlg(menu);
    // exec() retorna QDialog::Accepted (1) ou QDialog::Rejected (0)
    if(valor.isEmpty()) QMessageBox::information(this,"Erro","Coloque algum valor ");
    else
    {
        if(dlg.exec() == QDialog::Accepted)
        {
            if(menu->getConta()->fazerSaque(QtdSaque))
            {
                QMessageBox::information(this,"Sucesso","Saque feito com Sucesso");
            }
            else
                QMessageBox::information(this,"Erro","Saque não concluido");
            //mostrar mensagem de sucesso ??
            voltarMenu();
        }
    }
}

void FazerSaque::closeEvent(QCloseEvent *event)
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    if (MenuPrin)
        MenuPrin->show();

    event->accept();
}


