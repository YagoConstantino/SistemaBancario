#include "esqueceusenha.h"
#include "ui_esqueceusenha.h"
#include "mainwindow.h"
#include <QCloseEvent>


EsqueceuSenha::EsqueceuSenha(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EsqueceuSenha)
    ,Login(nullptr)
    ,conta()
{
    ui->setupUi(this);
    setWindowTitle("Esqueceu Senha");
    setAttribute(Qt::WA_DeleteOnClose);


    connect(ui->ConfButton,SIGNAL(clicked()),this,SLOT(ConfirmarTrocaDeSenha()));
    connect(ui->SairButton,SIGNAL(clicked()),this,SLOT(VoltarLogin()));
    connect(ui->MostrarSenha,SIGNAL(clicked(bool)),this,SLOT(mostrarSenha(bool)));
}

EsqueceuSenha::~EsqueceuSenha()
{
    delete ui;
}

void EsqueceuSenha::closeEvent(QCloseEvent *event)
{
    Login = qobject_cast<MainWindow*>(parentWidget());
    if (Login) {
        Login->show();  // Mostra a MainWindow
    }

    event->accept();  // Aceita o fechamento
}

//Deve mudar a senha na conta local e no banco de dados, verificar a senha com regex
bool EsqueceuSenha::mudarSenha(Conta cont)
{
    return false;
}

//Deve verificar se todos os dados foram passados

int EsqueceuSenha::verificaDados()
{
    if(_CPF.isEmpty() || _NomeMae.isEmpty())
    {
        QMessageBox::warning(this,"Erro","Preencha os Dados de CPF e Nome Mae");
        return 0;
    }

    if(_Senha.isEmpty() || _ConfirmaSenha.isEmpty())
    {
        QMessageBox::warning(this,"Erro","Preencha Senha e Confirma Senha");
        return 0;
    }

    if(_Senha != _ConfirmaSenha)
    {
        QMessageBox::warning(this,"Erro","Senhas não coincidem");
        return 0;
    }
    return 1;
}
//deve verificar se o CPF existe no banco de dados e se o nome da mae bate
//chama a função mudarSenha
void EsqueceuSenha::ConfirmarTrocaDeSenha()
{
    _CPF = ui->CPFtextBox->text();
    _NomeMae = ui->MaeTextBox->text();
    _Senha = ui->SenhaTextBox->text();
    _ConfirmaSenha = ui->ConfirmaSenhaTextBox->text();

    if(verificaDados())
    {
        QMessageBox::information(this,"Sucesso na troca de Senha","Deu Tudo certo na Troca de Senha");
        VoltarLogin();
    }
}

void EsqueceuSenha::VoltarLogin()
{
    Login = qobject_cast<MainWindow*>(parentWidget());
    Login->show();
    close();
}

void EsqueceuSenha::mostrarSenha(bool checked)
{
    ui->SenhaTextBox->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
    ui->ConfirmaSenhaTextBox->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}
