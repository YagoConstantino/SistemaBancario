#ifndef CONTA_H
#define CONTA_H
#include <QString>
#include <QDate>
#include <QSql>
#include <QDebug>
#include <QFileInfo>
#include <QSqlError>

class ConexaoBD;

class Conta
{
public:

    void resetar();
    bool fazerSaque(double qtdSaque);
    bool fazerDeposito(double qtdDeposito);
    bool fazerTransf(double qtdTransf,QString cpfReceptor);
    bool pagarFaturaCredito(double qtdPagamento);
    bool encerrarConta();
    bool confirmarSenha(QString cpf,QString senhaDigitada);
    bool trocarSenha(QString cpf,QString nomeMamae,QString senha,QWidget *janela);
    bool verificaContaExiste(QString cpf,QString senha,QWidget *janela);
    bool recuperaDadosConta(QString cpf);
    void atualizaExtratoLocal();
    const bool atualizaCreditoBD(int novoCredito);

    bool CadastraContaBD();

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

    void setCreditoTotal(int novoCredTotal);
    const double getCredTotal()const;

    const double getCredDisponivel()const;

    const int getIdade() const;

    void setFaturaCred(double novaFatCred);
    double const getFaturaCred()const;

    double getSaldo();
    double getFaturaCred();
    const QString getExtrato();


private:
    ConexaoBD* conexaoBD;

    QString nome;
    QString nomeMae;
    QString senha;
    QString CPF;
    QString email;
    QString extrato;
    QDate dataNascimento;

    int idade;

    double faturaCredito;
    double saldo;
    double creditoTotal;
    double creditoDisponivel;

    bool deveMudarExtrato;

// Singleton:
private:
    Conta();
    static Conta* instancia;

public:
    ~Conta();

    // Proíbe cópia e atribuição
    Conta(const Conta&) = delete;
    Conta& operator=(const Conta&) = delete;

    static Conta* getInstancia();
};

#endif // CONTA_H
