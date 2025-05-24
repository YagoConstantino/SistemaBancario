#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <regex>
#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    _MenuPrin(nullptr),
    _cad(nullptr),
    _Esq(nullptr),
    _CPFlogin(),
    _SenhaLogin(),
    contaAtual()
{
    ui->setupUi(this);
    setWindowTitle("Login");

    //setAttribute(Qt::WA_DeleteOnClose); Desnecessário para essa janela

    connect(ui->Confirmar,SIGNAL(clicked()),this,SLOT(Menu_Principal()));
    connect(ui->CriarConta,SIGNAL(clicked()),this,SLOT(AbrirCadastro()));
    connect(ui->EsqueceuSenha,SIGNAL(clicked()),this,SLOT(AbrirEsqueceuSenha()));
    connect(ui->MostrarSenha,SIGNAL(clicked(bool)),this,SLOT(mostrarSenha(bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Ser implementado depois , deve pegar os dados no banco de dados e inserir na conta atual
bool MainWindow::recuperarDadosConta()
{
    return false;
}

//Ser implementada depois, deve verificar no banco de dados se o login(CPF) existe e se a senha bate
//deve tambem chamar a recuperarDadosConta
bool MainWindow::verificarDadosConta(QString login, QString senha)
{

    string log = login.toStdString();
    string sen = senha.toStdString();

    regex padraoCPF(R"(^([0-9]{3}\.?){3}-?[0-9]{2}$)");
    regex padraoSenha(R"(^(?=.*[A-Z])(?=.*[0-9])(?=.*[^A-Za-z0-9]).{8,16}$)");

    if(!regex_match(log,padraoCPF) || !regex_match(sen,padraoSenha))
    {
        return false;
    }

    //Além dessa verificação devemos verificar no banco de dados se o login(CPF) existe e se a senha bate

    return verificaContaExiste() && recuperaDadosBanco();
}

Conta *MainWindow::getConta()
{
    return &contaAtual;
}

void MainWindow::clearTexto()
{
    ui->Login->clear();
    ui->Senha->clear();
}

void MainWindow::Menu_Principal()
{
    //Aqui deve ser feito a vericação do login e senha, se existem no banco de dados e se a senha confere
    //para dai então ir para o menuPrincipal, aqui(mainWindow) ou la deve ser armazenado o CPF ou ID
    //ou primarykey da conta para usarmos no conector do banco de dados, ou seja so armazenamos um dado
    _CPFlogin = ui->Login->text();
    _SenhaLogin = ui->Senha->text();

    if (verificarDadosConta(_CPFlogin,_SenhaLogin))
    {
        _MenuPrin = new MenuPrincipal(this);
        _MenuPrin->show();
        hide();
    }
    else
    {
        QMessageBox::warning(this,"Erro","Login ou senha inválidos");
        ui->Login->clear();
        ui->Senha->clear();
    }
}

void MainWindow::AbrirCadastro()
{
    _cad = new Cadastro(this);
    _cad->show();
    hide();
}

void MainWindow::AbrirEsqueceuSenha()
{
    _Esq = new EsqueceuSenha(this);
    _Esq->show();
    hide();
}

void MainWindow::mostrarSenha(bool checked)
{
    ui->Senha->setEchoMode(checked ? QLineEdit::Normal: QLineEdit::Password);
}

bool MainWindow::verificaContaExiste()
{
    return contaAtual.verificaContaExiste(_CPFlogin,_SenhaLogin,this);
}

bool MainWindow::recuperaDadosBanco()
{
    QSqlDatabase BD = contaAtual.getDataBase();
    return contaAtual.recuperaDadosConta(_CPFlogin);
}

