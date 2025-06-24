#ifndef CONEXAOBD_H
#define CONEXAOBD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <cstring>
#include <cstdlib>
#include <limits>
#include "conta.h"

class ConexaoBD
{
private:
    QSqlDatabase _bancoDeDados;

    // Criptografia
    static constexpr uint32_t delta = 0x9E3779B9;
    static constexpr uint32_t chave[4] = {0x7F8932AC, 0xAB547ED2, 0x6934BC20, 0xFF39A2D1};

private:
    static uint64_t criptografarTEA(uint64_t dado);
    static uint64_t descriptografarTEA(uint64_t dado);

    uint64_t toUint64(int num);
    uint64_t toUint64(double num);
    uint64_t toUint64(QString str);

    int toInt(uint64_t num);
    double toDouble(uint64_t num);
    QString toQString(uint64_t num);

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
    const bool atualizarCredito(QString cpf, int novoCredito);
};

#endif // CONEXAOBD_H
