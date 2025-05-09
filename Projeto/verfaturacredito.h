#ifndef VERFATURACREDITO_H
#define VERFATURACREDITO_H

#include <QDialog>
#include "conta.h"

namespace Ui {
class VerFaturaCredito;
}

class MenuPrincipal;
class VerFaturaCredito : public QDialog
{
    Q_OBJECT

public:
    explicit VerFaturaCredito(QWidget *parent = nullptr);
    ~VerFaturaCredito();

private:
    Ui::VerFaturaCredito *ui;
    MenuPrincipal *MenuPrin;
    double CredTotal;
    double CredDisponivel;
    double FaturaCred;
    double QtdPagar;

private slots:
    void voltarMenu();
    void pagarFatura();

    //Funções
private:
    void closeEvent(QCloseEvent *event) override;
    void setarDadosCredito();

};

#endif // VERFATURACREDITO_H
