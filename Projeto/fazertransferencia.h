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

private slots:
    void voltarMenu();

    //Funções
private:
    void closeEvent(QCloseEvent *event) override;
};

#endif // FAZERTRANSFERENCIA_H
