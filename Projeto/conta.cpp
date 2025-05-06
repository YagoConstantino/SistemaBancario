#include "conta.h"

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
    bancoDeDados.setDatabaseName("../db_Projeto.db");

    if (!bancoDeDados.open()) {
        qDebug() << "Erro ao abrir banco:" << bancoDeDados.lastError().text();
    }
    else
        qDebug() << "Banco aberto com sucesso";
}

Conta::~Conta()
{

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

const QSqlDatabase Conta::getDataBase() const
{
    return bancoDeDados;
}
