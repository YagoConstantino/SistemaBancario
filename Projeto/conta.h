#ifndef CONTA_H
#define CONTA_H
#include <QString>
#include <QDate>

class Conta
{
public:
    Conta();
    ~Conta();

    double getSaldo();
    double getFaturaCred();
    QString getExtrato();

    //Nao foram implementadas, se relacionam com o banco de dados e devem atualizar dados da conta local
    bool fazerDeposito();
    bool fazerSaque(double qtdSaque);
    bool fazerDepostido(double qtdDeposito);
    bool fazerTransf(double qtdTransf,QString cpfReceptor);
    bool pagarFaturaCredito(double qtdPagamento);
    bool encerrarConta();
    //////////////////////////////////////////////////////////////////

    void setNome(QString novoNome);
    const QString getNome()const ;

    void setNomeMae(QString novoNomeMae);
    const QString getNomeMae()const;

    void setSenha(QString novaSenha);
    const QString getSenha()const ;

    void setEmail(QString novoEmail);
    const QString getEmail()const;

    const QDate getNascimento() const ;

    const QString getCPF()const ;

    const double getCredTotal()const;
    const double getCredDisponivel()const;

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

};

#endif // CONTA_H
