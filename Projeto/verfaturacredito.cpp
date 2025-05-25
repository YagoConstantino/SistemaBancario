#include "verfaturacredito.h"
#include "ui_verfaturacredito.h"
#include "menuprincipal.h"
#include "confirmarsenha.h"
#include <qevent.h>

VerFaturaCredito::VerFaturaCredito(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VerFaturaCredito)
    ,MenuPrin(nullptr)
    ,CredTotal(0)
    ,CredDisponivel(0)
    ,FaturaCred(0)

{
    ui->setupUi(this);
    setWindowTitle("Fatura de Crédito");
    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarMenu()));
    connect(ui->PagarButton,SIGNAL(clicked()),this,SLOT(pagarFatura()));

    setarDadosCredito();
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

void VerFaturaCredito::setarDadosCredito()
{
    MenuPrincipal *menu = qobject_cast<MenuPrincipal*>(parentWidget());
    double credDisp = menu->getConta()->getCredDisponivel();
    double credTotal = menu->getConta()->getCredTotal();
    double fatura = menu->getConta()->getFaturaCred();

    QString dispTXT = QString::number(credDisp,'l',2);
    QString totalTXT = QString::number(credTotal,'l',2);
    QString fatTXT = QString::number(fatura,'l',2);

    ui->CredDispTxt->setText(dispTXT);
    ui->CredTotalTxt->setText(totalTXT);
    ui->FaturaTxt->setText(fatTXT);
}

void VerFaturaCredito::pagarFatura()
{
    // Criar uma janela parecida com a do deposito, pegar a quantidade e alterar no saldo e fatura no banco de dados
    MenuPrin = qobject_cast<MenuPrincipal*>(parentWidget());

    Conta* conta = Conta::getInstancia();

    // Verifica os valores inseridos para pagar a fatura
    bool ok = false;
    QtdPagar = ui->QtdPagarText->text().toDouble(&ok);

    if(!ok){
        QMessageBox::warning(this, "Erro", "Entrada de valor inválido");
        return;
    }
    else if(QtdPagar < 0.f){
        QMessageBox::warning(this, "Erro", "Valores negativos não são permitidos");
        return;
    }
    else if(QtdPagar > conta->getSaldo()){
        QMessageBox::warning(this, "Erro", "Valor inserido maior do que o saldo da conta");
        return;
    }
    else if(QtdPagar > conta->getFaturaCred()){
        QMessageBox::warning(this, "Erro", "Valor inserido maior do que a fatura");
        return;
    }

    ConfirmarSenha dlg(MenuPrin);
    // exec() retorna QDialog::Accepted (1) ou QDialog::Rejected (0)
    if(dlg.exec() == QDialog::Accepted)
    {
        if(conta->pagarFaturaCredito(QtdPagar))
        {
            QMessageBox::information(this,"Sucesso","Pagamento feito com Sucesso");
        }
        else
        {
            QMessageBox::information(this,"Erro","Pagamento não concluido");
        }
        //mostrar mensagem de sucesso ??
        voltarMenu();
    }
}
