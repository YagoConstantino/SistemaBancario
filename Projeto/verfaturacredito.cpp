#include "verfaturacredito.h"
#include "ui_verfaturacredito.h"
#include "menuprincipal.h"
#include <qevent.h>

VerFaturaCredito::VerFaturaCredito(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerFaturaCredito)
    ,MenuPrin(nullptr)

{
    ui->setupUi(this);
    setWindowTitle("Fatura de Crédito");
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
    connect(ui->PagarButton,SIGNAL(clicked()),this,SLOT(pagarFatura()));
}

VerFaturaCredito::~VerFaturaCredito()
{
    delete ui;
}

void VerFaturaCredito::voltarMenu()
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    MenuPrin->show();
    close();
}

void VerFaturaCredito::closeEvent(QCloseEvent *event)
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    if (MenuPrin)
        MenuPrin->show();

    event->accept();
}

void VerFaturaCredito::pagarFatura()
{
    // Criar uma janela parecida com a do deposito, pegar a quantidade e alterar no saldo e fatura no banco de dados
}
