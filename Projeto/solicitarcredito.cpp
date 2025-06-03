#include "solicitarcredito.h"
#include "ui_solicitarcredito.h"
#include "menuprincipal.h"

SolicitarCredito::SolicitarCredito(QWidget *parent)
    : QDialog(parent)
    , menuPrincipal(nullptr)
    , ui(new Ui::SolicitarCredito)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    preencheDados();
    conectarBotoes();
}

SolicitarCredito::~SolicitarCredito()
{
    delete ui;
}

// Volta ao menu principal
void SolicitarCredito::voltar()
{
    menuPrincipal = qobject_cast<MenuPrincipal*>(parentWidget());
    menuPrincipal->show();
    close();
}

void SolicitarCredito::conectarBotoes()
{
    connect(ui->Voltar,SIGNAL(clicked(bool)),this,SLOT(voltar()));
    connect(ui->Confirmar, SIGNAL(clicked(bool)),this,SLOT(confirmar()));
}

// Verifica as possíveis entradas do usuário na caixa para solicitar crédito
const bool SolicitarCredito::verificaEntrada()
{
    if(ui->QtdSolic2->text().isEmpty()){
        QMessageBox::warning(this, "Erro", "Crédito solicitado não preenchido.");

        return false;
    }

    bool ok = true;
    double credSolic = ui->QtdSolic2->text().toDouble(&ok);

    if(!ok){
        QMessageBox::warning(this, "Erro", "Valor inserido inválido.");

        return false;
    }
    if(credSolic < 0.f){
        QMessageBox::warning(this, "Erro", "Valores negativos não são permitidos.");

        return false;
    }
    else if(credSolic > ui->maxSolic2->text().toDouble()){
        QMessageBox::warning(this, "Erro", "Crédito solicitado maior que o permitido.");

        return false;
    }

    return true;
}

// Modifica a conta atual com o crédito solicitado
void SolicitarCredito::confirmar()
{
    if(!verificaEntrada()) return;

    Conta* conta = Conta::getInstancia();

    menuPrincipal = qobject_cast<MenuPrincipal*>(parentWidget());
    ConfirmarSenha dlg(menuPrincipal);

    if(dlg.exec() == QDialog::Accepted)
    {
        double novoCredito = conta->getCredTotal() + ui->QtdSolic2->text().toDouble();
        if(conta->atualizaCreditoBD(novoCredito))
        {
            QMessageBox::information(this,"Sucesso","Solicitação feita com Sucesso");
        }
        else
            QMessageBox::information(this,"Erro","Solicitação não concluída");

        voltar();
    }
}

// Preenche os dados dos textos da janela que dependem da conta atual
void SolicitarCredito::preencheDados()
{
    Conta* conta = Conta::getInstancia();

    QString maxSolic = QString::number(conta->getSaldo() * 2.5, 'l', 2);
    QString credAtual = QString::number(conta->getCredDisponivel(), 'l', 2);
    credAtual += " de " + QString::number(conta->getCredTotal(), 'l', 2);

    ui->credAtual2->setText(credAtual);
    ui->maxSolic2->setText(maxSolic);
}
