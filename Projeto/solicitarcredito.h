#ifndef SOLICITARCREDITO_H
#define SOLICITARCREDITO_H

#include <QDialog>
#include <QMessageBox>
#include "conta.h"
#include "confirmarsenha.h"

namespace Ui {
class SolicitarCredito;
}

class MenuPrincipal;

class SolicitarCredito : public QDialog
{
    Q_OBJECT

public:
    explicit SolicitarCredito(QWidget *parent = nullptr);
    ~SolicitarCredito();

private slots:
    void voltar();
    void confirmar();

private:
    MenuPrincipal* menuPrincipal;
    Ui::SolicitarCredito *ui;

    void preencheDados();
    void conectarBotoes();
    const bool verificaEntrada();
};

#endif // SOLICITARCREDITO_H
