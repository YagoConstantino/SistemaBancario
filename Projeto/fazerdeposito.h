#ifndef FAZERDEPOSITO_H
#define FAZERDEPOSITO_H

#include <QDialog>

namespace Ui {
class FazerDeposito;
}

class MenuPrincipal;

class FazerDeposito : public QDialog
{
    Q_OBJECT

public:
    explicit FazerDeposito(QWidget *parent = nullptr);
    ~FazerDeposito();

private slots:
    void voltarMenu();
    void confirmarSenha();

private:
    Ui::FazerDeposito *ui;
    MenuPrincipal *MenuPrin;

    //Funções
private:
    void closeEvent(QCloseEvent *event) override;
};

#endif // FAZERDEPOSITO_H
