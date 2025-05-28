#ifndef VEREXTRATO_H
#define VEREXTRATO_H

#include <QDialog>
#include "conta.h"

namespace Ui {
class VerExtrato;
}

class MenuPrincipal;
class VerExtrato : public QDialog
{
    Q_OBJECT

public:
    explicit VerExtrato(QWidget *parent = nullptr);
    ~VerExtrato();

private:
    Ui::VerExtrato *ui;
    MenuPrincipal  *MenuPrin;
    QString DadosExtrato;

private slots:
    void voltarMenu();
    void salvarPDF();

    //Funções
private:
    void closeEvent(QCloseEvent *event) override;
    void setarExtrato();

};

#endif // VEREXTRATO_H
