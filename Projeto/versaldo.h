#ifndef VERSALDO_H
#define VERSALDO_H

#include <QDialog>
#include "Conta.h"

namespace Ui {
class VerSaldo;
}

class MenuPrincipal;
class VerSaldo : public QDialog
{
    Q_OBJECT

public:
    explicit VerSaldo(QWidget *parent = nullptr);
    ~VerSaldo();

private:
    Ui::VerSaldo *ui;
    MenuPrincipal *MenuPrin;
    QString Saldo;

private slots:
    void voltarMenu();

    //Funções
private:
    void closeEvent(QCloseEvent *event) override;
    void setarSaldoAtual();

};

#endif // VERSALDO_H
