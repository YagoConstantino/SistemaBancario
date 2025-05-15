#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <regex>
#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    _MenuPrin(nullptr),
    _cad(nullptr),
    _Esq(nullptr),
    _CPFlogin(),
    _SenhaLogin(),
    contaAtual()
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose); Desnecessário para essa janela

    connect(ui->Confirmar,SIGNAL(clicked()),this,SLOT(Menu_Principal()));
    connect(ui->CriarConta,SIGNAL(clicked()),this,SLOT(AbrirCadastro()));
    connect(ui->EsqueceuSenha,SIGNAL(clicked()),this,SLOT(AbrirEsqueceuSenha()));
    connect(ui->MostrarSenha,SIGNAL(clicked(bool)),this,SLOT(mostrarSenha(bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Ser implementado depois , deve pegar os dados no banco de dados e inserir na conta atual
bool MainWindow::recuperarDadosConta()
{
    return false;
}

//Ser implementada depois, deve verificar no banco de dados se o login(CPF) existe e se a senha bate
//deve tambem chamar a recuperarDadosConta
bool MainWindow::verificarDadosConta(QString login, QString senha)
{

    string log = login.toStdString();
    string sen = senha.toStdString();

    regex padraoCPF(R"(^([0-9]{3}\.?){3}-?[0-9]{2}$)");
    regex padraoSenha(R"(^(?=.*[A-Z])(?=.*[0-9])(?=.*[^A-Za-z0-9]).{8,16}$)");

    if(!regex_match(log,padraoCPF) || !regex_match(sen,padraoSenha))
    {
        return false;
    }

    //Além dessa verificação devemos verificar no banco de dados se o login(CPF) existe e se a senha bate

    return verificaContaExiste() && recuperaDadosBanco();
}

Conta *MainWindow::getConta()
{
    return &contaAtual;
}

void MainWindow::clearTexto()
{
    ui->Login->clear();
    ui->Senha->clear();
}

void MainWindow::Menu_Principal()
{
    //Aqui deve ser feito a vericação do login e senha, se existem no banco de dados e se a senha confere
    //para dai então ir para o menuPrincipal, aqui(mainWindow) ou la deve ser armazenado o CPF ou ID
    //ou primarykey da conta para usarmos no conector do banco de dados, ou seja so armazenamos um dado
    _CPFlogin = ui->Login->text();
    _SenhaLogin = ui->Senha->text();

    if (verificarDadosConta(_CPFlogin,_SenhaLogin))
    {
        _MenuPrin = new MenuPrincipal(this);
        _MenuPrin->show();
        hide();
    }
    else
    {
        QMessageBox::warning(this,"Erro","Login ou senha inválidos");
        ui->Login->clear();
        ui->Senha->clear();
    }
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

bool MainWindow::verificaContaExiste()
{
    QSqlDatabase BD = contaAtual.getDataBase();
    //Verifica se o BD existe e esta aberto
    if(!BD.isOpen() && BD.open())
    {
        qDebug() << "Erro ao abrir DB em verificaContaExiste:"
                 << BD.lastError().text();
        return false;
    }

    //cria a query
    QSqlQuery queryCadastro(BD);
    queryCadastro.prepare(R"(
    SELECT Senha
    FROM Cadastro
    WHERE CPF = ?
    )");

    //vincula o CPF dado
    queryCadastro.addBindValue(_CPFlogin);

    //Ve se query funcionou
    if(!queryCadastro.exec())
    {
        qDebug() << "Erro ao executar verificarContaExiste:"
                 << queryCadastro.lastError().text();
        return false;

    }

    //Ve se o cpf existe
    if(!queryCadastro.next())
    {
        qDebug() << "CPF não encontrado:" << _CPFlogin;
        return false;
    }

    // compara a senha
    QString senhaArmazenada = queryCadastro.value(0).toString();
    if (senhaArmazenada != _SenhaLogin) {
        qDebug() << "Senha incorreta para o CPF:" << _CPFlogin;
        QMessageBox::warning(this,"Erro","Senha incorreta para o CPF ");
        return false;
    }



    return true;
}

bool MainWindow::recuperaDadosBanco()
{
    QSqlDatabase BD = contaAtual.getDataBase();

    if(!BD.isOpen() && !BD.open())
    {
        qDebug() << "Erro ao abrir DB em RecuperaDadosBanco: "
                 << BD.lastError().text();
        return false;
    }
    //Recupera a parte do cadastro
    QSqlQuery queryCad(BD);

    queryCad.prepare
    (
        R"(
        SELECT Nome, NomeMae, Email, Senha, DataNascimento
        FROM Cadastro
        WHERE CPF = ?
        )"
    );
    queryCad.addBindValue(_CPFlogin);

    if (!queryCad.exec())
    {
        qDebug() << "Erro ao executar recuperarDadosConta Cadastro:"
                 << queryCad.lastError().text();
        return false;
    }

    if (!queryCad.next()) {
        qDebug() << "Nenhum registro encontrado para CPF Cadastro" << _CPFlogin;
        return false;
    }

    //Atualiza na conta local
    contaAtual.setCPF(_CPFlogin);
    contaAtual.setNome(queryCad.value(0).toString());
    contaAtual.setNomeMae( queryCad.value(1).toString());
    contaAtual.setEmail(   queryCad.value(2).toString());
    contaAtual.setSenha(   queryCad.value(3).toString());
    // Se quiser também recuperar a data de nascimento:
    QDate nasc = QDate::fromString(queryCad.value(4).toString(), Qt::ISODate);
    contaAtual.setDataNascimeto(nasc);

    //Recupera do Saldo
    QSqlQuery querySaldo(BD);

    querySaldo.prepare(R"(
    SELECT Saldo
    FROM Saldo
    WHERE  CPF = ?

    )");

    querySaldo.addBindValue(_CPFlogin);

    if (!querySaldo.exec())
    {
        qDebug() << "Erro ao executar recuperarDadosConta Saldo:"
                 << querySaldo.lastError().text();
        return false;
    }


    if (!querySaldo.next()) {
        qDebug() << "Nenhum registro encontrado para CPF Saldo" << _CPFlogin;
        return false;
    }

    contaAtual.setSaldo(querySaldo.value(0).toDouble());

    QSqlQuery queryCredito(BD);

    queryCredito.prepare(R"(
    SELECT credito_total,fatura_atual
    FROM Credito
    WHERE CPF = ?
    )");

    queryCredito.addBindValue(_CPFlogin);

    if(!queryCredito.exec())
    {
        qDebug() << "Erro ao executar Query RecuperarDadosConta Credito:"
                 <<queryCredito.lastError().text();
    }

    if (!queryCredito.next()) {
        qDebug() << "Nenhum registro encontrado para CPF Credito" << _CPFlogin;
        return false;
    }

    contaAtual.setFaturaCred(queryCredito.value(1).toDouble());
    contaAtual.setCreditoTotal(queryCredito.value(0).toDouble());

    return true;
}

