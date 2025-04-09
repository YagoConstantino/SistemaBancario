#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    MenuPrin(nullptr),
    cad(nullptr)
{
    ui->setupUi(this);

    connect(ui->Confirmar,SIGNAL(clicked()),this,SLOT(Menu_Principal()));
    connect(ui->CriarConta,SIGNAL(clicked()),this,SLOT(AbrirCadastro()));
    connect(ui->MostrarSenha,SIGNAL(clicked(bool)),this,SLOT(mostrarSenha(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Menu_Principal()
{
    MenuPrin = new MenuPrincipal(this);
    MenuPrin->show();
    hide();
}

void MainWindow::AbrirCadastro()
{
    cad = new Cadastro(this);
    cad->show();
    hide();
}

void MainWindow::mostrarSenha(bool checked)
{
    ui->Senha->setEchoMode(checked ? QLineEdit::Normal: QLineEdit::Password);
}
