#include "conta.h"
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "ConexaoBD.h"

Conta* Conta::instancia = nullptr;

Conta* Conta::getInstancia() {
    if (instancia == nullptr)
        instancia = new Conta();

    return instancia;
}

Conta::Conta()
:
    nome(),
    nomeMae(),
    senha(),
    CPF(),
    email(),
    extrato(),
    dataNascimento(),
    faturaCredito(0.f),
    creditoDisponivel(0.f),
    creditoTotal(0.f),
    saldo(0.f),
    idade(0),
    deveMudarExtrato(true),
    conexaoBD(nullptr)
{
    conexaoBD = new ConexaoBD();
}

Conta::~Conta()
{
    if(conexaoBD != nullptr){
        delete conexaoBD;
        conexaoBD = nullptr;
    }
}

// Útil para troca de contas
void Conta::resetar()
{
    nome.clear();
    nomeMae.clear();
    senha.clear();
    CPF.clear();
    email.clear();
    extrato.clear();
    dataNascimento.setDate(0,0,0);
    faturaCredito = 0.f;
    creditoDisponivel = 0.f;
    creditoTotal = 0.f;
    saldo = 0.f;
    idade = 0.f;
    deveMudarExtrato = true;
}

bool Conta::fazerSaque(double qtdSaque)
{
    if(qtdSaque > saldo) return false;
    if(qtdSaque < 0) return false;
    //Atualiza localmente
    saldo -= qtdSaque;

    deveMudarExtrato = true;
    return conexaoBD->fazerSaque(CPF, qtdSaque);
}

bool Conta::fazerDeposito(double qtdDeposito)
{
    if(qtdDeposito < 0) return false;
    //Atualiza localmente
    saldo += qtdDeposito;

    deveMudarExtrato = true;
    return conexaoBD->fazerDeposito(CPF, qtdDeposito);
}

bool Conta::fazerTransf(double qtdTransf, QString cpfReceptor)
{
    saldo -= qtdTransf;

    deveMudarExtrato = true;
    return conexaoBD->fazerTransferencia(CPF, cpfReceptor, qtdTransf);
}

bool Conta::encerrarConta()
{
    //verificar se o saldo é = 0   //verificar se a fatura é = 0
    if(saldo!= 0 || faturaCredito != 0)
    {
        qDebug() << "Erro Para encerrar sua conta deve sacar todo seu saldo não ter uma fatura pendente";
        return false;
    }

    return conexaoBD->encerrarConta(CPF);
}

bool Conta::confirmarSenha(QString cpf, QString senhaDigitada)
{
    return conexaoBD->confirmarSenha(CPF, senhaDigitada);
}

bool Conta::trocarSenha(QString cpf, QString nomeMamae, QString senha,QWidget *janela)
{
    int resultado = conexaoBD->trocarSenha(CPF, nomeMamae, senha);

    if (resultado == 0)
    {
        qDebug() << "Erro ao executar mudarSenha EsqueceuSenha:";

        QMessageBox::warning(janela,"Erro","Erro ao acessar banco de dados");

        return false;
    }

    cpf.remove('.').remove('-');

    if (CPF != cpf) {
        qDebug() << "Nenhum registro encontrado para CPF EsqueceuSenha: " << cpf;
        QMessageBox::warning(janela,"Erro","Dados não batem, não houve troca de senha");
        return false;
    }

    if(resultado == -1)
    {
        qDebug() << "Nome da mae não bate com o registrado no BD";
        QMessageBox::warning(janela,"Erro","Dados não batem, não houve troca de senha");
        return false;
    }

    setSenha(senha);
    return true;
}

bool Conta::verificaContaExiste(QString cpf, QString senha, QWidget *janela)
{
    cpf.remove('.').remove('-');

    int resultado = conexaoBD->verificaContaExistente(cpf, senha);

    if (resultado == -2) {
        qDebug() << "Senha incorreta para o CPF:" << cpf;
        QMessageBox::warning(janela,"Erro","Senha incorreta para o CPF ");
        return false;
    }

    return true;
}

bool Conta::recuperaDadosConta(QString cpf)
{
    return conexaoBD->recuperaDadosConta(cpf);
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
    if(deveMudarExtrato)
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

void Conta::setCreditoTotal(int novoCredTotal)
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

const int Conta::getIdade() const
{
    return idade;
}

void Conta::setFaturaCred(double novaFatCred)
{
    faturaCredito = novaFatCred;
}

const double Conta::getFaturaCred() const
{
    return faturaCredito;
}

bool Conta::CadastraContaBD()
{
    setSaldo(0.0);
    creditoDisponivel = 0.0;
    creditoTotal = 0.0;
    faturaCredito = 0.0;
    extrato = "";

    return conexaoBD->cadastraConta();
}

bool Conta::pagarFaturaCredito(double qtdPagamento){
    saldo -= qtdPagamento;
    faturaCredito -= qtdPagamento;

    deveMudarExtrato = true;
    return conexaoBD->pagarFaturaCredito(CPF, qtdPagamento);
}

void Conta::atualizaExtratoLocal(){
    // Apaga o extrato desatualizado
    extrato.clear();

    extrato = conexaoBD->getExtrato(CPF);

    deveMudarExtrato = false;
}

const bool Conta::atualizaCreditoBD(int novoCredito)
{
    if(!conexaoBD->atualizarCredito(CPF, novoCredito)) return false;

    setCreditoTotal(novoCredito);

    return true;
}
void tratarCPF(QString &cpf)
{
    int i;
    QString CPFTratado;
    for(i=0;i<cpf.length();i++)
    {
        if(cpf[i] != '.' && cpf[i] != '-')
            CPFTratado += cpf[i];
    }
    cpf = CPFTratado;
}
