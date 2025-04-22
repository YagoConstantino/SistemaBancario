#include "encerrarconta.h"
#include "ui_encerrarconta.h"
#include "menuprincipal.h"
#include <qevent.h>
#include <QMessageBox>

EncerrarConta::EncerrarConta(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EncerrarConta),
    MenuPrin(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Encerrar Conta");
    setAttribute(Qt::WA_DeleteOnClose);


    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
    connect(ui->EncerrarButton,SIGNAL(clicked()),this,SLOT(encerrarConta()));
    connect(ui->MostrarSenha,SIGNAL(clicked(bool)),this,SLOT(mostrarSenha(bool)));
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

void EncerrarConta::encerrarConta()
{
    if(verificaDadosParaEncerramento())
    {
        QMessageBox::about(this,"Conta Encerrada","Conta foi Encerrada com sucesso");
        voltarMenu();
        //Deveria voltar para o login
    }
    //Apagar no Banco de dados se a senha estiver correta
}

void EncerrarConta::mostrarSenha(bool checked)
{
    ui->TextSenha->setEchoMode(checked ? QLineEdit::Normal: QLineEdit::Password);
}

int EncerrarConta::verificaDadosParaEncerramento()
{
    QString login = ui->TextLogin->text();
    QString senha = ui->TextSenha->text();

    if(login.isEmpty() || senha.isEmpty())
    {
        QMessageBox::warning(this,"insira seu login e senha","Erro ao ler dados, Login e Senha vazios");
        return 0;
    }
    //If login ou senha != do que ta no banco de dados return 0, com warning etc


    return 1;
}
