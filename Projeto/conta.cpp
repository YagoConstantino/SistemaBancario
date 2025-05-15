#include "conta.h"
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
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

    QString extrato = QString("- %1 R$").arg(QString::number(qtdSaque, 'f', 2));
    QString hoje = QDate::currentDate().toString(Qt::ISODate);
    QSqlQuery queryExtrato(bancoDeDados);
    queryExtrato.prepare(R"(
    INSERT INTO TransacoesSaidas
    (CPF,valorTransacao,dataTransacao)
    VALUES (?,?,?)
    )");

    queryExtrato.addBindValue(CPF);
    queryExtrato.addBindValue(extrato);
    queryExtrato.addBindValue(hoje);
    if(!queryExtrato.exec())
    {
        qDebug() << "Erro na execução da query de extrato em FazerSaque Ccnta "<< queryExtrato.lastError().text();
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

    QString extrato = QString("+ %1 R$").arg(QString::number(qtdDeposito, 'f', 2));
    QString hoje = QDate::currentDate().toString(Qt::ISODate);
    QSqlQuery queryExtrato(bancoDeDados);
    queryExtrato.prepare(R"(
    INSERT INTO TransacoesEntrada
    (CPF,valorTransacao,dataTransacao)
    VALUES (?,?,?)
    )");

    queryExtrato.addBindValue(CPF);
    queryExtrato.addBindValue(extrato);
    queryExtrato.addBindValue(hoje);
    if(!queryExtrato.exec())
    {
        qDebug() << "Erro na execução da query de extrato em FazerDeposito Conta "<< queryExtrato.lastError().text();
        return false;
    }


    return true;

}

bool Conta::fazerTransf(double qtdTransf, QString cpfReceptor)
{

    saldo -= qtdTransf;
    //verificar se abriu o banco de dados
    if (!bancoDeDados.isOpen() && !bancoDeDados.open()) {
        qDebug() << "Erro ao abrir DB em FazerTransf Conta:"
                 << bancoDeDados.lastError().text();
        return false;
    }

    //Verificar se o cpf receptor existe e recuperar seu saldo atual
    QSqlQuery querySaldoReceptora(bancoDeDados);

    querySaldoReceptora.prepare(R"(
        SELECT Saldo
        FROM Saldo
        WHERE CPF = ?

    )");

    querySaldoReceptora.addBindValue(cpfReceptor);

    if(!querySaldoReceptora.exec())
    {
        qDebug() << "Erro em recuperar o Saldo da conta Receptora em fazerTransferencia em conta: "
                 << querySaldoReceptora.lastError().text();
        return false;
    }
    if(!querySaldoReceptora.next())
    {
        qDebug() << "CPF não encontrado EM Transferencia conta:" << cpfReceptor;
        return false;
    }

    double saldoReceptora = querySaldoReceptora.value(0).toDouble();
    saldoReceptora += qtdTransf;


    if(!bancoDeDados.open() && !bancoDeDados.isOpen())
    {
        qDebug() << "Erro ao Abrir Banco de Dados em fazerTransf Conta"
                 << bancoDeDados.lastError().text();
        return false;
    }

    //atualizar saldo na conta transmissora
    QSqlQuery querySaldoTrans(bancoDeDados);

    querySaldoTrans.prepare(R"(
    UPDATE Saldo
    SET Saldo = ?
    WHERE CPF = ?
    )");

    querySaldoTrans.addBindValue(saldo);
    querySaldoTrans.addBindValue(CPF);

    if(!querySaldoTrans.exec())
    {
        qDebug()<<"Erro na execução da query em fazerTransf Conta : "
                 << querySaldoTrans.lastError().text();
        return false;
    }

    //atualizar em transações saida da conta transmissora
    QSqlQuery queryExtratoTrans(bancoDeDados);
    QString extratoSaida = QString("- %1 R$").arg(QString::number(qtdTransf, 'f', 2));
    QString hoje = QDate::currentDate().toString(Qt::ISODate);

    queryExtratoTrans.prepare(R"(
    INSERT INTO TransacoesSaidas
    (CPF,valorTransacao,dataTransacao)
    VALUES (?,?,?)
    )");

    queryExtratoTrans.addBindValue(CPF);
    queryExtratoTrans.addBindValue(extratoSaida);
    queryExtratoTrans.addBindValue(hoje);
    if(!queryExtratoTrans.exec())
    {
        qDebug() << "Erro na execução da query de extrato em fazerTransferencia Conta "
                 << queryExtratoTrans.lastError().text();
        return false;
    }

    //atualizar saldo na conta receptora

    QSqlQuery queryAtualizaSaldoRec(bancoDeDados);

    queryAtualizaSaldoRec.prepare(R"(
    UPDATE Saldo
    SET Saldo = ?
    WHERE CPF = ?
    )");

    queryAtualizaSaldoRec.addBindValue(saldoReceptora);;
    queryAtualizaSaldoRec.addBindValue(cpfReceptor);

    if(!queryAtualizaSaldoRec.exec())
    {
        qDebug () << "Erro ao atualizar o saldo da conta recptora em FazerTransferencia em conta :"
                 << queryAtualizaSaldoRec.lastError().text();

        return false;
    }
    //atualizar em transações de entrada da conta receptora
    QSqlQuery queryExtratoEntrada(bancoDeDados);
    QString extratoEntrada = QString("+ %1 R$").arg(QString::number(qtdTransf, 'f', 2));

    queryExtratoEntrada.prepare(R"(
    INSERT INTO TransacoesEntrada
    (CPF,valorTransacao,dataTransacao)
    VALUES (?,?,?)
    )");
    queryExtratoEntrada.addBindValue(cpfReceptor);
    queryExtratoEntrada.addBindValue(extratoEntrada);
    queryExtratoEntrada.addBindValue(hoje);

    if(!queryExtratoEntrada.exec())
    {
        qDebug() << "Erro ao salvar extrato de Entrada em fazer Transferencia em conta : "
                 << queryExtratoEntrada.lastError().text();
        return false;
    }

    return true;
}

bool Conta::encerrarConta()
{
    //verificar se o saldo é = 0   //verificar se a fatura é = 0
    if(saldo!= 0 || faturaCredito != 0)
    {
        qDebug() << "Erro Para encerrar sua conta deve sacar todo seu saldo não ter uma fatura pendente";
        return false;
    }

    if(!bancoDeDados.isOpen() && !bancoDeDados.open())
    {
        qDebug()<<"Erro ao abrir banco de dados em encerrarConta em Conta: "
                 <<bancoDeDados.lastError().text();
        return false;
    }

    //apagar de Cadastro
    QSqlQuery queryCadastro(bancoDeDados);

    queryCadastro.prepare(R"(
    DELETE FROM Cadastro
    WHERE CPF = ?
    )");

    queryCadastro.addBindValue(CPF);

    if(!queryCadastro.exec())
    {
        qDebug()<<"Erro na execução do delete em Cadastro no EncerrarConta em Conta: "
                 <<queryCadastro.lastError().text();

        return false;
    }

    //apagar de Saldo
    QSqlQuery querySaldo(bancoDeDados);

    querySaldo.prepare(R"(
    DELETE FROM Saldo
    WHERE CPF = ?

    )");

    querySaldo.addBindValue(CPF);

    if(!querySaldo.exec())
    {
        qDebug()<<"Erro na execução do Delete em Saldo no encerrarConta em Conta: "
                 <<querySaldo.lastError().text();
        return false;
    }
    //apagar de Credito
    QSqlQuery queryCredito(bancoDeDados);

    queryCredito.prepare(R"(
    DELETE FROM CREDITO
    WHERE CPF = ?
    )");

    queryCredito.addBindValue(CPF);

    if(!queryCredito.exec())
    {
        qDebug () <<"Erro ao executar o DELETE em Credito em encerrarConta na Conta: "
                 <<queryCredito.lastError().text();
        return false;
    }

    // apagar de TransacoesEntrada
    QSqlQuery queryTrasEntra(bancoDeDados);
    queryTrasEntra.prepare(R"(
    DELETE FROM TransacoesEntrada
    WHERE CPF = ?
    )");

    queryTrasEntra.addBindValue(CPF);

    if(!queryTrasEntra.exec())
    {
        qDebug() << "Erro na execuçã odo DELETE em Transacoes Entrada em encerrar Conta na classe Conta : "
                 <<queryTrasEntra.lastError().text();
        return false;
    }

    //apagar de TransacoesSaidas
    QSqlQuery queryTrasSaida(bancoDeDados);

    queryTrasSaida.prepare(R"(
    DELETE FROM TransacoesSaidas
    WHERE CPF = ?
    )");
    queryTrasSaida.addBindValue(CPF);

    if(!queryTrasSaida.exec())
    {
        qDebug () <<"Erro na execução do DELETE em TransacoesSaidas em encerrarConta na classe Conta :"
                 <<queryTrasSaida.lastError().text();
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

const QString Conta::getExtrato()
{
    atualizaExtratoLocal();
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

bool Conta::pagarFaturaCredito(double qtdPagamento){
    saldo -= qtdPagamento;
    faturaCredito -= qtdPagamento;

    // Verifica se o Banco de Dados ta aberto
    if (!bancoDeDados.isOpen() && !bancoDeDados.open()) {
        qDebug() << "Erro ao abrir DB em FazerSaque Conta:"
                 << bancoDeDados.lastError().text();
        return false;
    }

    // Atualiza no Banco de Dados:
    // Saldo
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
        qDebug()<<"Erro na execução da query em pagarFaturaCredito Conta : " << query.lastError().text();
        return false;
    }

    // Credito
    query.prepare(R"(
    UPDATE Credito
    set fatura_atual = ?
    where CPF = ?
    )");

    query.addBindValue(faturaCredito);
    query.addBindValue(CPF);

    if(!query.exec())
    {
        qDebug()<<"Erro na execução da query em pagarFaturaCredito Conta : " << query.lastError().text();
        return false;
    }

    // Atualiza extrato

    QString extrato = QString("- %1 R$").arg(QString::number(qtdPagamento, 'f', 2));
    QString hoje = QDate::currentDate().toString(Qt::ISODate);
    QSqlQuery queryExtrato(bancoDeDados);
    queryExtrato.prepare(R"(
    INSERT INTO TransacoesSaidas
    (CPF,valorTransacao,dataTransacao)
    VALUES (?,?,?)
    )");

    queryExtrato.addBindValue(CPF);
    queryExtrato.addBindValue(extrato);
    queryExtrato.addBindValue(hoje);

    if(!queryExtrato.exec())
    {
        qDebug() << "Erro na execução da query de extrato em FazerDeposito Conta "<< queryExtrato.lastError().text();
    }

    return true;
}

void Conta::atualizaExtratoLocal(){
    struct Registro{
        QString valor;
        QDate data;
    };

    std::vector<Registro> registros;
    registros.reserve(50);

    if(!bancoDeDados.isOpen() && !bancoDeDados.open())
    {
        qDebug() << "Erro ao abrir BD em atualizar extrato: "
                 << bancoDeDados.lastError().text();
        return;
    }

    QSqlQuery query(bancoDeDados);

    // Relativo as transacoes de entrada

    query.prepare
    (
        R"(
        SELECT valorTransacao, dataTransacao
        FROM TransacoesEntrada
        WHERE CPF = ?
        )"
    );

    query.addBindValue(CPF);

    if (!query.exec())
    {
        qDebug() << "Erro ao executar atualizar extrato:"
                 << query.lastError().text();
        return;
    }

    // Enquanto houver linhas e não ultrapassar o limite
    int i = 0;
    while(query.next() && i < 25){

        // Adiciona as transacoes de entradas
        Registro r;
        r.valor = query.value(0).toString();
        r.data = query.value(1).toDate();
        registros.push_back(r);

        i++;
    }

    // Relativo as transacoes de saida

    query.prepare
    (
        R"(
        SELECT valorTransacao, dataTransacao
        FROM TransacoesSaidas
        WHERE CPF = ?
        )"
    );

    query.addBindValue(CPF);

    if (!query.exec())
    {
        qDebug() << "Erro ao executar atualizar extrato:"
                 << query.lastError().text();
        return;
    }

    // Enquanto houver linhas e não ultrapassar o limite
    while(query.next() && i < 50){

        // Adiciona as transacoes de saidas
        Registro r;
        r.valor = query.value(0).toString();
        r.data = query.value(1).toDate();
        registros.push_back(r);

        i++;
    }

    // Ordenar todas as transações por data decrescente
    std::sort(registros.begin(), registros.end(), [](const Registro &a, const Registro &b) {
        return a.data > b.data;
    });

    // Forma o novo extrato
    QString extratoNovo;

    size_t tam = registros.size();
    for(int k = 0; k < tam; k++)
        extratoNovo.append(registros[k].valor + "; Data: " + registros[k].data.toString("dd/MM/yyyy") + '\n');

    // Atualiza
    extrato = extratoNovo;
}
