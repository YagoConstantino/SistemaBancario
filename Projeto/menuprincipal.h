#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QDialog>
#include "fazerdeposito.h"
#include "fazersaque.h"
#include "fazertransferencia.h"
#include "verfaturacredito.h"
#include "verextrato.h"
#include "encerrarconta.h"

namespace Ui { class MenuPrincipal; }
class MainWindow;

class MenuPrincipal : public QDialog
{
    Q_OBJECT

public:
    explicit MenuPrincipal(QWidget *parent = nullptr);
    ~MenuPrincipal();

private slots:
    void voltarLogin();
    void JanelaDeposito();
    void JanelaSaque();
    void JanelaTransf();
    void JanelaFatCred();
    void JanelaVerExtrato();
    void JanelaEncerrarConta();

//Funções
private:
    void closeEvent(QCloseEvent *event) override;
    void ConectaBotoesFuncoes();

private:
    Ui::MenuPrincipal *ui;
    MainWindow *Login;
    FazerDeposito *Dep;
    FazerSaque    *Saq;
    FazerTransferencia *Transf;
    VerFaturaCredito   *FatCred;
    VerExtrato         *VerExtra;
    EncerrarConta      *EnceCont;
};

#endif // MENUPRINCIPAL_H
