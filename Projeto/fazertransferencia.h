#ifndef FAZERTRANSFERENCIA_H
#define FAZERTRANSFERENCIA_H

#include <QDialog>

namespace Ui {
class FazerTransferencia;
}

class MenuPrincipal;
class FazerTransferencia : public QDialog
{
    Q_OBJECT

public:
    explicit FazerTransferencia(QWidget *parent = nullptr);
    ~FazerTransferencia();

private:
    Ui::FazerTransferencia *ui;
    MenuPrincipal *MenuPrin;
    QString DadosConta;
    double QtdTransferencia;

private slots:
    void voltarMenu();
    void confirmarSenha();

    //Funções
private:
    void closeEvent(QCloseEvent *event) override;

};

#endif // FAZERTRANSFERENCIA_H
