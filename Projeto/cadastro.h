#ifndef CADASTRO_H
#define CADASTRO_H

#include <QDialog>
#include <QString>  // para QString
#include <QDate>    // para QDate
#include "conta.h"

namespace Ui {
class Cadastro;
}

class MainWindow;
class Cadastro : public QDialog
{
    Q_OBJECT

public:
    explicit Cadastro(QWidget *parent = nullptr);
    ~Cadastro();

private:
    Ui::Cadastro *ui;
    MainWindow *Login;
    //Nome, CPF, email, data de nascimento, nome da mãe, e senha
    QString _nome;
    QString _CPF;
    QString _email;
    QDate _nascimento;
    QString _nomeMae;
    QString _Senha;
    QString _ConfirmaSenha;
    Conta *conta;

//Funções:
private:
    int verificaCadastro();
    void closeEvent(QCloseEvent *event) override;
    bool criaConta();
    Conta* getConta();

private slots:
    void voltarLogin();
    void ConfirmarCadastro();
    void clearCaixasTexto();
};

#endif // CADASTRO_H
