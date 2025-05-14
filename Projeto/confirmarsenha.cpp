#include "confirmarsenha.h"
#include "ui_confirmarsenha.h"
#include "menuprincipal.h"
#include <QMessageBox>
#include <QSqlQuery>
ConfirmarSenha::ConfirmarSenha(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmarSenha)
{
    ui->setupUi(this);

    connect(ui->MostrarSenhaCheckbox,SIGNAL(clicked(bool)),this,SLOT(mostrarSenha(bool)));
    connect(ui->OkBtn,SIGNAL(clicked()),this,SLOT(senhaOk()));
}

ConfirmarSenha::~ConfirmarSenha()
{
    delete ui;
}

void ConfirmarSenha::senhaOk()
{
    // Obtém CPF da conta ativa
    MenuPrincipal *menu = qobject_cast<MenuPrincipal*>(parentWidget());
    if (!menu) {
        QMessageBox::warning(this, tr("Erro"), tr("Não foi possível obter a conta."));
        reject();  // retorna false
        return;
    }
    QString cpf = menu->getConta()->getCPF();
    QString senhaDigitada = ui->SenhaTxt->text();
    QSqlDatabase BD = menu->getConta()->getDataBase();

    // Consulta no DB
    QSqlQuery query(BD);
    query.prepare("SELECT Senha FROM Cadastro WHERE CPF = ?");
    query.addBindValue(cpf);
    if (!query.exec() || !query.next()) {
        // CPF não existe ou erro
        QMessageBox::warning(this, tr("Erro"), tr("CPF não encontrado."));
        reject();  // retorna false
        return;
    }

    QString senhaArmazenada = query.value(0).toString();
    if (senhaDigitada == senhaArmazenada) {
        accept();  // retorna true
    } else {
        QMessageBox::warning(this, tr("Senha inválida"),
                             tr("A senha informada está incorreta."));
        reject();  // fecha e retorna false em caso de senha errada
    }
}

void ConfirmarSenha::mostrarSenha(bool checked)
{
    ui->SenhaTxt->setEchoMode(checked ? QLineEdit::Normal: QLineEdit::Password);
}
