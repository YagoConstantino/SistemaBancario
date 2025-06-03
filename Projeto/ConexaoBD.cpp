#include "ConexaoBD.h"

// Retorna o saldo da conta da conta com o cpf saldo
double ConexaoBD::getSaldo(QString cpf)
{
    QSqlQuery query(_bancoDeDados);

    query.prepare
    (R"(
        SELECT Saldo FROM Saldo
        WHERE CPF = ?
    )");

    query.addBindValue(cpf);

    if(!query.exec())
    {
        qDebug() << "Erro na execução da query em getSaldo de ConexaoBD: " << query.lastError().text();
        return std::numeric_limits<double>::max();
    }

    query.next();
    return query.value(0).toDouble();
}

// Retorna a fatura de credito da conta do cpf dado
double ConexaoBD::getFaturaCredito(QString cpf)
{
    QSqlQuery query(_bancoDeDados);

    query.prepare
    (R"(
        SELECT fatura_atual FROM Credito
        WHERE CPF = ?
    )");

    query.addBindValue(cpf);

    if(!query.exec())
    {
        qDebug() << "Erro na execução da query em getFaturaCredito de ConexaoBD "<< query.lastError().text();
        return std::numeric_limits<double>::max();
    }

    query.next();
    return query.value(0).toDouble();
}

// Retorna a senha da conta com o cpf dado
QString ConexaoBD::getSenha(QString cpf)
{
    QString senha;

    QSqlQuery query(_bancoDeDados);

    query.prepare
    (R"(
        SELECT Senha FROM Cadastro
        WHERE CPF = ?
    )");

    query.addBindValue(cpf);

    if(!query.exec())
    {
        qDebug() << "Erro na execução da query em getSenha de ConexaoBD "<< query.lastError().text();
        senha = "";
        return senha;
    }

    query.next();
    senha = query.value("Senha").toString();

    return senha;
}

// Retorna o nome da mae da conta com o cpf dado
QString ConexaoBD::getNomeMae(QString cpf)
{
    QString nome;
    nome.clear();

    QSqlQuery query(_bancoDeDados);

    query.prepare
    (R"(
        SELECT NomeMae FROM Cadastro
        WHERE CPF = ?
    )");

    query.addBindValue(cpf);

    if(!query.exec())
    {
        qDebug() << "Erro na execução da query em getNomeMae de ConexaoBD "<< query.lastError().text();
        nome = "";
        return nome;
    }

    query.next();
    nome = query.value(0).toString();

    return nome;
}

// atualiza o saldo da conta com o cpf dado
const bool ConexaoBD::setSaldo(QString cpf, double novoSaldo)
{
    QSqlQuery query(_bancoDeDados);
    query.prepare(R"(
        UPDATE Saldo
        SET Saldo = ?
        WHERE CPF = ?
    )");

    query.addBindValue(novoSaldo);
    query.addBindValue(cpf);

    if(!query.exec())
    {
        qDebug() << "Erro na execução da query em setSaldo de ConexaoBD: " << query.lastError().text();
        return false;
    }

    return true;
}

const bool ConexaoBD::setfaturaCredito(QString cpf, double novaFatura)
{
    QSqlQuery query(_bancoDeDados);

    query.prepare
    (R"(
        UPDATE Credito
        SET fatura_atual = ?
        WHERE CPF = ?
    )");

    query.addBindValue(novaFatura);
    query.addBindValue(cpf);

    if(!query.exec())
    {
        qDebug() << "Erro na execução da query em setFaturaCredito de ConexaoBD: " << query.lastError().text();
        return false;
    }

    return true;
}

// Atualiza a senha da conta com o cpf dado
const bool ConexaoBD::setSenha(QString cpf, QString novaSenha)
{
    QSqlQuery query(_bancoDeDados);

    query.prepare
    (R"(
        UPDATE Cadastro
        SET Senha = ?
        WHERE CPF = ?
    )");

    query.addBindValue(novaSenha);
    query.addBindValue(cpf);

    if(!query.exec())
    {
        qDebug() << "Erro na execução da query em setSenha de ConexaoBD: " << query.lastError().text();
        return false;
    }

    return true;
}

ConexaoBD::ConexaoBD() : _bancoDeDados(){
    _bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    _bancoDeDados.setDatabaseName("../../db_Projeto.db");

    if (!_bancoDeDados.open()) {
        qDebug() << "Erro ao abrir banco:" << _bancoDeDados.lastError().text();
    }
    else
        qDebug() << "Banco aberto com sucesso";
}

ConexaoBD::~ConexaoBD()
{
    _bancoDeDados.close();
}

// Atualiza o saldo da conta com o cpf dado
const bool ConexaoBD::fazerSaque(QString cpf, double qtdSaque)
{
    double saldo = getSaldo(cpf);
    if(saldo == std::numeric_limits<double>::max()) return false;

    setSaldo(cpf, saldo - qtdSaque);
    atualizaExtrato(cpf, qtdSaque, 0);

    return true;
}

// Atualiza o saldo da conta com o cpf dado
const bool ConexaoBD::fazerDeposito(QString cpf, double qtdDeposito)
{
    double saldo = getSaldo(cpf);
    if(saldo == std::numeric_limits<double>::max()) return false;

    setSaldo(cpf, saldo + qtdDeposito);
    atualizaExtrato(cpf, qtdDeposito, 1);

    return true;
}

// Atualiza o extrato da conta com o cpf dado
// se tipo for true, então eh entrada
// se tipo for false, então eh saida
const bool ConexaoBD::atualizaExtrato(QString cpf, double quantia, const bool tipo)
{
    QString extrato;

    // Data de hoje
    QString hoje = QDate::currentDate().toString(Qt::ISODate);

    QSqlQuery query(_bancoDeDados);

    if(tipo){
        extrato = QString("+ %1 R$").arg(QString::number(quantia, 'f', 2));

        query.prepare
        (R"(
            INSERT INTO TransacoesEntrada
            (CPF,valorTransacao,dataTransacao)
            VALUES (?,?,?)
        )");
    }
    else{
        extrato = QString("- %1 R$").arg(QString::number(quantia, 'f', 2));

        query.prepare
        (R"(
            INSERT INTO TransacoesSaidas
            (CPF,valorTransacao,dataTransacao)
            VALUES (?,?,?)
        )");
    }

    query.addBindValue(cpf);
    query.addBindValue(extrato);
    query.addBindValue(hoje);

    if(!query.exec())
    {
        qDebug() << "Erro na execução da query de extrato em atualizaExtrato em ConexaoBD "<< query.lastError().text();
        return false;
    }

    return true;
}

// Faz a transferencia de uma conta para a outra
// Atualiza o saldo e o extrato de ambas
const bool ConexaoBD::fazerTransferencia(QString cpfEmissor, QString cpfReceptor, double qtdTransf)
{
    QSqlQuery query(_bancoDeDados);

    // Relacionado a conta emissora (inicio)
    double saldo = getSaldo(cpfEmissor);

    if(saldo == std::numeric_limits<double>::max()) return false;

    setSaldo(cpfEmissor, saldo - qtdTransf);
    atualizaExtrato(cpfEmissor, qtdTransf, 0);
    // Relacionado a conta emissora (fim)

    // Relacionado a conta receptora (inicio)
    saldo = getSaldo(cpfReceptor);

    if(saldo == std::numeric_limits<double>::max()) return false;

    setSaldo(cpfReceptor, saldo + qtdTransf);
    atualizaExtrato(cpfReceptor, qtdTransf, 1);
    // Relacionado a conta receptora (fim)

    return true;
}

// Atualiza a fatura de credito da conta com o cpf dado
const bool ConexaoBD::pagarFaturaCredito(QString cpf, double qtdPagamento)
{
    double fatura = getFaturaCredito(cpf);
    if(fatura == std::numeric_limits<double>::max()) return false;

    setfaturaCredito(cpf, fatura - qtdPagamento);
    atualizaExtrato(cpf, qtdPagamento, 0);

    return true;
}

// Encerra a conta com o cpf dado
// Apaga todos os dados dela no banco de dados
const bool ConexaoBD::encerrarConta(QString cpf)
{
    //apagar de Cadastro
    QSqlQuery queryCadastro(_bancoDeDados);

    queryCadastro.prepare(R"(
    DELETE FROM Cadastro
    WHERE CPF = ?
    )");

    queryCadastro.addBindValue(cpf);

    if(!queryCadastro.exec())
    {
        qDebug()<<"Erro na execução do EncerrarConta em ConexaoBD: "
                 <<queryCadastro.lastError().text();

        return false;
    }

    //apagar de Saldo
    QSqlQuery querySaldo(_bancoDeDados);

    querySaldo.prepare(R"(
    DELETE FROM Saldo
    WHERE CPF = ?
    )");

    querySaldo.addBindValue(cpf);

    if(!querySaldo.exec())
    {
        qDebug()<<"Erro na execução do EncerrarConta em ConexaoBD: "
                 <<querySaldo.lastError().text();
        return false;
    }

    //apagar de Credito
    QSqlQuery queryCredito(_bancoDeDados);

    queryCredito.prepare(R"(
    DELETE FROM CREDITO
    WHERE CPF = ?
    )");

    queryCredito.addBindValue(cpf);

    if(!queryCredito.exec())
    {
        qDebug () <<"Erro ao executar EncerrarConta em ConexaoBD: "
                 <<queryCredito.lastError().text();
        return false;
    }

    // apagar de TransacoesEntrada
    QSqlQuery queryTrasEntra(_bancoDeDados);
    queryTrasEntra.prepare(R"(
    DELETE FROM TransacoesEntrada
    WHERE CPF = ?
    )");

    queryTrasEntra.addBindValue(cpf);

    if(!queryTrasEntra.exec())
    {
        qDebug() << "Erro na execução do EncerrarConta em ConexaoBD: "
                 <<queryTrasEntra.lastError().text();
        return false;
    }

    //apagar de TransacoesSaidas
    QSqlQuery queryTrasSaida(_bancoDeDados);

    queryTrasSaida.prepare(R"(
    DELETE FROM TransacoesSaidas
    WHERE CPF = ?
    )");
    queryTrasSaida.addBindValue(cpf);

    if(!queryTrasSaida.exec())
    {
        qDebug () <<"Erro na execução do EncerrarConta em ConexaoBD: "
                 <<queryTrasSaida.lastError().text();
        return false;
    }

    return true;
}

// Confirma a senha dada com a da conta com o cpf dado
const bool ConexaoBD::confirmarSenha(QString cpf, QString senhaDigitada)
{
    QString senha = getSenha(cpf);
    if(senha == "") return false;

    if(senha != senhaDigitada) return false;

    return true;
}

/*
Troca a senha da conta com o cpf dado
Tipos de saidas:
1: troca de senha feito
0: erro em Query
-1: nome da mae nao correspondente (incorreto)
*/
const int ConexaoBD::trocarSenha(QString cpf, QString nomeMae, QString senhaNova)
{
    QString nomeM = getNomeMae(cpf);
    if(nomeM == "") return 0;

    if(nomeM != nomeMae) return -1;

    return (int)setSenha(cpf, senhaNova);
}

/*
Verifica se a conta com o cpf dado existe
Tipos de saidas:
1: conta existe (cpf e senhaDigitada corretos)
0: erro na execucao de query
-1: cpf nao encontrado no banco de dados
-2: senhaDigitada nao correspondente (incorreta)
*/
const int ConexaoBD::verificaContaExistente(QString cpf, QString senhaDigitada)
{
    QSqlQuery query(_bancoDeDados);

    query.prepare(R"(
        SELECT Senha
        FROM Cadastro
        WHERE CPF = ?
    )");

    //vincula o CPF dado
    query.addBindValue(cpf);

    if(!query.exec())
    {
        qDebug() << "Erro ao executar verificaContaExistente em ConexaoBD:"
                 << query.lastError().text();
        return 0;
    }

    //Verifica se o cpf existe
    if(!query.next())
    {
        qDebug() << "CPF não encontrado:" << cpf;
        return -1;
    }

    // compara a senha
    QString senhaArmazenada = query.value(0).toString();
    if (senhaArmazenada != senhaDigitada) {
        qDebug() << "Senha incorreta para o CPF:" << cpf;
        return -2;
    }

    return 1;
}

// Recupera os dados da conta, com o cpf dado, no banco de dados
const bool ConexaoBD::recuperaDadosConta(QString cpf)
{
    Conta* conta = Conta::getInstancia();

    //Recupera a parte do cadastro
    QSqlQuery queryCad(_bancoDeDados);

    queryCad.prepare
    (
    R"(
        SELECT Nome, NomeMae, Email, Senha, DataNascimento
        FROM Cadastro
        WHERE CPF = ?
    )"
    );

    queryCad.addBindValue(cpf);

    if (!queryCad.exec())
    {
        qDebug() << "Erro ao executar recuperaDadosConta em ConexaoBD:"
                 << queryCad.lastError().text();
        return false;
    }

    if (!queryCad.next()) {
        qDebug() << "Nenhum registro encontrado para CPF de recuperaDadosConta em ConexaoBD" << cpf;
        return false;
    }

    //Atualiza na conta local
    conta->setCPF(cpf);
    conta->setNome(queryCad.value(0).toString());
    conta->setNomeMae(queryCad.value(1).toString());
    conta->setEmail(queryCad.value(2).toString());
    conta->setSenha(queryCad.value(3).toString());

    // Se quiser também recuperar a data de nascimento:
    QDate nasc = QDate::fromString(queryCad.value(4).toString(), Qt::ISODate);
    conta->setDataNascimeto(nasc);

    //Recupera do Saldo
    QSqlQuery querySaldo(_bancoDeDados);

    querySaldo.prepare(R"(
    SELECT Saldo
    FROM Saldo
    WHERE CPF = ?
    )");

    querySaldo.addBindValue(cpf);

    if (!querySaldo.exec())
    {
        qDebug() << "Erro ao executar recuperaDadosConta em ConexaoBD:"
                 << querySaldo.lastError().text();
        return false;
    }


    if (!querySaldo.next()) {
        qDebug() << "Nenhum registro encontrado para CPF Saldo" << cpf;
        return false;
    }

    conta->setSaldo(querySaldo.value(0).toDouble());

    // Recupera da tabela Credito no Banco de dados
    QSqlQuery queryCredito(_bancoDeDados);

    queryCredito.prepare(R"(
    SELECT credito_total,fatura_atual
    FROM Credito
    WHERE CPF = ?
    )");

    queryCredito.addBindValue(cpf);

    if(!queryCredito.exec())
    {
        qDebug() << "Erro ao executar Query em RecuperaDadosConta no ConexaoBD:"
                 <<queryCredito.lastError().text();
        return false;
    }

    if (!queryCredito.next()) {
        qDebug() << "Nenhum registro encontrado para CPF Credito" << cpf;
        return false;
    }

    conta->setFaturaCred(queryCredito.value(1).toDouble());
    conta->setCreditoTotal(queryCredito.value(0).toInt());

    return true;
}

const bool ConexaoBD::cadastraConta()
{
    Conta* conta = Conta::getInstancia();

    // INSERT em Cadastro
    {
        QSqlQuery query(_bancoDeDados);
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

        query.addBindValue(conta->getCPF());
        query.addBindValue(conta->getNome());
        query.addBindValue(conta->getNomeMae());
        query.addBindValue(conta->getIdade());
        query.addBindValue(conta->getEmail());
        query.addBindValue(conta->getSenha());
        query.addBindValue(conta->getNascimento().toString(Qt::ISODate));

        if (!query.exec()) {
            qDebug() << "Erro ao exec query de CadastroConta em ConexaoBD:"
                     << query.lastError().text();
            return false;
        }
    }

    // 4) INSERT em Credito
    {
        QSqlQuery queryCredito(_bancoDeDados);
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

        queryCredito.addBindValue(conta->getCPF());
        queryCredito.addBindValue(conta->getCredTotal());
        queryCredito.addBindValue(conta->getFaturaCred());

        if (!queryCredito.exec()) {
            qDebug() << "Erro ao exec Credito em CadastroConta de ConexaoBD:"
                     << queryCredito.lastError().text();
            return false;
        }
    }

    // 5) INSERT em Saldo
    {
        QSqlQuery querySaldo(_bancoDeDados);
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

        querySaldo.addBindValue(conta->getCPF());
        querySaldo.addBindValue(conta->getSaldo());

        if (!querySaldo.exec()) {
            qDebug() << "Erro ao exec Saldo em CadastroConta de ConexaoBD:"
                     << querySaldo.lastError().text();
            return false;
        }
    }

    return true;
}

// Atualiza o credito total da conta com o cpf dado
const bool ConexaoBD::atualizarCredito(QString cpf, int novoCredito)
{
    QSqlQuery query(_bancoDeDados);

    query.prepare
    (R"(
        UPDATE Credito
        SET credito_total = ?
        WHERE CPF = ?
    )");

    query.addBindValue(novoCredito);
    query.addBindValue(cpf);

    if (!query.exec()) {
        qDebug() << "Erro ao exec atualizarCredito de ConexaoBD:"
                 << query.lastError().text();
        return false;
    }

    return true;
}

// Devolve os extratos gravados no banco de dados e retorna em um unico texto
QString ConexaoBD::getExtrato(QString cpf){
    QString extrato;
    extrato.clear();

    QSqlQuery query(_bancoDeDados);

    // Auto explicativo
    query.prepare
        (
            R"(
        SELECT valorTransacao, dataTransacao
        FROM TransacoesSaidas
        WHERE CPF = ?

        UNION ALL

        SELECT valorTransacao, dataTransacao
        FROM TransacoesEntrada
        WHERE CPF = ?

        ORDER BY dataTransacao DESC, valorTransacao DESC
        LIMIT 50
        )"
            );

    query.addBindValue(cpf);
    query.addBindValue(cpf);

    if (!query.exec())
    {
        qDebug() << "Erro ao executar  getExtrato em ConexaoBD:"
                 << query.lastError().text();
        extrato = "";
        return extrato;
    }

    // Repreenche o extrato com informacoes atualizadas
    while(query.next()){
        extrato.append(query.value(0).toString());
        extrato.append("; Data: ");
        extrato.append(query.value(1).toDate().toString("dd/MM/yyyy"));
        extrato.append('\n');
    }

    return extrato;
}
