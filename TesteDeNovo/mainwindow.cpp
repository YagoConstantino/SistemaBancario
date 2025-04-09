#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    MenuPrin(nullptr)
{
    ui->setupUi(this);
    connect(ui->Confirmar,SIGNAL(clicked()),this,SLOT(Menu_Principal()));
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
