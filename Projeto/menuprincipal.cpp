#include "menuprincipal.h"
#include "ui_menuprincipal.h"
#include "mainwindow.h"  // static_cast
#include <QCloseEvent>

MenuPrincipal::MenuPrincipal(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MenuPrincipal),
    Login(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Menu Principal");

    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarLogin()));
}

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}

void MenuPrincipal::closeEvent(QCloseEvent *event)
{
    Login = qobject_cast<MainWindow*>(parentWidget());
    if (Login) {
        Login->show();  // Mostra a MainWindow
    }

    event->accept();  // Aceita o fechamento
}
void MenuPrincipal::voltarLogin()
{
    // Recupera o ponteiro para a MainWindow
    /*if (auto mw = qobject_cast<MainWindow*>(parentWidget())) {
        mw->show();   // Reexibe a janela principal
    }
    this->close();    // Fecha o diálogo*/
    Login = qobject_cast<MainWindow*>(parentWidget());
    Login->show();
    close();
}
