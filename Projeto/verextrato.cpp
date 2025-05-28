#include "verextrato.h"
#include "ui_verextrato.h"
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QPageLayout>
#include <QFontMetrics>
#include "menuprincipal.h"
#include <qevent.h>

VerExtrato::VerExtrato(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerExtrato),
    MenuPrin(nullptr)
    ,DadosExtrato()
{
    ui->setupUi(this);
    setWindowTitle("Ver Extrato");
    setAttribute(Qt::WA_DeleteOnClose);

    setarExtrato();

    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
    connect(ui->SalvarPDFButton,SIGNAL(clicked()),this,SLOT(salvarPDF()));
}

VerExtrato::~VerExtrato()
{
    delete ui;
}

void VerExtrato::voltarMenu()
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    MenuPrin->show();
    close();
}

void VerExtrato::salvarPDF()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Salvar extrato em PDF", QString(), "PDF files (*.pdf)");

    if(filepath.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Extensão do Arquivo não era .pdf");
        return;
    }

    // Informações do cliente
    /*MenuPrincipal *menu = qobject_cast<MenuPrincipal*>(parentWidget());
    QString nome = menu->getConta()->getNome();
    QString CPF = menu->getConta()->getCPF();
    QString data = QDate::currentDate().toString("dd/MM/yyyy");
    QString extrato = ui->textEdit->toPlainText();*/


}

void VerExtrato::closeEvent(QCloseEvent *event)
{
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());
    if (MenuPrin)
        MenuPrin->show();

    event->accept();
}

void VerExtrato::setarExtrato(){
    Conta* conta = Conta::getInstancia();

    QString extrato = conta->getExtrato();

    ui->textEdit->setPlainText(extrato);
}
