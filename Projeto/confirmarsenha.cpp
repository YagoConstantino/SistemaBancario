#include "confirmarsenha.h"
#include "ui_confirmarsenha.h"
#include "menuprincipal.h"
#include "conta.h"
#include <QMessageBox>
#include <QSqlQuery>

ConfirmarSenha::ConfirmarSenha(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmarSenha)
{
    ui->setupUi(this);
    setWindowTitle("Confimer sua Senha");

    connect(ui->MostrarSenhaCheckbox,SIGNAL(clicked(bool)),this,SLOT(mostrarSenha(bool)));
    connect(ui->OkBtn,SIGNAL(clicked()),this,SLOT(senhaOk()));
}

ConfirmarSenha::~ConfirmarSenha()
{
    delete ui;
}

void ConfirmarSenha::senhaOk()
{
    Conta* conta = Conta::getInstancia();

    // Obtém CPF da conta ativa
    QString cpf = conta->getCPF();
    QString senhaDigitada = ui->SenhaTxt->text();


    // Consulta no DB
    if(conta->confirmarSenha(cpf,senhaDigitada))
    {
         accept();
    }
    else {
        QMessageBox::warning(this, tr("Senha inválida"),
                             tr("A senha informada está incorreta."));
        reject();  // fecha e retorna false em caso de senha errada
    }
}

void ConfirmarSenha::mostrarSenha(bool checked)
{
    ui->SenhaTxt->setEchoMode(checked ? QLineEdit::Normal: QLineEdit::Password);
}
