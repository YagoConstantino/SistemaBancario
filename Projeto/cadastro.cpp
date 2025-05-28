#include "cadastro.h"
#include "ui_cadastro.h"
#include "mainwindow.h"
#include "conta.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <regex>
#include <string>
using namespace std;



Cadastro::Cadastro(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Cadastro),
    Login(nullptr),
    _nome(""),_CPF(""),_email(""),_nascimento(QDate::currentDate()),_nomeMae(""),_Senha(""),_ConfirmaSenha(""),
    conta()

{
    ui->setupUi(this);
    ui->dateEditNascimento->setDisplayFormat("dd/MM/yyyy");
    setWindowTitle("Cadastro");
    setAttribute(Qt::WA_DeleteOnClose);


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

//Deve criar uma nova conta com os dados pegos na interface grafica, cadastrar no banco de dados e passar
//para o MainWindow
bool Cadastro::criaConta()
{
    Conta *nova = getConta();
    //Tratar o CPF antes de mudar na conta, esse tratamento deve percorrer a string CPF e apagar os . ou -
    _CPF.remove('.').remove('-');
    nova->setCPF(_CPF);
    nova->setDataNascimeto(_nascimento);
    nova->setEmail(_email);
    nova->setNome(_nome);
    nova->setNomeMae(_nomeMae);
    nova->setSenha(_Senha);

    return nova->CadastraContaBD();
}

Conta *Cadastro::getConta()
{
    return Conta::getInstancia();
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
 *Deve chamar a função criaConta
*/
int Cadastro::verificaCadastro()
{
    QString dataStr = _nascimento.toString("dd/MM/yyyy");

    regex padraoEmail(R"(^[A-Za-z0-9._%+]+@[A-Za-z0-9.]+\.[A-Za-z]{2,4}$)");
    regex padraoCPF(R"(^([0-9]{3}\.?){3}-?[0-9]{2}$)");
    regex padraoSenha(R"(^(?=.*[A-Z])(?=.*[0-9])(?=.*[^A-Za-z0-9]).{8,16}$)");

    //strings para usar no metodo do regex
    std::string ema = _email.toStdString();
    std::string cpf = _CPF.toStdString();
    std::string senha  = _Senha.toStdString();

    //Verifica se a senha e confirmação de senha estão vazias,
    if(_Senha.isEmpty()||_ConfirmaSenha.isEmpty())
    {
        QMessageBox::warning(this, "Erro", "Preencha a senha e a confirmação.");
        return 0;
    }

    //verifica se a senha e confirma senha são iguais
    else if (_Senha != _ConfirmaSenha)
    {
        QMessageBox::warning(this, "Erro", "As senhas não coincidem.");
        return 0;
    }

    //verifica se nome,cpf,email e nome da mãe não são vazios
    else if (_nome.isEmpty() || _CPF.isEmpty() || _email.isEmpty() || _nomeMae.isEmpty() )
    {
        QMessageBox::warning(this, "Erro", "Preencha todos os campos obrigatórios.");
        return 0;
    }


    else if (!regex_match(ema,padraoEmail))
    {
        QMessageBox::warning(this,"Erro","Email inválido");
        return 0;
    }

    else if (!regex_match(cpf,padraoCPF))
    {
        QMessageBox::warning(this,"Erro","CPF inválido");
        return 0;
    }

    else if (!regex_match(senha,padraoSenha))
    {
        QMessageBox::warning(this,"Erro","Senha inválida");
        return 0;
    }

    //Deve ser mudado para salvar todos os dados no banco de dados
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

    if (verificaCadastro() && criaConta())
    {
        voltarLogin();
    }
    else
        qDebug ()<< "Erro ao cadastrar";
}
