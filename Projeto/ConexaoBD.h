#ifndef CONEXAOBD_H
#define CONEXAOBD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <limits>
#include "conta.h"

class ConexaoBD
{
private:
    QSqlDatabase _bancoDeDados;

private:
    double getSaldo(QString cpf);
    double getFaturaCredito(QString cpf);
    QString getSenha(QString cpf);
    QString getNomeMae(QString cpf);

    const bool setSaldo(QString cpf, double novoSaldo);
    const bool setfaturaCredito(QString cpf, double novaFatura);
    const bool setSenha(QString cpf, QString novaSenha);

public:
    ConexaoBD();
    ~ConexaoBD();

    const bool fazerSaque(QString cpf, double qtdSaque);
    const bool fazerDeposito(QString cpf, double qtdDeposito);
    const bool atualizaExtrato(QString cpf, double quantia, const bool tipo);
    QString getExtrato(QString cpf);
    const bool fazerTransferencia(QString cpfEmissor, QString cpfReceptor, double qtdTransf);
    const bool pagarFaturaCredito(QString cpf, double qtdPagamento);
    const bool encerrarConta(QString cpf);
    const bool confirmarSenha(QString cpf, QString senhaDigitada);
    const int trocarSenha(QString cpf, QString nomeMae, QString senhaNova);
    const int verificaContaExistente(QString cpf, QString senhaDigitada);
    const bool recuperaDadosConta(QString cpf);
    const bool cadastraConta();
};

#endif // CONEXAOBD_H
