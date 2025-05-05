#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
    //setAttribute(Qt::WA_DeleteOnClose); Desnecessário para essa janela

    connect(ui->Confirmar,SIGNAL(clicked()),this,SLOT(Menu_Principal()));
    connect(ui->CriarConta,SIGNAL(clicked()),this,SLOT(AbrirCadastro()));
    connect(ui->EsqueceuSenha,SIGNAL(clicked()),this,SLOT(AbrirEsqueceuSenha()));
    connect(ui->MostrarSenha,SIGNAL(clicked(bool)),this,SLOT(mostrarSenha(bool)));

    //Teste mudar mais adiante no projeto
    QSqlDatabase bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    bancoDeDados.setDatabaseName("../db_Projeto.db");

    if (!bancoDeDados.open()) {
        qDebug() << "Erro ao abrir banco:" << bancoDeDados.lastError().text();
    }
    else
        qDebug() << "Banco aberto com sucesso";
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
    return false;
}

void MainWindow::Menu_Principal()
{
    //Aqui deve ser feito a vericação do login e senha, se existem no banco de dados e se a senha confere
    //para dai então ir para o menuPrincipal, aqui(mainWindow) ou la deve ser armazenado o CPF ou ID
    //ou primarykey da conta para usarmos no conector do banco de dados, ou seja so armazenamos um dado

    _MenuPrin = new MenuPrincipal(this);
    _MenuPrin->show();
    hide();
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

