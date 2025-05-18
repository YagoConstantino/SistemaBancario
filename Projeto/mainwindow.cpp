#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    _MenuPrin(nullptr),
    _cad(nullptr),
    _Esq(nullptr)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);


    connect(ui->Confirmar,SIGNAL(clicked()),this,SLOT(Menu_Principal()));
    connect(ui->CriarConta,SIGNAL(clicked()),this,SLOT(AbrirCadastro()));
    connect(ui->EsqueceuSenha,SIGNAL(clicked()),this,SLOT(AbrirEsqueceuSenha()));
    connect(ui->MostrarSenha,SIGNAL(clicked(bool)),this,SLOT(mostrarSenha(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Menu_Principal()
{
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

