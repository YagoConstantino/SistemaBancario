#include "cadastro.h"
#include "ui_cadastro.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>

Cadastro::Cadastro(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Cadastro),
    Login(nullptr),
    _nome(""),_CPF(""),_email(""),_nascimento(QDate::currentDate()),_nomeMae(""),_Senha(""),_ConfirmaSenha("")

{
    ui->setupUi(this);
    ui->dateEditNascimento->setDisplayFormat("dd/MM/yyyy");
    setWindowTitle("Cadastro");

    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarLogin()));
    connect(ui->ConfirmarCad,SIGNAL(clicked()),this,SLOT(ConfirmarCadastro()));
    connect(ui->Limpar,SIGNAL(clicked()),this,SLOT(clearCaixasTexto()));
}

Cadastro::~Cadastro()
{
    delete ui;
}

void Cadastro::closeEvent(QCloseEvent *event)
{
    Login = qobject_cast<MainWindow*>(parentWidget());
    if (Login) {
        Login->show();  // Mostra a MainWindow
    }

    event->accept();  // Aceita o fechamento
}

void Cadastro::voltarLogin()
{
    Login = qobject_cast<MainWindow*>(parentWidget());
    Login->show();
    close();
}

void Cadastro::clearCaixasTexto()
{
    ui->NomeText->clear();
    ui->CPFtext->clear();
    ui->EmailText->clear();
    ui->MaeText->clear();
    ui->Senha->clear();
    ui->ConfirmaSenha->clear();
    //ui->dateEditNascimento->clear();
}
/*
 * Quando implementar mesmo note que , email tem formato especifico, CPF tem numero especifico e formato especifico
 *Senha tem quantidade e formato especifico.
*/
int Cadastro::verificaCadastro()
{
    QString dataStr = _nascimento.toString("dd/MM/yyyy");

    if(_Senha.isEmpty()||_ConfirmaSenha.isEmpty())
    {
        QMessageBox::warning(this, "Erro", "Preencha a senha e a confirmação.");
        return 0;
    }

    else if (_Senha != _ConfirmaSenha)
    {
        QMessageBox::warning(this, "Erro", "As senhas não coincidem.");
        return 0;
    }

    else if (_nome.isEmpty() || _CPF.isEmpty() || _email.isEmpty() || _nomeMae.isEmpty() )
    {
        QMessageBox::warning(this, "Erro", "Preencha todos os campos obrigatórios.");
        return 0;
    }

    else
    {
        QString info = QString("Usuário %1  CPF: %2  Nascimento: %3  Cadastrado com sucesso!").arg(_nome, _CPF, dataStr);

        QMessageBox::information(this, "Cadastro", info);
        return 1;

    }
}

void Cadastro::ConfirmarCadastro()
{
    _nome = ui->NomeText->text();
    _CPF = ui->CPFtext->text();
    _email = ui->EmailText->text();
    _nascimento = ui->dateEditNascimento->date();
    _nascimento.toString("dd-MM-yyyy");
    _nomeMae = ui->MaeText->text();
    _Senha = ui->Senha->text();
    _ConfirmaSenha = ui->ConfirmaSenha->text();

    if (verificaCadastro())
    {
        voltarLogin();
    }
}
