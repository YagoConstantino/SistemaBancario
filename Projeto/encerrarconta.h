#ifndef ENCERRARCONTA_H
#define ENCERRARCONTA_H

#include <QDialog>

namespace Ui {
class EncerrarConta;
}

class MenuPrincipal;
class EncerrarConta : public QDialog
{
    Q_OBJECT

public:
    explicit EncerrarConta(QWidget *parent = nullptr);
    ~EncerrarConta();

private:
    Ui::EncerrarConta *ui;
    MenuPrincipal  *MenuPrin;

private slots:
    void voltarMenu();
    void encerrarConta();
    void mostrarSenha(bool checked);

    //Funções
private:
    void closeEvent(QCloseEvent *event) override;
    int verificaDadosParaEncerramento();
};

#endif // ENCERRARCONTA_H
