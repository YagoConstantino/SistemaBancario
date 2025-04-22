#ifndef VERFATURACREDITO_H
#define VERFATURACREDITO_H

#include <QDialog>

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

private slots:
    void voltarMenu();
    void pagarFatura();

    //Funções
private:
    void closeEvent(QCloseEvent *event) override;
};

#endif // VERFATURACREDITO_H
