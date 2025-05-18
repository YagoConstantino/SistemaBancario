#ifndef CONTA_H
#define CONTA_H
#include <QString>
#include <QDate>
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QFileInfo>
#include <QSqlError>

class Conta
{
public:
    Conta();
    ~Conta();

    //Nao foram implementadas, se relacionam com o banco de dados e devem atualizar dados da conta local
    bool fazerSaque(double qtdSaque);
    bool fazerDeposito(double qtdDeposito);
    bool fazerTransf(double qtdTransf,QString cpfReceptor);
    bool encerrarConta();
    //////////////////////////////////////////////////////////////////

    void setNome(QString novoNome);
    const QString getNome()const ;

    void setNomeMae(QString novoNomeMae);
    const QString getNomeMae()const;

    void setSenha(QString novaSenha);
    const QString getSenha()const ;

    void setCPF(QString novoCPF);
    const QString getCPF()const ;

    void setEmail(QString novoEmail);
    const QString getEmail()const;

    void setDataNascimeto(QDate novoNascimento);
    const QDate getNascimento() const ;

    void setSaldo(double novoSaldo);
    const double getSaldo()const;

    void setCreditoTotal(double novoCredTotal);
    const double getCredTotal()const;

    const double getCredDisponivel()const;

    void setFaturaCred(double novaFatCred);
    double const getFaturaCred()const;

    QSqlDatabase const getDataBase()const;

    double getSaldo();
    double getFaturaCred();
    const QString getExtrato();
    void atualizaExtratoLocal();

    bool CadastraContaBD();
    bool pagarFaturaCredito(double qtdPagamento);

    //Não sei se precisa de mais setters e getters, saldo, creditos , faturas e extratos serão alterados e recuperados
    // em outras funções


private:
    QString nome;
    QString nomeMae;
    QString senha;
    QString CPF;
    QString email;
    QString extrato;
    QDate dataNascimento;

    double faturaCredito;
    double saldo;
    double creditoTotal;
    double creditoDisponivel;

    bool deveMudarExtrato;

    QSqlDatabase bancoDeDados;

};

#endif // CONTA_H
