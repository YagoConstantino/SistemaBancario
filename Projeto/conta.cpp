#include "conta.h"
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
Conta::Conta()
:
    nome(),
    nomeMae(),
    senha(),
    CPF(),
    email(),
    extrato(),
    dataNascimento(),
    faturaCredito(),
    creditoDisponivel(),
    creditoTotal(),
    saldo(),
    bancoDeDados()

{
    bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    bancoDeDados.setDatabaseName("../../db_Projeto.db");

    if (!bancoDeDados.open()) {
        qDebug() << "Erro ao abrir banco:" << bancoDeDados.lastError().text();
    }
    else
        qDebug() << "Banco aberto com sucesso";

}

Conta::~Conta()
{
    bancoDeDados.close();
}

bool Conta::fazerSaque(double qtdSaque)
{
    if(qtdSaque > saldo) return false;
    if(qtdSaque < 0) return false;
    //Atualiza localmente
    saldo -= qtdSaque;

    //Verifica se o Banco de Dados ta aberto
    if (!bancoDeDados.isOpen() && !bancoDeDados.open()) {
        qDebug() << "Erro ao abrir DB em FazerSaque Conta:"
                 << bancoDeDados.lastError().text();
        return false;
    }

    //Atualiza no Banco de Dados
    QSqlQuery query(bancoDeDados);
    query.prepare(R"(
    UPDATE Saldo
    set Saldo = ?
    where CPF = ?
    )");

    query.addBindValue(saldo);
    query.addBindValue(CPF);

    if(!query.exec())
    {
        qDebug()<<"Erro na execução da query em fazerSaque Conta : " << query.lastError().text();
        return false;
    }

    return true;

}

bool Conta::fazerDeposito(double qtdDeposito)
{
    if(qtdDeposito < 0) return false;
    //Atualiza localmente
    saldo += qtdDeposito;

    //Verifica se o Banco de Dados ta aberto
    if (!bancoDeDados.isOpen() && !bancoDeDados.open()) {
        qDebug() << "Erro ao abrir DB em FazerDeposito Conta:"
                 << bancoDeDados.lastError().text();
        return false;
    }

    //Atualiza no Banco de Dados
    QSqlQuery query(bancoDeDados);
    query.prepare(R"(
    UPDATE Saldo
    set Saldo = ?
    where CPF = ?
    )");

    query.addBindValue(saldo);
    query.addBindValue(CPF);

    if(!query.exec())
    {
        qDebug()<<"Erro na execução da query em fazerDeposito Conta : " << query.lastError().text();
        return false;
    }

    return true;

}

double Conta::getSaldo()
{
    return saldo;
}

double Conta::getFaturaCred()
{
    return faturaCredito;
}

QString Conta::getExtrato()
{
    return extrato;
}

void Conta::setNome(QString novoNome)
{
    nome = novoNome;
}

const QString Conta::getNome() const
{
    return nome;
}

void Conta::setNomeMae(QString novoNomeMae)
{
    nomeMae = novoNomeMae;
}

const QString Conta::getNomeMae() const
{
    return nomeMae;
}

void Conta::setSenha(QString novaSenha)
{
    //verificar novasenha com regex
    senha = novaSenha;
}

const QString  Conta::getSenha() const
{
    return senha;
}

void Conta::setCPF(QString novoCPF)
{
    CPF = novoCPF;
}

void Conta::setEmail(QString novoEmail)
{
    // verificar novo email com regex
    email = novoEmail;
}

const QString  Conta::getEmail() const
{
    return email;
}

const QString Conta::getExtrato() const
{
    return extrato;
}

void Conta::setDataNascimeto(QDate novoNascimento)
{
    dataNascimento = novoNascimento;
}

const QDate Conta::getNascimento() const
{
    return dataNascimento;
}

void Conta::setSaldo(double novoSaldo)
{
    saldo = novoSaldo;
}

const double Conta::getSaldo() const
{
    return saldo;
}

void Conta::setCreditoTotal(double novoCredTotal)
{
    creditoTotal = novoCredTotal;
    creditoDisponivel = creditoTotal - faturaCredito;
}

const QString Conta::getCPF() const
{
    return CPF;
}

const double Conta::getCredTotal() const
{
    return creditoTotal;
}

const double Conta::getCredDisponivel() const
{
    return creditoDisponivel;
}

void Conta::setFaturaCred(double novaFatCred)
{
    faturaCredito = novaFatCred;
}

const double Conta::getFaturaCred() const
{
    return faturaCredito;
}

const QSqlDatabase Conta::getDataBase() const
{
    return bancoDeDados;
}

bool Conta::CadastraContaBD()
{
    setSaldo(0.0);
    creditoDisponivel = 0.0;
    creditoTotal = 0.0;
    faturaCredito = 0.0;
    extrato = "";


    // 1) Banco aberto?
    if (!bancoDeDados.isOpen() && !bancoDeDados.open()) {
        qDebug() << "Erro ao abrir DB em CadastraContaBD:"
                 << bancoDeDados.lastError().text();
        return false;
    }

    // 2) Calcula idade…
    QDate hoje = QDate::currentDate();
    int idade = hoje.year() - dataNascimento.year();
    if (hoje < QDate(hoje.year(),
                     dataNascimento.month(),
                     dataNascimento.day()))
        --idade;

    // 3) INSERT em Cadastro
    {
        QSqlQuery query(bancoDeDados);
        const QString sql =
            "INSERT INTO Cadastro "
            "(CPF, Nome, NomeMae, Idade, Email, Senha, DataNascimento) "
            "VALUES (?, ?, ?, ?, ?, ?, ?)";
        if (!query.prepare(sql)) {
            qDebug() << "Erro no prepare Cadastro:"
                     << query.lastError().text()  // query, não outro objeto
                     << "\nSQL =" << sql;
            return false;
        }

        query.addBindValue(CPF);
        query.addBindValue(nome);
        query.addBindValue(nomeMae);
        query.addBindValue(idade);
        query.addBindValue(email);
        query.addBindValue(senha);
        query.addBindValue(dataNascimento.toString(Qt::ISODate));

        if (!query.exec()) {
            qDebug() << "Erro ao exec Cadastro:"
                     << query.lastError().text();
            return false;
        }
    }

    // 4) INSERT em Credito
    {
        QSqlQuery queryCredito(bancoDeDados);
        const QString sql =
            "INSERT INTO Credito "
            "(CPF, credito_total, fatura_atual) "
            "VALUES (?, ?, ?)";
        if (!queryCredito.prepare(sql)) {
            qDebug() << "Erro no prepare Credito:"
                     << queryCredito.lastError().text()
                     << "\nSQL =" << sql;
            return false;
        }

        queryCredito.addBindValue(CPF);
        queryCredito.addBindValue(0);
        queryCredito.addBindValue(0);


        if (!queryCredito.exec()) {
            qDebug() << "Erro ao exec Credito:"
                     << queryCredito.lastError().text();
            return false;
        }
    }

    // 5) INSERT em Saldo
    {
        QSqlQuery querySaldo(bancoDeDados);
        const QString sql =
            "INSERT INTO Saldo "
            "(CPF, Saldo) "
            "VALUES (?, ?)";
        if (!querySaldo.prepare(sql)) {
            qDebug() << "Erro no prepare Saldo:"
                     << querySaldo.lastError().text()
                     << "\nSQL =" << sql;
            return false;
        }

        querySaldo.addBindValue(CPF);
        querySaldo.addBindValue(0);

        if (!querySaldo.exec()) {
            qDebug() << "Erro ao exec Saldo:"
                     << querySaldo.lastError().text();
            return false;
        }
    }

    return true;
}
