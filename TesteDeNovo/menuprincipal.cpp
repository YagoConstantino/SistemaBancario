#include "menuprincipal.h"
#include "ui_menuprincipal.h"
#include "mainwindow.h"  // Para poder fazer dynamic_cast

MenuPrincipal::MenuPrincipal(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MenuPrincipal)
{
    ui->setupUi(this);

    connect(ui->Sair,
            &QPushButton::clicked,
            this,
            &MenuPrincipal::voltarLogin);
}

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}

void MenuPrincipal::voltarLogin()
{
    // Recupera o ponteiro para a MainWindow
    if (auto mw = qobject_cast<MainWindow*>(parentWidget())) {
        mw->show();   // Reexibe a janela principal
    }
    this->close();    // Fecha o diálogo
}
